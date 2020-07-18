#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <borealis.hpp>

namespace BTWE
{
    class ItemInput;
    class SaveFileEditor;

    class Container
    {
        private:
            brls::TabFrame* RootFrame;
            brls::List* List;
            std::map<std::string, brls::ListItem*> Items;
            std::string Title;
            std::string Icon;
            

        public:
            Container(brls::TabFrame* rootFrame, std::string title, std::string icon);
            void AddItem(brls::View* view);
            void AddInput(ItemInput* item);
            void AddInput(brls::ListItem* item, std::string id);
            void PushtoView();            
            
    };
}

#endif