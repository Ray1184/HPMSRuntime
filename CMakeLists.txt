# Runtime project
cmake_minimum_required(VERSION 3.15)
project(HPMSRuntime)

set(CMAKE_SHARED_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_PREFIX)

set(HPMSENGINE_VERSION master)
set(GLM_VERSION 0.9.9.8)
set(LUA_VERSION master)
set(LUABRIDGE_VERSION 2.6)

include_directories(include)

# Third party
include(Shared.cmake)

install_from_repo(https://github.com/Ray1184/HPMSEngine.git HPMSEngine ${HPMSENGINE_VERSION} TRUE /include/)

install_from_repo(https://github.com/LuaDist/lua.git LUA ${LUA_VERSION} TRUE /src/)

# Lua configuration copy
if (NOT DEFINED DEP_PATH)
    set(DEP_PATH ${CMAKE_CURRENT_BINARY_DIR}/_deps)
endif ()
set(LUA_BUILD_PATH ${DEP_PATH}/lua-build)
set(LUA_SRC_PATH ${DEP_PATH}/lua-src/src)
configure_file(${LUA_BUILD_PATH}/luaconf.h ${LUA_SRC_PATH}/luaconf.h COPYONLY)

install_from_repo(https://github.com/vinniefalco/LuaBridge.git LUABRIDGE ${LUABRIDGE_VERSION} TRUE /Source/LuaBridge/)

include_directories(${DEP_PATH}/glfw-src/include)
include_directories(${DEP_PATH}/glm-src)
include_directories(${DEP_PATH}/physfs-src/src)
include_directories(${DEP_PATH}/pods-src/include)

add_definitions(-DSTB_IMAGE_IMPLEMENTATION -DSTB_IMAGE_STATIC -DGLM_ENABLE_EXPERIMENTAL)

set(SOURCES
        src/logic/CalcUtils.cpp
        src/logic/SectorUtils.cpp
        src/logic/LogicItemsCache.cpp
        src/logic/controllers/Collisor.cpp
        src/logic/controllers/Animator.cpp)

if (CREATE_RUNTIME_LIB)
    add_library(HPMSRuntime ${SOURCES})
else ()
    add_executable(HPMSRuntime ${SOURCES} src/HPMSRuntimeMain.cpp)
endif ()
target_link_libraries(HPMSRuntime liblua LuaBridge HPMSEngine)

# Post build
set(HPMSENGINE_DLL HPMSEngine${CMAKE_DEBUG_POSTFIX}.dll)

add_custom_command(TARGET HPMSRuntime
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${DEP_PATH}/hpmsengine-build/${HPMSENGINE_DLL} ${CMAKE_CURRENT_BINARY_DIR}/${HPMSENGINE_DLL}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
        )
if (MSYS OR MINGW)
    add_custom_command(TARGET HPMSRuntime
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/dist/libgcc_s_seh-1.dll ${CMAKE_CURRENT_BINARY_DIR}/libgcc_s_seh-1.dll
            COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/dist/libwinpthread-1.dll ${CMAKE_CURRENT_BINARY_DIR}/libwinpthread-1.dll
            COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/dist/libstdc++-6.dll ${CMAKE_CURRENT_BINARY_DIR}/libstdc++-6.dll
            )

endif ()
