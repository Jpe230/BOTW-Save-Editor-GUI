#include "headers/SaveFileEditor.hpp"
#include "headers/Container.hpp"
#include "headers/ItemInput.hpp"
#include "headers/Translations.hpp"
#include <vector> 
#include <algorithm>


namespace BTWE{

    const char* const SaveFileEditor::VERSION[]  = {"v1.0", "v1.1", "v1.2", "v1.3", "v1.3.1", "Kiosk", "v1.3.3", "v1.3.4", "v1.4", "v1.5", "v1.5*", "v1.6", "v1.6*", "v1.6**", "v1.6***"};
    const int         SaveFileEditor::FILESIZE[] = {896976, 897160, 897112, 907824, 907824,   916576,  1020648,  1020648,  1027208,1027208,1027248, 1027216,1027216, 1027216 , 1027216};
    const int         SaveFileEditor::HEADER[]   = {0x24e2, 0x24ee, 0x2588, 0x29c0, 0x2a46,   0x2f8e,  0x3ef8,   0x3ef9,   0x471a, 0x471b, 0x471b,  0x471e, 0x0f423d,0x0f423e, 0x0f423f};
    const int         SaveFileEditor::MAX_ITEMS  = 420;
    const u_int64_t   SaveFileEditor::HashKey[]  = 
    {
        0x0bee9e46, //'MAP'
        0x0cbf052a, //'FLAGS_BOW'
        0x1e3fd294, //'FLAGSV_BOW'
        0x23149bf8, //'RUPEES'
        0x2906f327, //'MAX_HEARTS'
        0x333aa6e5, //'HORSE_SADDLES'
        0x3adff047, //'MAX_STAMINA'
        0x441b7231, //'DEFEATED_MOLDUGA_COUNTER'
        0x54679940, //'DEFEATED_HINOX_COUNTER'
        0x57ee221d, //'FLAGS_WEAPON'
        0x5f283289, //'ITEMS'
        0x6150c6be, //'HORSE_REINS'
        0x698266be, //'DEFEATED_TALUS_COUNTER'
        0x69f17e8a, //'FLAGSV_SHIELD'
        0x6a09fc59, //'ITEMS_QUANTITY'
        0x73c29681, //'PLAYTIME'
        0x7b74e117, //'HORSE_NAMES'
        0x8a94e07a, //'KOROK_SEED_COUNTER'
        0x9383490e, //'MapApp_MapIconNo'
        0x97f925c3, //'RELIC_GERUDO'
        0x982ba201, //'HORSE_POSITION'
        0x9c6cfd3f, //'HORSE_MANES'
        0xa40ba103, //'PLAYER_POSITION'
        0xa6d926bc, //'FLAGSV_WEAPON'
        0xc247b696, //'HORSE_TYPES'
        0xc5238d2b, //'FLAGS_SHIELD'
        0xc9328299, //'MOTORCYCLE'
        0xce7afed3, //'MONS'
        0xd913b769, //'MAPTYPE'
        0xe1a0ca54, //'HORSE_BONDS'
        0xea9def3f, //'MapApp_MapIconPos'
        0xf1cf4807, //'RELIC_GORON'
        0xfda0cde4 //'RELIC_RITO
    };

    const int SaveFileEditor::SIZEARR = 15;
  
    SaveFileEditor::SaveFileEditor(std::string fileName, brls::TabFrame* root) : saveFile(fileName)
    {
        Root = root;

        HomeContainer     = new Container(Root, "Home"    , "");
        WeaponContainer   = new Container(Root, "Weapon"  , "");
        BowContainer      = new Container(Root, "Bow"     , "");
        ShieldContainer   = new Container(Root, "Shield"  , "");
        ClotheContainer   = new Container(Root, "Clothe"  , "");
        MaterialContainer = new Container(Root, "Material", "");
        FoodContainer     = new Container(Root, "Food"    , "");
        OtherContainer    = new Container(Root, "Other"   , "");

        bool validity = CheckValidity();

        if(!validity) {
            std::exit(0);
        }

        translations = new Translations();

        currentItem = 0;

        Load();

    }

