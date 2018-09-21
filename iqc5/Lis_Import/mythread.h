#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "lis.h"

#define MAX_SIZE 20*1024*1024      //200M      最大可以设置为208M即208*1024*1024

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = 0);
    ~myThread();

    bool extract(const QString& in_file_path, const QString &out_file_path);
    void import(Lis *lis);

public:
    QString in_path;
    QString out_path;
    Lis *lis;
signals:
    void importCompleted();
    void importFailed();
    void unCompressCompleted();
    void unCompressFailed();

public slots:


    // QThread interface
protected:
    void run();
};

#endif // MYTHREAD_H
