#ifndef MANAGEPROJECT_H
#define MANAGEPROJECT_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class ManageProject;
}

class ManageProject : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ManageProject(QWidget *parent = 0);
    ~ManageProject();

    void InitProjects();
    
private slots:
    void on_inputKeyword_textChanged(const QString &arg1);

    void on_list_itemDoubleClicked(QListWidgetItem *item);


    void OnBtnTableEditClicked();
    void OnBtnTableEditDataClicked();

    void OnBtnTableDeleteClicked();

    void on_btnNew_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::ManageProject *ui;
};

#endif // MANAGEPROJECT_H