    void SaveFileEditor::Load()
    {
        
        HomeContainer->AddItem(new brls::Header("Statistics"));

        AddIntInput("rupees"       , "Rupees"                      , saveFile.readU32(offsets["RUPEES"])      , 6, HomeContainer);
        AddIntInput("mons"         , "Mons"                        , saveFile.readU32(offsets["MONS"])        , 6, HomeContainer);
        AddIntInput("relic-gerundo", "Gerundo Relic remaining uses", saveFile.readU32(offsets["RELIC_GERUDO"]), 2, HomeContainer);
        AddIntInput("relic-goron"  , "Goron Relic remaining uses"  , saveFile.readU32(offsets["RELIC_GORON"]) , 2, HomeContainer);
        AddIntInput("relic-rito"   , "Rito Relic remaining uses"   , saveFile.readU32(offsets["RELIC_RITO"])  , 2, HomeContainer);

        AddNonInput("Playtime", ToTime(saveFile.readU32(offsets["PLAYTIME"])), HomeContainer);

        /*Max Hearts*/
        std::map<u_int8_t, std::string>::iterator heart_It = hearts.begin();
        std::vector<std::string> heartList;

        int selectedHeart = 0;
        int secondCounter = 0;

        while (heart_It != hearts.end())
        {
            u_int8_t key = heart_It->first;
            if(key == saveFile.readU8(offsets["MAX_HEARTS"]))
               selectedHeart = secondCounter;

            std::string value = heart_It->second;
            heartList.push_back(value);

            heart_It++;
            secondCounter++;
        }
        AddSelectInput("MAX_HEARTS", "Max. Hearts", heartList, selectedHeart, HomeContainer);
        
        std::map<u_int32_t, std::string>::iterator stamina_It = stamina.begin();
        std::vector<std::string> staminaList;

        int selectedStamina = 0;
        secondCounter = 0;

        while (stamina_It != stamina.end())
        {
            u_int32_t key = stamina_It->first;
            if(key == saveFile.readU32(offsets["MAX_STAMINA"]))
               selectedHeart = secondCounter;

            std::string value = stamina_It->second;
            staminaList.push_back(value);

            stamina_It++;
            secondCounter++;
        }

        AddSelectInput("MAX_STAMINA", "Max. Stamina", staminaList, selectedStamina, HomeContainer);

        HomeContainer->AddItem(new brls::Header("Coordinates"));

        AddFloatInput("pos-x", "Current Link Coords. X", saveFile.readF32(offsets["PLAYER_POSITION"]), HomeContainer);
        AddFloatInput("pos-y", "Current Link Coords. Y", saveFile.readF32(offsets["PLAYER_POSITION"] + 8), HomeContainer);
        AddFloatInput("pos-z", "Current Link Coords. Z", saveFile.readF32(offsets["PLAYER_POSITION"] + 16), HomeContainer);

       
        HomeContainer->AddItem(new brls::Header("Completionism"));

        AddNonInput("Korok Seeds", std::to_string(saveFile.readU32(offsets["KOROK_SEED_COUNTER"])), HomeContainer);
        AddNonInput("Defeated Hinox", std::to_string(saveFile.readU32(offsets["DEFEATED_HINOX_COUNTER"])), HomeContainer);
        AddNonInput("Defeated Talus", std::to_string(saveFile.readU32(offsets["DEFEATED_TALUS_COUNTER"])), HomeContainer);
        AddNonInput("Defeated Molduga", std::to_string(saveFile.readU32(offsets["DEFEATED_MOLDUGA_COUNTER"])), HomeContainer);
       


        /*Map Select Box*/
        /*
        std::vector<std::string> mapOptions;
        for(int i = 0; i<10; i++)
        {
            for(int j = 0; j<8; j++)
            {
                std::string option = (char)(65 + 1) + "-" + std::to_string(j+1);
                mapOptions.push_back(option);
            }
        }

        for(int i = 0; i<120; i++)
        {
            std::string option  = "Dungeon";
            if(i<100)   option += "0";
            if(i<10)    option += "0";
            
            option += std::to_string(i);
        }

        mapOptions.push_back("RemainsElectric");
        mapOptions.push_back("RemainsFire"    );
        mapOptions.push_back("RemainsWater"   );
        mapOptions.push_back("RemainsWind"    );


        AddSelectInput("map", "Map", mapOptions, HomeList);
       */

        int modifiers[] = {0, 0, 0};
        int search = 0; ///0:weapons, 1:bows, 2:shields

        for(int i = 0; i < MAX_ITEMS; i++)
        {
            std::string itemNameId = LoadItemName(i);
            if(itemNameId == "") break;

            Container* container = GetItemContainer(itemNameId);
            AddItemInput(i, container);
        }

        HomeContainer->PushtoView();
        WeaponContainer->PushtoView();
        BowContainer->PushtoView();
        ShieldContainer->PushtoView();
        ClotheContainer->PushtoView();
        MaterialContainer->PushtoView();
        FoodContainer->PushtoView();
        OtherContainer->PushtoView();
    }

    Container* SaveFileEditor::GetItemContainer(std::string nameId)
    {
        //LIKE REALLY, I DONT KNOW WHAT IM DOING
        
        for (auto& trans : translations->translations["Translations"].items())
        {
            if(trans.value()["items"].contains(nameId))
            {
                std::string v = trans.value()["id"];
                return ContainerMap[v];
            }
        }

        return OtherContainer;
    }

