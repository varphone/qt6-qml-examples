#ifndef GROOVE_AREA_INFO_H
#define GROOVE_AREA_INFO_H

#include <QList>
#include <QMetaType>
#include <QPointF>
#include <QSharedPointer>


/// 一个代表焊道面积数据的类型。
struct GrooveAreaInfo
{
    /// 时间戳。
    qint64 timestamp;
    /// 焊道面积。
    qint64 area;
    /// 焊道面积多边形。
    QList<QPointF> polygon;

    Q_GADGET
    Q_PROPERTY(qint64 timestamp MEMBER timestamp)
    Q_PROPERTY(qint64 area MEMBER area)
    Q_PROPERTY(QList<QPointF> polygon MEMBER polygon)
};

/// 一个代表焊道面积数据的智能指针类型。
typedef QSharedPointer<GrooveAreaInfo> GrooveAreaInfoPtr;

#endif // GROOVE_AREA_INFO_H
