#include "Headers/Container.hpp"
#include "Headers/ItemInput.hpp"
#include "headers/SaveFileEditor.hpp"


namespace BTWE
{
    Container::Container(brls::TabFrame* rootFrame, std::string title, std::string icon)
    {
        RootFrame = rootFrame;
        Title = title;
        Icon = icon;
        List = new brls::List();
    }

    void Container::AddItem(brls::View* view)
    {
       List->addView(view);
    }

    void Container::AddInput(brls::ListItem* item, std::string id)
    {
        Items[id] = item;
        AddItem(item);
    }

    void Container::AddInput(ItemInput* item)
    {
        AddItem(item->GetView());
    }

    void Container::PushtoView()
    {
        RootFrame->addTab(Title, List);
    }
}