#include "gtest/gtest.h"

#include "mini_web_server/mini_web_server.h"

TEST(MiniWebServerBuilderTest, Constructor)
{
    MiniWebServerBuilder builder;
}

TEST(MiniWebServerBuilderTest, MakeEmpty)
{
    MiniWebServerBuilder builder;
    auto server = builder.Make();
}
