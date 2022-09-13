# Mini Web Server

## Project Description

Mini Web Server lives up to its name! Its a simple, partial implementation of HTTP/1.1 to be used 
for server files from a directory. It uses a toml file for reading in the configuration and
immediately opens a port using the information provided in the toml

## Configuration File

A Toml file containing the configuration for the server.

By default, it will check the current directory for the file. If not found, it will error.

### Format

There are three fields which currently can be present in the file. If the fields are not present the
default values will be used

#### address ( default = 127.0.0.1 )

The address field is an ipv4 address which the server will use to listen for connections. If you
want to listen on every address and allow in-bound connections, listen on 0.0.0.0

##### Example

``` 
address = "0.0.0.0"
```

#### port ( default = 80 )

The port is the port which the server will for incoming connections. All ports below 1000 requires
elevated priveleges to use. Change this port to a value above 1000.

##### Example

```
port = 4000
```

#### path ( defualt = . )

The path is the root directory of the webserver. Default root will be the current directory the
application is ran from

##### Example

```
path = "/some/path"
```

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

### Class(ConfigFileReader)
- Reads in the configuration and sets it in the builder

## Todo
- [x] Setup project with src, include, and test directories
- [x] Setup cmake with compile\_commands.json
- [x] Add executable in CMakeLists.txt for mini\_web\_server
- [x] Fetch googletest to be used for unit and integration testing
- [x] Restructure CMakeLists.txt to use variables for include files, shared source files between
  executable and tests, and main file for executable mini\_web\_server
- [x] Add googletests for class MiniWebServer constructor
- [x] Create the class MiniWebServerState for holding the webserver state ( place inside
  MiniWebServer). Modify MiniWebServer to have a constructor that accepts the state object
- [x] Create the class MiniWebServerBuilder to create a MiniWebServer instance.
- [x] Add Fields to MiniWebServerConfigState ( note: State -> ConfigState )
    - ip address + port
    - serving directory
- [x] Add Setters in MiniWebServerBuilder for ip address + port and serving directory
- [x] Create Configuration File Reader class. Functions should be to both read a file and read
  from string
- [ ] Add Comments to TOML. Make TOML type checking stricter. ( NICE TO HAVE )
- [x] Have Main try to find and call ConfigFileReader with file. Crash otherwise
- [x] Add private helper Init and Run Methods to MiniWebServer. Init setups the server. 
  Run contains the main loop. Run also calls init to setup the server. The main function only needs
  (and can) call Run.
- [x] Add Listener and Connection Classes. Listener should accept the port and address. Connection
  should have Read() and Write() which both accept char\* buffers with length.
- [x] Add A Listener to MiniWebServer members and a hashmap of connections



