cmake_minimum_required(VERSION 3.10)

project(qt-pwm-app)

# Enable cross-compilation if needed
if(CMAKE_CROSSCOMPILING)
    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR aarch64)
endif()

# Set up Qt6 to be found from the Buildroot toolchain
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/youssef/mydata/study/embedded_linux_kitchen/buildroot/output/host/usr/lib/cmake/Qt6)


# Enable AutoMoc for Qt Meta-Object Compiler
set(CMAKE_AUTOMOC ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

# Add Qt resources (GIF & QML)
qt_add_resources(RESOURCES resources.qrc)

# Set source files
set(SOURCES
    src/pwmController.cpp
    src/main.cpp
)

set(HEADERS
    src/pwmController.h
)

# Define the executable
add_executable(qt-pwm-app ${SOURCES} ${HEADERS} ${RESOURCES})

# Link the Qt6 libraries
target_link_libraries(qt-pwm-app Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml)

# Install the executable to /usr/bin
install(TARGETS qt-pwm-app DESTINATION /usr/bin)

# Install QML file to /usr/share/qt-pwm-app/
install(FILES main.qml DESTINATION /usr/share/qt-pwm-app/)
