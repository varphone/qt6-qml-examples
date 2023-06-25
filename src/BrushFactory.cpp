#include "BrushFactory.h"

#include <QJSEngine>
#include <QPainter>
#include <QPainterPath>
#include <QQmlEngine>
#include <QRadialGradient>

Q_GLOBAL_STATIC(BrushFactory, singletonInstance)

BrushFactory::BrushFactory(QObject* parent) : QObject(parent)
{
}

BrushFactory::~BrushFactory()
{
}

QBrush BrushFactory::defaultBrush()
{
    QRadialGradient gradient(15, 15, 15, 15, 15);
    gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));

    QBrush brush(gradient);
    return brush;
}

QBrush BrushFactory::patternBrush(PatternKind kind, QSizeF size,
                                  QColor fillColor, QColor strokeColor,
                                  qreal lineWidth)
{
    switch (kind) {
    case PatternKind::Ball:
        return ballBrush(size.width() / 2, fillColor);
    case PatternKind::Cross:
        return crossBrush(size, fillColor, strokeColor, lineWidth);
    default:
        return QBrush(fillColor);
    }
}

QBrush BrushFactory::ballBrush(qreal r, QColor fillColor)
{
    QRadialGradient gradient(r, r, r, r, r);
    gradient.setColorAt(0, fillColor);
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    QBrush brush(gradient);
    return brush;
}

QBrush BrushFactory::crossBrush(QSizeF size, QColor fillColor,
                                QColor strokeColor, qreal lineWidth)
{
    int cx = size.width();
    int cy = size.height();
    QImage image(QSize(cx, cy), QImage::Format_ARGB32);
    image.fill(0);
    {
        QPainter p(&image);
        QPainterPath pp;
        pp.moveTo(0, 0);
        pp.lineTo(cx, cy);
        pp.moveTo(cx, 0);
        pp.lineTo(0, cy);
        pp.addRect(0, 10, cx, 2);
        // qreal strokeOffset = lineWidth * 0.5;
        // qreal strokeWidth = lineWidth * 1.5;
        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setColor(strokeColor);
        pen.setWidth(lineWidth * 0.5);
        // p.setPen(pen);
        // auto pad = lineWidth * 2;
        // p.drawLine(QLineF(pad, pad, cx - pad, cy - pad));
        // p.drawLine(QLineF(cx - pad, pad, pad, cy - pad));
        // // p.end();
        // pen.setColor(fillColor);
        // pen.setWidth(lineWidth);
        // pad = lineWidth * 2.5;
        // p.setPen(QPen(fillColor, lineWidth));
        // p.drawLine(QLineF(pad, pad, cx - pad, cy - pad));
        // p.drawLine(QLineF(cx - pad, pad, pad, cy - pad));
        // p.fillPath(pp, QBrush(fillColor));
        // p.strokePath(pp, QPen(strokeColor, lineWidth));
        // p.setPen(QPen(strokeColor, lineWidth));
        // p.setBrush(QBrush(fillColor));
        // p.drawPath(pp);
        p.fillPath(pp, QBrush(fillColor));
        p.strokePath(pp, QPen(strokeColor, 1));
        p.end();
    }
    QBrush brush(image);
    return brush;
}

QBrush* BrushFactory::createBrush(PatternKind kind, QSizeF size,
                                  QColor fillColor, QColor strokeColor,
                                  qreal lineWidth)
{
    return new QBrush(
        patternBrush(kind, size, fillColor, strokeColor, lineWidth));
}

QObject* BrushFactory::qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return singletonInstance();
}

void BrushFactory::registerMetaTypes(const char* uri)
{
    qRegisterMetaType<BrushFactory>();
    qRegisterMetaType<BrushFactory>("BrushFactory&");
    qmlRegisterSingletonType<BrushFactory>(uri, 1, 0, "BrushFactory",
                                           BrushFactory::qmlInstance);
    qmlRegisterUncreatableType<BrushFactory>(
        uri, 1, 0, "BrushFactory",
        QStringLiteral("BrushFactory is uncreatable"));
    qmlRegisterUncreatableType<BrushFactory::PatternKind>(
        uri, 1, 0, "PatternKind", QStringLiteral("PatternKind is uncreatable"));
}
