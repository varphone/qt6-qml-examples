#ifndef UTILS_H
#define UTILS_H

#include "Utils.h"
#include <QString>

/// 将时间戳转换为字符串。
/// @param ts 时间戳，单位：毫秒。
/// @return 字符串。
QString tsToString(qint64 ts);

#endif // UTILS_H
