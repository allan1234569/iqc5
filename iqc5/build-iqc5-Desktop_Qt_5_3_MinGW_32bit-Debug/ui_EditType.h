/********************************************************************************
** Form generated from reading UI file 'EditType.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITTYPE_H
#define UI_EDITTYPE_H

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

class Ui_EditType
{
public:
    QPushButton *btnCancel;
    QPushButton *btnOK;
    QGroupBox *groupBox;
    QLabel *label_2;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLabel *label;
    QLabel *label_7;
    QLineEdit *inputTestTypeName;
    QLabel *label_3;
    QLineEdit *inputTestTypeCode;

    void setupUi(QDialog *EditType)
    {
        if (EditType->objectName().isEmpty())
            EditType->setObjectName(QStringLiteral("EditType"));
        EditType->resize(539, 256);
        btnCancel = new QPushButton(EditType);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(270, 210, 75, 23));
        btnOK = new QPushButton(EditType);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(180, 210, 75, 23));
        groupBox = new QGroupBox(EditType);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 501, 181));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-10, 60, 81, 16));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputCategory = new QComboBox(groupBox);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(320, 20, 141, 22));
        inputSubject = new QComboBox(groupBox);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(90, 20, 141, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 31, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(270, 20, 41, 16));
        inputTestTypeName = new QLineEdit(groupBox);
        inputTestTypeName->setObjectName(QStringLiteral("inputTestTypeName"));
        inputTestTypeName->setGeometry(QRect(91, 60, 139, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 60, 81, 16));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputTestTypeCode = new QLineEdit(groupBox);
        inputTestTypeCode->setObjectName(QStringLiteral("inputTestTypeCode"));
        inputTestTypeCode->setGeometry(QRect(321, 60, 139, 20));
        QWidget::setTabOrder(inputCategory, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(EditType);

        QMetaObject::connectSlotsByName(EditType);
    } // setupUi

    void retranslateUi(QDialog *EditType)
    {
        EditType->setWindowTitle(QApplication::translate("EditType", "\346\226\260\345\273\272\350\264\250\346\243\200\346\240\207\345\207\206", 0));
        btnCancel->setText(QApplication::translate("EditType", "\345\217\226\346\266\210", 0));
        btnOK->setText(QApplication::translate("EditType", "\347\241\256\345\256\232", 0));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("EditType", "\345\220\215\347\247\260", 0));
        label->setText(QApplication::translate("EditType", "\344\270\223\344\270\232", 0));
        label_7->setText(QApplication::translate("EditType", "\344\272\232\344\270\223\344\270\232", 0));
        label_3->setText(QApplication::translate("EditType", "\347\274\251\345\206\231", 0));
    } // retranslateUi

};

namespace Ui {
    class EditType: public Ui_EditType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITTYPE_H
