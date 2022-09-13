#include "mini_web_server/mini_web_server.h"

#include <iostream>

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
    return true;
}

