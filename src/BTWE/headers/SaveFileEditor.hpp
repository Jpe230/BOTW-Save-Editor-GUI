#pragma once

#ifndef SAVEFILEDITOR_H
#define SAVEFILEDITOR_H

#include "File.hpp"
#include <borealis.hpp>
#include <string>
#include <map>
#include <vector>



namespace BTWE
{
    class Container;
    class ItemInput;
    class Translations;

    class SaveFileEditor
    {
        private:
            File saveFile;

            std::map<std::string, u_int64_t> offsets;
            std::map<std::string, u_int64_t> headers;

            std::map<u_int8_t, std::string>  hearts;
            std::map<u_int32_t, std::string> stamina;

            std::map<u_int64_t, std::string> hashes;

            brls::TabFrame* Root;

            /* brls::List* HomeTab;
            brls::List* WeaponTab;
            brls::List* BowTab;
            brls::List* ShieldTab;
            brls::List* ClotheTab;
            brls::List* MaterialTab;
            brls::List* FoodTab;
            brls::List* OtherTab;
            brls::List* HorseTab; */

            Container* HomeContainer;
            Container* WeaponContainer;
            Container* BowContainer;
            Container* ShieldContainer;
            Container* ClotheContainer;
            Container* MaterialContainer;
            Container* FoodContainer;
            Container* OtherContainer;
            //Container* HorseContainer;

            Translations* translations;

            std::map<std::string, ItemInput*> InputList;
            std::map<std::string, Container*> ContainerMap;

            static const char* const VERSION [];
            static const         int HEADER  [];
            static const         int FILESIZE[];
            static const   u_int64_t HashKey [];

            int currentItem;

            static const int SIZEARR;
            static const int MAX_ITEMS;
            

            std::string ReadString   (int offset, int len = 8);
            std::string ReadString64 (int offset, int arrayIndex = -1);
            std::string ReadString256(int offset);
            std::string LoadItemName (int index);
            std::string ToTime       (u_int32_t value);

            Container* GetItemContainer(std::string nameId);
            std::string GetItemTranslation(std::string itemNameId);
            int  GetItemQuantityOffset(int index);

            bool        CheckValidity();
            
            void        GetOffsets(int index);
            void        InitHashes();

            void        LoadSaveFile();
            void        Load();
            
        public:
            SaveFileEditor(std::string fileName, brls::TabFrame* root);
            void LoadHomeTab(Container* container);
            void AddNonInput(std::string label, std::string value, Container* container);
            void AddFloatInput(std::string id, std::string label, float value, Container* container);
            void AddIntInput(std::string id, std::string label, int value, int maxValue, Container* container);
            void AddSelectInput(std::string id, std::string label, std::vector<std::string> options, int selectedValue, Container* container);
            void AddItemInput(int index,Container* container);
            

    };
}

#endif