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

// 一个代表图案画刷的类型。
//
// 该类型的实例可以在 QML 中使用。
// 该类型的实例可以在 C++ 中使用。
class PatternBrush : public QObject {
    Q_OBJECT
    /// 一个代表图案画刷的属性。
    Q_PROPERTY(QBrush brush READ brush NOTIFY brushChanged)
    /// 一个代表图案大小的属性。
    Q_PROPERTY(QSize size READ size WRITE setSize NOTIFY sizeChanged)
    QML_ELEMENT
public:
    /// 构造函数。
    /// @param parent 父对象。
    explicit PatternBrush(QObject* parent = nullptr);

    /// 析构函数。
    virtual ~PatternBrush();

    /// 返回图案画刷。
    QBrush brush() const;

    /// 返回图案大小。
    QSize size() const;

    /// 设置图案大小。
    /// @param size 图案大小。
    /// @note 该函数会发出 sizeChanged 信号。
    void setSize(const QSize& size);

    /// 注册该类型的元类型。
    /// @param uri 该类型的 URI。
    static void registerMetaTypes(const char* uri);

public slots:
    // void collectGarbage();

    /// 返回一个空的图案画刷。
    QBrush dummyBrush() const;

signals:
    /// 该信号在图案画刷发生变化时发出。
    /// @param brush 新的图案画刷。
    /// @note 该信号对应 brush 属性。
    void brushChanged(const QBrush& brush);

    /// 该信号在图案大小发生变化时发出。
    /// @param size 新的图案大小。
    /// @note 该信号对应 size 属性。
    /// @note 该信号在 setSize() 函数中发出。
    void sizeChanged(const QSize& size);

private:
    /// 更新图案。
    void updatePattern();

private:
    /// 图案大小。
    QSize mSize{20, 20};
    /// 图案画刷。
    QBrush mBrush{};
    /// 图案图像。
    QImage mImage{};
    /// 定时器（用于生成测试图案）。
    QTimer mTimer{};
};

#endif // PATTERN_BRUSH_H
