#ifndef GROOVE_AREA_SOURCE_H
#define GROOVE_AREA_SOURCE_H

#include <QAreaSeries>
#include <QList>
#include <QObject>
#include <QPointF>
#include <QPointer>
#include <QQmlEngine>
#include <QSharedPointer>


class LiveDataGenerator;
struct GrooveAreaInfo;
class GrooveAreaProvider;

/// 一个代表焊道面积数据源的类型。
class GrooveAreaSource : public QObject {
    Q_OBJECT
    /// 焊道面积数据提供者。
    Q_PROPERTY(GrooveAreaProvider* provider READ provider WRITE setProvider
                   NOTIFY providerChanged)
    /// 焊道面积数据序列。
    Q_PROPERTY(
        QAreaSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
    QML_ELEMENT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit GrooveAreaSource(QObject* parent = nullptr);
    /// 析构函数。
    virtual ~GrooveAreaSource();

    /// 返回焊道面积数据提供者。
    GrooveAreaProvider* provider() const;

    /// 设置焊道面积数据提供者。
    /// @param provider 焊道面积数据提供者。
    /// @note 该方法在 UI 线程中调用。
    void setProvider(GrooveAreaProvider* provider);

    /// 返回焊道面积数据序列。
    QAreaSeries* series() const;

    /// 设置焊道面积数据序列。
    /// @param series 焊道面积数据序列。
    ///
    void setSeries(QAreaSeries* series);

signals:
    /// 当焊道面积数据提供者发生变化时发出此信号。
    /// @param provider 焊道面积数据提供者。
    /// @note 该信号在 UI 线程中发出。
    void providerChanged(GrooveAreaProvider* provider);

    /// 当焊道面积数据序列发生变化时发出此信号。
    /// @param series 焊道面积数据序列。
    /// @note 该信号在 UI 线程中发出。
    void seriesChanged(QAreaSeries* series);

private slots:
    /// 当焊道面积数据发生变化时调用此方法。
    /// @param info 焊道面积数据。
    /// @note 该方法在 UI 线程中调用。
    void onGrooveAreaChanged(QSharedPointer<GrooveAreaInfo> grooveAreaInfo);

private:
    /// 焊道面积数据信息。
    QSharedPointer<GrooveAreaInfo> mGrooveAreaInfo{nullptr};
    /// 焊道面积数据提供者。
    QPointer<GrooveAreaProvider> mProvider{nullptr};
    /// 焊道面积数据序列。
    QPointer<QAreaSeries> mSeries{nullptr};
};

#endif // GROOVE_AREA_SOURCE_H
