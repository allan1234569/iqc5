#ifndef POPBOX_H
#define POPBOX_H

#include <QWidget>

namespace Ui {
class PopBox;
}

class PopBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit PopBox(QWidget *parent = 0);
    ~PopBox();
    void SetText(QString text);
    int no;
    int level;
    
private:
    Ui::PopBox *ui;
};

#endif // POPBOX_H
