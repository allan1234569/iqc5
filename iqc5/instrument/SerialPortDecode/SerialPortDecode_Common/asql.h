#ifndef ASQL_H
#define ASQL_H

#include <QSqlDatabase>
#include <QSqlQuery>

    typedef enum ErrorType {
        UnkownError = 0,
        SelectError,
        InsertError,
        UpdateError,
        ConnectionError,
        StatementError,
        UnkownDeviceError
    }ErrorType;

class ASql
{


public:
    ASql();
    void setHostName(const QString &hostname);

    void init();

    bool open();

    void close();

    bool isOpened();

    /**
     * @brief sendResult
     * @param as_sampleNo   标本号
     * @param as_itemCode   项目代号
     * @param as_dataTime   日期
     * @param as_result
     * @param as_instr
     * @param as_labNo
     * @param as_resultDateTime
     * @return 返回四种值-1,0,1
     *          -1 数据库打开失败
     *          0  发送结果成功
     *          1  查询错误
     */
    int sendResult(QString as_sampleNo, QString as_itemCode, QString as_result, QString as_instr, QString as_labNo, QString as_resultDateTime);

    void handleError(ErrorType type, QString SqlStatement);

private:
    QSqlDatabase db;

    int m_lastErrorType;

    bool m_bOpened;
};

#endif // ASQL_H
