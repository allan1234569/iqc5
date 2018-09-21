#ifndef ADECODEBASE_H
#define ADECODEBASE_H

#include <QStringList>

class ADecodeBase
{
public:
    ADecodeBase();

    /**
     * @brief CutAstmCheckSum
     * @param as_data
     * @return
     */
    int CutAstmCheckSum(QString &as_data) const;

    /**
     * @brief CutZeroChar
     * @param as_data
     * @return
     */
    QString CutZeroChar(QString as_data) const;


    /**
     * @brief DivSampleNos
     * @param as_str
     * @param as_ret
     * @return
     */
    int DivSampleNos(QString as_str, QString &as_ret) const;

    /**
     * @brief isDigitStr    判断字符串是否为纯数字
     *                      如果给定字符串是纯数字返回真，否则返回假
     * @param src
     * @return
     */
    bool IsDigitStr(QString as_src) const;

    /**
     * @brief GetBlankArray
     * @param as_str
     * @param asl_array
     * @return
     */
    int GetBlankArray(QString as_str, QStringList &asl_array) const;

    /**
     * @brief GetAscii  获取字符串中的第一个字符的ASCII码
     * @param ab_data   目标字符串
     * @return
     */
    int GetAscii(QByteArray ab_data)const;

    /**
     * @brief GetResult
     * @param as_result
     * @return
     */
    QString GetResult(QString as_result) const;

    /**
     * @brief GetField
     * @param as_str
     * @param as_cut
     * @param as_index
     * @return
     */
    QString GetField(QString as_str, QString as_cut, quint32 as_index) const;

    /**
     * @brief GetFileContent    获取文件内容
     * @param as_file           文件名
     * @return
     */
    QString GetFileContent(QString as_file) const;

    /**
     * @brief GetLine       获取指定行的内容
     * @param as_str        传入的字符串
     * @param as_lineNumber 指定行号
     * @return              返回as_lineNumber行的内容
     */
    QString GetLine(QString as_str, int as_lineNumber = 0) const;

    /**
     * @brief GetMonth
     * @param as_month  月份的缩写，如1月份表示为”JAN",返回值则为1
     * @return  如果返回0，表示所提供的月份信息不正确，否则对应的月份值
     */
    int GetMonth(QString as_month) const;

    /**
     * @brief GetSeg    截取数据段
     * @param as_data   传入的数据
     * @param as_stx    数据段起始字符串
     * @param as_etx    数据段结束字符串
     * @param as_ret    截取到的数据保存在传入的此参数中
     * @return          返回值，有四个值-2，-1，0，1
     *                  -2表示给定的字符串（as_data）中找不到起始字符串（as_stx）
     *                  -1表示传入的参数as_stx为空
     *                  0表示正确截取字符串
     *                  1表示在给定的字符串（as_data）中没有找到结束字符串（as_etx），但是返回了起始字符串（as_stx）之后的所有内容
     */
    int GetSeg(QString &as_data, QString as_stx, QString as_etx, QString &as_ret);

    /**
     * @brief GetSeg    根据给定字符串中的空格将字符串中的数据保存成数组
     * @param as_str    传入的字符串
     * @param asl_list  数据保存在此参数中
     * @return          返回数组大小
     */
    int GetSeg(QString as_str, QStringList &asl_list);

    /**
     * @brief HexToDec
     * @param as_hexStr
     * @return
     */
    int HexToDec(QString as_hexStr) const;

    /**
     * @brief PutArrayBlank
     * @param as_str
     * @param asl_list
     * @return
     */
    int PutArrayBlank(QString as_str, QStringList &asl_list);

    /**
     * @brief PutStrToArray 将字符串按步进值存入数据
     * @param as_str        字符串
     * @param ai_step       步进值，该值小于等于0时为一组
     * @param asl_list      数组
     * @return
     */
    int PutStrToArray(QString as_str, int ai_step, QStringList &asl_list);

    /**
     * @brief PutStrToArray 根据给定子字符串进行分割，保存到数组
     * @param as_str        数据字符串
     * @param as_cut        子字符串
     * @param asl_list      数组
     * @return
     */
    int PutStrToArray(QString as_str, QString as_cut, QStringList &asl_list);

    /**
     * @brief replace
     * @param as_str
     * @param ac_before
     * @param ac_after
     * @return
     */
    QString Replace(QString as_str, const char *ac_before, const char *ac_after);

    /**
     * @brief ReplaceZeroChar   将空字符替换成ASCII为1的字符
     * @param ac_str
     * @return
     */
    char *ReplaceZeroChar(const char *ac_str);

    /**
     * @brief ReplaceZeroChar
     * @param ac_str
     * @param ai_char
     * @return
     */
    char *ReplaceZeroChar(const char *ac_str, int ai_char);

    /**
     * @brief TransEResult
     * @param as_result
     * @return
     */
    QString TransEResult(QString as_result) const;

    /**
     * @brief TransNResult
     * @param as_result
     * @return
     */
    QString TransNResult(QString as_result) const;

    /**
     * @brief TransUrineResult
     * @param as_result
     * @return
     */
    QString TransUrineResult(QString as_result) const;

};

#endif // ADECODEBASE_H
