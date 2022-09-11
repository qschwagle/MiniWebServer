#include "mini_web_server/mini_web_server.h"

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

