#include "parserthred.h"
#include <QFile>
#include<QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QVector>
#include <QImage>

#include "global.h"

extern QSettings *settings;
extern ClientSocket *client;

parserThred::parserThred(QObject *parent) :
    QThread(parent)
{
}

parserThred::~parserThred()
{
}

parserThred::parserThred(QObject *parent, const QStringList &files) :
    QThread(parent),m_files(files)
{
}

void parserThred::parser(const QString &content)
{
    QString dataTime, sampleId, testTypeCode;
    if(content.contains(QRegularExpression("<STX>\\dR")))
    {
        QStringList list = split(content,QRegularExpression("<CR><ETX>[0-9a-zA-Z]<CR><LF>"));
        foreach (QString str, list) {
            QStringList tempList = split(str,QRegularExpression("\\n"));
            foreach (QString line, tempList) {
                if( line.contains(QRegularExpression("<STX>\\dH")) )
                {
                    QRegularExpression regH("\\|\\d+<CR>");
                    QRegularExpressionMatch rm = regH.match(line);
                    if(rm.hasMatch())
                    {
                       dataTime = rm.capturedTexts().at(0);
                       dataTime.remove("|");
                       dataTime.remove("<CR>");
                    }
                }
                else if( line.contains(QRegularExpression("<STX>\\dO")) )//解析样本号
                {
                    QRegularExpression regO("O\\|(\\d)+\\|(\\d+)\\|\\d+\\|\\^+\\d+\\^+(\\w+)\\^+\\d+");
                    QRegularExpressionMatch rm = regO.match(line);
                    if(rm.hasMatch())
                    {
                        rm.capturedTexts().at(1);//子项目编号
                        sampleId = rm.capturedTexts().at(2);//样本号
                        testTypeCode = rm.capturedTexts().at(3);//检测项目
                    }
                }
                else if( line.contains(QRegularExpression("<STX>\\dR")) )
                {/*4R|1|^^^1^IgG^400^^F|15.2|g/l|7 TO 16 g/l|||F||||20140217102804<CR><ETX>9C<CR><LF>*/
                    QRegularExpression regR("R\\|\\d+\\|\\^+\\d+\\^+(\\w+)\\^+\\d+\\^+\\w+\\|+(\\d+.\\d+)");
                    QRegularExpressionMatch rm = regR.match(line);
                    if(rm.hasMatch())
                    {
                        QString testType = rm.capturedTexts().at(1);
                        QString value = rm.capturedTexts().at(2);
                        if(testType == testTypeCode)
                        {
                            MyProject *pro = new MyProject;
                            pro->sampleId = sampleId;
                            pro->testTypeCode = testTypeCode;
                            pro->Value = value.toDouble();
                            pro->DataTime = dataTime;
                            ProjectVec.push_back(pro);

                            testTypeCode.clear();
                            sampleId.clear();
                        }
                    }
                }
            }
        }
    }
}

QStringList parserThred::split(const QString &desStr, const QRegularExpression &re, QString::SplitBehavior behavior) const
{
    return desStr.split(re,behavior);
}

void parserThred::formatStr(QString &dataStr)
{
    QString tStr = dataStr;
    dataStr.clear();
    QStringList list = tStr.split("\r\n");
    foreach (QString str, list) {
        if(str.contains("<ENQ>") || str.contains("<STX>") || str.contains("<EOT>"))
        {
            str = str.right( str.length() - str.indexOf("<"));
            str.append("\r\n");
            dataStr.append(str);
        }
    }
}

QByteArray parserThred::convertToJson()
{
    QJsonDocument jsonDocment;
    QJsonArray jsonArray;
    for(int i = 0; i < ProjectVec.size(); i++ )
    {
        MyProject *pro = ProjectVec.at(i);
        QJsonObject jsonObject;
        jsonObject.insert("sampleId",pro->sampleId);
        jsonObject.insert("testTypeCode",pro->testTypeCode);
        jsonObject.insert("value",QString::number(pro->Value));
        jsonObject.insert("dataTime",pro->DataTime);
        jsonObject.insert("deviceName",device.DeviceName);
        jsonObject.insert("modelName",device.ModelName);
        jsonObject.insert("brandName",device.BrandName);
        jsonObject.insert("deviceId",device.DeviceId);
        jsonObject.insert("modelId",device.ModelId);
        jsonObject.insert("brandId",device.BrandId);
        jsonArray.insert(i,jsonObject);
    }
    jsonDocment.setArray(jsonArray);
    QByteArray jsonData;
    if( !jsonDocment.isEmpty() )
    {
        jsonData= jsonDocment.toJson();
    }

    return jsonData;
}

