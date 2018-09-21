#ifndef W_LUMO_H
#define W_LUMO_H

#include "basewindow.h"

class W_Lumo : public BaseWindow
{
    Q_OBJECT

public:
    W_Lumo(QWidget *parent = 0);
    ~W_Lumo();

    // BaseWindow interface
public:
    void set_TableWidgetHeader();

    void file_decode(const QString as_file, const QString as_path);

    void excel_file_decode(const QString as_filepath);

    void loadConfig();

private slots:
    void on_Import_PushButton_clicked();

private:
    QString m_sSampleNoLabel;
    QString m_sItemNoLabel;
    QString m_sResultLabel;
};

#endif // W_LUMO_H
