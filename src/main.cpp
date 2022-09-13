#include <iostream>
#include <fstream>
#include "mini_web_server/configuration_reader.h"
#include "mini_web_server/mini_web_server.h"

int main(int argc, char** argv)
{
    MiniWebServerBuilder builder;

    try {
        ConfigurationReader config_reader;
        config_reader.ReadFromFile(builder, "config.toml");
    } catch(std::domain_error err) {
        std::cerr << err.what();
        std::cerr << "Error while loading: config.toml" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    auto server = builder.Make();
}
