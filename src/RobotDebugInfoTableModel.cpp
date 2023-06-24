#include "RobotDebugInfoTableModel.h"
#include "RobotDebugInfo.h"
#include "RobotDebugInfoProvider.h"
#include "Utils.h"

#include <QColor>
#include <QDateTime>
#include <QFile>

const int kDeltaRole = Qt::UserRole + 1;
const int kDeltaColorRole = Qt::UserRole + 2;
const int kHightlightRole = Qt::UserRole + 3;

RobotDebugInfoTableModel::RobotDebugInfoTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

RobotDebugInfoTableModel::~RobotDebugInfoTableModel()
{
}

int RobotDebugInfoTableModel::rowCount(const QModelIndex& index) const
{
    return mRobotDebugInfos.size();
}

int RobotDebugInfoTableModel::columnCount(const QModelIndex& index) const
{
    return 12;
}

QVariant RobotDebugInfoTableModel::data(const QModelIndex& index,
                                        int role) const
{
    if (!index.isValid())
        return QVariant();

    // Highlight the row if the seam is not found.
    if (role == kHightlightRole) {
        return !mRobotDebugInfos.at(index.row()).seamFound;
    }

    auto column = index.column();
    switch (column) {
    case 0:
        return column0Data(index, role);
    case 1:
        return column1Data(index, role);
    case 2:
        return column2Data(index, role);
    case 3:
        return column3Data(index, role);
    case 4:
        return column4Data(index, role);
    case 5:
        return column5Data(index, role);
    case 6:
        return column6Data(index, role);
    case 7:
        return column7Data(index, role);
    case 8:
        return column8Data(index, role);
    case 9:
        return column9Data(index, role);
    case 10:
        return column10Data(index, role);
    default:
        break;
    }

    return QVariant();
}

QVariant RobotDebugInfoTableModel::headerData(int section,
                                              Qt::Orientation orientation,
                                              int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
    case 0:
        return tr("序号");
    case 1:
        return tr("请求时间");
    case 2:
        return tr("响应时间");
    case 3:
        return tr("找到焊缝");
    case 4:
        return tr("焊缝时间");
    case 5:
        return tr("焊缝 Y");
    case 6:
        return tr("焊缝 Z");
    case 7:
        return tr("机器人时间");
    case 8:
        return tr("机器人 X");
    case 9:
        return tr("机器人 Y");
    case 10:
        return tr("机器人 Z");
    case 11:
        return tr("");
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> RobotDebugInfoTableModel::roleNames() const
{
    return {
        {Qt::DisplayRole, "display"},
        {Qt::TextAlignmentRole, "textAlignment"},
        {kDeltaRole, "delta"},
        {kDeltaColorRole, "deltaColor"},
        {kHightlightRole, "highlight"},
    };
}

int RobotDebugInfoTableModel::capacity() const
{
    return mCapacity;
}

void RobotDebugInfoTableModel::setCapacity(int capacity)
{
    if (mCapacity == capacity)
        return;
    mCapacity = capacity;
    emit capacityChanged(mCapacity);
}

bool RobotDebugInfoTableModel::freezed() const
{
    return mFreezed;
}

void RobotDebugInfoTableModel::setFreezed(bool freezed)
{
    if (mFreezed == freezed)
        return;
    mFreezed = freezed;
    emit freezedChanged(mFreezed);
}

RobotDebugInfoProvider* RobotDebugInfoTableModel::provider() const
{
    return mProvider;
}

void RobotDebugInfoTableModel::setProvider(RobotDebugInfoProvider* provider)
{
    if (mProvider == provider)
        return;
    if (mProvider)
        disconnect(mProvider, &RobotDebugInfoProvider::robotDebugInfoChanged,
                   this,
                   qOverload<QSharedPointer<RobotDebugInfo>>(
                       &RobotDebugInfoTableModel::addRobotDebugInfo));
    if (provider)
        connect(provider, &RobotDebugInfoProvider::robotDebugInfoChanged, this,
                qOverload<QSharedPointer<RobotDebugInfo>>(
                    &RobotDebugInfoTableModel::addRobotDebugInfo));
    mProvider = provider;
    emit providerChanged(mProvider);
}

bool RobotDebugInfoTableModel::load(const QUrl& fileUrl)
{
    QFile file(fileUrl.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    setFreezed(true);
    beginResetModel();
    mRobotDebugInfos.clear();
    mRowShift = 1;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() < 10)
            continue;
        RobotDebugInfo info;
        info.requestTs = fields.at(0).toLongLong();
        info.respondTs = fields.at(1).toLongLong();
        info.seamFound = fields.at(2).toInt();
        info.seamTs = fields.at(3).toLongLong();
        info.seamY = fields.at(4).toDouble();
        info.seamZ = fields.at(5).toDouble();
        info.robotTs = fields.at(6).toLongLong();
        info.robotX = fields.at(7).toDouble();
        info.robotY = fields.at(8).toDouble();
        info.robotZ = fields.at(9).toDouble();
        mRobotDebugInfos.append(info);
    }
    endResetModel();
    return true;
}

