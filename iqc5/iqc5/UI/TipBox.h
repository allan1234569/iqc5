#ifndef TIPBOX_H
#define TIPBOX_H

#include <QWidget>
#include <QLabel>
#include <QString>

namespace Ui {
class TipBox;
}

class TipBox : public QWidget
{
    Q_OBJECT

public:
    explicit TipBox(QWidget *parent = 0);
    ~TipBox();

    void SetStr(QString text);
    void paintEvent(QPaintEvent *);


private:
    Ui::TipBox *ui;
    QLabel *tip_label;
    QString tip_Str;
};

#endif // TIPBOX_H
