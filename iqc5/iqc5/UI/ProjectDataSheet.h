#ifndef PROJECTDATASHEET_H
#define PROJECTDATASHEET_H

#include <QWidget>
#include <Project.h>
#include <QTreeWidgetItem>

namespace Ui {
class ProjectDataSheet;
}

class ProjectDataSheet : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectDataSheet(QWidget *parent = 0);
    ~ProjectDataSheet();

    void initProject();

    void initTableWidget();

private:
    void showProjectDetail();

private slots:
    void on_export_Btn_clicked();

    void on_close_Btn_clicked();

    void on_inputKeyword_textChanged(const QString &arg1);

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::ProjectDataSheet *ui;

    Project currentProject;
};

#endif // PROJECTDATASHEET_H
