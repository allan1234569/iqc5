/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *importBtn;
    QPushButton *cancleBtn;
    QRadioButton *selectDirectoryRadioBtn;
    QRadioButton *selectFileRadioBtn;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 300);
        importBtn = new QPushButton(Widget);
        importBtn->setObjectName(QStringLiteral("importBtn"));
        importBtn->setGeometry(QRect(40, 250, 75, 30));
        cancleBtn = new QPushButton(Widget);
        cancleBtn->setObjectName(QStringLiteral("cancleBtn"));
        cancleBtn->setGeometry(QRect(290, 250, 75, 30));
        selectDirectoryRadioBtn = new QRadioButton(Widget);
        selectDirectoryRadioBtn->setObjectName(QStringLiteral("selectDirectoryRadioBtn"));
        selectDirectoryRadioBtn->setGeometry(QRect(50, 20, 70, 16));
        selectDirectoryRadioBtn->setLayoutDirection(Qt::RightToLeft);
        selectDirectoryRadioBtn->setChecked(true);
        selectFileRadioBtn = new QRadioButton(Widget);
        selectFileRadioBtn->setObjectName(QStringLiteral("selectFileRadioBtn"));
        selectFileRadioBtn->setGeometry(QRect(170, 20, 70, 16));
        selectFileRadioBtn->setLayoutDirection(Qt::RightToLeft);
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 50, 221, 20));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 40, 20));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 40, 20));
        comboBox = new QComboBox(Widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(50, 100, 220, 22));
        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(280, 50, 81, 21));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        importBtn->setText(QApplication::translate("Widget", "\345\257\274  \345\205\245", 0));
        cancleBtn->setText(QApplication::translate("Widget", "\345\217\226  \346\266\210", 0));
        selectDirectoryRadioBtn->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\347\233\256\345\275\225", 0));
        selectFileRadioBtn->setText(QApplication::translate("Widget", "\351\200\211\346\213\251\346\226\207\344\273\266", 0));
        label->setText(QApplication::translate("Widget", "\350\267\257\345\276\204\357\274\232", 0));
        label_2->setText(QApplication::translate("Widget", "\347\263\273\347\273\237\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
