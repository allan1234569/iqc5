/********************************************************************************
** Form generated from reading UI file 'EditMaterial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMATERIAL_H
#define UI_EDITMATERIAL_H

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

class Ui_EditMaterial
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_1;
    QLineEdit *inputName;
    QLineEdit *inputOrigin;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_7;
    QComboBox *inputManufacturer;
    QComboBox *inputCountry;
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

    void setupUi(QDialog *EditMaterial)
    {
        if (EditMaterial->objectName().isEmpty())
            EditMaterial->setObjectName(QStringLiteral("EditMaterial"));
        EditMaterial->resize(635, 485);
        verticalLayout = new QVBoxLayout(EditMaterial);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_1 = new QWidget(EditMaterial);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_1->sizePolicy().hasHeightForWidth());
        widget_1->setSizePolicy(sizePolicy);
        widget_1->setMinimumSize(QSize(0, 100));
        inputName = new QLineEdit(widget_1);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(60, 20, 271, 20));
        inputOrigin = new QLineEdit(widget_1);
        inputOrigin->setObjectName(QStringLiteral("inputOrigin"));
        inputOrigin->setGeometry(QRect(410, 20, 131, 20));
        label = new QLabel(widget_1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(-40, 20, 81, 16));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(widget_1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(310, 20, 81, 16));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(widget_1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(-40, 50, 81, 16));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(widget_1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(310, 50, 81, 16));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputManufacturer = new QComboBox(widget_1);
        inputManufacturer->setObjectName(QStringLiteral("inputManufacturer"));
        inputManufacturer->setGeometry(QRect(60, 50, 271, 22));
        inputCountry = new QComboBox(widget_1);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(410, 50, 131, 22));

        verticalLayout->addWidget(widget_1);

        widget_2 = new QWidget(EditMaterial);
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
        btnAdd->setGeometry(QRect(10, 120, 32, 32));
        btnAdd->setIconSize(QSize(32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_3);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 160, 32, 32));
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);
        btnOK = new QPushButton(widget_3);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(0, 230, 75, 23));
        btnCancel = new QPushButton(widget_3);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(0, 270, 75, 23));

        horizontalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(inputName, inputOrigin);

        retranslateUi(EditMaterial);

        QMetaObject::connectSlotsByName(EditMaterial);
    } // setupUi

    void retranslateUi(QDialog *EditMaterial)
    {
        EditMaterial->setWindowTitle(QApplication::translate("EditMaterial", "\346\226\260\345\273\272\350\264\250\346\216\247\345\223\201", 0));
        label->setText(QApplication::translate("EditMaterial", "\345\220\215\347\247\260", 0));
        label_2->setText(QApplication::translate("EditMaterial", "\346\235\245\346\272\220", 0));
        label_3->setText(QApplication::translate("EditMaterial", "\345\216\202\345\225\206", 0));
        label_7->setText(QApplication::translate("EditMaterial", "\345\233\275\345\256\266", 0));
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnOK->setText(QApplication::translate("EditMaterial", "\347\241\256\345\256\232", 0));
        btnCancel->setText(QApplication::translate("EditMaterial", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class EditMaterial: public Ui_EditMaterial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMATERIAL_H
