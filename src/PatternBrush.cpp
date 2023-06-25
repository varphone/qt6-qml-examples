#include "PatternBrush.h"

#include <QBrush>
#include <QColor>
#include <QGradient>
#include <QImage>
#include <QJSEngine>
#include <QPainter>
#include <QPixmap>
#include <QRandomGenerator>
#include <QString>
#include <QtQml>

PatternBrush::PatternBrush(QObject* parent) : QObject(parent)
{
    mImage = QImage(400, 400, QImage::Format_ARGB32);
    mImage.fill(0xff00ffff);
    mBrush.setTextureImage(mImage);
    // For testing, we update the brush every 15ms
    connect(&mTimer, &QTimer::timeout, this, &PatternBrush::updatePattern);
    mTimer.setInterval(15);
    mTimer.start();
}

PatternBrush::~PatternBrush()
{
}

QBrush PatternBrush::brush() const
{
    return mBrush;
}

QSize PatternBrush::size() const
{
    return mSize;
}

void PatternBrush::setSize(const QSize& size)
{
    if (mSize != size) {
        mSize = size;
        emit sizeChanged(size);
    }
}

void PatternBrush::registerMetaTypes(const char* uri)
{
    qRegisterMetaType<PatternBrush>();
    qRegisterMetaType<PatternBrush>("PatternBrush&");
    qmlRegisterType<PatternBrush>(uri, 1, 0, "PatternBrush");
}

// void PatternBrush::collectGarbage()
// {
//     auto engine = qjsEngine(this);
//     if (engine) {
//         engine->collectGarbage();
//     }
// }

QBrush PatternBrush::dummyBrush() const
{
    return QBrush{};
}

void PatternBrush::updatePattern()
{
    auto r = QRandomGenerator::global()->bounded(255);
    auto g = QRandomGenerator::global()->bounded(255);
    auto b = QRandomGenerator::global()->bounded(255);
    auto bgColor = QColor(r, g, b);
    auto fgColor = QColor(255 - r, 255 - g, 255 - b);
    mImage.fill(bgColor);
    {
        QPainter p(&mImage);
        p.setPen(QPen(fgColor, 2));
        // 画一个叉型图案
        p.drawLine(0, 0, mSize.width(), mSize.height());
        p.drawLine(0, mSize.height(), mSize.width(), 0);
    }
    mBrush.setTextureImage(mImage);
    emit brushChanged(mBrush);
}
