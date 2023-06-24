#ifndef POINT_CLOUD_PROVIDER_H
#define POINT_CLOUD_PROVIDER_H

#include <QList>
#include <QObject>
#include <QPointF>
#include <QSharedPointer>

struct PointCloudInfo;

/// 一个代表点云数据提供者的类型。
class PointCloudProvider : public QObject {
    Q_OBJECT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit PointCloudProvider(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~PointCloudProvider() = default;

    /// 设置点云数据信息。
    void setPointCloudInfo(QSharedPointer<PointCloudInfo> pointCloudInfo);

signals:
    /// 当点云数据发生变化时发出此信号。
    /// @param pointCloudInfo 点云数据。
    /// @note 该信号在非 UI 线程中发出。
    void pointCloudChanged(QSharedPointer<PointCloudInfo> pointCloudInfo);

private:
    /// 点云数据信息。
    QSharedPointer<PointCloudInfo> mPointCloudInfo{nullptr};
};

#endif // POINT_CLOUD_PROVIDER_H
