cmake_minimum_required(VERSION 3.16)
project(QtCMakeDemo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Find the required Qt packages
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)

# Add header files
set(HEADERS
    include/mainwindow.h
)

# Add UI files
set(UI_FILES
    ui/mainwindow.ui
)

# Add resource files if any
set(RESOURCES
    resources/resources.qrc
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES} ${RESOURCES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# Install settings
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
) 