# Mini Web Server

## Project Description
Mini Web Server lives up to its name! Its a simple, partial implementation of HTTP/1.1 to be used 
for server files from a directory. It uses a toml file for reading in the configuration and
immediately opens a port using the information provided in the toml

## Architecture

### Class(MiniWebServer)

- Main program class / object
- This object is created through a builder which then returns this object
- The main function will then start the object and all execution flow will occur through the
  MiniWebserver.

### Class(MiniWebServerState)
- Holds the state for the webserver

### Class(MiniWebServerBuilder)
- Builds an Instance of the Webserver 

## Todo
- [x] Setup project with src, include, and test directories
- [x] Setup cmake with compile\_commands.json
- [x] Add executable in CMakeLists.txt for mini\_web\_server
- [x] Fetch googletest to be used for unit and integration testing
- [x] Restructure CMakeLists.txt to use variables for include files, shared source files between
  executable and tests, and main file for executable mini\_web\_server
- [x] Add googletests for class MiniWebServer constructor
- [ ] Create the class MiniWebServerState for holding the webserver state ( place inside
  MiniWebServer). Modify MiniWebServer to have a constructor that accepts the state object
- [ ] Create the class MiniWebServerBuilder to create a MiniWebServer instance.



