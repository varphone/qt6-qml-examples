cmake_minimum_required(VERSION 3.16)

project(core LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml)

include(GNUInstallDirs)

qt_standard_project_setup()

qt_add_library(${PROJECT_NAME}
    GrooveAreaInfo.h
    GrooveAreaProvider.cpp
    GrooveAreaProvider.h
    GrooveAreaSource.cpp
    GrooveAreaSource.h
    LiveDataGenerator.cpp
    LiveDataGenerator.h
    LivePointCloud.cpp
    LivePointCloud.h
    PointCloudInfo.h
    PointCloudProvider.cpp
    PointCloudProvider.h
    PointCloudSource.cpp
    PointCloudSource.h
    RobotDebugInfo.h
    RobotDebugInfoProvider.cpp
    RobotDebugInfoProvider.h
    RobotDebugInfoTableModel.cpp
    RobotDebugInfoTableModel.h
    Utils.cpp
    Utils.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
