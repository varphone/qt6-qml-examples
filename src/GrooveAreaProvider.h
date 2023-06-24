#ifndef GROOVE_AREA_PROVIDER_H
#define GROOVE_AREA_PROVIDER_H

#include <QList>
#include <QObject>
#include <QPointF>
#include <QSharedPointer>


struct GrooveAreaInfo;

/// 一个代表焊道面积数据提供者的类型。
class GrooveAreaProvider : public QObject {
    Q_OBJECT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit GrooveAreaProvider(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~GrooveAreaProvider() = default;

    /// 设置焊道面积数据。
    void setGrooveAreaInfo(QSharedPointer<GrooveAreaInfo> grooveAreaInfo);

signals:
    /// 当焊道面积数据发生变化时发出此信号。
    /// @param grooveAreaInfo 焊道面积数据。
    /// @note 该信号在非 UI 线程中发出。
    void grooveAreaChanged(QSharedPointer<GrooveAreaInfo> grooveAreaInfo);

private:
    /// 焊道面积数据。
    QSharedPointer<GrooveAreaInfo> mGrooveAreaInfo{nullptr};
};

#endif // GROOVE_AREA_PROVIDER_H
