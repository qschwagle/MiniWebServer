#include "mini_web_server/mini_web_server_builder.h"

#include "mini_web_server/mini_web_server.h"

std::unique_ptr<MiniWebServer> MiniWebServerBuilder::Make()
{
    MiniWebServer::ConfigState config;
    return std::make_unique<MiniWebServer>(config);
}

