/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label_4;
    QLabel *softnameLabel;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *Passwd_LineEdit;
    QComboBox *UserName_ComboBox;
    QPushButton *login_Btn;
    QPushButton *cancel_Btn;
    QLabel *stateLabel;
    QLabel *RegistrationState_Label;
    QPushButton *AccreditBtn;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        Login->setWindowIcon(icon);
        label_4 = new QLabel(Login);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 270, 200, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        softnameLabel = new QLabel(Login);
        softnameLabel->setObjectName(QStringLiteral("softnameLabel"));
        softnameLabel->setGeometry(QRect(90, 20, 210, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font.setPointSize(15);
        softnameLabel->setFont(font);
        softnameLabel->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(Login);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 80, 50, 20));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 130, 50, 20));
        Passwd_LineEdit = new QLineEdit(Login);
        Passwd_LineEdit->setObjectName(QStringLiteral("Passwd_LineEdit"));
        Passwd_LineEdit->setGeometry(QRect(140, 130, 160, 20));
        Passwd_LineEdit->setEchoMode(QLineEdit::Password);
        UserName_ComboBox = new QComboBox(Login);
        UserName_ComboBox->setObjectName(QStringLiteral("UserName_ComboBox"));
        UserName_ComboBox->setGeometry(QRect(140, 80, 160, 22));
        UserName_ComboBox->setEditable(true);
        login_Btn = new QPushButton(Login);
        login_Btn->setObjectName(QStringLiteral("login_Btn"));
        login_Btn->setGeometry(QRect(90, 190, 80, 30));
        cancel_Btn = new QPushButton(Login);
        cancel_Btn->setObjectName(QStringLiteral("cancel_Btn"));
        cancel_Btn->setGeometry(QRect(220, 190, 80, 30));
        stateLabel = new QLabel(Login);
        stateLabel->setObjectName(QStringLiteral("stateLabel"));
        stateLabel->setGeometry(QRect(70, 270, 60, 20));
        stateLabel->setAlignment(Qt::AlignCenter);
        RegistrationState_Label = new QLabel(Login);
        RegistrationState_Label->setObjectName(QStringLiteral("RegistrationState_Label"));
        RegistrationState_Label->setGeometry(QRect(130, 270, 60, 20));
        RegistrationState_Label->setAlignment(Qt::AlignCenter);
        AccreditBtn = new QPushButton(Login);
        AccreditBtn->setObjectName(QStringLiteral("AccreditBtn"));
        AccreditBtn->setGeometry(QRect(0, 270, 30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/triangle_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        AccreditBtn->setIcon(icon1);
        AccreditBtn->setIconSize(QSize(30, 30));
        AccreditBtn->setFlat(true);
        QWidget::setTabOrder(UserName_ComboBox, Passwd_LineEdit);
        QWidget::setTabOrder(Passwd_LineEdit, login_Btn);
        QWidget::setTabOrder(login_Btn, cancel_Btn);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "\347\231\273\345\275\225\345\210\260\350\264\250\346\231\237\350\264\250\351\207\217\346\216\247\345\210\266\350\275\257\344\273\266", 0));
        label_4->setText(QApplication::translate("Login", "\344\270\212\346\265\267\350\264\250\346\231\237\347\224\237\347\211\251\347\247\221\346\212\200\346\234\211\351\231\220\345\205\254\345\217\270", 0));
        softnameLabel->setText(QApplication::translate("Login", "\350\264\250\346\231\237\350\264\250\351\207\217\346\216\247\345\210\266\350\275\257\344\273\266", 0));
        label_2->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        label_3->setText(QApplication::translate("Login", "\345\257\206\347\240\201\357\274\232", 0));
        Passwd_LineEdit->setText(QApplication::translate("Login", "123456", 0));
        UserName_ComboBox->clear();
        UserName_ComboBox->insertItems(0, QStringList()
         << QApplication::translate("Login", "Admin", 0)
        );
        login_Btn->setText(QApplication::translate("Login", "\347\231\273 \345\275\225", 0));
        cancel_Btn->setText(QApplication::translate("Login", "\345\217\226 \346\266\210", 0));
        stateLabel->setText(QString());
        RegistrationState_Label->setText(QApplication::translate("Login", "<html><head/><body><p><span style=\" color:#ff0000;\">\346\234\252\346\216\210\346\235\203</span></p></body></html>", 0));
#ifndef QT_NO_TOOLTIP
        AccreditBtn->setToolTip(QApplication::translate("Login", "\346\216\210\346\235\203", 0));
#endif // QT_NO_TOOLTIP
        AccreditBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
