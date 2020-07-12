#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>

#include "BTWE/BTWE.hpp"
#include <string>

int main(int argc, char* argv[])
{

    BTWE::SaveFileEditor saveEditor("resources/game_data.sav");

    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("Borealis example"))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("Borealis Example App");
    rootFrame->setIcon(BOREALIS_ASSET("icon/borealis.jpg"));


    brls::List* testList = new brls::List();

    brls::ListItem* dialogItem = new brls::ListItem("Open a dialog");
    dialogItem->getClickEvent()->subscribe([](brls::View* view) {
        brls::Dialog* dialog = new brls::Dialog("Warning: PozzNX will wipe all data on your Switch and render it inoperable, do you want to proceed?");

        brls::GenericEvent::Callback closeCallback = [dialog](brls::View* view) {
            dialog->close();
            brls::Application::notify("Running PozzNX...");
        };

        dialog->addButton("Continue", closeCallback);
        dialog->addButton("Continue", closeCallback);
        dialog->addButton("Continue", closeCallback);

        dialog->setCancelable(false);

        dialog->open();
    });

    testList->addView(dialogItem);


    rootFrame->addTab("First tab", testList);
    rootFrame->addSeparator();
    rootFrame->addTab("Third tab", new brls::Rectangle(nvgRGB(255, 0, 0)));
    rootFrame->addTab("Fourth tab", new brls::Rectangle(nvgRGB(0, 255, 0)));

    // Add the root view to the stack
    brls::Application::pushView(rootFrame);

    

    // Run the app
    while (brls::Application::mainLoop());    
    // Exit
    return EXIT_SUCCESS;
}
