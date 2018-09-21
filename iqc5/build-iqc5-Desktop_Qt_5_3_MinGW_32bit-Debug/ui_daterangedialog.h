/********************************************************************************
** Form generated from reading UI file 'daterangedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATERANGEDIALOG_H
#define UI_DATERANGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DateRangeDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QPushButton *Calculate_PushButton;
    QPushButton *Cancel_PushButton;

    void setupUi(QDialog *DateRangeDialog)
    {
        if (DateRangeDialog->objectName().isEmpty())
            DateRangeDialog->setObjectName(QStringLiteral("DateRangeDialog"));
        DateRangeDialog->resize(232, 173);
        DateRangeDialog->setMinimumSize(QSize(232, 173));
        DateRangeDialog->setMaximumSize(QSize(232, 173));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        DateRangeDialog->setWindowIcon(icon);
        label = new QLabel(DateRangeDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 60, 20));
        label_2 = new QLabel(DateRangeDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 80, 60, 20));
        startDateEdit = new QDateEdit(DateRangeDialog);
        startDateEdit->setObjectName(QStringLiteral("startDateEdit"));
        startDateEdit->setGeometry(QRect(90, 20, 120, 22));
        startDateEdit->setCalendarPopup(true);
        endDateEdit = new QDateEdit(DateRangeDialog);
        endDateEdit->setObjectName(QStringLiteral("endDateEdit"));
        endDateEdit->setGeometry(QRect(90, 80, 120, 22));
        endDateEdit->setCalendarPopup(true);
        Calculate_PushButton = new QPushButton(DateRangeDialog);
        Calculate_PushButton->setObjectName(QStringLiteral("Calculate_PushButton"));
        Calculate_PushButton->setGeometry(QRect(20, 140, 70, 23));
        Cancel_PushButton = new QPushButton(DateRangeDialog);
        Cancel_PushButton->setObjectName(QStringLiteral("Cancel_PushButton"));
        Cancel_PushButton->setGeometry(QRect(140, 140, 70, 23));
        Cancel_PushButton->setCheckable(false);
        Cancel_PushButton->setAutoRepeat(false);
        Cancel_PushButton->setAutoExclusive(false);
        Cancel_PushButton->setAutoDefault(true);
        Cancel_PushButton->setDefault(false);
        Cancel_PushButton->setFlat(false);

        retranslateUi(DateRangeDialog);

        QMetaObject::connectSlotsByName(DateRangeDialog);
    } // setupUi

    void retranslateUi(QDialog *DateRangeDialog)
    {
        DateRangeDialog->setWindowTitle(QApplication::translate("DateRangeDialog", "\350\257\267\351\200\211\346\213\251\346\227\245\346\234\237", 0));
        label->setText(QApplication::translate("DateRangeDialog", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0));
        label_2->setText(QApplication::translate("DateRangeDialog", "\347\273\223\346\235\237\346\227\245\346\234\237\357\274\232", 0));
        startDateEdit->setDisplayFormat(QApplication::translate("DateRangeDialog", "yyyy-MM-dd", 0));
        endDateEdit->setDisplayFormat(QApplication::translate("DateRangeDialog", "yyyy-MM-dd", 0));
        Calculate_PushButton->setText(QApplication::translate("DateRangeDialog", "\345\274\200\345\247\213\350\256\241\347\256\227", 0));
        Cancel_PushButton->setText(QApplication::translate("DateRangeDialog", "\345\217\226 \346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class DateRangeDialog: public Ui_DateRangeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATERANGEDIALOG_H
