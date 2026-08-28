cmake_minimum_required(VERSION 3.14)
project(wordle CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(CPR_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CPR_ENABLE_SSL ON CACHE BOOL "" FORCE)

if(WIN32)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(CPR_USE_WINSSL ON CACHE BOOL "" FORCE)
    set(CURL_USE_SCHANNEL ON CACHE BOOL "" FORCE)
endif()

find_package(cpr CONFIG QUIET)
find_package(nlohmann_json CONFIG QUIET)

if(NOT TARGET cpr::cpr)
    FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.5
    )
    FetchContent_MakeAvailable(cpr)
endif()

if(NOT TARGET nlohmann_json::nlohmann_json)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(json)
endif()

add_executable(wordle
    main.cpp
    game.cpp
    evaluator.cpp
    dictionary.cpp
    display.cpp
)

target_link_libraries(wordle PRIVATE cpr::cpr nlohmann_json::nlohmann_json)

if(WIN32)
    target_link_libraries(wordle PRIVATE ws2_32 wldap32 crypt32 normaliz)
endif()

install(TARGETS wordle DESTINATION bin)
