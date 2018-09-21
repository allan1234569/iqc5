#include "EditProject.h"
#include "ui_EditProject.h"
#include "Service/CategoryService.h"
#include "Service/TestTypeService.h"
#include "Service/TestParamService.h"
#include "Service/MaterialService.h"
#include "Service/ReagentService.h"
#include "Service/DeviceService.h"
#include "Service/ProjectService.h"
#include "Service/MethodService.h"
#include "Service/UnitService.h"
#include "ManageProject.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include <QKeyEvent>
#include <QLineEdit>
#include "MainWindow.h"

EditProject::EditProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProject)
{
    //mainWindow = 0;

    ui->setupUi(this);

    Init();
}

EditProject::~EditProject()
{
    delete ui;
}

void EditProject::Init()
{
    projectId = "";
    this->setWindowTitle("新建项目");


    //初始化科目下拉框
    CategoryService *categoryService = new CategoryService();
    QVector<Category> subjects = categoryService->GetCategories();
    ui->inputSubject->clear();
    Category category;
    foreach(category, subjects)
    {
        ui->inputSubject->addItem(category.CategoryName, category.CategoryId);
    }

    QString firstSubjectId = ui->inputSubject->itemData(0).toString();
    QVector<Category> categories = categoryService->GetCategories(firstSubjectId);

    ui->inputCategory->clear();
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }

//    //初始化设备下拉框
//    DeviceService *deviceService = new DeviceService();
//    QVector<Device> devices = deviceService->GetAll(ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toInt(),"");

//    ui->inputDevice->clear();
//    Device device;
//    foreach(device, devices)
//    {
//        ui->inputDevice->addItem(device.model, device.Id);
//    }


    //初始化医院下拉框
    UnitService *unitService;unitService = new UnitService();
    QVector<Unit> hospitals = unitService->GetByParentId("");
    ui->inputHospital->clear();

    foreach(Unit hospital, hospitals)
    {
        ui->inputHospital->addItem(hospital.UNITNAME, hospital.UNITID);
    }
    ui->inputHospital->setCurrentIndex(0);

    QString firstHospitalId = ui->inputHospital->itemData(0).toString();

    QVector<Unit> sections = unitService->GetByParentId(firstHospitalId);

    ui->inputSection->clear();
    foreach(Unit section, sections)
    {
        ui->inputSection->addItem(section.UNITNAME, section.UNITID);
    }
    ui->inputSection->setCurrentIndex(0);

    QString firstSectionId = ui->inputSection->itemData(0).toString();

    QVector<Unit> offices = unitService->GetByParentId(firstSectionId);

    ui->inputOffice->clear();
    foreach(Unit office, offices)
    {
        ui->inputOffice->addItem(office.UNITNAME, office.UNITID);
    }
    ui->inputOffice->setCurrentIndex(0);

    QString firstOfficeId = ui->inputOffice->itemData(0).toString();

    QVector<Unit> groups = unitService->GetByParentId(firstOfficeId);

    ui->inputGroup->clear();
    foreach(Unit group, groups)
    {
        ui->inputGroup->addItem(group.UNITNAME, group.UNITID);
    }
    ui->inputGroup->setCurrentIndex(0);


    ui->lstProjectName->setVisible(false);
}

bool EditProject::eventFilter(QObject*obj,QEvent*event)
{
    return QObject::eventFilter(obj,event);
}


