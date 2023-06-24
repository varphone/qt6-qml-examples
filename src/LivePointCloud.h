#ifndef LIVE_POINT_CLOUD_H
#define LIVE_POINT_CLOUD_H

#include "GrooveAreaProvider.h"
#include "LiveDataGenerator.h"
#include "PointCloudProvider.h"
#include "RobotDebugInfoProvider.h"

#include <QList>
#include <QObject>
#include <QPointF>
#include <QPointer>
#include <QQmlEngine>
#include <QSharedPointer>

/// 一个代表实时点云数据的类型。
class LivePointCloud : public QObject {
    Q_OBJECT
    /// 点云数据输出最小间隔。
    Q_PROPERTY(int minInterval READ minInterval WRITE setMinInterval NOTIFY
                   minIntervalChanged)
    /// 实时帧率。
    Q_PROPERTY(double realtimeFps READ realtimeFps NOTIFY realtimeFpsChanged)
    /// 焊道面积数据提供者。
    Q_PROPERTY(GrooveAreaProvider* grooveAreaProvider READ grooveAreaProvider
                   NOTIFY grooveAreaChanged)
    /// 点云数据提供者。
    Q_PROPERTY(PointCloudProvider* pointCloudProvider READ pointCloudProvider
                   NOTIFY pointCloudChanged)
    /// 机器人调试信息提供者。
    Q_PROPERTY(RobotDebugInfoProvider* robotDebugInfoProvider READ
                   robotDebugInfoProvider NOTIFY robotDebugInfoChanged)
    QML_ELEMENT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit LivePointCloud(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~LivePointCloud();

    /// 返回点云数据输出最小间隔。
    /// @return 点云数据输出最小间隔。
    /// @note 该方法在 UI 线程中调用。
    int minInterval() const;

    /// 设置点云数据输出最小间隔。
    /// @param minInterval 点云数据输出最小间隔。
    /// @note 该方法在 UI 线程中调用。
    void setMinInterval(int minInterval);

    /// 返回实时帧率。
    double realtimeFps(void) const;

    /// 设置实时帧率。
    /// @param realtimeFps 实时帧率。
    /// @note 该方法在 UI 线程中调用。
    void setRealtimeFps(double realtimeFps);

    /// 返回焊道面积数据提供者。
    /// @return 焊道面积数据提供者。
    /// @note 该方法在 UI 线程中调用。
    GrooveAreaProvider* grooveAreaProvider() const;

    /// 返回点云数据提供者。
    /// @return 点云数据提供者。
    /// @note 该方法在 UI 线程中调用。
    PointCloudProvider* pointCloudProvider() const;

    /// 返回机器人调试信息提供者。
    /// @return 机器人调试信息提供者。
    /// @note 该方法在 UI 线程中调用。
    RobotDebugInfoProvider* robotDebugInfoProvider() const;

public slots:

signals:
    /// 当点云数据输出最小间隔发生变化时发出此信号。
    /// @param minInterval 点云数据输出最小间隔。
    /// @note 该信号在 UI 线程中发出。
    void minIntervalChanged(int minInterval);

    /// 当实时帧率发生变化时发出此信号。
    /// @param realtimeFps 实时帧率。
    /// @note 该信号在 UI 线程中发出。
    void realtimeFpsChanged(double realtimeFps);

    /// 当焊道面积数据提供者发生变化时发出此信号。
    /// @param grooveAreaProvider 焊道面积数据提供者。
    /// @note 该信号在 UI 线程中发出。
    void grooveAreaChanged(GrooveAreaProvider* grooveAreaProvider);

    /// 当点云数据提供者发生变化时发出此信号。
    /// @param pointCloudProvider 点云数据提供者。
    /// @note 该信号在 UI 线程中发出。
    void pointCloudChanged(PointCloudProvider* pointCloudProvider);

    /// 当机器人调试信息提供者发生变化时发出此信号。
    /// @param robotDebugInfoProvider 机器人调试信息提供者。
    /// @note 该信号在 UI 线程中发出。
    void robotDebugInfoChanged(RobotDebugInfoProvider* robotDebugInfoProvider);

private:
    /// 焊道面积数据提供者。
    GrooveAreaProvider* mGrooveAreaProvider{nullptr};
    /// 点云数据提供者。
    PointCloudProvider* mPointCloudProvider{nullptr};
    /// 机器人调试信息提供者。
    RobotDebugInfoProvider* mRobotDebugInfoProvider{nullptr};
    /// 点云数据生成器。
    QPointer<LiveDataGenerator> mGenerator{nullptr};
};

#endif // LIVE_POINT_CLOUD_H
