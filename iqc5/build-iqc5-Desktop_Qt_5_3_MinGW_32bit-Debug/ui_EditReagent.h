/********************************************************************************
** Form generated from reading UI file 'EditReagent.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITREAGENT_H
#define UI_EDITREAGENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditReagent
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_3;
    QLineEdit *inputName;
    QComboBox *inputManufacturer;
    QComboBox *inputCountry;
    QLabel *label_2;
    QLineEdit *inputProjectName;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *table;
    QWidget *widget_3;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *EditReagent)
    {
        if (EditReagent->objectName().isEmpty())
            EditReagent->setObjectName(QStringLiteral("EditReagent"));
        EditReagent->resize(644, 481);
        verticalLayout = new QVBoxLayout(EditReagent);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(EditReagent);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 100));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 30, 81, 16));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 60, 81, 16));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 60, 81, 16));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputName = new QLineEdit(widget);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(100, 30, 111, 20));
        inputManufacturer = new QComboBox(widget);
        inputManufacturer->setObjectName(QStringLiteral("inputManufacturer"));
        inputManufacturer->setGeometry(QRect(100, 60, 111, 22));
        inputCountry = new QComboBox(widget);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(320, 60, 111, 22));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 30, 81, 16));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputProjectName = new QLineEdit(widget);
        inputProjectName->setObjectName(QStringLiteral("inputProjectName"));
        inputProjectName->setGeometry(QRect(320, 30, 111, 20));

        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(EditReagent);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        table = new QTableWidget(widget_2);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout_2->addWidget(table);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(80, 0));
        btnAdd = new QPushButton(widget_3);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(10, 80, 32, 32));
        btnAdd->setIconSize(QSize(32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_3);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 120, 32, 32));
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);
        btnOK = new QPushButton(widget_3);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(0, 220, 75, 23));
        btnCancel = new QPushButton(widget_3);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(0, 260, 75, 23));

        horizontalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(EditReagent);

        QMetaObject::connectSlotsByName(EditReagent);
    } // setupUi

    void retranslateUi(QDialog *EditReagent)
    {
        EditReagent->setWindowTitle(QApplication::translate("EditReagent", "\346\226\260\345\273\272\350\257\225\345\211\202", 0));
        label->setText(QApplication::translate("EditReagent", "\345\220\215\347\247\260", 0));
        label_7->setText(QApplication::translate("EditReagent", "\345\233\275\345\256\266", 0));
        label_3->setText(QApplication::translate("EditReagent", "\345\216\202\345\225\206", 0));
        label_2->setText(QApplication::translate("EditReagent", "\346\243\200\346\265\213\351\241\271\347\233\256", 0));
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnOK->setText(QApplication::translate("EditReagent", "\347\241\256\345\256\232", 0));
        btnCancel->setText(QApplication::translate("EditReagent", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class EditReagent: public Ui_EditReagent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITREAGENT_H
