/********************************************************************************
** Form generated from reading UI file 'EditMethod.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMETHOD_H
#define UI_EDITMETHOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditMethod
{
public:
    QGroupBox *groupBox;
    QLineEdit *inputName;
    QLabel *label_2;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *btnCancel;
    QPushButton *btnOK;

    void setupUi(QDialog *EditMethod)
    {
        if (EditMethod->objectName().isEmpty())
            EditMethod->setObjectName(QStringLiteral("EditMethod"));
        EditMethod->resize(463, 214);
        groupBox = new QGroupBox(EditMethod);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 431, 131));
        inputName = new QLineEdit(groupBox);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(110, 100, 141, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 81, 16));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputCategory = new QComboBox(groupBox);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(110, 60, 141, 22));
        inputSubject = new QComboBox(groupBox);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(110, 20, 141, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 20, 31, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 60, 41, 16));
        btnCancel = new QPushButton(EditMethod);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(260, 170, 75, 23));
        btnOK = new QPushButton(EditMethod);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(170, 170, 75, 23));

        retranslateUi(EditMethod);

        QMetaObject::connectSlotsByName(EditMethod);
    } // setupUi

    void retranslateUi(QDialog *EditMethod)
    {
        EditMethod->setWindowTitle(QApplication::translate("EditMethod", "\346\226\260\345\273\272\346\243\200\346\265\213\346\226\271\346\263\225", 0));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("EditMethod", "\345\220\215\347\247\260", 0));
        label_3->setText(QApplication::translate("EditMethod", "\344\270\223\344\270\232", 0));
        label_4->setText(QApplication::translate("EditMethod", "\344\272\232\344\270\223\344\270\232", 0));
        btnCancel->setText(QApplication::translate("EditMethod", "\345\217\226\346\266\210", 0));
        btnOK->setText(QApplication::translate("EditMethod", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class EditMethod: public Ui_EditMethod {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMETHOD_H
