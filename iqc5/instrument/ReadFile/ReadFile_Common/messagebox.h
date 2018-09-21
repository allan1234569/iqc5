#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox :public QMessageBox
{
    Q_OBJECT
public:
    explicit MessageBox(QWidget *parent = 0);
    MessageBox(const QString title, const QString msg, QWidget *parent);

signals:

public slots:

};

#endif // MESSAGEBOX_H
