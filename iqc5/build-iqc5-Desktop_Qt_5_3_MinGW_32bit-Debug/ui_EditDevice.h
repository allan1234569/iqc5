/********************************************************************************
** Form generated from reading UI file 'EditDevice.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDEVICE_H
#define UI_EDITDEVICE_H

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

class Ui_EditDevice
{
public:
    QGroupBox *groupBox;
    QLineEdit *inputcode;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *inputsteelseal;
    QLabel *label_4;
    QLineEdit *inputinstalldate;
    QLabel *label_5;
    QLineEdit *inputstopdate;
    QLineEdit *inputassetscode;
    QLineEdit *inputName;
    QLabel *label_11;
    QLineEdit *inputsn;
    QLabel *label_12;
    QLineEdit *inputinstallplace;
    QLineEdit *inputmemo;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QComboBox *inputBrand;
    QComboBox *inputModel;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *btnCancel;
    QPushButton *btnOK;

    void setupUi(QDialog *EditDevice)
    {
        if (EditDevice->objectName().isEmpty())
            EditDevice->setObjectName(QStringLiteral("EditDevice"));
        EditDevice->resize(521, 297);
        groupBox = new QGroupBox(EditDevice);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 501, 221));
        inputcode = new QLineEdit(groupBox);
        inputcode->setObjectName(QStringLiteral("inputcode"));
        inputcode->setGeometry(QRect(80, 80, 141, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-20, 80, 81, 16));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(-20, 120, 81, 16));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputsteelseal = new QLineEdit(groupBox);
        inputsteelseal->setObjectName(QStringLiteral("inputsteelseal"));
        inputsteelseal->setGeometry(QRect(80, 120, 141, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(-20, 160, 81, 16));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputinstalldate = new QLineEdit(groupBox);
        inputinstalldate->setObjectName(QStringLiteral("inputinstalldate"));
        inputinstalldate->setGeometry(QRect(80, 160, 141, 20));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(-20, 190, 81, 16));
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputstopdate = new QLineEdit(groupBox);
        inputstopdate->setObjectName(QStringLiteral("inputstopdate"));
        inputstopdate->setGeometry(QRect(80, 190, 141, 20));
        inputassetscode = new QLineEdit(groupBox);
        inputassetscode->setObjectName(QStringLiteral("inputassetscode"));
        inputassetscode->setGeometry(QRect(320, 120, 141, 20));
        inputName = new QLineEdit(groupBox);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(80, 40, 381, 20));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(220, 80, 81, 16));
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputsn = new QLineEdit(groupBox);
        inputsn->setObjectName(QStringLiteral("inputsn"));
        inputsn->setGeometry(QRect(320, 80, 141, 20));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(220, 160, 81, 16));
        label_12->setLayoutDirection(Qt::LeftToRight);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputinstallplace = new QLineEdit(groupBox);
        inputinstallplace->setObjectName(QStringLiteral("inputinstallplace"));
        inputinstallplace->setGeometry(QRect(320, 160, 141, 20));
        inputmemo = new QLineEdit(groupBox);
        inputmemo->setObjectName(QStringLiteral("inputmemo"));
        inputmemo->setGeometry(QRect(320, 190, 141, 20));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(220, 190, 81, 16));
        label_13->setLayoutDirection(Qt::LeftToRight);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(220, 120, 81, 16));
        label_14->setLayoutDirection(Qt::LeftToRight);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(-20, 40, 81, 16));
        label_15->setLayoutDirection(Qt::LeftToRight);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputBrand = new QComboBox(groupBox);
        inputBrand->setObjectName(QStringLiteral("inputBrand"));
        inputBrand->setGeometry(QRect(80, 10, 141, 22));
        inputModel = new QComboBox(groupBox);
        inputModel->setObjectName(QStringLiteral("inputModel"));
        inputModel->setGeometry(QRect(320, 7, 141, 22));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(38, 12, 31, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(260, 10, 41, 16));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 10, 10, 20));
        label->setStyleSheet(QStringLiteral("color: rgb(254, 0, 0);"));
        label->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(460, 10, 10, 20));
        label_8->setStyleSheet(QStringLiteral("color: rgb(254, 0, 0);"));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(460, 40, 10, 20));
        label_9->setStyleSheet(QStringLiteral("color: rgb(254, 0, 0);"));
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(460, 160, 10, 20));
        label_10->setStyleSheet(QStringLiteral("color: rgb(254, 0, 0);"));
        label_10->setAlignment(Qt::AlignCenter);
        btnCancel = new QPushButton(EditDevice);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(270, 260, 75, 23));
        btnOK = new QPushButton(EditDevice);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(180, 260, 75, 23));

        retranslateUi(EditDevice);

        QMetaObject::connectSlotsByName(EditDevice);
    } // setupUi

    void retranslateUi(QDialog *EditDevice)
    {
        EditDevice->setWindowTitle(QApplication::translate("EditDevice", "\346\226\260\345\273\272\344\273\252\345\231\250", 0));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("EditDevice", "\344\273\252\345\231\250\347\274\226\347\240\201", 0));
        label_3->setText(QApplication::translate("EditDevice", "\351\222\242\345\215\260", 0));
        label_4->setText(QApplication::translate("EditDevice", "\345\256\211\350\243\205\346\227\245\346\234\237", 0));
        label_5->setText(QApplication::translate("EditDevice", "\346\212\245\345\272\237\346\227\245\346\234\237", 0));
        label_11->setText(QApplication::translate("EditDevice", "\346\235\241\345\275\242\347\240\201", 0));
        label_12->setText(QApplication::translate("EditDevice", "\345\256\211\350\243\205\345\234\260\347\202\271", 0));
        label_13->setText(QApplication::translate("EditDevice", "\345\244\207\346\263\250", 0));
        label_14->setText(QApplication::translate("EditDevice", "\345\233\272\345\256\232\350\265\204\344\272\247\347\274\226\347\240\201", 0));
        label_15->setText(QApplication::translate("EditDevice", "\344\273\252\345\231\250\345\220\215\347\247\260", 0));
        label_6->setText(QApplication::translate("EditDevice", "\345\223\201\347\211\214", 0));
        label_7->setText(QApplication::translate("EditDevice", "\345\236\213\345\217\267", 0));
        label->setText(QApplication::translate("EditDevice", "*", 0));
        label_8->setText(QApplication::translate("EditDevice", "*", 0));
        label_9->setText(QApplication::translate("EditDevice", "*", 0));
        label_10->setText(QApplication::translate("EditDevice", "*", 0));
        btnCancel->setText(QApplication::translate("EditDevice", "\345\217\226\346\266\210", 0));
        btnOK->setText(QApplication::translate("EditDevice", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class EditDevice: public Ui_EditDevice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDEVICE_H
