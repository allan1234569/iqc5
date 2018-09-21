#include "ManageProject.h"
#include "ui_ManageProject.h"
#include "Service/ProjectService.h"
#include "UI/EditProject.h"
//#include "UI/EditProjectData.h"
#include "Model/Security.h"

ManageProject::ManageProject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManageProject)
{
    ui->setupUi(this);

    InitProjects();

}

void ManageProject::InitProjects()
{
    ProjectService *service = new ProjectService();
    QString keyword = ui->keyword->text();
    QVector<Project> projects = service->SearchProject("","",keyword,"","","","");
    Project project;

    ui->table->setColumnCount(6);
    ui->table->setRowCount(projects.count());
    QStringList headers;
    headers << tr("专业") << tr("项目") << tr("质控品")<< tr("编辑")<< tr("数据录入")<< tr("删除");
    ui->table->setHorizontalHeaderLabels(headers);
    for(int i=0;i<projects.count();i++)
    {

        ui->table->setItem(i, 0, new QTableWidgetItem(projects[i].testType.CategoryName));
        ui->table->setItem(i, 1, new QTableWidgetItem(projects[i].ProjectName));
        ui->table->setColumnWidth(1,200);
        ui->table->setItem(i, 2, new QTableWidgetItem(projects[i].MaterialName));

        QPushButton *editButton=new QPushButton(tr("编辑"));
        QString s1 = QString("%1").arg(projects[i].ProjectId);
        editButton->setToolTip(s1);
        connect(editButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditClicked()));
        ui->table->setCellWidget(i,3,editButton);

        QPushButton *editDataButton=new QPushButton(tr("数据录入"));
        QString s2 = QString("%1").arg(projects[i].ProjectId);
        editDataButton->setToolTip(s2);
        connect(editDataButton,SIGNAL(clicked()),this,SLOT(OnBtnTableEditDataClicked()));
        ui->table->setCellWidget(i,4,editDataButton);

        QPushButton *deleteButton=new QPushButton(tr("删除"));
        deleteButton->setToolTip(QString("%1").arg(projects[i].ProjectId));
        connect(deleteButton,SIGNAL(clicked()),this,SLOT(OnBtnTableDeleteClicked()));
        ui->table->setCellWidget(i,5,deleteButton);

        ui->table->setColumnHidden(2,true);

        if(QString::compare(Security::userName.toLower(), "admin") != 0)
        {
            ui->table->setColumnHidden(3,true);
            ui->table->setColumnHidden(5,true);
        }
    }
    ui->table->resizeRowsToContents();
}

ManageProject::~ManageProject()
{
    delete ui;
}

void ManageProject::on_inputKeyword_textChanged(const QString &arg1)
{
    InitProjects();
}

void ManageProject::OnBtnTableEditClicked()
{
    QPushButton *pbt = dynamic_cast<QPushButton*>(this->sender());
    if(pbt == 0)
        return;
    int x = pbt->frameGeometry().x();
    int y = pbt->frameGeometry().y();
    QModelIndex index = ui->table->indexAt(QPoint(x,y));
    int row = index.row();
    if(row == -1)
        return;

    ProjectService *service = new ProjectService();
    EditProject *window = new EditProject(this);
    QString id = pbt->toolTip();
    window->SetModel(service->GetById(id));
    window->showMaximized();
}

void ManageProject::OnBtnTableEditDataClicked()
{
    QPushButton *pbt = dynamic_cast<QPushButton*>(this->sender());
    if(pbt == 0)
        return;
    int x = pbt->frameGeometry().x();
    int y = pbt->frameGeometry().y();
    QModelIndex index = ui->table->indexAt(QPoint(x,y));
    int row = index.row();
    if(row == -1)
        return;

//    ProjectService *service = new ProjectService();
//    EditProjectData *window = new EditProjectData(this);
//    QString id = pbt->toolTip();
//    window->SetModel(service->GetById(id));
//    window->showMaximized();
}

void ManageProject::OnBtnTableDeleteClicked()
{
    QPushButton *pbt = dynamic_cast<QPushButton*>(this->sender());
    if(pbt == 0)
        return;
    int x = pbt->frameGeometry().x();
    int y = pbt->frameGeometry().y();
    QModelIndex index = ui->table->indexAt(QPoint(x,y));
    int row = index.row();
    if(row == -1)
        return;

    ProjectService *service = new ProjectService();
    service->DeleteById(pbt->toolTip());
    InitProjects();
}

void ManageProject::on_list_itemDoubleClicked(QListWidgetItem *item)
{
    ProjectService *service; service = new ProjectService();
    QString projectId = item->toolTip();
    EditProject *window = new EditProject(this);
    window->SetModel(service->GetById(projectId));
    window->showMaximized();
}

void ManageProject::on_btnNew_clicked()
{
    EditProject *window = new EditProject(this);
    window->showMaximized();
}

void ManageProject::on_btnRefresh_clicked()
{
    InitProjects();
}
