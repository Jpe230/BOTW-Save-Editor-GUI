#include "headers/SaveFileEditor.hpp"

namespace BTWE{

    const char* const SaveFileEditor::VERSION[]  = {"v1.0", "v1.1", "v1.2", "v1.3", "v1.3.1", "Kiosk", "v1.3.3", "v1.3.4", "v1.4", "v1.5", "v1.5*", "v1.6", "v1.6*", "v1.6**", "v1.6***"};
    const int         SaveFileEditor::FILESIZE[] = {896976, 897160, 897112, 907824, 907824,   916576,  1020648,  1020648,  1027208,1027208,1027248, 1027216,1027216, 1027216 , 1027216};
    const int         SaveFileEditor::HEADER[]   = {0x24e2, 0x24ee, 0x2588, 0x29c0, 0x2a46,   0x2f8e,  0x3ef8,   0x3ef9,   0x471a, 0x471b, 0x471b,  0x471e, 0x0f423d,0x0f423e, 0x0f423f};

    const int SaveFileEditor::SIZEARR = 15;

  
    SaveFileEditor::SaveFileEditor(std::string fileName) : saveFile(fileName)
    {
       
        bool validity = CheckValidity();

        if(!validity) {
            std::exit(0);
        }

        LoadSaveFile();

    }

    void SaveFileEditor::LoadSaveFile()
    {
         printf("Hello 3\n");
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
                    
                    offsets[hashes[value]] = j+4;
                    headers[hashes[value]] = value;
                    startSearchOffset = j+4;

                    //There should be a break where dunno why is not working
                    //break;
                }
            }
        }
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
        v.erase(std::find(v.begin(), v.end(), '0'), v.end());

		return v;
    }

    std::string SaveFileEditor::ReadString64(int offset, int arrayIndex)
    {
        if(arrayIndex > -1)
            offset += 0x80 * arrayIndex;

        return ReadString(offset, 16);
    }

    void SaveFileEditor::InitHashes()
    {
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
    }
}

