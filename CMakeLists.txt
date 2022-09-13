cmake_minimum_required(VERSION 3.22)

project(mini_web_server)

SET(INCLUDE_FILES 
    include/mini_web_server/mini_web_server.h 
    include/mini_web_server/configuration_reader.h
    include/mini_web_server/connection.h
    include/mini_web_server/listener.h
)

SET(SRC_FILES 
    src/mini_web_server.cpp
    src/configuration_reader.cpp
    src/listener.cpp
    src/connection.cpp
)

SET(MAIN_FILE 
    src/main.cpp
)

SET(TEST_FILES 
    test/mini_web_server_test.cpp
    test/mini_web_server_builder_test.cpp
    test/configuration_reader_test.cpp
)

add_executable(mini_web_server ${MAIN_FILE} ${SRC_FILES} ${INCLUDE_FILES})

SET_PROPERTY(TARGET mini_web_server PROPERTY CXX_STANDARD 20)

target_include_directories(mini_web_server PUBLIC ${PROJECT_SOURCE_DIR}/include)

Include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # v1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL ""  FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(mini_web_server_test ${SRC_FILES} ${INCLUDE_FILES} ${TEST_FILES})

target_include_directories(mini_web_server_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(mini_web_server_test PUBLIC GTest::gtest_main)

SET_PROPERTY(TARGET mini_web_server_test PROPERTY CXX_STANDARD 20)

include(GoogleTest)

gtest_discover_tests(mini_web_server_test)
