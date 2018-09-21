#ifndef PARSERTHRED_H
#define PARSERTHRED_H

#include <QThread>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QPainter>
#include <QHostAddress>
#include <QTcpSocket>

//#include "../../iqc5/Model/TestType.h"
//#include "../../iqc5/Model/Project.h"
//#include "../../iqc5/Model/Result.h"
#include "../../iqc5/iqc5/Model/Device.h"

#include "myProject.h"



class parserThred : public QThread
{
    Q_OBJECT
public:
    explicit parserThred(QObject *parent = 0);
    parserThred(QObject *parent, const QStringList &files);
    ~parserThred();


    QString captureData(const QStringList &files) const;
    void parser(const QString &content);
    QStringList	split(const QString &desStr, const QRegularExpression & re, QString::SplitBehavior behavior = QString::KeepEmptyParts) const;
    void formatStr(QString &dataStr);
    QByteArray convertToJson();
    void getConfigInfo();

    //QRENCODE MODEL
public:
    void setString(QString str);
    bool saveImage(QString filename,int size);
private:
    void draw(QPainter &painter, int height, int width);

private:
    QVector<MyProject*> ProjectVec;
    Device device;
    QHostAddress hostAddress;
    int hostPort;
signals:

public slots:

protected:
    void run();

private:
    QStringList m_files;

};

#endif // PARSERTHRED_H
