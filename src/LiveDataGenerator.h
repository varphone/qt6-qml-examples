#ifndef LIVE_DATA_GENERATOR_H
#define LIVE_DATA_GENERATOR_H

#include <QDateTime>
#include <QObject>
#include <QPolygonF>
#include <QRunnable>
#include <QSharedPointer>
#include <QThread>

struct GrooveAreaInfo;
struct PointCloudInfo;
struct RobotDebugInfo;

/// 一个代表实时数据生成器的类型。
/// @note 该类在非 UI 线程中使用。
class LiveDataGenerator : public QObject, public QRunnable {
    Q_OBJECT
public:
    /// 构造函数。
    /// @param parent 父对象。
    LiveDataGenerator(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~LiveDataGenerator();

    /// 返回点云数据输出最小间隔。
    /// @return 点云数据输出最小间隔。
    /// @note 该方法在非 UI 线程中调用。
    int minInterval() const;

    /// 设置点云数据输出最小间隔。
    /// @param minInterval 点云数据输出最小间隔。
    /// @note 该方法在非 UI 线程中调用。
    void setMinInterval(int minInterval);

    /// 返回实时帧率。
    double realtimeFps(void) const;

    /// 返回 LiveDataGenerator 对象是否运行。
    /// @return LiveDataGenerator 对象是否运行。
    /// @note 该方法在非 UI 线程中调用。
    bool isRunning() const;

    /// 设置 LiveDataGenerator 对象是否运行。
    /// @param running LiveDataGenerator 对象是否运行。
    /// @note 该方法在非 UI 线程中调用。
    void setRunning(bool running);

    /// 构造一个圆弧扇形的多边形。
    /// @param center 圆弧扇形的圆心。
    /// @param radius 圆弧扇形的半径。
    /// @param startAngle 圆弧扇形的起始角度。
    /// @param angleSpan 圆弧扇形的角度跨度。
    /// @return 圆弧扇形的多边形。
    QPolygonF buildArcPiePolygon(const QPointF& center, qreal radius,
                                 qreal startAngle, qreal angleSpan);

    /// 构造一个正弦波形的点集。
    /// @param phaseShift 正弦波形的相位偏移。
    /// @return 正弦波形的点集。
    QVector<QPointF> buildSinWavePoints(double phaseShift);

    /// 生成一个新的焊道面积数据信息。
    /// @return 新的焊道面积数据信息。
    QSharedPointer<GrooveAreaInfo> generateGrooveAreaInfo();

    /// 生成一个新的点云数据信息。
    /// @return 新的点云数据信息。
    QSharedPointer<PointCloudInfo> generatePointCloudInfo();

    /// 生成一个新的机器人调试信息。
    /// @return 新的机器人调试信息。
    QSharedPointer<RobotDebugInfo> generateRobotDebugInfo();

    /// 重写 QRunnable::run() 方法。
    /// @note 该方法在非 UI 线程中调用。
    void run() override;

signals:
    /// 当点云数据输出实时帧率发生变化时发出此信号。
    void realtimeFpsChanged(double realtimeFps);

    /// 当焊道面积数据发生变化时发出此信号。
    void newGrooveArea(QSharedPointer<GrooveAreaInfo> grooveAreaInfo);

    /// 当点云数据发生变化时发出此信号。
    void newPointCloud(QSharedPointer<PointCloudInfo> pointCloudInfo);

    /// 当机器人调试信息发生变化时发出此信号。
    void newRobotDebugInfo(QSharedPointer<RobotDebugInfo> robotDebugInfo);

private:
    bool mRunning{false};
    int mMinInterval{100};
    double mRealtimeFps{0.0};
    double mGrooveArea{0.0};
    double mGrooveAreaRadius{0.0};
    double mGrooveAreaStartAngle{0.0};
    double mGrooveAreaAngleSpan{0.0};
    double mSineWavePhaseShift{0.0};
};

#endif // LIVE_DATA_GENERATOR_H
