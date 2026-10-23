cmake_minimum_required(VERSION 3.25)
project(TgBot)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SRC_BOT "${CMAKE_CURRENT_SOURCE_DIR}/src/bot")
set(SRC_CURL "${CMAKE_CURRENT_SOURCE_DIR}/src/curl")
set(EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/examples")

find_package(CURL REQUIRED)
find_package(utf8cpp REQUIRED)
find_package(nlohmann_json REQUIRED)

#// Settings for library compilation.

set(PROJ_LIB_NAME "${PROJECT_NAME}Lib")

file(GLOB_RECURSE SRC_FILES_LIB_BOT "${SRC_BOT}/*.hpp" "${SRC_BOT}/*.cpp" "${SRC_BOT}/*.inl")
file(GLOB_RECURSE SRC_FILES_LIB_CURL "${SRC_CURL}/*.hpp" "${SRC_CURL}/*.cpp" "${SRC_CURL}/*.inl")

add_library(${PROJ_LIB_NAME} STATIC ${SRC_FILES_LIB_BOT} ${SRC_FILES_LIB_CURL})

target_include_directories(${PROJ_LIB_NAME} PUBLIC ${SRC})

target_link_libraries(${PROJ_LIB_NAME} PUBLIC CURL::libcurl utf8cpp nlohmann_json::nlohmann_json)

set_target_properties(${PROJ_LIB_NAME} PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)

source_group("src\\bot" FILES ${SRC_FILES_LIB_BOT})
source_group("src\\curl" FILES ${SRC_FILES_LIB_CURL})

#// Example of use.

set(EXA_FILES "${EXAMPLES}/main.cpp")

add_executable(${PROJECT_NAME} ${EXA_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC CURL::libcurl utf8cpp nlohmann_json::nlohmann_json ${PROJ_LIB_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON)

source_group("examples" FILES ${EXA_FILES})