bool RobotDebugInfoTableModel::save(const QUrl& fileUrl)
{
    QFile file(fileUrl.toLocalFile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    for (const auto& info : mRobotDebugInfos) {
        out << info.requestTs << "," << info.respondTs << "," << info.seamFound
            << "," << info.seamTs << "," << info.seamY << "," << info.seamZ
            << "," << info.robotTs << "," << info.robotX << "," << info.robotY
            << "," << info.robotZ << "\n";
    }
    return true;
}

QVariant RobotDebugInfoTableModel::column0Data(const QModelIndex& index,
                                               int role) const
{
    if (role == Qt::DisplayRole) {
        return index.row() + mRowShift;
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column1Data(const QModelIndex& index,
                                               int role) const
{
    auto requestTs = mRobotDebugInfos.at(index.row()).requestTs;
    if (role == Qt::DisplayRole)
        return tsToString(requestTs);
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRequestTs = mRobotDebugInfos.at(index.row() - 1).requestTs;
        return tsToString(requestTs - lastRequestTs);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRequestTs = mRobotDebugInfos.at(index.row() - 1).requestTs;
        auto delta = requestTs - lastRequestTs;
        if (delta < 0)
            return QColor::fromRgb(255, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column2Data(const QModelIndex& index,
                                               int role) const
{
    auto respondTs = mRobotDebugInfos.at(index.row()).respondTs;
    if (role == Qt::DisplayRole) {
        return tsToString(respondTs);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRespondTs = mRobotDebugInfos.at(index.row() - 1).respondTs;
        return tsToString(respondTs - lastRespondTs);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRespondTs = mRobotDebugInfos.at(index.row() - 1).respondTs;
        auto delta = respondTs - lastRespondTs;
        if (delta < 0)
            return QColor::fromRgb(255, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column3Data(const QModelIndex& index,
                                               int role) const
{
    if (role == Qt::DisplayRole) {
        return mRobotDebugInfos.at(index.row()).seamFound;
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column4Data(const QModelIndex& index,
                                               int role) const
{
    auto seamTs = mRobotDebugInfos.at(index.row()).seamTs;
    if (role == Qt::DisplayRole) {
        return tsToString(seamTs);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamTs = mRobotDebugInfos.at(index.row() - 1).seamTs;
        return tsToString(seamTs - lastSeamTs);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamTs = mRobotDebugInfos.at(index.row() - 1).seamTs;
        auto delta = seamTs - lastSeamTs;
        if (delta < 0)
            return QColor::fromRgb(255, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column5Data(const QModelIndex& index,
                                               int role) const
{
    auto seamY = mRobotDebugInfos.at(index.row()).seamY;
    if (role == Qt::DisplayRole) {
        return QString("%1").arg(seamY, 0, 'f', 2);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamY = mRobotDebugInfos.at(index.row() - 1).seamY;
        return QString("%1").arg(seamY - lastSeamY, 0, 'f', 2);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamY = mRobotDebugInfos.at(index.row() - 1).seamY;
        auto delta = seamY - lastSeamY;
        if (std::abs(delta) > 10)
            return QColor::fromRgb(128, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column6Data(const QModelIndex& index,
                                               int role) const
{
    auto seamZ = mRobotDebugInfos.at(index.row()).seamZ;
    if (role == Qt::DisplayRole) {
        return QString("%1").arg(seamZ, 0, 'f', 2);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamZ = mRobotDebugInfos.at(index.row() - 1).seamZ;
        return QString("%1").arg(seamZ - lastSeamZ, 0, 'f', 2);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastSeamZ = mRobotDebugInfos.at(index.row() - 1).seamZ;
        auto delta = seamZ - lastSeamZ;
        if (std::abs(delta) > 10)
            return QColor::fromRgb(128, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column7Data(const QModelIndex& index,
                                               int role) const
{
    auto robotTs = mRobotDebugInfos.at(index.row()).robotTs;
    if (role == Qt::DisplayRole) {
        return tsToString(robotTs);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotTs = mRobotDebugInfos.at(index.row() - 1).robotTs;
        return tsToString(robotTs - lastRobotTs);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotTs = mRobotDebugInfos.at(index.row() - 1).robotTs;
        auto delta = robotTs - lastRobotTs;
        if (delta < 0)
            return QColor::fromRgb(255, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column8Data(const QModelIndex& index,
                                               int role) const
{
    auto robotX = mRobotDebugInfos.at(index.row()).robotX;
    if (role == Qt::DisplayRole) {
        return QString::number(robotX, 'f', 2);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotX = mRobotDebugInfos.at(index.row() - 1).robotX;
        return QString::number(robotX - lastRobotX, 'f', 2);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotX = mRobotDebugInfos.at(index.row() - 1).robotX;
        auto delta = robotX - lastRobotX;
        if (std::abs(delta) > 10)
            return QColor::fromRgb(128, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column9Data(const QModelIndex& index,
                                               int role) const
{
    auto robotY = mRobotDebugInfos.at(index.row()).robotY;
    if (role == Qt::DisplayRole) {
        return QString::number(robotY, 'f', 2);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotY = mRobotDebugInfos.at(index.row() - 1).robotY;
        return QString::number(robotY - lastRobotY, 'f', 2);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotY = mRobotDebugInfos.at(index.row() - 1).robotY;
        auto delta = robotY - lastRobotY;
        if (std::abs(delta) > 10)
            return QColor::fromRgb(128, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

QVariant RobotDebugInfoTableModel::column10Data(const QModelIndex& index,
                                                int role) const
{
    auto robotZ = mRobotDebugInfos.at(index.row()).robotZ;
    if (role == Qt::DisplayRole) {
        return QString::number(robotZ, 'f', 2);
    }
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignRight;
    else if (role == kDeltaRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotZ = mRobotDebugInfos.at(index.row() - 1).robotZ;
        return QString::number(robotZ - lastRobotZ, 'f', 2);
    }
    else if (role == kDeltaColorRole) {
        if (index.row() == 0)
            return QVariant();
        auto lastRobotZ = mRobotDebugInfos.at(index.row() - 1).robotZ;
        auto delta = robotZ - lastRobotZ;
        if (std::abs(delta) > 10)
            return QColor::fromRgb(128, 0, 0);
        else
            return QColor::fromRgb(0, 128, 0);
    }
    return QVariant();
}

void RobotDebugInfoTableModel::addRobotDebugInfo(const RobotDebugInfo& info)
{
    if (mFreezed)
        return;
    if (mCapacity > 0 && mRobotDebugInfos.size() >= mCapacity) {
        beginRemoveRows(QModelIndex(), 0, 0);
        mRobotDebugInfos.removeFirst();
        mRowShift++;
        endRemoveRows();
    }
    beginInsertRows(QModelIndex(), mRobotDebugInfos.size(),
                    mRobotDebugInfos.size());
    mRobotDebugInfos.append(info);
    endInsertRows();
}

void RobotDebugInfoTableModel::addRobotDebugInfo(
    QSharedPointer<RobotDebugInfo> info)
{
    addRobotDebugInfo(*info);
}
