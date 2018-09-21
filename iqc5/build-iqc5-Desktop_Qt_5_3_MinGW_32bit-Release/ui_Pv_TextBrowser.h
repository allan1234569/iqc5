/********************************************************************************
** Form generated from reading UI file 'Pv_TextBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PV_TEXTBROWSER_H
#define UI_PV_TEXTBROWSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pv_TextBrowser
{
public:
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Pv_TextBrowser)
    {
        if (Pv_TextBrowser->objectName().isEmpty())
            Pv_TextBrowser->setObjectName(QStringLiteral("Pv_TextBrowser"));
        Pv_TextBrowser->resize(600, 367);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        Pv_TextBrowser->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(Pv_TextBrowser);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textBrowser = new QTextBrowser(Pv_TextBrowser);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout->addWidget(textBrowser);

        horizontalLayout->setStretch(0, 1);

        retranslateUi(Pv_TextBrowser);

        QMetaObject::connectSlotsByName(Pv_TextBrowser);
    } // setupUi

    void retranslateUi(QWidget *Pv_TextBrowser)
    {
        Pv_TextBrowser->setWindowTitle(QApplication::translate("Pv_TextBrowser", "\345\256\236\351\252\214\350\246\201\346\261\202", 0));
    } // retranslateUi

};

namespace Ui {
    class Pv_TextBrowser: public Ui_Pv_TextBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PV_TEXTBROWSER_H
