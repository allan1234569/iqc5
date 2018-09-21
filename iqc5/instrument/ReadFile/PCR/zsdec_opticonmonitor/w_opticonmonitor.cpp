#include "w_opticonmonitor.h"
#include <QClipboard>

W_Opticonmonitor::W_Opticonmonitor(QWidget *parent)
    : BaseWindow(parent)
{
    this->setWindowTitle(tr("PCR_OPTICONMONITOR"));
//    setFileType(BaseWindow::Clipboard);
    init();

    QPushButton *GetData_PushButton = new QPushButton;
    connect(GetData_PushButton,SIGNAL(clicked()),this,SLOT(slt_getClipboard()));
    GetData_PushButton->setText(tr("获取数据"));
    QVBoxLayout *vBoxLayout = qobject_cast<QVBoxLayout*>(ui->widget->layout());
    vBoxLayout->insertWidget(2,GetData_PushButton);
}

W_Opticonmonitor::~W_Opticonmonitor()
{

}

void W_Opticonmonitor::set_TableWidgetHeader()
{

}

void W_Opticonmonitor::on_Import_PushButton_clicked()
{

}

void W_Opticonmonitor::slt_getClipboard()
{
    QClipboard *clipbord = QApplication::clipboard();
    ui->FilePath_LineEdit->setText(clipbord->text());
}
