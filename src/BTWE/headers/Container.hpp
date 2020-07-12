#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <borealis.hpp>

namespace BTWE
{
    class SaveFileEditor;

    class Container
    {
        private:
            SaveFileEditor* FileEditor;
            brls::TabFrame* RootFrame;
            brls::List* List;
            std::map<std::string, brls::ListItem*> Items;
            std::string Title;
            std::string Icon;
            

        public:
            Container(SaveFileEditor* fileEditor, brls::TabFrame* rootFrame, std::string title, std::string icon);
            void AddItem(brls::View* view);
            void AddInput(brls::ListItem* item, std::string id);
            void PushtoView();            
            
    };
}

#endif