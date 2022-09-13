#include "mini_web_server/mini_web_server.h"

#include <iostream>
#include <sstream>

std::unique_ptr<MiniWebServer> MiniWebServerBuilder::Make()
{
    MiniWebServer::ConfigState config;

    config.mAddress = mAddress;
    config.mPort = mPort;
    config.mDirectoryPath = mDirectoryPath;
    config.mWasInitialized = true;

    auto res = std::make_unique<MiniWebServer>(config);
    Reset();
    return res;
}

int MiniWebServer::Run()
{
    if(!Init()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

bool MiniWebServer::Init()
{
    try { 
        mListener = std::make_unique<Listener>(mConfigState.GetAddress(), mConfigState.GetPort());
    }
    catch(std::domain_error err) {
        std::stringstream msg;
        msg << err.what();
        msg << "Error while trying to initialize MiniWebServer" << std::endl;
        throw std::domain_error(msg.str());
    }
    return true;
}

