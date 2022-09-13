#include "gtest/gtest.h"

#include "mini_web_server/configuration_reader.h"

TEST(ConfigurationReaderTest, Constructor)
{
    ConfigurationReader reader;
}

TEST(ConfigurationReader, ReadFromStringPort)
{
    ConfigurationReader reader;
    MiniWebServerBuilder builder;

    std::string default_correct_config = 
    "port = 4000\n";

    reader.ReadFromString(builder, default_correct_config);

    ASSERT_EQ(builder.GetPort(), 4000);
}

TEST(ConfigurationReader, ReadFromStringAddress)
{
    ConfigurationReader reader;
    MiniWebServerBuilder builder;

    std::string default_correct_config = 
    "address = \"192.0.0.1\"\n";

    reader.ReadFromString(builder, default_correct_config);

    ASSERT_EQ(builder.GetAddress(), "192.0.0.1");
}


TEST(ConfigurationReader, ReadFromStringDirectory)
{
    ConfigurationReader reader;
    MiniWebServerBuilder builder;

    std::string default_correct_config = 
    "path = \"/root/something\"\n";

    reader.ReadFromString(builder, default_correct_config);

    ASSERT_EQ(builder.GetDirectoryPath(), "/root/something");
}

TEST(ConfigurationReader, ReadFromStringComplete)
{
    ConfigurationReader reader;
    MiniWebServerBuilder builder;

    std::string default_correct_config = 
    "address = \"10.20.20.1\"\n"
    "port = 5432\n"
    "path = \"helloworld\"\n";

    reader.ReadFromString(builder, default_correct_config);

    ASSERT_EQ(builder.GetDirectoryPath(), "helloworld");
    ASSERT_EQ(builder.GetAddress(), "10.20.20.1");
    ASSERT_EQ(builder.GetPort(), 5432);
}

