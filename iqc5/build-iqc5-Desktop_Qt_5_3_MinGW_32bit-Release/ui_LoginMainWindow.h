/********************************************************************************
** Form generated from reading UI file 'LoginMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINMAINWINDOW_H
#define UI_LOGINMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginMainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QMainWindow *LoginMainWindow)
    {
        if (LoginMainWindow->objectName().isEmpty())
            LoginMainWindow->setObjectName(QStringLiteral("LoginMainWindow"));
        LoginMainWindow->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginMainWindow->sizePolicy().hasHeightForWidth());
        LoginMainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        LoginMainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(LoginMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        LoginMainWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginMainWindow);

        QMetaObject::connectSlotsByName(LoginMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginMainWindow)
    {
        LoginMainWindow->setWindowTitle(QApplication::translate("LoginMainWindow", "\347\231\273\345\275\225\345\210\260\350\264\250\346\231\237\350\264\250\351\207\217\346\216\247\345\210\266\350\275\257\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginMainWindow: public Ui_LoginMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINMAINWINDOW_H
