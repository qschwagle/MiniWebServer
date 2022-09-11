#include "gtest/gtest.h"

#include "mini_web_server/mini_web_server_builder.h"

TEST(MiniWebServerBuilderTest, Constructor)
{
    MiniWebServerBuilder builder;
}

TEST(MiniWebServerBuilderTest, MakeEmpty)
{
    MiniWebServerBuilder builder;
    auto server = builder.Make();

}

