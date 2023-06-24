#include "GrooveAreaSource.h"
#include "GrooveAreaInfo.h"
#include "GrooveAreaProvider.h"

#include <QLineSeries>
#include <QThread>

GrooveAreaSource::GrooveAreaSource(QObject* parent) : QObject(parent)
{
}

GrooveAreaSource::~GrooveAreaSource()
{
    // 断开 mProvider 的 grooveAreaChanged 信号与 onGrooveAreaChanged 槽的连接。
    if (mProvider)
        disconnect(mProvider, &GrooveAreaProvider::grooveAreaChanged, this,
                   &GrooveAreaSource::onGrooveAreaChanged);
}

GrooveAreaProvider* GrooveAreaSource::provider() const
{
    return mProvider;
}

void GrooveAreaSource::setProvider(GrooveAreaProvider* provider)
{
    if (mProvider == provider)
        return;
    if (mProvider)
        disconnect(mProvider, &GrooveAreaProvider::grooveAreaChanged, this,
                   &GrooveAreaSource::onGrooveAreaChanged);
    if (provider)
        connect(provider, &GrooveAreaProvider::grooveAreaChanged, this,
                &GrooveAreaSource::onGrooveAreaChanged);
    mProvider = provider;
    emit providerChanged(mProvider);
}

QAreaSeries* GrooveAreaSource::series() const
{
    return mSeries;
}

void GrooveAreaSource::setSeries(QAreaSeries* series)
{
    if (mSeries == series)
        return;
    mSeries = series;
    emit seriesChanged(mSeries);
}

void GrooveAreaSource::onGrooveAreaChanged(
    QSharedPointer<GrooveAreaInfo> grooveAreaInfo)
{
    mGrooveAreaInfo = grooveAreaInfo;
    // 更新 mSeries 的数据。
    if (mSeries)
        mSeries->upperSeries()->replace(mGrooveAreaInfo->polygon);
}
