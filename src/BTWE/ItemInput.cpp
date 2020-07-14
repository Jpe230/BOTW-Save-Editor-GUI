#include "headers/ItemInput.hpp"


namespace BTWE
{
    ItemInput::ItemInput(std::string itemName, std::string id, u_int32_t defaultValue, int maxValue) : Id(id)
    {
        brls::ListItem* item = new brls::IntegerInputListItem(itemName, defaultValue, "", "", maxValue);
        
        item->getClickEvent()->subscribe([](brls::View* view) {

            printf("test");
        });
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