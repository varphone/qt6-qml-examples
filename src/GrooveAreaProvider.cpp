#include "GrooveAreaProvider.h"
#include "GrooveAreaInfo.h"

GrooveAreaProvider::GrooveAreaProvider(QObject* parent) : QObject(parent)
{
}

void GrooveAreaProvider::setGrooveAreaInfo(
    QSharedPointer<GrooveAreaInfo> grooveAreaInfo)
{
    mGrooveAreaInfo = grooveAreaInfo;
    emit grooveAreaChanged(mGrooveAreaInfo);
}