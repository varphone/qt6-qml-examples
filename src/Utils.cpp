#include "Utils.h"

#include <QDebug>

const int kMillisPerDay = 24 * 60 * 60 * 1000;
const int kMillisPerHour = 60 * 60 * 1000;
const int kMillisPerMinute = 60 * 1000;
const int kMillisPerSecond = 1000;

QString tsToString(qint64 ts)
{
    if (ts == 0)
        return QString("0.000");
    bool negative = ts < 0;
    if (negative)
        ts = -ts;
    qint64 days = ts / kMillisPerDay;
    qint64 hours = (ts - days * kMillisPerDay) / kMillisPerHour;
    qint64 minutes =
        (ts - days * kMillisPerDay - hours * kMillisPerHour) / kMillisPerMinute;
    qint64 seconds = (ts - days * kMillisPerDay - hours * kMillisPerHour -
                      minutes * kMillisPerMinute) /
                     kMillisPerSecond;
    qint64 milliseconds = ts - days * kMillisPerDay - hours * kMillisPerHour -
                          minutes * kMillisPerMinute -
                          seconds * kMillisPerSecond;
    if (ts < kMillisPerSecond) {
        if (negative)
            return QString("-0.%2").arg(milliseconds, 3, 10, QChar('0'));
        else
            return QString("0.%1").arg(milliseconds, 3, 10, QChar('0'));
    }
    if (ts <= kMillisPerMinute) {
        if (negative)
            return QString("-%1.%2")
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
        else
            return QString("%1.%2")
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
    }
    if (ts < kMillisPerHour) {
        if (negative)
            return QString("-%1:%2.%3")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
        else
            return QString("%1:%2.%3")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
    }
    if (ts < kMillisPerDay) {
        if (negative)
            return QString("-%1d %2:%3.%4")
                .arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
        else
            return QString("%1d %2:%3.%4")
                .arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
                .arg(milliseconds, 3, 10, QChar('0'));
    }
    if (negative)
        return QString("-%1d %2:%3:%4.%5")
            .arg(days)
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'))
            .arg(milliseconds, 3, 10, QChar('0'));
    else
        return QString("%1d %2:%3:%4.%5")
            .arg(days)
            .arg(hours, 2, 10, QChar('0'))
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'))
            .arg(milliseconds, 3, 10, QChar('0'));
}
