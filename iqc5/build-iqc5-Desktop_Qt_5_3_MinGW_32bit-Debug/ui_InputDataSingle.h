/********************************************************************************
** Form generated from reading UI file 'InputDataSingle.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDATASINGLE_H
#define UI_INPUTDATASINGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputDataSingle
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget_1;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QLabel *label_2;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLabel *label_3;
    QLabel *lblTestTypeInfo;
    QLineEdit *inputDeviceName;
    QLabel *inputDescription;
    QLabel *label_8;
    QLineEdit *inputCustomName;
    QLineEdit *inputEnglishName;
    QLabel *label_9;
    QLineEdit *inputChineseName;
    QLabel *label_10;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *widget_4;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QGroupBox *groupBox_4;

    void setupUi(QMainWindow *InputDataSingle)
    {
        if (InputDataSingle->objectName().isEmpty())
            InputDataSingle->setObjectName(QStringLiteral("InputDataSingle"));
        InputDataSingle->resize(991, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        InputDataSingle->setWindowIcon(icon);
        centralwidget = new QWidget(InputDataSingle);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 200));
        groupBox->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        inputKeyword = new QLineEdit(groupBox);
        inputKeyword->setObjectName(QStringLiteral("inputKeyword"));

        verticalLayout->addWidget(inputKeyword);

        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);


        horizontalLayout_2->addWidget(groupBox);

        widget_1 = new QWidget(centralwidget);
        widget_1->setObjectName(QStringLiteral("widget_1"));
        verticalLayout_2 = new QVBoxLayout(widget_1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget_2 = new QWidget(widget_1);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(0, 120));
        widget_2->setMaximumSize(QSize(16777215, 120));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(446, 59, 81, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputCategory = new QComboBox(widget_2);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(528, 55, 141, 22));
        inputSubject = new QComboBox(widget_2);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(315, 54, 141, 22));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(263, 53, 51, 20));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblTestTypeInfo = new QLabel(widget_2);
        lblTestTypeInfo->setObjectName(QStringLiteral("lblTestTypeInfo"));
        lblTestTypeInfo->setGeometry(QRect(77, 54, 31, 20));
        lblTestTypeInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputDeviceName = new QLineEdit(widget_2);
        inputDeviceName->setObjectName(QStringLiteral("inputDeviceName"));
        inputDeviceName->setGeometry(QRect(111, 53, 141, 20));
        inputDescription = new QLabel(widget_2);
        inputDescription->setObjectName(QStringLiteral("inputDescription"));
        inputDescription->setGeometry(QRect(340, 76, 201, 16));
        inputDescription->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 25, 81, 16));
        inputCustomName = new QLineEdit(widget_2);
        inputCustomName->setObjectName(QStringLiteral("inputCustomName"));
        inputCustomName->setGeometry(QRect(112, 21, 141, 20));
        inputEnglishName = new QLineEdit(widget_2);
        inputEnglishName->setObjectName(QStringLiteral("inputEnglishName"));
        inputEnglishName->setGeometry(QRect(315, 22, 141, 20));
        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(258, 22, 81, 16));
        inputChineseName = new QLineEdit(widget_2);
        inputChineseName->setObjectName(QStringLiteral("inputChineseName"));
        inputChineseName->setGeometry(QRect(528, 24, 141, 20));
        label_10 = new QLabel(widget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(474, 23, 81, 16));

        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(widget_1);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(widget_3);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));

        horizontalLayout->addWidget(tabWidget);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setMinimumSize(QSize(80, 0));
        btnAdd = new QPushButton(widget_4);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setGeometry(QRect(10, 150, 32, 32));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/add_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon1);
        btnAdd->setIconSize(QSize(32, 32));
        btnAdd->setFlat(true);
        btnDelete = new QPushButton(widget_4);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(10, 190, 32, 32));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/delete_big.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon2);
        btnDelete->setIconSize(QSize(32, 32));
        btnDelete->setFlat(true);
        btnOK = new QPushButton(widget_4);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(0, 310, 71, 23));
        btnCancel = new QPushButton(widget_4);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(0, 350, 71, 23));

        horizontalLayout->addWidget(widget_4);


        verticalLayout_2->addWidget(widget_3);

        groupBox_4 = new QGroupBox(widget_1);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 40));
        groupBox_4->setMaximumSize(QSize(16777215, 40));

        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout_2->addWidget(widget_1);

        InputDataSingle->setCentralWidget(centralwidget);

        retranslateUi(InputDataSingle);

        QMetaObject::connectSlotsByName(InputDataSingle);
    } // setupUi

    void retranslateUi(QMainWindow *InputDataSingle)
    {
        InputDataSingle->setWindowTitle(QApplication::translate("InputDataSingle", "\351\241\271\347\233\256\346\265\217\350\247\210", 0));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("InputDataSingle", "\344\272\232\344\270\223\344\270\232:", 0));
        label_3->setText(QApplication::translate("InputDataSingle", "\344\270\223\344\270\232:", 0));
        lblTestTypeInfo->setText(QApplication::translate("InputDataSingle", "\344\273\252\345\231\250:", 0));
        inputDescription->setText(QString());
        label_8->setText(QApplication::translate("InputDataSingle", "\350\207\252\345\256\232\344\271\211\345\220\215\347\247\260:", 0));
        label_9->setText(QApplication::translate("InputDataSingle", "\350\213\261\346\226\207\347\256\200\347\247\260:", 0));
        label_10->setText(QApplication::translate("InputDataSingle", "\344\270\255\346\226\207\345\205\250\347\247\260:", 0));
        btnAdd->setText(QString());
        btnDelete->setText(QString());
        btnOK->setText(QApplication::translate("InputDataSingle", "\344\277\235\345\255\230", 0));
        btnCancel->setText(QApplication::translate("InputDataSingle", "\345\205\263\351\227\255", 0));
        groupBox_4->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class InputDataSingle: public Ui_InputDataSingle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDATASINGLE_H
