#ifndef PV_TEXTBROWSER_H
#define PV_TEXTBROWSER_H

#include <QWidget>

namespace Ui {
class Pv_TextBrowser;
}

class Pv_TextBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit Pv_TextBrowser(QWidget *parent = 0);
    void setHtml(const QString &html);
    ~Pv_TextBrowser();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Pv_TextBrowser *ui;
};

#endif // PV_TEXTBROWSER_H
