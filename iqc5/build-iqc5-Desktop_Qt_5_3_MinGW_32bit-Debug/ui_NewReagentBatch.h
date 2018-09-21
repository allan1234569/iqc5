/********************************************************************************
** Form generated from reading UI file 'NewReagentBatch.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWREAGENTBATCH_H
#define UI_NEWREAGENTBATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewReagentBatch
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget_1;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_button;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *table;
    QWidget *widget_3;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QWidget *widget_4;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *inputBatchNo;
    QLabel *inputDescription;
    QLabel *label_7;
    QLineEdit *inputRegisterNo;
    QPushButton *pushButton;
    QLabel *lblTestTypeInfo_3;
    QLineEdit *inputReagentName;
    QLineEdit *inputCountry;
    QLineEdit *inputMenufacturer;

    void setupUi(QMainWindow *NewReagentBatch)
    {
        if (NewReagentBatch->objectName().isEmpty())
            NewReagentBatch->setObjectName(QStringLiteral("NewReagentBatch"));
        NewReagentBatch->resize(1144, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewReagentBatch->setWindowIcon(icon);
        centralwidget = new QWidget(NewReagentBatch);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputKeyword = new QLineEdit(groupBox_3);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox_3);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout->addWidget(groupBox_3);

        widget_1 = new QWidget(centralwidget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        verticalLayout_2 = new QVBoxLayout(widget_1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_button = new QWidget(widget_1);
        widget_button->setObjectName(QStringLiteral("widget_button"));
        horizontalLayout_2 = new QHBoxLayout(widget_button);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        table = new QTableWidget(widget_button);
        table->setObjectName(QStringLiteral("table"));

        horizontalLayout_2->addWidget(table);

        widget_3 = new QWidget(widget_button);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(80, 0));
        btnAdd = new QPushButton(widget_3);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(10, 150, 32, 32));
        btnAdd->setIconSize(QSize(32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_3);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 190, 32, 32));
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);
        btnOK = new QPushButton(widget_3);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(0, 360, 75, 23));
        btnCancel = new QPushButton(widget_3);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(0, 390, 75, 23));

        horizontalLayout_2->addWidget(widget_3);


        verticalLayout_2->addWidget(widget_button);

        widget_4 = new QWidget(widget_1);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(0, 80));
        widget_4->setMaximumSize(QSize(16777215, 80));
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(70, 50, 41, 16));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 21, 81, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 20, 51, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputBatchNo = new QLineEdit(widget_4);
        inputBatchNo->setObjectName(QStringLiteral("inputBatchNo"));
        inputBatchNo->setGeometry(QRect(110, 50, 141, 20));
        inputDescription = new QLabel(widget_4);
        inputDescription->setObjectName(QStringLiteral("inputDescription"));
        inputDescription->setGeometry(QRect(340, 76, 201, 16));
        inputDescription->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(widget_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(260, 52, 81, 16));
        inputRegisterNo = new QLineEdit(widget_4);
        inputRegisterNo->setObjectName(QStringLiteral("inputRegisterNo"));
        inputRegisterNo->setGeometry(QRect(310, 50, 121, 20));
        pushButton = new QPushButton(widget_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(663, 49, 75, 23));
        lblTestTypeInfo_3 = new QLabel(widget_4);
        lblTestTypeInfo_3->setObjectName(QStringLiteral("lblTestTypeInfo_3"));
        lblTestTypeInfo_3->setGeometry(QRect(440, 21, 71, 20));
        lblTestTypeInfo_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputReagentName = new QLineEdit(widget_4);
        inputReagentName->setObjectName(QStringLiteral("inputReagentName"));
        inputReagentName->setGeometry(QRect(510, 20, 141, 20));
        inputCountry = new QLineEdit(widget_4);
        inputCountry->setObjectName(QStringLiteral("inputCountry"));
        inputCountry->setGeometry(QRect(110, 20, 141, 20));
        inputMenufacturer = new QLineEdit(widget_4);
        inputMenufacturer->setObjectName(QStringLiteral("inputMenufacturer"));
        inputMenufacturer->setGeometry(QRect(310, 20, 121, 20));

        verticalLayout_2->addWidget(widget_4);


        horizontalLayout->addWidget(widget_1);

        NewReagentBatch->setCentralWidget(centralwidget);

        retranslateUi(NewReagentBatch);

        QMetaObject::connectSlotsByName(NewReagentBatch);
    } // setupUi

    void retranslateUi(QMainWindow *NewReagentBatch)
    {
        NewReagentBatch->setWindowTitle(QApplication::translate("NewReagentBatch", "\350\257\225\345\211\202\346\211\271\351\207\217\346\226\260\345\273\272", 0));
        groupBox_3->setTitle(QString());
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnOK->setText(QApplication::translate("NewReagentBatch", "\344\277\235\345\255\230", 0));
        btnCancel->setText(QApplication::translate("NewReagentBatch", "\345\205\263\351\227\255", 0));
        label_6->setText(QApplication::translate("NewReagentBatch", "\346\211\271\345\217\267:", 0));
        label_2->setText(QApplication::translate("NewReagentBatch", "\345\216\202\345\256\266:", 0));
        label_3->setText(QApplication::translate("NewReagentBatch", "\344\272\247\345\234\260:", 0));
        inputDescription->setText(QString());
        label_7->setText(QApplication::translate("NewReagentBatch", "\346\263\250\345\206\214\345\217\267:", 0));
        pushButton->setText(QApplication::translate("NewReagentBatch", "\346\237\245\350\257\242", 0));
        lblTestTypeInfo_3->setText(QApplication::translate("NewReagentBatch", "\350\264\250\346\216\247\345\223\201\345\220\215\347\247\260:", 0));
    } // retranslateUi

};

namespace Ui {
    class NewReagentBatch: public Ui_NewReagentBatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWREAGENTBATCH_H