void EditProject::SetModel(Project project)
{
    if(project.ProjectId != 0)
    {
        ui->ckbOnOpen->setVisible(false);

        projectId = project.ProjectId;
        this->setWindowTitle("修改项目");

        for(int i=0;i<ui->inputSubject->count();i++)
        {
            if(project.testType.SubjectId == ui->inputSubject->itemData(i).toString())
            {
                ui->inputSubject->setCurrentIndex(i);
                break;
            }
        }


        for(int i=0;i<ui->inputCategory->count();i++)
        {
            if(project.testType.CategoryId == ui->inputCategory->itemData(i).toString())
            {
                ui->inputCategory->setCurrentIndex(i);
                break;
            }
        }

//        for(int i=0;i<ui->inputMaterial->count();i++)
//        {
//            if(project.material.Id== ui->inputMaterial->itemData(i).toString())
//            {
//                ui->inputMaterial->setCurrentIndex(i);
//                break;
//            }
//        }
//        for(int i=0;i<ui->inputReagent->count();i++)
//        {
//            if(project.ReagentId== ui->inputReagent->itemData(i).toString())
//            {
//                ui->inputReagent->setCurrentIndex(i);
//                break;
//            }
//        }
        for(int i=0;i<ui->inputTestType->count();i++)
        {
            if(project.testType.TestTypeId== ui->inputTestType->itemData(i).toString())
            {
                ui->inputTestType->setCurrentIndex(i);
                break;
            }
        }
        for(int i=0;i<ui->inputStandard->count();i++)
        {
            if(project.StandardId== ui->inputStandard->itemData(i).toString())
            {
                ui->inputStandard->setCurrentIndex(i);
                break;
            }
        }
//        for(int i=0;i<ui->inputMethod->count();i++)
//        {
//            if(project.Method== ui->inputMethod->itemText(i))
//            {
//                ui->inputMethod->setCurrentIndex(i);
//                break;
//            }
//        }
//        for(int i=0;i<ui->inputDevice->count();i++)
//        {
//            if(project.device.Id == ui->inputDevice->itemData(i).toString())
//            {
//                ui->inputDevice->setCurrentIndex(i);
//                break;
//            }
//        }



        ui->txtProjectName->setText(project.ProjectName);
        ui->txtEnglishName->setText(project.EnglishName);
        ui->txtCustomName->setText(project.CustomName);
        ui->inputMethodName->setText(project.MethodName);
        ui->inputDeviceName->setText(project.DeviceName);

        //ui->inputNum->setValue(project.num);
        ui->inputLevel->setValue(project.level);

        //ui->txtCreator->setText(project.Creator);


    }


    ui->lstProjectName->setVisible(false);
}

void EditProject::on_btnOK_clicked()
{
    ProjectService *projectService; projectService = new ProjectService();

    Project project;
    project.ProjectId = projectId;
    if(ui->txtProjectName->text().length()== 0)
    {
        project.ProjectName = ui->inputTestType->itemText(ui->inputTestType->currentIndex()) + QString("%1").arg(QDate::currentDate().toString("yyyyMMdd"));
    }
    else
    {
        project.ProjectName = ui->txtProjectName->text();
    }
    if(project.ProjectId == 0 && projectService->SearchProject("","",project.ProjectName,"","","","").count() > 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("今天已经开展过该项目, 不能重复开展"));
        return;
    }
    //project.material.Id =ui->inputMaterial->itemData(ui->inputMaterial->currentIndex()).toInt();
    //project.ReagentId =ui->inputReagent->itemData(ui->inputReagent->currentIndex()).toInt();

    TestTypeService *typeService = new TestTypeService();
    QString typeId = ui->inputTestType->itemData(ui->inputTestType->currentIndex()).toString();
    TestType type = typeService->GetById(typeId);
    project.testType.TestTypeId = type.TestTypeId;

    QString standardid = ui->inputStandard->itemData(ui->inputStandard->currentIndex()).toString();
    project.StandardId = standardid;

    TestParamService *testParamService = new TestParamService();
    TestParam testParam = testParamService->GetByTestTypeAndStandard(type.TestTypeId, standardid);
    project.CV = testParam.CV;
    project.Bias = testParam.Bias;
    project.TEa = testParam.TEa;
    //project.Method = ui->inputMethodName->text();
    project.DeviceName = ui->inputDeviceName->text();
    //project.num = ui->inputNum->text().toInt();
    project.level = ui->inputLevel->text().toInt();

    project.EnglishName = ui->txtEnglishName->text();
    project.CustomName = ui->txtCustomName->text();
    //project.Creator = ui->txtCreator->text();


    if(project.ProjectId == 0)
    {
        projectId = projectService->Insert(project);
        QMessageBox::information(this, tr("信息") ,tr("新建成功"));


        if(ui->ckbOnOpen->checkState())
        {
            projectId = "";
        }
        else
        {
            //Project p = projectService->GetById(projectId);
            //SetModel(p);

            this->close();
        }

    }
    else
    {
        projectService->UpdateModel(project);
        QMessageBox::information(this, tr("信息") ,tr("保存成功"));
    }

    ManageProject *f = qobject_cast<ManageProject*>(this->parent());
    if(f!=NULL)
    {
        f->InitProjects();
    }

