#pragma once
#ifndef ITEMINPUT_H
#define ITEMINPUT_H

#include <string>
#include <borealis.hpp>

namespace BTWE
{
    class SaveFileEditor;

    enum TypeInput
    {
        WEAPON,
        BOW,
        SHIELD,
        ARROW,
        CLOTH,
        MATERIAL,
        FOOD,
        OTHER,
        HORSE
    };

    class ItemInput
    {
        private:
            u_int32_t   Value;
            u_int32_t   Modifier;
            u_int32_t   ModifierValue;
            u_int32_t   Durability;

            std::string ItemName;

            std::string Id;

            brls::View* View;

        public:
            /*Contructor for Integer Input Box*/
            ItemInput(std::string itemName, std::string id, u_int32_t defaultValue, int maxValue);

            /*Constructor for Float Input Box*/
            ItemInput(std::string itemName, std::string id, float value, int decimalPlaces, int maxValue);

            /*Constructor for Select List Item*/
            ItemInput(std::string itemName, std::string id, std::vector<std::string> values, unsigned int selectedValue);

            /*Constructor for Item*/
            ItemInput(std::string itemname, std::string id, u_int32_t defaultValue);

            /*Constructor for Weapon, Bow and Shield*/
            //ItemInput(std::string itemName, std::string id, u_int32_t durability, u_int32_t modifier, u_int32_t modifierValue, TypeInput type);

            /*Constructor for Arrows, Materials, Food and Other*/
            //ItemInput(std::string itemName, std::string id, u_int32_t quantity, TypeInput type);

            /*Constructor for Clothes*/
            //ItemInput(std::string itemName, std::string id, u_int32_t color);

            /*Constructor for Non-Interactive Obj*/
            ItemInput(std::string label, std::string value);

            u_int32_t GetValue();
            u_int32_t GetModifier();
            u_int32_t GetModifierValue();
            u_int32_t GetDurability();

            std::string GetLabel(std::string itemName);
            std::string GetName();
            std::string GetID();

            brls::View* GetView();

            
    };
}

#endif