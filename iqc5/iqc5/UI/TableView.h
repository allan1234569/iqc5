#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QDialog>
#include "Model/Result.h"

namespace Ui {
class TableView;
}

class TableView : public QDialog
{
    Q_OBJECT
    
public:
    explicit TableView(QWidget *parent = 0);
    ~TableView();

    void ShowTable(int rowCount, QVector< QVector<Result> > allData);
    
private:
    Ui::TableView *ui;
};

#endif // TABLEVIEW_H
