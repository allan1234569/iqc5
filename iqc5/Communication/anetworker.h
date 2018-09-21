#ifndef ANETWORKER_H
#define ANETWORKER_H

#include <QWidget>
#include <QTimer>

#include "aserver.h"
#include "aclient.h"

namespace Ui {
class ANetWorker;
}

class ANetWorker : public QWidget
{
    Q_OBJECT

public:
    explicit ANetWorker(QWidget *parent = 0);
    ~ANetWorker();

    void clear_display();

    void reStart();

signals:

    void sig_displayTrayIcon(bool flag);

    /**
     * @brief sig_curStatus
     * @param source        要显示的图标路径
     */
    void sig_curStatus(const QString &msg, const QString &source);

protected slots:

    void slt_showData(const QString &value);

    void slt_showStatus(const QString &msg, const QString &status);

    void slt_displayTrayIcon(bool flag);

private:
    Ui::ANetWorker *ui;

    AServer *m_pServer;
    AClient *m_pClient;

    int m_timerInterval;
};

#endif // ANETWORKER_H
