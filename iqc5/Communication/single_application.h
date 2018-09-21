#ifndef SINGLE_APPLICATION_H
#define SINGLE_APPLICATION_H

#include <QApplication>
#include <QFile>
#include <QMutex>


#define LOCKFILE

class SingleApplication : public QApplication
{
    Q_OBJECT
public:

    SingleApplication(int &argc, char *argv[]);
    ~SingleApplication();
    bool isRunning();

private:
    bool _isRunning;
    QFile *m_lockFile;
    QMutex m_Mutex;
};

#endif // SINGLE_APPLICATION_H
