#include "LivePointCloud.h"

#include <QThreadPool>

LivePointCloud::LivePointCloud(QObject* parent) : QObject(parent)
{
    mGrooveAreaProvider = new GrooveAreaProvider(this);
    mPointCloudProvider = new PointCloudProvider(this);
    mRobotDebugInfoProvider = new RobotDebugInfoProvider(this);

    // 创建 LiveDataGenerator 对象。
    mGenerator = new LiveDataGenerator();
    // 将 LiveDataGenerator 对象的 newGrooveArea 信号连接到 GrooveAreaProvider
    // 对象的 setGrooveAreaInfo 槽。
    connect(mGenerator, &LiveDataGenerator::newGrooveArea, mGrooveAreaProvider,
            &GrooveAreaProvider::setGrooveAreaInfo);
    // 将 LiveDataGenerator 对象的 newPointCloud 信号连接到 PointCloudProvider
    // 对象的 setPointCloudInfo 槽。
    connect(mGenerator, &LiveDataGenerator::newPointCloud, mPointCloudProvider,
            &PointCloudProvider::setPointCloudInfo);
    // 将 LiveDataGenerator 对象的 newRobotDebugInfo 信号连接到
    // RobotDebugInfoProvider 对象的 setRobotDebugInfo 槽。
    connect(mGenerator, &LiveDataGenerator::newRobotDebugInfo,
            mRobotDebugInfoProvider,
            &RobotDebugInfoProvider::setRobotDebugInfo);
    // 将 LiveDataGenerator 对象的 realtimeFpsChanged 信号连接到
    // LivePointCloud 对象的 realtimeFpsChanged 信号。
    connect(mGenerator, &LiveDataGenerator::realtimeFpsChanged, this,
            &LivePointCloud::realtimeFpsChanged);
    // 启动 LiveDataGenerator 对象。
    mGenerator->setRunning(true);
    // 在 QThreadPool 中启动 mGenerator。
    // QThreadPool 会自动管理线程的生命周期。
    QThreadPool::globalInstance()->start(mGenerator);
}

LivePointCloud::~LivePointCloud()
{
    // 停止 LiveDataGenerator 对象。
    if (mGenerator)
        mGenerator->setRunning(false);
}

int LivePointCloud::minInterval() const
{
    if (mGenerator)
        return mGenerator->minInterval();
    return 0;
}

void LivePointCloud::setMinInterval(int minInterval)
{
    if (mGenerator)
        mGenerator->setMinInterval(minInterval);
}

double LivePointCloud::realtimeFps(void) const
{
    if (mGenerator)
        return mGenerator->realtimeFps();
    return 0;
}

GrooveAreaProvider* LivePointCloud::grooveAreaProvider() const
{
    return mGrooveAreaProvider;
}

PointCloudProvider* LivePointCloud::pointCloudProvider() const
{
    return mPointCloudProvider;
}

RobotDebugInfoProvider* LivePointCloud::robotDebugInfoProvider() const
{
    return mRobotDebugInfoProvider;
}
