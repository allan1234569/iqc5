#ifndef EDITPROJECT_H
#define EDITPROJECT_H
#include "Model/Project.h"
#include <QDialog>
#include <QTableWidget>
#include <QListWidget>
#include <QCloseEvent>
#include "MainWindow.h"

class Project;

namespace Ui {
class EditProject;
}

class EditProject : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditProject(QWidget *parent = 0);
    ~EditProject();
    void Init();

    void SetModel(Project project);

    //MainWindow *mainWindow;

private:

    void keyPressEvent (QKeyEvent * keyevent);
    void closeEvent(QCloseEvent* event);

    QLineEdit *lineEdit;
    QListWidget *listWidget;

    
private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_inputCategory_currentIndexChanged(int index);

    void on_inputNum_valueChanged(int arg1);

    void on_inputLevel_valueChanged(int arg1);

    void on_inputMaterial_currentIndexChanged(int index);

    void on_inputTestType_currentIndexChanged(int index);

    void on_inputStandard_currentIndexChanged(int index);

    void on_inputSubject_currentIndexChanged(int index);

    void on_btnImport_clicked();

    void on_txtProjectName_textChanged(const QString &arg1);

    void on_inputDeviceName_textChanged(const QString &arg1);

    void on_inputMethodName_textChanged(const QString &arg1);

    void on_txtEnglishName_textChanged(const QString &arg1);

    void on_txtCustomName_textChanged(const QString &arg1);

    void on_inputHospital_currentIndexChanged(int index);
    void on_inputSection_currentIndexChanged(int index);
    void on_inputOffice_currentIndexChanged(int index);

    void on_lstProjectName_clicked(const QModelIndex &index);



private:
    Ui::EditProject *ui;
    QString projectId;
    QString categoryId;
    QString materialId;
    QVector<QTableWidget *> tables;

    bool eventFilter(QObject *object, QEvent *e);
    void GetByDic();

};

#endif // EDITPROJECT_H