void parserThred::getConfigInfo()
{
    hostAddress.setAddress(settings->value(QString("SERVER/ip")).toString());
    hostPort = settings->value(QString("SERVER/port")).toInt();
    device.DeviceName = settings->value(QString("DEVICE/DeviceName")).toString();
    device.ModelName = settings->value(QString("DEVICE/ModelName")).toString();
    device.BrandName = settings->value(QString("DEVICE/BrandName")).toString();

    device.DeviceId = settings->value(QString("DEVICE/DeviceId")).toString();
    device.ModelId = settings->value(QString("DEVICE/ModelId")).toString();
    device.BrandId = settings->value(QString("DEVICE/BrandId")).toString();
}

void parserThred::setString(QString str)
{
//    string = str;
//    if( qr != NULL)
//    {
//        QRcode_free(qr);
//    }

//    qr = QRcode_encodeString(string.toStdString().c_str(),
//                             1,
//                             QR_ECLEVEL_L,
//                             QR_MODE_8,
//                             1);
}

bool parserThred::saveImage(QString filename, int size)
{
    return false;
//    if( size != 0 && !filename.isEmpty() )
//    {
//        QImage image(size,size,QImage::Format_Mono);
//        QPainter painter(&image);
//        QColor background(Qt::white);
//        painter.setBrush(background);
//        painter.setPen(Qt::NoPen);
//        painter.drawRect(0,0,size,size);
//        if( qr != NULL)
//        {
//            draw(painter,size,size);
//        }
//        return image.save(filename);
//    }
//    else
//    {
//        return false;
//    }
}

void parserThred::draw(QPainter &painter, int height, int width)
{
//    QColor foreground(Qt::black);
//    painter.setBrush(foreground);
//    const int qr_width = qr->width > 0 ?qr->width : 1;
//    double scale_x = width / qr_width;
//    double scale_y = height / qr_width;
//    for(int  y = 0; y < qr_width; y++)
//    {
//        for(int x = 0; x < qr_width; x++)
//        {
//            unsigned char b = qr->data[y*qr_width + x];
//            if( b & 0x01)
//            {
//                QRect r(x * scale_x, y *scale_y, scale_x, scale_y);
//                painter.drawRects(&r,1);

//            }
//        }
//    }
}

void parserThred::run()
{
    getConfigInfo();
    if( m_files.empty() )
        return;
    else
    {
        QString parserStr = captureData(m_files);
        formatStr(parserStr);

        ProjectVec.clear();
        QStringList list = parserStr.split("<EOT>\r\n");
        foreach (QString str, list) {
            parser(str);
        }
        QByteArray jsonStr = convertToJson();
        jsonStr.prepend("#<DataStart ");
        jsonStr.append(" DataEnd>#");
        client->sendMessage(jsonStr);
    }
}


QString parserThred::captureData(const QStringList &files) const
{
    QDir dir;
    QString allData;

    foreach (QString str, files) {
        str = str.left(str.indexOf("\r\n"));
        QFile file(dir.absolutePath() + QString("/received/")+str); //新接收到的文件
        if( !file.open(QIODevice::ReadOnly) )
        {
            return "";
        }
        QByteArray content;
        content =  file.readAll();

        QFile srcfile(dir.absolutePath() + QString("/rawdata/") +str);  //上次的文件
        if( srcfile.exists() )
        {
            if(!srcfile.open(QIODevice::ReadWrite))
            {
                file.close();
                return "";
            }
            QByteArray lastLineStr;
            while( !srcfile.atEnd() )
            {
                lastLineStr = srcfile.readLine();
            }


            srcfile.write(content);
            srcfile.close();

            content = content.right(content.length() - content.indexOf(lastLineStr) -lastLineStr.length());
            allData += content;
        }
        else
        {
            if(!srcfile.open(QIODevice::ReadWrite))
            {
                file.close();
                return "";
            }
            srcfile.write(content);
            srcfile.close();
            allData += content;
        }

        file.close();
    }

    return allData;
}
