#ifndef MANAGEDATAIMPORT_H
#define MANAGEDATAIMPORT_H

#include <QDialog>
#include <QListWidgetItem>
#include "Delegate/trackdelegate.h"

namespace Ui {
class ManageDataImport;
}

class ManageDataImport : public QDialog
{
    Q_OBJECT

public:
    explicit ManageDataImport(QWidget *parent = 0);
    ~ManageDataImport();

    void init();

    void loadTableContents();

    void saveTableContents();


private slots:
    void on_Cancel_PushButton_clicked();

    void on_Save_PushButton_clicked();

    void on_Ensure_PushButton_clicked();

    void on_Add_ToolButton_clicked();

    void on_Delete_ToolButton_clicked();

    void slt_Editing(const QString &txt);

    void slt_EditFinished();

    void slt_listWidget_Clicked(QListWidgetItem *item);

    void on_tableWidget_itemSelectionChanged();

    void on_BtnSelectPath_clicked();

private:


private:
    Ui::ManageDataImport *ui;
    QListWidget *listWidget;
    QStringList m_TestTypes;

    TrackDelegate *projectDelegate;
    TrackDelegate *densityDelegate;

    bool b_isEditing;

    // QObject interface
public:
    bool eventFilter(QObject *target, QEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *keyevent);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *e);
};

#endif // MANAGEDATAIMPORT_H
