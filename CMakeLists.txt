# Runtime project
cmake_minimum_required(VERSION 3.15)
project(HPMSRuntime)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

include_directories(include)
include_directories(../Engine/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Engine ${CMAKE_CURRENT_BINARY_DIR}/Engine)

# Third party
include(../Shared.cmake)

install_from_repo(https://github.com/g-truc/glm.git GLM master TRUE /)

install_from_repo(https://github.com/LuaDist/lua.git LUA master TRUE /src/)

# Config luaconfig.h.in
set(LUA_CONF_PATH ${CMAKE_CURRENT_BINARY_DIR}/../_deps/lua-src/src)
configure_file(${LUA_CONF_PATH}/luaconf.h.in ${LUA_CONF_PATH}/luaconf.h)
message(STATUS "Workaround for ${LUA_CONF_PATH}/luaconf.h - done")

install_from_repo(https://github.com/vinniefalco/LuaBridge LUABRIDGE master TRUE /Source/LuaBridge/)

add_definitions(-DSTB_IMAGE_IMPLEMENTATION -DSTB_IMAGE_STATIC -DGLM_ENABLE_EXPERIMENTAL)


add_executable(HPMSRuntime src/Main.cpp)
target_link_libraries(HPMSRuntime liblua LuaBridge HPMSEngine)