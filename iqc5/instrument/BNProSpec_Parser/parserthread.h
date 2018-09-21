#ifndef PARSERTHREAD_H
#define PARSERTHREAD_H

#include <QThread>
#include <QSqlDatabase>
#include "myProject.h"

#include "Result.h"
#include "TestType.h"
#include "Project.h"
#include "Device.h"

#include "global.h"

extern QSqlDatabase db;



class parserThread : public QThread
{
    Q_OBJECT
public:
    explicit parserThread(QObject *parent = 0);
    parserThread(QObject *parent, QString path);

protected:
    void getDeviceInfo();
    QByteArray parser(const QString &content);
    void parserFieldValue(MyProject &pro, const QString &parsedString);
    void parserSampleId(MyProject &pro, const QString &parsedString);
    QStringList	split(const QString &desStr, const QRegularExpression & re, QString::SplitBehavior behavior = QString::KeepEmptyParts) const;
    void getFromJsonData(const QByteArray &jsonData);
    void CommitToDatabase();

signals:

public slots:

protected:
    void run();

private:
    QVector<TestType*> TestTypeVec;
    QVector<Project*> ProjectVec;
    QVector<Result*> ResultVec;
    Device device;
    QString filePath;
};

#endif // PARSERTHREAD_H
