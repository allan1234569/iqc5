/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QAction *action_DecodeSetup;
    QAction *action_Help;
    QAction *action_OriginalData;
    QAction *action_DecodeLog;
    QAction *action_ReadFile;
    QAction *action_ReHandle;
    QAction *action_Exit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;

    void setupUi(QMainWindow *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QStringLiteral("BaseWindow"));
        BaseWindow->resize(428, 326);
        action_DecodeSetup = new QAction(BaseWindow);
        action_DecodeSetup->setObjectName(QStringLiteral("action_DecodeSetup"));
        action_Help = new QAction(BaseWindow);
        action_Help->setObjectName(QStringLiteral("action_Help"));
        action_OriginalData = new QAction(BaseWindow);
        action_OriginalData->setObjectName(QStringLiteral("action_OriginalData"));
        action_DecodeLog = new QAction(BaseWindow);
        action_DecodeLog->setObjectName(QStringLiteral("action_DecodeLog"));
        action_ReadFile = new QAction(BaseWindow);
        action_ReadFile->setObjectName(QStringLiteral("action_ReadFile"));
        action_ReHandle = new QAction(BaseWindow);
        action_ReHandle->setObjectName(QStringLiteral("action_ReHandle"));
        action_Exit = new QAction(BaseWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        centralWidget = new QWidget(BaseWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BaseWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BaseWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 428, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        BaseWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action_ReadFile);
        menu->addAction(action_ReHandle);
        menu->addAction(action_Exit);
        menu_2->addAction(action_OriginalData);
        menu_2->addAction(action_DecodeLog);
        menu_3->addAction(action_DecodeSetup);
        menu_4->addAction(action_Help);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "MainWindow", 0));
        action_DecodeSetup->setText(QApplication::translate("BaseWindow", "\351\205\215\347\275\256\350\256\276\347\275\256", 0));
        action_Help->setText(QApplication::translate("BaseWindow", "\345\270\256\345\212\251", 0));
        action_OriginalData->setText(QApplication::translate("BaseWindow", "\346\237\245\347\234\213\345\216\237\345\247\213\346\225\260\346\215\256", 0));
        action_DecodeLog->setText(QApplication::translate("BaseWindow", "\346\237\245\347\234\213\350\247\243\346\236\220\346\227\245\345\277\227", 0));
        action_ReadFile->setText(QApplication::translate("BaseWindow", "\350\257\273\345\217\226\346\226\207\344\273\266", 0));
        action_ReHandle->setText(QApplication::translate("BaseWindow", "\351\207\215\346\226\260\345\244\204\347\220\206\345\275\223\346\227\245\346\225\260\346\215\256", 0));
        action_Exit->setText(QApplication::translate("BaseWindow", "\351\200\200\345\207\272", 0));
        menu->setTitle(QApplication::translate("BaseWindow", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("BaseWindow", "\346\237\245\347\234\213", 0));
        menu_3->setTitle(QApplication::translate("BaseWindow", "\350\256\276\347\275\256", 0));
        menu_4->setTitle(QApplication::translate("BaseWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
