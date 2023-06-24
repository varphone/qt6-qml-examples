#ifndef ROBOT_DEBUG_INFO_H
#define ROBOT_DEBUG_INFO_H

#include <QtGlobal>

struct RobotDebugInfo
{
    qint64 requestTs;
    qint64 respondTs;
    bool seamFound;
    qint64 seamTs;
    float seamY;
    float seamZ;
    qint64 robotTs;
    float robotX;
    float robotY;
    float robotZ;
};

#endif // ROBOT_DEBUG_INFO_H