    void SaveFileEditor::AddFloatInput(std::string id, std::string label, float value, Container* container)
    {
        ItemInput* item = new ItemInput(label, id, value, 0, 6);
        container->AddInput(item);
    }

    void SaveFileEditor::AddNonInput(std::string label, std::string value, Container* container)
    {
        ItemInput* item = new ItemInput(label, value);
        container->AddInput(item);
    }

    void SaveFileEditor::AddSelectInput(std::string id, std::string label, std::vector<std::string> options, int selectedValue, Container* container)
    {
        ItemInput* item = new ItemInput(label, id, options, selectedValue);
        container->AddInput(item);
        InputList[id] = item;
    }

    void SaveFileEditor::AddIntInput(std::string id, std::string label, int value, int maxValue, Container* container)
    {
        ItemInput* item = new ItemInput(label, id, value, maxValue);
        container->AddInput(item);
        InputList[id] = item;
    }

    void SaveFileEditor::AddItemInput(int index, Container* container)
    {
        std::string itemNameId = LoadItemName(index);
        u_int32_t itemValue = saveFile.readU32(GetItemQuantityOffset(index));

        std::string itemId = "item-number-" + std::to_string(currentItem);
        currentItem++;

        std::string label = GetItemTranslation(itemNameId);

        AddNonInput(label, std::to_string(itemValue), container);

    }

    std::string SaveFileEditor::GetItemTranslation(std::string itemNameId)
    {
        for (auto& trans : translations->translations["Translations"].items())
        {
            if(trans.value()["items"].contains(itemNameId))
            {
                std::string v = trans.value()["items"][itemNameId];
                return v;
            }
        }

        return itemNameId;
    }

    int SaveFileEditor::GetItemQuantityOffset(int index)
    {
        return offsets["ITEMS_QUANTITY"] + index * 0x08;
    }    
    bool SaveFileEditor::CheckValidity()
    {
        int versionHash = saveFile.readU32(0);
       
        for(int i = 0; i < SIZEARR; i++)
        {
            if(saveFile.fileSize == FILESIZE[i] && versionHash == HEADER[i] && saveFile.readU32(4) == 0xffffffff)
            {
                GetOffsets(i);
                return true;
            }
            else if(saveFile.fileSize >= 896976 && saveFile.fileSize <= 1500000 && versionHash == HEADER[i] && saveFile.readU32(4) == 0xffffffff)
            {
                GetOffsets(i);
                return true;
            }
        }

        return false;
    }

    std::string SaveFileEditor::ToTime(u_int32_t value)
    {
        int seconds = value%60;
        std::string seconds_string = std::to_string(seconds);

        int minutes = (int)(value / 60.0) % 60;
        std::string minutes_string = std::to_string(minutes);

        int hours = (int)(value/3600.0);
        std::string hours_string = std::to_string(hours);

        if(seconds < 10) seconds_string = '0' + seconds_string;
        if(minutes < 10) minutes_string = '0' + minutes_string;
        if(hours   < 10)   hours_string = '0' +   hours_string;
        
		return hours_string + ":" + minutes_string + ":" + seconds_string;
    }

