#include "Headers/Container.hpp"

#include "headers/SaveFileEditor.hpp"


namespace BTWE
{
    Container::Container(SaveFileEditor* fileEditor, brls::TabFrame* rootFrame, std::string title, std::string icon)
    {
        FileEditor = fileEditor;
        RootFrame = rootFrame;
        Title = title;
        Icon = icon;
        List = new brls::List();
       
        FileEditor->LoadHomeTab(this);
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

    void Container::PushtoView()
    {
        RootFrame->addTab(Title, List);
    }
}