#include "headers/ItemInput.hpp"


namespace BTWE
{
    ItemInput::ItemInput(std::string itemName, std::string id, u_int32_t defaultValue, int maxValue) : Id(id)
    {
        brls::ListItem* item = new brls::IntegerInputListItem(itemName, defaultValue, "", "", maxValue);
        
        item->getClickEvent()->subscribe([](brls::View* view) {
            //printf("test");
        });

        this->View = item;
    }

    ItemInput::ItemInput(std::string itemName, std::string id, float value, int decimalPlaces, int maxValue)
    {
        brls::ListItem* item = new brls::InputListItem(itemName, std::to_string(value), "", "", maxValue);

        this->View = item;
    }

    ItemInput::ItemInput(std::string itemName, std::string id, std::vector<std::string> values, unsigned int selectedValue)
    {
        brls::SelectListItem* item = new brls::SelectListItem(itemName, values, selectedValue);

        this->View = item;
    }

    ItemInput::ItemInput(std::string label, std::string value)
    {
        brls::ListItem* item = new brls::ListItem(label);
        item->setValue(value);
        this->View = item;
    }

    brls::View* ItemInput::GetView()
    {
        return this->View;
    }

    std::string ItemInput::GetID()
    {
        return this->Id;
    }
}