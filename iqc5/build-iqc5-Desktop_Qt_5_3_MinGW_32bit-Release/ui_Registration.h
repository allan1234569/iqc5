/********************************************************************************
** Form generated from reading UI file 'Registration.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QLabel *label;
    QLineEdit *AccreditCode_LineEdit;
    QLineEdit *MachineCode_LineEdit;
    QLabel *label_2;
    QLabel *state_Label;
    QPushButton *BtnTurnBack;
    QPushButton *Btn_Accredit;

    void setupUi(QWidget *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QStringLiteral("Registration"));
        Registration->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Registration->sizePolicy().hasHeightForWidth());
        Registration->setSizePolicy(sizePolicy);
        label = new QLabel(Registration);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 170, 50, 20));
        AccreditCode_LineEdit = new QLineEdit(Registration);
        AccreditCode_LineEdit->setObjectName(QStringLiteral("AccreditCode_LineEdit"));
        AccreditCode_LineEdit->setGeometry(QRect(60, 170, 270, 20));
        AccreditCode_LineEdit->setAlignment(Qt::AlignCenter);
        MachineCode_LineEdit = new QLineEdit(Registration);
        MachineCode_LineEdit->setObjectName(QStringLiteral("MachineCode_LineEdit"));
        MachineCode_LineEdit->setGeometry(QRect(60, 130, 270, 20));
        MachineCode_LineEdit->setAlignment(Qt::AlignCenter);
        MachineCode_LineEdit->setReadOnly(true);
        label_2 = new QLabel(Registration);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 130, 50, 20));
        state_Label = new QLabel(Registration);
        state_Label->setObjectName(QStringLiteral("state_Label"));
        state_Label->setGeometry(QRect(340, 170, 20, 20));
        BtnTurnBack = new QPushButton(Registration);
        BtnTurnBack->setObjectName(QStringLiteral("BtnTurnBack"));
        BtnTurnBack->setGeometry(QRect(0, 270, 400, 30));
        Btn_Accredit = new QPushButton(Registration);
        Btn_Accredit->setObjectName(QStringLiteral("Btn_Accredit"));
        Btn_Accredit->setGeometry(QRect(160, 210, 75, 23));

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QWidget *Registration)
    {
        Registration->setWindowTitle(QApplication::translate("Registration", "Form", 0));
        label->setText(QApplication::translate("Registration", "\346\216\210\346\235\203\347\240\201\357\274\232", 0));
        AccreditCode_LineEdit->setText(QApplication::translate("Registration", "\350\257\267\350\276\223\345\205\245\346\216\210\346\235\203\347\240\201", 0));
#ifndef QT_NO_TOOLTIP
        MachineCode_LineEdit->setToolTip(QApplication::translate("Registration", "\350\257\267\345\260\206\350\257\245\346\234\272\345\231\250\347\240\201\345\217\221\347\273\231\350\275\257\344\273\266\344\276\233\345\272\224\345\225\206\344\273\245\350\216\267\345\217\226\346\216\210\346\235\203\347\240\201", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("Registration", "\346\234\272\345\231\250\347\240\201\357\274\232", 0));
        state_Label->setText(QString());
        BtnTurnBack->setText(QApplication::translate("Registration", "\350\277\224 \345\233\236", 0));
        Btn_Accredit->setText(QApplication::translate("Registration", "\346\216\210 \346\235\203", 0));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
