#include "LiveDataGenerator.h"
#include "GrooveAreaInfo.h"
#include "PointCloudInfo.h"
#include "RobotDebugInfo.h"
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <algorithm>

LiveDataGenerator::LiveDataGenerator(QObject* parent) : QObject(parent)
{
}

LiveDataGenerator::~LiveDataGenerator()
{
}

int LiveDataGenerator::minInterval() const
{
    return mMinInterval;
}

void LiveDataGenerator::setMinInterval(int minInterval)
{
    mMinInterval = std::clamp(minInterval, 1, 1000);
}

double LiveDataGenerator::realtimeFps(void) const
{
    return mRealtimeFps;
}

bool LiveDataGenerator::isRunning() const
{
    return mRunning;
}

void LiveDataGenerator::setRunning(bool running)
{
    mRunning = running;
}

QPolygonF LiveDataGenerator::buildArcPiePolygon(const QPointF& center,
                                                qreal radius, qreal startAngle,
                                                qreal angleSpan)
{
    QPolygonF polygon;
    polygon << center;
    const int arcSteps =
        std::clamp(QRandomGenerator::global()->bounded(20), 2, 20);
    const qreal angleStep = angleSpan / arcSteps;
    for (int i = 0; i <= arcSteps; ++i) {
        const qreal angle = startAngle + i * angleStep;
        polygon << QPointF(center.x() + radius * qCos(angle),
                           center.y() + radius * qSin(angle));
    }
    polygon << center;
    return polygon;
}

QVector<QPointF> LiveDataGenerator::buildSinWavePoints(double phaseShift)
{
    QVector<QPointF> points;
    points.reserve(200);
    for (int i = -100; i < 100; ++i) {
        points.append(QPointF(i, qSin(i + phaseShift) * 50));
    }
    return points;
}

QSharedPointer<GrooveAreaInfo> LiveDataGenerator::generateGrooveAreaInfo()
{
    mGrooveArea += 0.1;
    if (mGrooveArea > 100)
        mGrooveArea = 0;
    mGrooveAreaRadius = QRandomGenerator::global()->bounded(100);
    mGrooveAreaStartAngle = QRandomGenerator::global()->bounded(360);
    mGrooveAreaAngleSpan = QRandomGenerator::global()->bounded(360);

    auto startAngle = mGrooveAreaStartAngle * M_PI / 180;
    auto angleSpan = mGrooveAreaAngleSpan * M_PI / 180;

    auto grooveAreaInfo = QSharedPointer<GrooveAreaInfo>::create();
    grooveAreaInfo->timestamp =
        QDateTime::currentDateTime().toMSecsSinceEpoch();
    grooveAreaInfo->area = mGrooveArea;
    grooveAreaInfo->polygon = buildArcPiePolygon(
        QPointF(0, 0), mGrooveAreaRadius, startAngle, angleSpan);

    return grooveAreaInfo;
}

QSharedPointer<PointCloudInfo> LiveDataGenerator::generatePointCloudInfo()
{
    auto pointCloudInfo = QSharedPointer<PointCloudInfo>::create();
    pointCloudInfo->timestamp =
        QDateTime::currentDateTime().toMSecsSinceEpoch();
    pointCloudInfo->points = buildSinWavePoints(mSineWavePhaseShift);
    return pointCloudInfo;
}

QSharedPointer<RobotDebugInfo> LiveDataGenerator::generateRobotDebugInfo()
{
    auto rng = QRandomGenerator::global();
    auto robotDebugInfo = QSharedPointer<RobotDebugInfo>::create();
    robotDebugInfo->requestTs =
        QDateTime::currentDateTime().toMSecsSinceEpoch();
    robotDebugInfo->respondTs = robotDebugInfo->requestTs;
    robotDebugInfo->seamFound = rng->bounded(0, 2) == 1;
    robotDebugInfo->seamTs = robotDebugInfo->requestTs;
    robotDebugInfo->seamY = (float)(rng->bounded(-10000, 10000)) / 100.0;
    robotDebugInfo->seamZ = (float)(rng->bounded(-10000, 10000)) / 100.0;
    robotDebugInfo->robotTs = robotDebugInfo->requestTs;
    robotDebugInfo->robotX = (float)(rng->bounded(-100000, 100000)) / 100.0;
    robotDebugInfo->robotY = (float)(rng->bounded(-100000, 100000)) / 100.0;
    robotDebugInfo->robotZ = (float)(rng->bounded(-100000, 100000)) / 100.0;
    return robotDebugInfo;
}

void LiveDataGenerator::run()
{
    QVector<double> fpsHistory{};
    quint64 totalFrameCount = 0;
    QElapsedTimer timer;

    fpsHistory.reserve(20);
    timer.start();

    while (mRunning) {
        auto grooveAreaInfo = generateGrooveAreaInfo();
        auto pointCloudInfo = generatePointCloudInfo();
        auto robotDebugInfo = generateRobotDebugInfo();
        emit newGrooveArea(grooveAreaInfo);
        emit newPointCloud(pointCloudInfo);
        emit newRobotDebugInfo(robotDebugInfo);
        mSineWavePhaseShift += 0.1;
        totalFrameCount++;
        /// 计算实时帧率。
        auto timePerFrame = timer.elapsed();
        timer.restart();
        auto fps = 1000.0 / timePerFrame;
        if (fpsHistory.size() >= 5)
            fpsHistory.pop_front();
        fpsHistory.append(fps);
        auto sum = std::accumulate(fpsHistory.begin(), fpsHistory.end(), 0.0);
        fps = sum / fpsHistory.size();
        if (std::abs(mRealtimeFps - fps) > 1.0) {
            mRealtimeFps = fps;
            emit realtimeFpsChanged(mRealtimeFps);
        }
        /// 控制输出帧率。
        QThread::msleep(mMinInterval);
    }
}
