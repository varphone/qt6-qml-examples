#include <QBrush>
#include <QObject>

class QJSEngine;
class QQmlEngine;

class BrushFactory : public QObject {
    Q_OBJECT
public:
    BrushFactory(QObject* parent = nullptr);
    ~BrushFactory();

    enum PatternKind
    {
        Ball,
        Circle,
        Cross,
        Diamond,
        Plus,
        Triangle,
    };

    Q_ENUM(PatternKind)

    Q_INVOKABLE QBrush defaultBrush();
    Q_INVOKABLE QBrush patternBrush(PatternKind kind, QSizeF size,
                                    QColor fillColor, QColor strokeColor,
                                    qreal lineWidth = 2.0);

    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);
    static void registerMetaTypes(const char* uri);

public slots:
    QBrush* createBrush(PatternKind kind, QSizeF size, QColor fillColor,
                        QColor strokeColor, qreal lineWidth = 2.0);

private:
    QBrush ballBrush(qreal r, QColor fillColor);
    QBrush crossBrush(QSizeF size, QColor fillColor, QColor strokeColor,
                      qreal lineWidth = 2.0);
};

Q_DECLARE_METATYPE(BrushFactory)
Q_DECLARE_METATYPE(BrushFactory::PatternKind)
