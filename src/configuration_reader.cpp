#include "mini_web_server/configuration_reader.h"

#include <fstream>
#include <sstream>
#include <unordered_map> 
#include <functional>

void ConfigurationReader::ReadFromFile(MiniWebServerBuilder& builder, std::string path)
{
    std::ifstream file{path};

    if(file.fail()) {
        std::stringstream err_msg;
        err_msg << "Unable to open file: " << path << std::endl;
        throw std::domain_error(err_msg.str());
    }
    ReadFromStream(builder, file);
}

void ConfigurationReader::ReadFromString(MiniWebServerBuilder& builder, std::string config)
{
    std::stringstream str(config);
    ReadFromStream(builder, str);
}

/**
 * States of the reader in ConfigurationReader::ReadFromStream
 *
 * BEGIN OR IDENTIFER -> IDENTIFIER_WHITESPACE -> EQUALS -> EQUALS_WHITESPACE -> (INTEGER_VALUE
 * | STRING_VALUE) -> VALUE_WHITESPACE OR TERMINAL-> IDENTIFIER 
 */
enum class ReadingStates 
{
    IDENTIFIER,
    IDENTIFIER_WHITESPACE_EQUALS,
    EQUALS_WHITESPACE,
    INTEGER_VALUE,
    STRING_VALUE,
    VALUE_WHITESPACE
};

void ConfigurationReader::ReadFromStream(MiniWebServerBuilder& builder, std::istream& input_stream)
{
    // should read an <string> "=" <string>
    std::unordered_map<std::string, std::function<void (MiniWebServerBuilder& builder, std::string& value)>> callbacks;

    callbacks["path"] = [] (MiniWebServerBuilder& builder, std::string& value) { 
        builder.SetDirectoryPath(value);
    };
    callbacks["port"] = [] (MiniWebServerBuilder& builder, std::string& value) { 
        int val = std::stoi(value);
        if(val <= 0 || val > 65535) {
            std::stringstream err_msg;
            err_msg << "specified port value \"" << value << 
                "\" is not a valid port" << std::endl;;
            throw std::domain_error(err_msg.str());
        }
        builder.SetPort(val);
    };
    callbacks["address"] = [](MiniWebServerBuilder& builder, std::string& value) { 
        builder.SetAddress(value);
    };

    ReadingStates current_state = ReadingStates::IDENTIFIER;
    int count = 0;
    std::string value_buffer;
    std::string id_buffer;
    while(!input_stream.eof()) {
        auto c = input_stream.get();
        if(input_stream.fail()) {
            break;
        }

        // in general, only 20 white space characters consider until error
        switch(current_state) {
            case ReadingStates::IDENTIFIER:
                // max identifier length 20 
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "Identifier in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;
                if(isspace(c) || c == '=') {
                    if(!callbacks.contains(id_buffer)) {
                        std::stringstream err_msg;
                        err_msg << "Unknown Identifier: " << id_buffer << std::endl;
                        throw std::domain_error(err_msg.str());
                    }
                    current_state = ReadingStates::IDENTIFIER_WHITESPACE_EQUALS;
                    count = 0;
                    input_stream.putback(c);
                } else {
                    id_buffer.push_back(c);
                }
                break;
            case ReadingStates::IDENTIFIER_WHITESPACE_EQUALS:
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "Whitespace following identifier in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;

                if(!isspace(c) || c == '\n') {
                    if(c == '=') {
                        current_state = ReadingStates::EQUALS_WHITESPACE;
                        count = 0;
                    } else {
                        std::stringstream err_msg;
                        err_msg << "Expected: = after value and whitespace. found: \"" << c << "\"" << std::endl;
                        throw std::domain_error(err_msg.str());
                    }
                }
                break;
            case ReadingStates::EQUALS_WHITESPACE:
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "Whitespace following equals in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;
                if(!isspace(c)) {
                    if(c == '\n') {
                        std::stringstream err_msg;
                        err_msg << "Unexpected newline character found after equals" << std::endl;
                        throw std::domain_error(err_msg.str());
                    }
                    input_stream.putback(c);
                    if(c == '"') {
                        current_state = ReadingStates::STRING_VALUE;
                    } else {
                        current_state = ReadingStates::INTEGER_VALUE;
                    }
                    count = 0;
                }
                break;
            case ReadingStates::STRING_VALUE:
                // max value length 20
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "The Value in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;
                if(count == 1) continue; // remove the first quote
                if(c == '"') {
                    callbacks[id_buffer](builder, value_buffer);
                    value_buffer = "";
                    id_buffer = "";
                    current_state = ReadingStates::VALUE_WHITESPACE;
                    count = 0;
                } else {
                    value_buffer.push_back(c);
                }
                break;

            case ReadingStates::INTEGER_VALUE:
                // max value length 20
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "The Value in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;
                if(isspace(c)) {
                    callbacks[id_buffer](builder, value_buffer);
                    value_buffer = "";
                    id_buffer = "";
                    current_state = ReadingStates::VALUE_WHITESPACE;
                    count = 0;
                    input_stream.putback(c);
                } else {
                    value_buffer.push_back(c);
                }
                break;
            case ReadingStates::VALUE_WHITESPACE:
                if(count > 20) {
                    std::stringstream err_msg;
                    err_msg << "The whitespace follwoing a Value in config file is longer than 20 characters" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                count++;
                if(isspace(c)) {
                    if(c == '\n') {
                        current_state = ReadingStates::IDENTIFIER;
                        count = 0;
                    }
                } else {
                    std::stringstream err_msg;
                    err_msg << "Expected NEWLINE or whitespace, found a non whitespace character:\""<< c << "\"" << std::endl;
                    throw std::domain_error(err_msg.str());
                }
                break;
        }
    }
    if(current_state == ReadingStates::VALUE_WHITESPACE || current_state == ReadingStates::STRING_VALUE || current_state == ReadingStates::IDENTIFIER && id_buffer.size() != 0) {
        std::stringstream err_msg;
        err_msg << "Configuration Processing ended while not completing an IDENTIFIER VALUE PAIR" << std::endl;
        throw std::domain_error(err_msg.str());
    }

    if(current_state == ReadingStates::INTEGER_VALUE) {
        callbacks[id_buffer](builder, value_buffer);
    }
}
