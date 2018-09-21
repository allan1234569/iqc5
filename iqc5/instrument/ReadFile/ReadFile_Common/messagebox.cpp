#include "messagebox.h"
#include <QIcon>

MessageBox::MessageBox(QWidget *parent):
    QMessageBox(parent)
{
    move(parent->pos().x() + parent->width()/2,
          parent->pos().y() + parent->height()/2
         );
}

MessageBox::MessageBox(const QString title, const QString msg,QWidget *parent)
{
   setGeometry(parent->pos().x() + parent->width()/2,
                       parent->pos().y() + parent->height()/2,
                       width(),
                       height()
                       );

    setWindowIcon(parent->windowIcon());
    setWindowTitle(title);
    setText(msg);
}
