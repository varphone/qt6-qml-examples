cmake_minimum_required(VERSION 3.16)

project(tableview LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick QuickControls2 QuickDialogs2 LabsQmlModels)

include(GNUInstallDirs)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    # WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Charts
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::QuickDialogs2
    Qt::LabsQmlModels
    core
)

# Resources:
set(resources_resource_files
    "qml/Main.qml"
    "qml/RobotDebugInfoPage.qml"
)

qt6_add_resources(${PROJECT_NAME} "tableview"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

qt_add_resources(${PROJECT_NAME} fonts
    PREFIX /
    BASE ${CMAKE_CURRENT_SOURCE_DIR}/../../assets
    BIG_RESOURCES
    FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../assets/fonts/Font Awesome 6 Free-Solid-900.otf"
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
