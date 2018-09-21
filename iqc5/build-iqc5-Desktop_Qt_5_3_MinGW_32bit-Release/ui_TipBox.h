/********************************************************************************
** Form generated from reading UI file 'TipBox.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIPBOX_H
#define UI_TIPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TipBox
{
public:

    void setupUi(QWidget *TipBox)
    {
        if (TipBox->objectName().isEmpty())
            TipBox->setObjectName(QStringLiteral("TipBox"));
        TipBox->resize(400, 300);

        retranslateUi(TipBox);

        QMetaObject::connectSlotsByName(TipBox);
    } // setupUi

    void retranslateUi(QWidget *TipBox)
    {
        TipBox->setWindowTitle(QApplication::translate("TipBox", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class TipBox: public Ui_TipBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIPBOX_H
