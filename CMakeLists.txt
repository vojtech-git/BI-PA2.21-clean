cmake_minimum_required(VERSION 3.20)
project(CleanBomberman CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    find_package(unofficial-pdcurses CONFIG REQUIRED)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(Curses::Curses PROPERTIES
        INTERFACE_LINK_LIBRARIES unofficial::pdcurses::pdcurses
    )
    add_compile_definitions(PDC_WIDE)
else()
    set(CURSES_NEED_NCURSES TRUE)
    set(CURSES_NEED_WIDE TRUE)
    find_package(Curses REQUIRED)

    if(NOT TARGET Curses::Curses)
        add_library(Curses::Curses INTERFACE IMPORTED)
        set_target_properties(Curses::Curses PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
        )
    endif()

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

file(GLOB_RECURSE DOMAIN_SOURCES       CONFIGURE_DEPENDS "src/domain/*.cpp")
file(GLOB_RECURSE APPLICATION_SOURCES  CONFIGURE_DEPENDS "src/application/*.cpp")
file(GLOB_RECURSE INTEGRATION_SOURCES  CONFIGURE_DEPENDS "src/integration/*.cpp")
file(GLOB_RECURSE PRESENTATION_SOURCES CONFIGURE_DEPENDS "src/presentation/*.cpp")

# --- Domain Layer ---
add_library(domain STATIC ${DOMAIN_SOURCES})
target_include_directories(domain PUBLIC src)

# --- Application Layer ---
add_library(application STATIC ${APPLICATION_SOURCES})
target_include_directories(application PUBLIC src)
target_link_libraries(application PUBLIC domain)

# --- Integration Layer ---
add_library(integration STATIC ${INTEGRATION_SOURCES})
target_include_directories(integration PUBLIC src)
target_link_libraries(integration PUBLIC application)

# --- Presentation Layer ---
add_library(presentation STATIC ${PRESENTATION_SOURCES})
target_include_directories(presentation PUBLIC src)
target_link_libraries(presentation PUBLIC
    application
    Curses::Curses
)

if(WIN32)
    target_compile_definitions(presentation PUBLIC PDC_WIDE)
endif()

# --- Executable ---
add_executable(CleanBomberman src/main.cpp)
target_include_directories(CleanBomberman PRIVATE src)
target_link_libraries(CleanBomberman PRIVATE
    domain
    application
    integration
    presentation
)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/maps" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/leaderboards" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
