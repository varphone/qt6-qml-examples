#ifndef ROBOT_DEBUG_INFO_H
#define ROBOT_DEBUG_INFO_H

#include <QMetaType>
#include <QSharedPointer>
#include <QtGlobal>

/// 一个代表机器人调试信息的类型。
struct RobotDebugInfo
{
    /// 请求时间戳。
    qint64 requestTs;
    /// 响应时间戳。
    qint64 respondTs;
    /// 是否找到焊缝。
    bool seamFound;
    /// 焊缝时间戳。
    qint64 seamTs;
    /// 焊缝 Y 坐标。
    float seamY;
    /// 焊缝 Z 坐标。
    float seamZ;
    /// 机器人时间戳。
    qint64 robotTs;
    /// 机器人 X 坐标。
    float robotX;
    /// 机器人 Y 坐标。
    float robotY;
    /// 机器人 Z 坐标。
    float robotZ;

    Q_GADGET
    Q_PROPERTY(qint64 requestTs MEMBER requestTs)
    Q_PROPERTY(qint64 respondTs MEMBER respondTs)
    Q_PROPERTY(bool seamFound MEMBER seamFound)
    Q_PROPERTY(qint64 seamTs MEMBER seamTs)
    Q_PROPERTY(float seamY MEMBER seamY)
    Q_PROPERTY(float seamZ MEMBER seamZ)
    Q_PROPERTY(qint64 robotTs MEMBER robotTs)
    Q_PROPERTY(float robotX MEMBER robotX)
    Q_PROPERTY(float robotY MEMBER robotY)
    Q_PROPERTY(float robotZ MEMBER robotZ)
};

/// 一个代表机器人调试信息的智能指针类型。
typedef QSharedPointer<RobotDebugInfo> RobotDebugInfoPtr;

Q_DECLARE_METATYPE(RobotDebugInfo)

#endif // ROBOT_DEBUG_INFO_H
