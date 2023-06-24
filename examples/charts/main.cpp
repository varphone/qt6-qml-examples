// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "GrooveAreaSource.h"
#include "LivePointCloud.h"
#include "PointCloudSource.h"

#include <QApplication>
#include <QDir>
#include <QQmlEngine>
#include <QQuickView>

int main(int argc, char* argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore
    // QApplication must be used.
    QApplication app(argc, argv);

    qRegisterMetaType<QSharedPointer<GrooveAreaInfo>>(
        "QSharedPointer<GrooveAreaInfo>");
    qRegisterMetaType<QSharedPointer<PointCloudInfo>>(
        "QSharedPointer<PointCloudInfo>");
    RobotDebugInfo::registerMetaTypes();

    qmlRegisterType<GrooveAreaSource>("Examples.Extras", 1, 0,
                                      "GrooveAreaSource");
    qmlRegisterType<LivePointCloud>("Examples.Extras", 1, 0, "LivePointCloud");
    qmlRegisterType<PointCloudSource>("Examples.Extras", 1, 0,
                                      "PointCloudSource");

    QQuickView viewer;
    viewer.setMinimumSize({600, 400});

    // The following are needed to make examples run without having to install
    // the module in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(extraImportPath.arg(
        QGuiApplication::applicationDirPath(), QString::fromLatin1("qml")));
    viewer.engine()->addImportPath(":/qml");
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer,
                     &QWindow::close);

    viewer.setTitle(QStringLiteral("Qt Charts QML Example Gallery"));
    viewer.setSource(QUrl("qrc:/qml/Main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    return app.exec();
}
