#include "PointCloudSource.h"
#include "PointCloudInfo.h"
#include "PointCloudProvider.h"

#include <QXYSeries>
#include <QThread>

PointCloudSource::PointCloudSource(QObject* parent) : QObject(parent)
{
}

PointCloudSource::~PointCloudSource()
{
    // 断开 mProvider 的 pointCloudChanged 信号与 onPointCloudChanged 槽的连接。
    if (mProvider)
        disconnect(mProvider, &PointCloudProvider::pointCloudChanged, this,
                   &PointCloudSource::onPointCloudChanged);
}

PointCloudProvider* PointCloudSource::provider() const
{
    return mProvider;
}

void PointCloudSource::setProvider(PointCloudProvider* provider)
{
    if (mProvider == provider)
        return;
    if (mProvider)
        disconnect(mProvider, &PointCloudProvider::pointCloudChanged, this,
                   &PointCloudSource::onPointCloudChanged);
    if (provider)
        connect(provider, &PointCloudProvider::pointCloudChanged, this,
                &PointCloudSource::onPointCloudChanged);
    mProvider = provider;
    emit providerChanged(mProvider);
}

QXYSeries* PointCloudSource::series() const
{
    return mSeries;
}

void PointCloudSource::setSeries(QXYSeries* series)
{
    if (mSeries == series)
        return;
    mSeries = series;
    emit seriesChanged(mSeries);
}

void PointCloudSource::onPointCloudChanged(
    QSharedPointer<PointCloudInfo> pointCloudInfo)
{
    mPointCloudInfo = pointCloudInfo;
    // 更新 mSeries 的数据。
    if (mSeries)
        mSeries->replace(mPointCloudInfo->points.toList());
}
