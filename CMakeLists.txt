cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(yout40Ll3D VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory(
    $ENV{GEODE_SDK}
    ${CMAKE_CURRENT_BINARY_DIR}/geode
)

setup_geode_mod(${PROJECT_NAME})

# ============================================================
# COPIE DE SHREK.PNG DANS LES RESSOURCES DU MOD
# ============================================================

set(SHREK_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/shrek.png"
)

set(SHREK_DEST
    "${CMAKE_CURRENT_BINARY_DIR}/resources/shrek.png"
)

if (EXISTS "${SHREK_SOURCE}")

    file(
        COPY "${SHREK_SOURCE}"
        DESTINATION
        "${CMAKE_CURRENT_BINARY_DIR}/resources"
    )

    message(STATUS "shrek.png trouve : ${SHREK_SOURCE}")
    message(STATUS "shrek.png copie vers : ${SHREK_DEST}")

else()

    message(
        FATAL_ERROR
        "shrek.png introuvable a la racine du projet : ${SHREK_SOURCE}"
    )

endif()