#include "gtest/gtest.h"

#include "mini_web_server/mini_web_server.h"

TEST(MiniWebServerTest, Constructor) 
{
    MiniWebServer::ConfigState config_state;
    MiniWebServer server(config_state);
}

TEST(MiniWebServerConfigStateTest, Constructor)
{
    MiniWebServer::ConfigState config_state;
    ASSERT_EQ(config_state.GetAddress(), "");

    ASSERT_EQ(config_state.GetPort(), 0);

    ASSERT_EQ(config_state.GetDirectoryPath(), "");

    ASSERT_EQ(config_state.WasInitialized(), false);
}
