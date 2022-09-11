#include "gtest/gtest.h"

#include "mini_web_server/mini_web_server.h"

TEST(MiniWebServer, Constructor) 
{
    MiniWebServer::ConfigState config_state;
    MiniWebServer server(config_state);
}
