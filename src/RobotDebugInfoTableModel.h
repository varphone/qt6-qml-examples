#ifndef ROBOT_DEBUG_INFO_TABLE_MODEL_H
#define ROBOT_DEBUG_INFO_TABLE_MODEL_H

#include "RobotDebugInfo.h"

#include <QAbstractTableModel>
#include <QPointer>
#include <QQmlEngine>
#include <QUrl>

class RobotDebugInfoProvider;

/// 一个代表机器人调试信息表格模型的类型。
class RobotDebugInfoTableModel : public QAbstractTableModel {
    Q_OBJECT
    /// 最大行数。
    Q_PROPERTY(
        int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged)
    /// 是否冻结。
    Q_PROPERTY(bool freezed READ freezed WRITE setFreezed NOTIFY freezedChanged)
    /// 机器人调试信息提供者。
    Q_PROPERTY(RobotDebugInfoProvider* provider READ provider WRITE setProvider
                   NOTIFY providerChanged)
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:
    /// 构造函数。
    explicit RobotDebugInfoTableModel(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~RobotDebugInfoTableModel();

    /// 返回最大行数。
    int rowCount(const QModelIndex& = QModelIndex()) const override;

    /// 返回列数。
    int columnCount(const QModelIndex& = QModelIndex()) const override;

    /// 返回指定索引的数据。
    QVariant data(const QModelIndex& index, int role) const override;

    /// 返回表头数据。
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /// 返回角色名称列表。
    QHash<int, QByteArray> roleNames() const override;

    /// 返回最大容量。
    int capacity() const;

    /// 设置最大容量。
    /// @param capacity 最大容量。
    /// @note 该方法在 UI 线程中调用。
    void setCapacity(int capacity);

    /// 返回是否冻结。
    bool freezed() const;

    /// 设置是否冻结。
    /// @param freezed 是否冻结。
    /// @note 该方法在 UI 线程中调用。
    void setFreezed(bool freezed);

    /// 返回机器人调试信息提供者。
    RobotDebugInfoProvider* provider() const;

    /// 设置机器人调试信息提供者。
    /// @param provider 机器人调试信息提供者。
    /// @note 该方法在 UI 线程中调用。
    void setProvider(RobotDebugInfoProvider* provider);

public slots:
    /// 加载指定文件中的机器人调试信息。
    /// @param fileUrl 文件 URL。
    /// @return 加载是否成功。
    bool load(const QUrl& fileUrl);

    /// 保存机器人调试信息到指定文件。
    /// @param fileUrl 文件 URL。
    /// @return 保存是否成功。
    bool save(const QUrl& fileUrl);

signals:
    /// 当最大容量发生变化时发出此信号。
    /// @param capacity 最大容量。
    /// @note 该信号在 UI 线程中发出。
    void capacityChanged(int capacity);

    /// 当是否冻结发生变化时发出此信号。
    /// @param freezed 是否冻结。
    /// @note 该信号在 UI 线程中发出。
    void freezedChanged(bool freezed);

    /// 当机器人调试信息提供者发生变化时发出此信号。
    /// @param provider 机器人调试信息提供者。
    /// @note 该信号在 UI 线程中发出。
    void providerChanged(RobotDebugInfoProvider* provider);

private:
    void addRobotDebugInfo(const RobotDebugInfo& info);
    void addRobotDebugInfo(QSharedPointer<RobotDebugInfo> info);
    QVariant column0Data(const QModelIndex& index, int role) const;
    QVariant column1Data(const QModelIndex& index, int role) const;
    QVariant column2Data(const QModelIndex& index, int role) const;
    QVariant column3Data(const QModelIndex& index, int role) const;
    QVariant column4Data(const QModelIndex& index, int role) const;
    QVariant column5Data(const QModelIndex& index, int role) const;
    QVariant column6Data(const QModelIndex& index, int role) const;
    QVariant column7Data(const QModelIndex& index, int role) const;
    QVariant column8Data(const QModelIndex& index, int role) const;
    QVariant column9Data(const QModelIndex& index, int role) const;
    QVariant column10Data(const QModelIndex& index, int role) const;

private:
    /// 最大容量（仅用于动态更新）。
    int mCapacity{100};
    /// 是否冻结。
    bool mFreezed{false};
    /// 行偏移量。
    int mRowShift{1};
    /// 机器人调试信息提供者。
    QPointer<RobotDebugInfoProvider> mProvider{nullptr};
    /// 机器人调试信息列表。
    QList<RobotDebugInfo> mRobotDebugInfos{};
};

#endif // ROBOT_DEBUG_INFO_TABLE_MODEL_H
