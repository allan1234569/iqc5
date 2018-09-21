/********************************************************************************
** Form generated from reading UI file 'popbox.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPBOX_H
#define UI_POPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopBox
{
public:
    QLabel *txtMsg;

    void setupUi(QWidget *PopBox)
    {
        if (PopBox->objectName().isEmpty())
            PopBox->setObjectName(QStringLiteral("PopBox"));
        PopBox->resize(204, 74);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        PopBox->setWindowIcon(icon);
        PopBox->setStyleSheet(QStringLiteral("border:none"));
        txtMsg = new QLabel(PopBox);
        txtMsg->setObjectName(QStringLiteral("txtMsg"));
        txtMsg->setGeometry(QRect(10, 10, 181, 51));
        txtMsg->setLayoutDirection(Qt::LeftToRight);
        txtMsg->setAlignment(Qt::AlignCenter);

        retranslateUi(PopBox);

        QMetaObject::connectSlotsByName(PopBox);
    } // setupUi

    void retranslateUi(QWidget *PopBox)
    {
        PopBox->setWindowTitle(QApplication::translate("PopBox", "\344\277\241\346\201\257", 0));
        txtMsg->setText(QApplication::translate("PopBox", "\345\234\250\346\216\2471", 0));
    } // retranslateUi

};

namespace Ui {
    class PopBox: public Ui_PopBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPBOX_H
