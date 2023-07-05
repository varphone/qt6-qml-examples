#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H

#include <QQmlListProperty>
#include <QThread>
#include <QTimer>

class WorkerThread : public QThread {
    Q_OBJECT
    Q_PROPERTY(
        QQmlListProperty<QObject> children READ children NOTIFY childrenChanged)
    Q_CLASSINFO("DefaultProperty", "children")
public:
    explicit WorkerThread(QObject* parent = nullptr);
    virtual ~WorkerThread();

    QQmlListProperty<QObject> children();

    void appendChild(QObject* child);
    qsizetype childCount() const;
    QObject* childAt(qsizetype index) const;
    void clearChildren();
    void replaceChild(qsizetype index, QObject* child);
    void removeLastChild();

    void run() override;

public slots:
    void reportThreadInfo();

signals:
    void childrenChanged();

private:
    static void appendChildWrapper(QQmlListProperty<QObject>* list,
                                   QObject* child);
    static qsizetype childCountWrapper(QQmlListProperty<QObject>* list);
    static QObject* childAtWrapper(QQmlListProperty<QObject>* list,
                                   qsizetype index);
    static void clearChildrenWrapper(QQmlListProperty<QObject>* list);
    static void replaceChildWrapper(QQmlListProperty<QObject>* list,
                                    qsizetype index, QObject* child);
    static void removeLastChildWrapper(QQmlListProperty<QObject>* list);

private:
    // QTimer mTicker{};
    QList<QObject*> mChildren;
};

#endif // WORKER_THREAD_H
