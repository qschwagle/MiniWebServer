#ifndef MINI_WEB_SERVER_CONFIGURATION_READER_H
#define MINI_WEB_SERVER_CONFIGURATION_READER_H 1

#include <string>
#include <istream>

#include "mini_web_server/mini_web_server.h"

#include <stdexcept>

/**
 * Reads a configuration file and string to build a MiniWebServer
 */
class ConfigurationReader
{
    public:
        /**
         * Reads the configuration from a file
         * \param path path to config file
         */
        void ReadFromFile(MiniWebServerBuilder& builder, std::string path);

        /**
         * Reads the configuration from a string
         * \param config configuration as a string
         */
        void ReadFromString(MiniWebServerBuilder& builder, std::string config);

        /**
         * Reads the configuration through an input stream
         * \param input_stream input_stream of characters
         */
        void ReadFromStream(MiniWebServerBuilder& builder, std::istream& input_stream);
    private:
};

#endif