//    if(this->mainWindow != 0)
//    {
//        if(this->mainWindow->openedProjectWindow!=0)
//        {
//            this->mainWindow->openedProjectWindow->InitProjects();
//        }
//        if(this->mainWindow->openedAnalyzeProjectWindow!=0)
//        {
//            this->mainWindow->openedAnalyzeProjectWindow->InitProjects();
//        }
//        if(this->mainWindow->openedAnalyzeRuleWindow!=0)
//        {
//            this->mainWindow->openedAnalyzeRuleWindow->InitProjects();
//        }
//    }
    //this->close();

}


void EditProject::on_btnCancel_clicked()
{
    this->close();
}

void EditProject::on_inputMaterial_currentIndexChanged(int index)
{
//    materialId =ui->inputMaterial->itemData(index).toString();

//    //初始化项目类型下拉框
//    TestTypeService *typeService = new TestTypeService();
//    QVector<TestType> types = typeService->GetByCategoryIdAndMaterialId(categoryId, materialId);

//    ui->inputTestType->clear();
//    TestType type;
//    foreach(type, types)
//    {
//        ui->inputTestType->addItem(type.Name, type.Id);
//    }

}


void EditProject::on_inputNum_valueChanged(int arg1)
{
    //this->InitResultTable(ui->inputLevel->text().toInt(), ui->inputNum->text().toInt());
}

void EditProject::on_inputLevel_valueChanged(int arg1)
{
    //this->InitResultTable(ui->inputLevel->text().toInt(), ui->inputNum->text().toInt());
}

void EditProject::on_inputTestType_currentIndexChanged(int index)
{
    //初始化标准下拉框
    TestParamService *service = new TestParamService();
    QVector<Standard> standards = service->GetStandard(ui->inputTestType->itemData(ui->inputTestType->currentIndex()).toString());
    ui->inputStandard->clear();
    Standard standard;
    foreach(standard, standards)
    {
        ui->inputStandard->addItem(standard.StandardName, standard.StandardId);
    }

}

void EditProject::on_inputStandard_currentIndexChanged(int index)
{

    QString testTypeId = ui->inputTestType->itemData(ui->inputTestType->currentIndex()).toString();
    QString standardId = ui->inputStandard->itemData(ui->inputStandard->currentIndex()).toString();
    TestParamService *service = new TestParamService();
    TestParam p = service->GetByTestTypeAndStandard(testTypeId, standardId);
    ui->inputDescription->setText(QString("TEa:%1,  CV:%2, Bias:%3 ").arg(p.TEa).arg(p.CV).arg(p.Bias));
}

void EditProject::on_inputSubject_currentIndexChanged(int index)
{
    //初始化亚专业下拉框
    CategoryService *categoryService = new CategoryService();

    QString subjectId = ui->inputSubject->itemData(index).toString();
    QVector<Category> categories = categoryService->GetCategories(subjectId);

    ui->inputCategory->clear();
    Category category;
    foreach(category, categories)
    {
        ui->inputCategory->addItem(category.CategoryName, category.CategoryId);
    }

//    //初始化设备下拉框
//    DeviceService *deviceService = new DeviceService();
//    QVector<Device> devices = deviceService->GetAll(ui->inputCategory->itemData(ui->inputCategory->currentIndex()).toInt(), "");

//    ui->inputDevice->clear();
//    Device device;
//    foreach(device, devices)
//    {
//        ui->inputDevice->addItem(device.model, device.Id);
//    }
}


