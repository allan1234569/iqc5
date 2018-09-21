#ifndef W_A2000_H
#define W_A2000_H

#include "basewindow.h"
#include <QRegularExpression>

class W_A2000 : public BaseWindow
{
    Q_OBJECT

public:
    W_A2000(QWidget *parent = 0);
    ~W_A2000();

    void resetUi();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    /**
     * @brief GetId 根据文件名，得到相应的日期的ID
     * @return      返回一个列表
     */
    void GetId(QString filename);

private slots:
    void on_Import_PushButton_clicked();

    // BaseWindow interface
public:
    void loadConfig();

    // BaseWindow interface
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    qint32 m_nSampleIndex;
    qint32 m_nItemIndex;
    qint32 m_nResultIndex;
    qint32 m_nIdIndex;

    bool m_bOuter_Command;

    QStringList IdMap;  //读取保存已经导入数据库ID号

//    QLineEdit *sampleMin_LineEdit;
//    QLineEdit *sampleMax_LineEdit;
//    QLabel *line_Label;
//    QLabel *TestType_Label;
//    QComboBox *TestType_Combox;

};

#endif // W_A2000_H
