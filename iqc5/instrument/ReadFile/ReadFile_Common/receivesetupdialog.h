#ifndef RECEIVESETUPDIALOG_H
#define RECEIVESETUPDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QKeyEvent>
#include <QTableWidgetItem>

#include "Delegate/trackdelegate.h"

namespace Ui {
class ReceiveSetupDialog;
}

class ReceiveSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveSetupDialog(QWidget *parent = 0);
    ~ReceiveSetupDialog();

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

private:


private:
    Ui::ReceiveSetupDialog *ui;

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
};

#endif // RECEIVESETUPDIALOG_H