    void SaveFileEditor::InitHashes()
    {
        ContainerMap["weapons"]   = WeaponContainer;
        ContainerMap["bows"]      = BowContainer;
        ContainerMap["shields"]   = ShieldContainer;
        ContainerMap["clothes"]   = ClotheContainer;
        ContainerMap["materials"] = MaterialContainer;
        ContainerMap["food"]      = FoodContainer;
        ContainerMap["other"]     = OtherContainer;

        hashes[(u_int64_t)0x0bee9e46] = "MAP";
        hashes[(u_int64_t)0x0cbf052a] = "FLAGS_BOW";
        hashes[(u_int64_t)0x1e3fd294] = "FLAGSV_BOW";
        hashes[(u_int64_t)0x23149bf8] = "RUPEES";
        hashes[(u_int64_t)0x2906f327] = "MAX_HEARTS";
        hashes[(u_int64_t)0x333aa6e5] = "HORSE_SADDLES";
        hashes[(u_int64_t)0x3adff047] = "MAX_STAMINA";
        hashes[(u_int64_t)0x441b7231] = "DEFEATED_MOLDUGA_COUNTER";
        hashes[(u_int64_t)0x54679940] = "DEFEATED_HINOX_COUNTER";
        hashes[(u_int64_t)0x57ee221d] = "FLAGS_WEAPON";
        hashes[(u_int64_t)0x5f283289] = "ITEMS";
        hashes[(u_int64_t)0x6150c6be] = "HORSE_REINS";
        hashes[(u_int64_t)0x698266be] = "DEFEATED_TALUS_COUNTER";
        hashes[(u_int64_t)0x69f17e8a] = "FLAGSV_SHIELD";
        hashes[(u_int64_t)0x6a09fc59] = "ITEMS_QUANTITY";
        hashes[(u_int64_t)0x73c29681] = "PLAYTIME";
        hashes[(u_int64_t)0x7b74e117] = "HORSE_NAMES";
        hashes[(u_int64_t)0x8a94e07a] = "KOROK_SEED_COUNTER";
        hashes[(u_int64_t)0x9383490e] = "MapApp_MapIconNo";
        hashes[(u_int64_t)0x97f925c3] = "RELIC_GERUDO";
        hashes[(u_int64_t)0x982ba201] = "HORSE_POSITION";
        hashes[(u_int64_t)0x9c6cfd3f] = "HORSE_MANES";
        hashes[(u_int64_t)0xa40ba103] = "PLAYER_POSITION";
        hashes[(u_int64_t)0xa6d926bc] = "FLAGSV_WEAPON";
        hashes[(u_int64_t)0xc247b696] = "HORSE_TYPES";
        hashes[(u_int64_t)0xc5238d2b] = "FLAGS_SHIELD";
        hashes[(u_int64_t)0xc9328299] = "MOTORCYCLE";
        hashes[(u_int64_t)0xce7afed3] = "MONS";
        hashes[(u_int64_t)0xd913b769] = "MAPTYPE";
        hashes[(u_int64_t)0xe1a0ca54] = "HORSE_BONDS";
        hashes[(u_int64_t)0xea9def3f] = "MapApp_MapIconPos";
        hashes[(u_int64_t)0xf1cf4807] = "RELIC_GORON";
        hashes[(u_int64_t)0xfda0cde4] = "RELIC_RITO";

        hearts[4  ] = "1 heart";
        hearts[8  ] = "2 hearts";
        hearts[12 ] = "3 hearts";
        hearts[16 ] = "4 hearts";
        hearts[20 ] = "5 hearts";
        hearts[24 ] = "6 hearts";
        hearts[28 ] = "7 hearts";
        hearts[32 ] = "8 hearts";
        hearts[36 ] = "9 hearts";
        hearts[40 ] = "10 hearts";
        hearts[44 ] = "11 hearts";
        hearts[48 ] = "12 hearts";
        hearts[52 ] = "13 hearts";
        hearts[56 ] = "14 hearts";
        hearts[60 ] = "15 hearts";
        hearts[64 ] = "16 hearts";
        hearts[68 ] = "17 hearts";
        hearts[72 ] = "18 hearts";
        hearts[76 ] = "19 hearts";
        hearts[80 ] = "20 hearts";
        hearts[84 ] = "21 hearts";
        hearts[88 ] = "22 hearts";
        hearts[92 ] = "23 hearts";
        hearts[96 ] = "24 hearts";
        hearts[100] = "25 hearts";
        hearts[104] = "26 hearts";
        hearts[108] = "27 hearts";
        hearts[112] = "28 hearts";
        hearts[116] = "29 hearts";
        hearts[120] = "30 hearts";

        stamina[1148846080] = "1 wheel";
        stamina[1150681088] = "1 wheel+1/5";
        stamina[1152319488] = "1 wheel+2/5";
        stamina[1153957888] = "1 wheel+3/5";
        stamina[1155596288] = "1 wheel+4/5";
        stamina[1157234688] = "2 wheels";
        stamina[1158250496] = "2 wheels+1/5";
        stamina[1159069696] = "2 wheels+2/5";
        stamina[1159888896] = "2 wheels+3/5";
        stamina[1160708096] = "2 wheels+4/5";
        stamina[1161527296] = "3 wheels";

    }

    void SaveFileEditor::GetOffsets(int index)
    {
        InitHashes();
        int startSearchOffset = 0x0c;

        for(int i=0; i<hashes.size(); i++)
        {
            for(int j=startSearchOffset; j<saveFile.fileSize; j+=4)
            {
                u_int64_t value = saveFile.readU32(j);

                if (hashes.find(value) == hashes.end()) {} 
                else {
                    if(HashKey[i] == value)
                    {
                        offsets[hashes[HashKey[i]]] = j+4;
                        headers[hashes[HashKey[i]]] = HashKey[i];
                        startSearchOffset = j+8;
                        break;
                    }  
                }
            }
        }
    }

    std::string SaveFileEditor::LoadItemName(int index)
    {
        return ReadString64(offsets["ITEMS"] + index * 0x80);
    }

    std::string SaveFileEditor::ReadString(int offset, int len)
    {
		std::string v = "";

        for(int i=0; i<len; i++)
        {
            v += saveFile.readString(offset,4);
            offset+=8;
        }

        //string cleanup
        v.erase(std::find(v.begin(), v.end(), '\0'), v.end());

		return v;
    }

    std::string SaveFileEditor::ReadString64(int offset, int arrayIndex)
    {
        if(arrayIndex > -1)
            offset += 0x80 * arrayIndex;

        return ReadString(offset, 16);
    }

}

