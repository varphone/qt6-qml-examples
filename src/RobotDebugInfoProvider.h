#ifndef ROBOT_DEBUG_INFO_PROVIDER_H
#define ROBOT_DEBUG_INFO_PROVIDER_H

#include "RobotDebugInfo.h"
#include <QList>
#include <QObject>
#include <QPointF>
#include <QSharedPointer>

/// 一个代表机器人调试信息提供者的类型。
class RobotDebugInfoProvider : public QObject {
    Q_OBJECT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit RobotDebugInfoProvider(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~RobotDebugInfoProvider() = default;

    /// 设置机器人调试信息。
    void setRobotDebugInfo(QSharedPointer<RobotDebugInfo> robotDebugInfo);

signals:
    /// 当机器人调试信息发生变化时发出此信号。
    /// @param robotDebugInfo 机器人调试信息。
    /// @note 该信号在非 UI 线程中发出。
    void robotDebugInfoChanged(QSharedPointer<RobotDebugInfo> robotDebugInfo);

private:
    /// 机器人调试信息。
    QSharedPointer<RobotDebugInfo> mRobotDebugInfo{nullptr};
};

#endif // ROBOT_DEBUG_INFO_PROVIDER_H
