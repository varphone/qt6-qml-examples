#include "PatternBrush.h"

#include <QBrush>
#include <QColor>
#include <QGradient>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QtQml>
#include <qcolor.h>
#include <qrandom.h>

PatternBrush::PatternBrush(QObject* parent) : QObject(parent)
{
    mImage = QImage(100, 100, QImage::Format_ARGB32);
    mImage.fill(0xff00ffff);
    mBrush.setTextureImage(mImage);
    mTimer.setInterval(15);
    connect(&mTimer, &QTimer::timeout, this, [this]() {
        auto r = QRandomGenerator::global()->bounded(255);
        auto g = QRandomGenerator::global()->bounded(255);
        auto b = QRandomGenerator::global()->bounded(255);
        auto bgColor = QColor(r, g, b);
        auto fgColor = QColor(255 - r, 255 - g, 255 - b);
        mImage.fill(bgColor);
        QPainter p(&mImage);
        p.setPen(fgColor);
        p.drawLine(0, 0, mSize.width(), mSize.height());
        p.drawLine(0, mSize.height(), mSize.width(), 0);
        mBrush.setTextureImage(mImage);
        emit brushChanged();
    });
    mTimer.start();
}

PatternBrush::~PatternBrush()
{
}

const QBrush& PatternBrush::brush() const
{
    return mBrush;
}

// void PatternBrush::setBrush(const QBrush& brush)
// {
//     if (mBrush != brush) {
//         mBrush = brush;
//         emit brushChanged();
//     }
// }

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
