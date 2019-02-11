cmake_minimum_required(VERSION 3.2)

# OVE_Core submodule
set(OVE_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OmniVerse-Engine-Core)
if(EXISTS ${OVE_CORE_DIR})

    message("Updating core module ...")
    execute_process(COMMAND git pull origin master
        WORKING_DIRECTORY ${OVE_CORE_DIR})
    message("Core module updated.")

else()

    message("Initializing core module ...")
    execute_process(COMMAND git submodule add https://github.com/VIGameStudio/OmniVerse-Engine-Core.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND git submodule update --init --recursive OmniVerse-Engine-Core
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    message("Core module initialized.")

endif()

set(OVE_CORE_BUILD_DEMO OFF CACHE BOOL "enable X functionality" FORCE)
set(OVE_CORE_BUILD_TEST OFF CACHE BOOL "enable X functionality" FORCE)
add_subdirectory(OmniVerse-Engine-Core)
set(OVE_CORE_INCLUDE_DIR ${OVE_CORE_DIR}/src PARENT_SCOPE)
