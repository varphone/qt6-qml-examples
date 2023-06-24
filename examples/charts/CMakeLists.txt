cmake_minimum_required(VERSION 3.16)

project(charts LANGUAGES CXX)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/charts")

find_package(Qt6 REQUIRED COMPONENTS Charts Core Gui Qml Quick QuickControls2)

include(GNUInstallDirs)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    main.cpp
    # GrooveAreaInfo.h
    # GrooveAreaProvider.cpp
    # GrooveAreaProvider.h
    # GrooveAreaSource.cpp
    # GrooveAreaSource.h
    # LiveDataGenerator.cpp
    # LiveDataGenerator.h
    # LivePointCloud.cpp
    # LivePointCloud.h
    # PointCloudInfo.h
    # PointCloudProvider.cpp
    # PointCloudProvider.h
    # PointCloudSource.cpp
    # PointCloudSource.h
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
    core
)

# Resources:
set(resources_resource_files
    "qml/AreaSeries.qml"
    "qml/AreaSeriesDynamic.qml"
    "qml/BadgeLabel.qml"
    "qml/BarSeries.qml"
    "qml/BarSeriesHorizontal.qml"
    "qml/BarSeriesPercent.qml"
    "qml/BarSeriesPercentHorizontal.qml"
    "qml/BarSeriesStacked.qml"
    "qml/BarSeriesStackedHorizontal.qml"
    "qml/BoxPlotSeries.qml"
    "qml/CandlestickSeries.qml"
    "qml/CategoryAxis.qml"
    "qml/CategoryAxisPolar.qml"
    "qml/DateTimeAxis.qml"
    "qml/DateTimeAxisPolar.qml"
    "qml/Donut.qml"
    "qml/LineSeries.qml"
    "qml/Main.qml"
    "qml/PieChart.qml"
    "qml/SplineSeries.qml"
    "qml/ScatterSeries.qml"
    "qml/TwoSeries.qml"
    "qml/TwoSeriesPolar.qml"
    "qml/WheelOfFortune.qml"
    "qml/customlegend/AnimatedAreaSeries.qml"
    "qml/customlegend/ChartViewHighlighted.qml"
    "qml/customlegend/ChartViewSelector.qml"
    "qml/customlegend/ChartViewStacked.qml"
    "qml/customlegend/CustomLegend.qml"
    "qml/customlegend/Main.qml"
    "qml/f1legends/F1Legends.qml"
    "qml/f1legends/SpeedsList.qml"
)

qt6_add_resources(${PROJECT_NAME} "charts"
    PREFIX
        "/"
    FILES
        ${resources_resource_files}
)

# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND "${CMAKE_COMMAND}" -E
#         copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/qml/f1legends/hamilton.png"
#         "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
# )

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
