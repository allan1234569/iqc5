#ifndef DATERANGEDIALOG_H
#define DATERANGEDIALOG_H

#include <QDialog>

namespace Ui {
class DateRangeDialog;
}

class DateRangeDialog : public QDialog
{
    Q_OBJECT

public:
    typedef enum State{
        Calculate,
        Cancel
    }State;

public:
    explicit DateRangeDialog(QWidget *parent = 0);
    ~DateRangeDialog();

    QString m_startDate;
    QString m_endDate;
    State m_state;

private slots:
    void on_Cancel_PushButton_clicked();

    void on_Calculate_PushButton_clicked();

    void on_startDateEdit_dateChanged(const QDate &date);

    void on_endDateEdit_dateChanged(const QDate &date);

private:
    Ui::DateRangeDialog *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);

    bool isOk;
};

#endif // DATERANGEDIALOG_H