void EditProject::on_inputCategory_currentIndexChanged(int index)
{

    categoryId =ui->inputCategory->itemData(index).toString();

    //初始化项目类型下拉框
    TestTypeService *typeService = new TestTypeService();
    QVector<TestType> types = typeService->GetByCategoryId(categoryId);

    ui->inputTestType->clear();
    TestType type;
    foreach(type, types)
    {
        ui->inputTestType->addItem(type.TestTypeName, type.TestTypeId);
    }

//    //初始化样品下拉框
//    MaterialService *materialService = new MaterialService();
//    QVector<Material> materials = materialService->GetMaterialsByCategoryId(categoryId);

//    ui->inputMaterial->clear();
//    Material material;
//    foreach(material, materials)
//    {
//        ui->inputMaterial->addItem(material.Name, material.Id);
//    }

//    //初始化试剂下拉框
//    ReagentService *reagentService = new ReagentService();
//    QVector<Reagent> reagents = reagentService->GetReagentsByCategoryId(categoryId);

//    ui->inputReagent->clear();
//    Reagent reagent;
//    foreach(reagent, reagents)
//    {
//        ui->inputReagent->addItem(reagent.Name, reagent.Id);
//    }

//    //初始化方法下拉框
//    MethodService *methodService = new MethodService();
//    QVector<Method> methods = methodService->GetByCategoryId(categoryId);

//    ui->inputMethod->clear();
//    Method method;
//    foreach(method, methods)
//    {
//        ui->inputMethod->addItem(method.Name, method.Id);
//    }
//    ui->inputMethod->view()->setFixedWidth(300);

}

void EditProject::on_btnImport_clicked()
{
    if(projectId == 0)
    {
        QMessageBox::information(this, tr("信息") ,tr("请先保存项目"));
        return;
    }
    QString strFilePath = QFileDialog::getOpenFileName(this,tr("保存为"));

     ProjectService s;
     try
     {
//         s.Update(this->projectId, strFilePath);
//         Project p = s.GetById(this->projectId);
//         SetModel(p);

         QMessageBox::information(this, tr("信息") ,tr("导入数据成功"));
     }
     catch(...)
     {

         QMessageBox::information(this, tr("信息") ,tr("导入数据失败 文件格式不正确"));
     }
}

void EditProject::GetByDic()
{

}


void EditProject::on_inputDeviceName_textChanged(const QString &arg1)
{
    lineEdit=ui->inputDeviceName;
    listWidget=ui->lstProjectName;

    listWidget->setGeometry(lineEdit->geometry().x()+10,lineEdit->geometry().y()+28, lineEdit->geometry().width(), 120);


    listWidget->clear();

    QString dicType = "device";
    QString strFilePath = QString("dic_%1.txt").arg(dicType);
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if (line.indexOf(lineEdit->text()) != -1)
        {
            listWidget->addItem(line);
        }

    }
    file.close();

    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void EditProject::on_inputMethodName_textChanged(const QString &arg1)
{
    lineEdit=ui->inputMethodName;
    listWidget=ui->lstProjectName;

    listWidget->setGeometry(lineEdit->geometry().x()+10,lineEdit->geometry().y()+28, lineEdit->geometry().width(), 120);


    listWidget->clear();

    QString dicType = "method";
    QString strFilePath = QString("dic_%1.txt").arg(dicType);
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if (line.indexOf(lineEdit->text()) != -1)
        {
            listWidget->addItem(line);
        }

    }
    file.close();

    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void EditProject::on_txtProjectName_textChanged(const QString &arg1)
{
    lineEdit=ui->txtProjectName;
    listWidget=ui->lstProjectName;

    listWidget->setGeometry(lineEdit->geometry().x()+10,lineEdit->geometry().y()+28, lineEdit->geometry().width(), 120);


    listWidget->clear();

    QString dicType = "project";
    QString strFilePath = QString("dic_%1.txt").arg(dicType);
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if (line.indexOf(lineEdit->text()) != -1)
        {
            listWidget->addItem(line);
        }

    }
    file.close();

    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void EditProject::on_txtEnglishName_textChanged(const QString &arg1)
{

    lineEdit=ui->txtEnglishName;
    listWidget=ui->lstProjectName;

    listWidget->setGeometry(lineEdit->geometry().x()+10,lineEdit->geometry().y()+28, lineEdit->geometry().width(), 120);


    listWidget->clear();

    QString dicType = "project";
    QString strFilePath = QString("dic_%1.txt").arg(dicType);
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if (line.indexOf(lineEdit->text()) != -1)
        {
            listWidget->addItem(line);
        }

    }
    file.close();

    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void EditProject::on_txtCustomName_textChanged(const QString &arg1)
{
    lineEdit=ui->txtCustomName;
    listWidget=ui->lstProjectName;

    listWidget->setGeometry(lineEdit->geometry().x()+10,lineEdit->geometry().y()+28, lineEdit->geometry().width(), 120);

    listWidget->clear();

    QString dicType = "project";
    QString strFilePath = QString("dic_%1.txt").arg(dicType);
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(NULL, tr("提示信息："), tr("未能打开文件"));
        return;
    }
    QTextStream stream(&file);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if (line.indexOf(lineEdit->text()) != -1)
        {
            listWidget->addItem(line);
        }

    }
    file.close();

    if (listWidget->count() > 0)
    {
        listWidget->setVisible(true);
    }
    else
    {
        listWidget->setVisible(false);
    }
}

