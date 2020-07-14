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

    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop());    
    // Exit
    return EXIT_SUCCESS;
}
