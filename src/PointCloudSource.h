#ifndef POINT_CLOUD_SOURCE_H
#define POINT_CLOUD_SOURCE_H

#include <QXYSeries>
#include <QList>
#include <QObject>
#include <QPointF>
#include <QPointer>
#include <QQmlEngine>
#include <QSharedPointer>


class LiveDataGenerator;
struct PointCloudInfo;
class PointCloudProvider;

/// 一个代表点云数据源的类型。
class PointCloudSource : public QObject {
    Q_OBJECT
    /// 点云数据提供者。
    Q_PROPERTY(PointCloudProvider* provider READ provider WRITE setProvider
                   NOTIFY providerChanged)
    /// 点云数据序列。
    Q_PROPERTY(
        QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
    QML_ELEMENT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit PointCloudSource(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~PointCloudSource();

    /// 返回点云数据提供者。
    PointCloudProvider* provider() const;

    /// 设置点云数据提供者。
    /// @param provider 点云数据提供者。
    /// @note 该方法在 UI 线程中调用。
    void setProvider(PointCloudProvider* provider);

    /// 返回点云数据序列。
    QXYSeries* series() const;

    /// 设置点云数据序列。
    /// @param series 点云数据序列。
    ///
    void setSeries(QXYSeries* series);

signals:
    /// 当点云数据提供者发生变化时发出此信号。
    /// @param provider 点云数据提供者。
    /// @note 该信号在 UI 线程中发出。
    void providerChanged(PointCloudProvider* provider);

    /// 当点云数据序列发生变化时发出此信号。
    /// @param series 点云数据序列。
    /// @note 该信号在 UI 线程中发出。
    void seriesChanged(QXYSeries* series);

private slots:
    /// 当点云数据发生变化时调用此方法。
    /// @param info 点云数据。
    /// @note 该方法在 UI 线程中调用。
    void onPointCloudChanged(QSharedPointer<PointCloudInfo> PointCloudInfo);

private:
    /// 点云数据信息。
    QSharedPointer<PointCloudInfo> mPointCloudInfo{nullptr};
    /// 点云数据提供者。
    QPointer<PointCloudProvider> mProvider{nullptr};
    /// 点云数据序列。
    QPointer<QXYSeries> mSeries{nullptr};
};

#endif // POINT_CLOUD_SOURCE_H
