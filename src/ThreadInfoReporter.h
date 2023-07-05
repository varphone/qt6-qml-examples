#include <QObject>
#include <QTimer>

class ThreadInfoReporter : public QObject {
    Q_OBJECT

public:
    explicit ThreadInfoReporter(QObject* parent = nullptr);
    virtual ~ThreadInfoReporter();

public slots:
    void report();

private:
    QTimer mTicker{};
};