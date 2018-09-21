#ifndef ASQL_H
#define ASQL_H

#include <QSqlDatabase>
#include <QSqlQuery>

class ASql
{
    typedef enum ErrorType {
        SelectError,
        InsertError,
        UpdateError,
        ConnectionError,
        StatementError,
        UnkownError
    }ErrorType;

public:
    ASql();
    void setHostName(const QString &hostname);

    void init();

    bool open();

    void close();

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
     *          2  仪器信息配置错误
     */
    int sendResult(QString as_sampleNo, QString as_itemCode, QString as_result, QString as_instr, QString as_labNo, QString as_resultDateTime) const;

    QStringList getItems();

    void handleError(const QString errorString);



private:
    QSqlDatabase db;
};

#endif // ASQL_H
