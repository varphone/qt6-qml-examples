#ifndef PATTERN_BRUSH_H
#define PATTERN_BRUSH_H

#include <QBrush>
#include <QColor>
#include <QGradient>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QString>
#include <QtQml>

class PatternBrush : public QObject {
    Q_OBJECT
    Q_PROPERTY(const QBrush& brush READ brush NOTIFY brushChanged)
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    QML_ELEMENT
public:
    explicit PatternBrush(QObject* parent = nullptr);
    virtual ~PatternBrush();

    const QBrush& brush() const;
    // void setBrush(const QBrush& brush);

    QSize size() const;
    void setSize(const QSize& size);

    static void registerMetaTypes(const char* uri);

signals:
    void brushChanged();
    void sizeChanged(const QSize& size);

private:
    QSize mSize{20, 20};
    QBrush mBrush{};
    QImage mImage{};
    QTimer mTimer{};
};

#endif // PATTERN_BRUSH_H
