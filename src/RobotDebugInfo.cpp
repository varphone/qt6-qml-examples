#include "RobotDebugInfo.h"

void RobotDebugInfo::registerMetaTypes()
{
    qRegisterMetaType<RobotDebugInfo>();
    qRegisterMetaType<RobotDebugInfo>("RobotDebugInfo&");
    qRegisterMetaType<QSharedPointer<RobotDebugInfo>>();
}
