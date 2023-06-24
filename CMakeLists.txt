cmake_minimum_required(VERSION 3.18)

cmake_policy(SET CMP0091 NEW)

project(qt6-qml-examples
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_VERBOSE_MAKEFILE ON)

# list(APPEND QML_DIRS
#     "${CMAKE_BINARY_DIR}/qml"
#     "${CMAKE_BINARY_DIR}/qml/Fv"
#     "${CMAKE_BINARY_DIR}/qml/Fv/App"
#     "${CMAKE_BINARY_DIR}/qml/Fv/Components"
#     "${CMAKE_BINARY_DIR}/qml/Fv/Theme"
# )

# set(QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/qml" CACHE STRING "" FORCE)

include(GNUInstallDirs)

# find_package(Qt6 6.4 CONFIG REQUIRED
#      COMPONENTS
#         # Core components
#         Core
#         Gui
#         # Extra components
#         Svg
#         # Qml components
#         Qml
#         QmlCore
#         Quick
#         QuickControls2
#         # QuickControls2BasicStyle
#         QuickDialogs2
#         QuickDialogs2QuickImpl
#         QuickDialogs2Utils
#         QuickWidgets
#         # Qml extra components
#         ChartsQml
#         DataVisualizationQml
#         VirtualKeyboard
# )

# find_package(toml11 CONFIG REQUIRED)

# find_path(RAPIDCSV_INCLUDE_DIRS "rapidcsv.h")

# add_subdirectory(qml)
add_subdirectory(src)
add_subdirectory(examples)

# # 安装目标文件
# install(TARGETS ${PROJECT_NAME})

# # 调试运行配置
# if(WIN32)
#     add_custom_command(TARGET ${PROJECT_NAME}
#         POST_BUILD
#             COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix ${CMAKE_BINARY_DIR}
#     )
# endif()
