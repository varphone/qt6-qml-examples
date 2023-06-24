#include "RobotDebugInfoProvider.h"
#include "RobotDebugInfo.h"

RobotDebugInfoProvider::RobotDebugInfoProvider(QObject* parent)
    : QObject(parent)
{
}

void RobotDebugInfoProvider::setRobotDebugInfo(
    QSharedPointer<RobotDebugInfo> robotDebugInfo)
{
    mRobotDebugInfo = robotDebugInfo;
    emit robotDebugInfoChanged(mRobotDebugInfo);
}
