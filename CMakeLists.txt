cmake_minimum_required(VERSION 3.5)

project(Qt_widget_application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if we are using Emscripten
if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    # Add specific configurations for Emscripten
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=4 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
    # Set up the virtual file system
    file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
endif()

# Find Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Quick)

# List of source files for the project
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    parametricdataentry.h parametricdataentry.cpp parametricdataentry.ui
    combatinventory.h combatinventory.cpp combatinventory.ui
    minimize.h minimize.cpp
    mytooltip.h mytooltip.cpp
    markcoords.h markcoords.cpp
    borderproperty.h
    animatedqgroupbox.h
    qtexteditborder.h
    config.h
)

include_directories(${CMAKE_SOURCE_DIR})

# If you have additional headers in a specific directory, include it here
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define the executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt_widget_application
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(Qt_widget_application
        ${PROJECT_SOURCES}
    )
endif()

# Link necessary libraries
target_link_libraries(Qt_widget_application PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::WebSockets  # Add this line for WebSocket support
)

# Set properties for the target executable
set_target_properties(Qt_widget_application PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install targets
install(TARGETS Qt_widget_application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install the HTML file
install(FILES ${CMAKE_BINARY_DIR}/index.html DESTINATION ${CMAKE_INSTALL_BINDIR})

# Finalize the executable if using Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt_widget_application)
endif()
