#include "daterangedialog.h"
#include "ui_daterangedialog.h"
#include <QMessageBox>
#include <QDebug>

DateRangeDialog::DateRangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateRangeDialog)
{
    ui->setupUi(this);

    QDate date;
    date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),1);
    ui->startDateEdit->setDate(date);

    date.setDate(QDate::currentDate().year(),QDate::currentDate().month(),QDate::currentDate().daysInMonth());
    ui->endDateEdit->setDate(date);

    ui->Cancel_PushButton->setFocus();

    isOk = false;

}

DateRangeDialog::~DateRangeDialog()
{
    delete ui;
}

void DateRangeDialog::on_Cancel_PushButton_clicked()
{
    isOk = false;
    this->close();
}

void DateRangeDialog::on_Calculate_PushButton_clicked()
{

    if(ui->startDateEdit->date() > ui->endDateEdit->date())
    {
        QMessageBox msgbox;
        msgbox.setWindowIcon(this->windowIcon());
        msgbox.setWindowTitle("日期设置错误");
        msgbox.setText("结束日期不能早于起始日期");
        msgbox.setStandardButtons(QMessageBox::Ok);
        msgbox.setButtonText(QMessageBox::Ok, "确定");
        msgbox.exec();
        return;
    }
    isOk = true;
    this->close();
}

void DateRangeDialog::on_startDateEdit_dateChanged(const QDate &date)
{
    m_startDate = date.toString("yyyy-MM-dd");
}

void DateRangeDialog::on_endDateEdit_dateChanged(const QDate &date)
{
    m_endDate = date.toString("yyyy-MM-dd");
}

void DateRangeDialog::closeEvent(QCloseEvent *e)
{
    if (isOk)
    {
        m_state = Calculate;
    }
    else
    {
        m_startDate = Cancel;
    }

    QDialog::closeEvent(e);
}
