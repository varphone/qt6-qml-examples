#ifndef POINT_CLOUD_INFO_H
#define POINT_CLOUD_INFO_H

#include <QMetaType>
#include <QSharedPointer>
#include <QVector>
#include <QPointF>


/// 一个代表点云数据信息的类型。
struct PointCloudInfo
{
    /// 时间戳。
    qint64 timestamp;
    /// 点云数据。
    QVector<QPointF> points;

    Q_GADGET
    Q_PROPERTY(qint64 timestamp MEMBER timestamp)
    Q_PROPERTY(QVector<QPointF> points MEMBER points)
};

/// 一个代表点云数据信息的智能指针类型。
typedef QSharedPointer<PointCloudInfo> PointCloudInfoPtr;

Q_DECLARE_METATYPE(PointCloudInfo)

#endif // POINT_CLOUD_INFO_H
