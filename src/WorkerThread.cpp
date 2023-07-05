#include "WorkerThread.h"

#include <QDebug>
#include <qobject.h>
#include <qthread.h>

WorkerThread::WorkerThread(QObject* parent) : QThread(parent)
{
    qDebug() << "WorkerThread::WorkerThread";
    start();
}

WorkerThread::~WorkerThread()
{
    qDebug() << "WorkerThread::~WorkerThread";
    quit();
    wait();
}

QQmlListProperty<QObject> WorkerThread::children()
{
    return {this,
            this,
            &WorkerThread::appendChildWrapper,
            &WorkerThread::childCountWrapper,
            &WorkerThread::childAtWrapper,
            &WorkerThread::clearChildrenWrapper,
            &WorkerThread::replaceChildWrapper,
            &WorkerThread::removeLastChildWrapper};
}

// void WorkerThread::run()

void WorkerThread::appendChild(QObject* child)
{
    qDebug() << "WorkerThread::appendChild" << child << child->objectName()
             << child->parent();
    child->setParent(nullptr);
    child->moveToThread(this);
    qDebug() << "WorkerThread::appendChild" << child << child->objectName()
             << child->parent();
    mChildren.append(child);
    emit childrenChanged();
}

qsizetype WorkerThread::childCount() const
{
    qDebug() << "WorkerThread::childCount";
    return mChildren.count();
}

QObject* WorkerThread::childAt(qsizetype index) const
{
    qDebug() << "WorkerThread::childAt" << index;
    return mChildren.at(index);
}

void WorkerThread::clearChildren()
{
    qDebug() << "WorkerThread::clearChildren";
    mChildren.clear();
    emit childrenChanged();
}

void WorkerThread::replaceChild(qsizetype index, QObject* child)
{
    qDebug() << "WorkerThread::replaceChild" << index << child;
    mChildren.replace(index, child);
    emit childrenChanged();
}

void WorkerThread::removeLastChild()
{
    qDebug() << "WorkerThread::removeLastChild";
    mChildren.removeLast();
    emit childrenChanged();
}

void WorkerThread::run()
{
    qDebug() << "WorkerThread::run" << this << currentThreadId()
             << QThread::currentThread()
             << QThread::currentThread()->objectName();
    // auto ticker = new QTimer();
    // connect(ticker, &QTimer::timeout, this, &WorkerThread::reportThreadInfo);
    // ticker->setInterval(1000);
    // ticker->start();
    // ticker->moveToThread(this);
    exec();
    // ticker->stop();
    // delete ticker;
}

void WorkerThread::reportThreadInfo()
{
    qDebug() << "WorkerThread::reportThreadInfo" << this << currentThreadId()
             << QThread::currentThread()
             << QThread::currentThread()->objectName();
}

void WorkerThread::appendChildWrapper(QQmlListProperty<QObject>* list,
                                      QObject* child)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        self->appendChild(child);
    }
}

qsizetype WorkerThread::childCountWrapper(QQmlListProperty<QObject>* list)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        return self->childCount();
    }
    return 0;
}

QObject* WorkerThread::childAtWrapper(QQmlListProperty<QObject>* list,
                                      qsizetype index)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        return self->childAt(index);
    }
    return nullptr;
}

void WorkerThread::clearChildrenWrapper(QQmlListProperty<QObject>* list)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        self->clearChildren();
    }
}

void WorkerThread::replaceChildWrapper(QQmlListProperty<QObject>* list,
                                       qsizetype index, QObject* child)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        self->replaceChild(index, child);
    }
}

void WorkerThread::removeLastChildWrapper(QQmlListProperty<QObject>* list)
{
    auto self = qobject_cast<WorkerThread*>(list->object);
    if (self) {
        self->removeLastChild();
    }
}
