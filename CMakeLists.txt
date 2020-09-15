# Runtime project
cmake_minimum_required(VERSION 3.15)
project(HPMSRuntime)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

include_directories(include)

# Third party
include(Shared.cmake)

install_from_repo(https://github.com/Ray1184/HPMSEngine.git HPMSEngine master TRUE /include/)

install_from_repo(https://github.com/g-truc/glm.git GLM master TRUE /)

install_from_repo(https://github.com/LuaDist/lua.git LUA master TRUE /src/)

install_from_repo(https://github.com/vinniefalco/LuaBridge LUABRIDGE master TRUE /Source/LuaBridge/)

add_definitions(-DSTB_IMAGE_IMPLEMENTATION -DSTB_IMAGE_STATIC -DGLM_ENABLE_EXPERIMENTAL)


add_executable(HPMSRuntime src/Main.cpp)
target_link_libraries(HPMSRuntime liblua LuaBridge HPMSEngine)