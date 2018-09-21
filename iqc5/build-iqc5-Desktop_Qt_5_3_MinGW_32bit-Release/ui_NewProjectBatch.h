/********************************************************************************
** Form generated from reading UI file 'NewProjectBatch.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTBATCH_H
#define UI_NEWPROJECTBATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewProjectBatch
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_1;
    QHBoxLayout *horizontalLayout;
    QTableWidget *table;
    QWidget *widget_2;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QWidget *widget_3;
    QLabel *label_6;
    QLabel *label_2;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLabel *label_3;
    QLabel *lblTestTypeInfo;
    QLineEdit *inputMethodName;
    QLineEdit *inputDeviceName;
    QLabel *inputDescription;
    QLabel *label_7;
    QLineEdit *inputReagentName;
    QLabel *lblTestTypeInfo_2;
    QLineEdit *inputMaterialName;
    QPushButton *pushButton;
    QPushButton *btnConfigColumn;
    QLabel *lblTestTypeInfo_3;
    QLineEdit *inputName;
    QWidget *widget_4;

    void setupUi(QMainWindow *NewProjectBatch)
    {
        if (NewProjectBatch->objectName().isEmpty())
            NewProjectBatch->setObjectName(QStringLiteral("NewProjectBatch"));
        NewProjectBatch->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewProjectBatch->setWindowIcon(icon);
        centralwidget = new QWidget(NewProjectBatch);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_1 = new QWidget(centralwidget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        horizontalLayout = new QHBoxLayout(widget_1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        table = new QTableWidget(widget_1);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout->addWidget(table);

        widget_2 = new QWidget(widget_1);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(80, 0));
        btnAdd = new QPushButton(widget_2);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(10, 150, 32, 32));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/add_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon1);
        btnAdd->setIconSize(QSize(32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_2);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 190, 32, 32));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/delete_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon2);
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);
        btnOK = new QPushButton(widget_2);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(0, 240, 75, 23));
        btnCancel = new QPushButton(widget_2);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(0, 270, 75, 23));

        horizontalLayout->addWidget(widget_2);


        verticalLayout->addWidget(widget_1);

        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 80));
        widget_3->setMaximumSize(QSize(16777215, 80));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 50, 81, 16));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 21, 81, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputCategory = new QComboBox(widget_3);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(310, 21, 141, 22));
        inputSubject = new QComboBox(widget_3);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(110, 20, 141, 22));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 20, 51, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblTestTypeInfo = new QLabel(widget_3);
        lblTestTypeInfo->setObjectName(QStringLiteral("lblTestTypeInfo"));
        lblTestTypeInfo->setGeometry(QRect(470, 20, 31, 20));
        lblTestTypeInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputMethodName = new QLineEdit(widget_3);
        inputMethodName->setObjectName(QStringLiteral("inputMethodName"));
        inputMethodName->setGeometry(QRect(110, 50, 141, 20));
        inputDeviceName = new QLineEdit(widget_3);
        inputDeviceName->setObjectName(QStringLiteral("inputDeviceName"));
        inputDeviceName->setGeometry(QRect(510, 21, 141, 20));
        inputDescription = new QLabel(widget_3);
        inputDescription->setObjectName(QStringLiteral("inputDescription"));
        inputDescription->setGeometry(QRect(340, 76, 201, 16));
        inputDescription->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(widget_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(260, 52, 81, 16));
        inputReagentName = new QLineEdit(widget_3);
        inputReagentName->setObjectName(QStringLiteral("inputReagentName"));
        inputReagentName->setGeometry(QRect(510, 50, 141, 20));
        lblTestTypeInfo_2 = new QLabel(widget_3);
        lblTestTypeInfo_2->setObjectName(QStringLiteral("lblTestTypeInfo_2"));
        lblTestTypeInfo_2->setGeometry(QRect(470, 49, 31, 20));
        lblTestTypeInfo_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputMaterialName = new QLineEdit(widget_3);
        inputMaterialName->setObjectName(QStringLiteral("inputMaterialName"));
        inputMaterialName->setGeometry(QRect(310, 50, 141, 20));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(663, 49, 75, 23));
        btnConfigColumn = new QPushButton(widget_3);
        btnConfigColumn->setObjectName(QStringLiteral("btnConfigColumn"));
        btnConfigColumn->setGeometry(QRect(747, 50, 75, 23));
        lblTestTypeInfo_3 = new QLabel(widget_3);
        lblTestTypeInfo_3->setObjectName(QStringLiteral("lblTestTypeInfo_3"));
        lblTestTypeInfo_3->setGeometry(QRect(665, 23, 31, 20));
        lblTestTypeInfo_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputName = new QLineEdit(widget_3);
        inputName->setObjectName(QStringLiteral("inputName"));
        inputName->setGeometry(QRect(696, 22, 141, 20));

        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 40));
        widget_4->setMaximumSize(QSize(16777215, 40));

        verticalLayout->addWidget(widget_4);

        NewProjectBatch->setCentralWidget(centralwidget);
        QWidget::setTabOrder(inputSubject, inputCategory);
        QWidget::setTabOrder(inputCategory, inputDeviceName);
        QWidget::setTabOrder(inputDeviceName, inputMethodName);
        QWidget::setTabOrder(inputMethodName, inputMaterialName);
        QWidget::setTabOrder(inputMaterialName, inputReagentName);
        QWidget::setTabOrder(inputReagentName, pushButton);
        QWidget::setTabOrder(pushButton, table);
        QWidget::setTabOrder(table, btnAdd);
        QWidget::setTabOrder(btnAdd, btnDelete);
        QWidget::setTabOrder(btnDelete, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);

        retranslateUi(NewProjectBatch);

        QMetaObject::connectSlotsByName(NewProjectBatch);
    } // setupUi

    void retranslateUi(QMainWindow *NewProjectBatch)
    {
        NewProjectBatch->setWindowTitle(QApplication::translate("NewProjectBatch", "\346\226\260\345\273\272\351\241\271\347\233\256", 0));
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnOK->setText(QApplication::translate("NewProjectBatch", "\344\277\235\345\255\230", 0));
        btnCancel->setText(QApplication::translate("NewProjectBatch", "\345\205\263\351\227\255", 0));
        label_6->setText(QApplication::translate("NewProjectBatch", "\346\226\271\346\263\225:", 0));
        label_2->setText(QApplication::translate("NewProjectBatch", "\344\272\232\344\270\223\344\270\232:", 0));
        label_3->setText(QApplication::translate("NewProjectBatch", "\344\270\223\344\270\232:", 0));
        lblTestTypeInfo->setText(QApplication::translate("NewProjectBatch", "\344\273\252\345\231\250:", 0));
        inputDescription->setText(QString());
        label_7->setText(QApplication::translate("NewProjectBatch", "\350\264\250\346\216\247\345\223\201:", 0));
        lblTestTypeInfo_2->setText(QApplication::translate("NewProjectBatch", "\350\257\225\345\211\202:", 0));
        pushButton->setText(QApplication::translate("NewProjectBatch", "\346\237\245\350\257\242", 0));
        btnConfigColumn->setText(QApplication::translate("NewProjectBatch", "\350\256\276\347\275\256", 0));
        lblTestTypeInfo_3->setText(QApplication::translate("NewProjectBatch", "\345\220\215\347\247\260:", 0));
    } // retranslateUi

};

namespace Ui {
    class NewProjectBatch: public Ui_NewProjectBatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTBATCH_H
