cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(led-manager VERSION 1.0 LANGUAGES CXX)

include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIR})

set(SERVER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/server/server.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/server/session.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/base_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_color_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_rate_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_state_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_color_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_rate_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_state_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/command_parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/util/led.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/util/log.h
)

set(SERVER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/session.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/base_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_color_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_rate_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_state_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_color_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_rate_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_state_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/command_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/log.cpp
)

set(CLIENT_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/client/client.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/base_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_color_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_rate_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/get_led_state_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_color_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_rate_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/set_led_state_command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/command/command.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/util/log.h
)

set(CLIENT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/base_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_color_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_rate_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/get_led_state_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_color_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_rate_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command/set_led_state_command.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/log.cpp
)

add_executable(led-server tools/server.cpp ${SERVER_HEADERS} ${SERVER_SOURCES})
target_link_libraries(led-server LINK_PUBLIC ${Boost_LIBRARIES})
set_property(TARGET led-server PROPERTY CXX_STANDARD 17)

add_executable(led-client tools/client.cpp ${CLIENT_HEADERS} ${CLIENT_SOURCES})
target_link_libraries(led-client LINK_PUBLIC ${Boost_LIBRARIES})
set_property(TARGET led-client PROPERTY CXX_STANDARD 17)
