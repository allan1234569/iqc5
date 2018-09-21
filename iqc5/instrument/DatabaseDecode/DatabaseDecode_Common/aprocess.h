#ifndef APROCESS_H
#define APROCESS_H

#include <QThread>

class AProcess : public QThread
{
    Q_OBJECT
public:
    explicit AProcess(QObject *parent = 0);
    ~AProcess();

    void setProgram(const QString &path);

signals:


public slots:



    // QThread interfacecx
protected:
    void run();

private:
    QString m_sProgram;
};

#endif // APROCESS_H
