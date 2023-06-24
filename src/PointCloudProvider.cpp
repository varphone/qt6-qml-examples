#include "PointCloudProvider.h"
#include "PointCloudInfo.h"

PointCloudProvider::PointCloudProvider(QObject* parent) : QObject(parent)
{
}

void PointCloudProvider::setPointCloudInfo(
    QSharedPointer<PointCloudInfo> pointCloudInfo)
{
    mPointCloudInfo = pointCloudInfo;
    emit pointCloudChanged(mPointCloudInfo);
}
