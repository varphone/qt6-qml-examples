#include "ThreadInfoReporter.h"

#include <QDebug>
#include <QThread>

ThreadInfoReporter::ThreadInfoReporter(QObject* parent) : QObject(parent)
{
    qDebug() << "ThreadInfoReporter::ThreadInfoReporter";
    connect(&mTicker, &QTimer::timeout, this, &ThreadInfoReporter::report);
    mTicker.setInterval(1000);
    mTicker.start();
}

ThreadInfoReporter::~ThreadInfoReporter()
{
    qDebug() << "ThreadInfoReporter::~ThreadInfoReporter";
}

void ThreadInfoReporter::report()
{
    qDebug() << "ThreadInfoReporter::report" << QThread::currentThread()
             << QThread::currentThreadId();
}
