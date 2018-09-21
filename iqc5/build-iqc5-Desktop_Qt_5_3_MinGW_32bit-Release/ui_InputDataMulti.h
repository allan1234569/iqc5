/********************************************************************************
** Form generated from reading UI file 'InputDataMulti.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATAMULTI_H
#define UI_INPUTDATAMULTI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputDataMulti
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_2;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QSpinBox *spinBox;
    QTableWidget *table;
    QWidget *widget;
    QPushButton *btnSave;
    QPushButton *btnClose;

    void setupUi(QMainWindow *InputDataMulti)
    {
        if (InputDataMulti->objectName().isEmpty())
            InputDataMulti->setObjectName(QStringLiteral("InputDataMulti"));
        InputDataMulti->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        InputDataMulti->setWindowIcon(icon);
        centralwidget = new QWidget(InputDataMulti);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(200, 0));
        groupBox->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        inputKeyword = new QLineEdit(groupBox);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout_2->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widget_2 = new QWidget(groupBox_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 30));
        dateEdit = new QDateEdit(widget_2);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(60, 0, 110, 22));
        dateEdit->setInputMethodHints(Qt::ImhDate|Qt::ImhPreferNumbers);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 6, 54, 12));
        spinBox = new QSpinBox(widget_2);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(265, 4, 159, 22));

        verticalLayout_3->addWidget(widget_2);

        table = new QTableWidget(groupBox_2);
        table->setObjectName(QStringLiteral("table"));

        verticalLayout_3->addWidget(table);

        widget = new QWidget(groupBox_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 60));
        widget->setMaximumSize(QSize(16777215, 60));
        btnSave = new QPushButton(widget);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(290, 20, 75, 23));
        btnClose = new QPushButton(widget);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(380, 20, 75, 23));

        verticalLayout_3->addWidget(widget);


        horizontalLayout->addWidget(groupBox_2);

        InputDataMulti->setCentralWidget(centralwidget);

        retranslateUi(InputDataMulti);

        QMetaObject::connectSlotsByName(InputDataMulti);
    } // setupUi

    void retranslateUi(QMainWindow *InputDataMulti)
    {
        InputDataMulti->setWindowTitle(QApplication::translate("InputDataMulti", "\346\225\260\346\215\256\345\275\225\345\205\245", 0));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        dateEdit->setDisplayFormat(QApplication::translate("InputDataMulti", "yyyy-MM-dd", 0));
        label_2->setText(QApplication::translate("InputDataMulti", "\346\227\245\346\234\237", 0));
        btnSave->setText(QApplication::translate("InputDataMulti", "\344\277\235\345\255\230", 0));
        btnClose->setText(QApplication::translate("InputDataMulti", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class InputDataMulti: public Ui_InputDataMulti {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATAMULTI_H