void EditProject::keyPressEvent (QKeyEvent * keyevent)
{

    int uKey = keyevent->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);

    if(key == Qt::Key_Escape)
    {
        if(listWidget != NULL)
        {
            listWidget->setVisible(false);
        }
    }
    if(QApplication::focusWidget() != lineEdit || listWidget->count() == 0)
        return;

    int iIndex = listWidget->currentRow();
    if(key == Qt::Key_Up)
    {
        iIndex--;
        if(iIndex < 0) iIndex = 0;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);

    }
    else if (key == Qt::Key_Down)
    {
        iIndex++;
        if(iIndex >= listWidget->count()) iIndex = listWidget->count() - 1;
        QListWidgetItem *pItem = listWidget->item(iIndex);
        listWidget->setCurrentItem(pItem);
    }
    else if (key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        if(listWidget != NULL)
        {
            if(listWidget->currentItem() != NULL)
            {
                QString s = listWidget->currentItem()->text();
                lineEdit->setText(s);
            }
            listWidget->setVisible(false);
        }
    }
}

void EditProject::on_lstProjectName_clicked(const QModelIndex &index)
{
    if(listWidget != NULL && lineEdit != NULL)
    {
        QString s = listWidget->currentItem()->text();
        lineEdit->setText(s);
        listWidget->setVisible(false);
    }
}


void EditProject::on_inputHospital_currentIndexChanged(int index)
{
    //初始化科下拉框
    UnitService *unitService;unitService = new UnitService();
    QString hospitalId = ui->inputHospital->itemData(index).toString();

    QVector<Unit> sections = unitService->GetByParentId(hospitalId);

    ui->inputSection->clear();
    foreach(Unit section, sections)
    {
        ui->inputSection->addItem(section.UNITNAME, section.UNITID);
    }
    ui->inputSection->setCurrentIndex(0);


}

void EditProject::on_inputSection_currentIndexChanged(int index)
{
    //初始化室下拉框
    UnitService *unitService;unitService = new UnitService();
    QString sectionId = ui->inputSection->itemData(index).toString();

    QVector<Unit> offices = unitService->GetByParentId(sectionId);

    ui->inputOffice->clear();
    foreach(Unit office, offices)
    {
        ui->inputOffice->addItem(office.UNITNAME, office.UNITID);
    }
    ui->inputOffice->setCurrentIndex(0);


}

void EditProject::on_inputOffice_currentIndexChanged(int index)
{
    //初始化组下拉框
    UnitService *unitService;unitService = new UnitService();
    QString officeId = ui->inputOffice->itemData(index).toString();

    QVector<Unit> groups = unitService->GetByParentId(officeId);

    ui->inputGroup->clear();
    foreach(Unit group, groups)
    {
        ui->inputGroup->addItem(group.UNITNAME, group.UNITID);
    }
    ui->inputGroup->setCurrentIndex(0);


}

void EditProject::closeEvent(QCloseEvent *event)
{
    MainWindow::canOpen = true;
    event->accept();
}
