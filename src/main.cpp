#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>

#include "BTWE/BTWE.hpp"
#include <string>

int main(int argc, char* argv[])
{

    BTWE::SaveFileEditor* saveEditor = new BTWE::SaveFileEditor("resources/game_data.sav");

    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init("Borealis example"))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("BOTW Save Editor");
    rootFrame->setIcon(BOREALIS_ASSET("icon/borealis.jpg"));

    BTWE::Container home(saveEditor, rootFrame, "Home", "");

   /*  brls::List* testList = new brls::List();
    
    brls::IntegerInputListItem* testItem = new brls::IntegerInputListItem("Ruppees", 99, "Text");
    testItem->setThumbnail("resources/icon/borealis.jpg");


    testList->addView(testItem);


    rootFrame->addTab("First tab", testList);
    rootFrame->addSeparator();
    rootFrame->addTab("Third tab", new brls::Rectangle(nvgRGB(255, 0, 0)));
    rootFrame->addTab("Fourth tab", new brls::Rectangle(nvgRGB(0, 255, 0))); */

    // Add the root view to the stack
    brls::Application::pushView(rootFrame);

    

    // Run the app
    while (brls::Application::mainLoop());    
    // Exit
    return EXIT_SUCCESS;
}
