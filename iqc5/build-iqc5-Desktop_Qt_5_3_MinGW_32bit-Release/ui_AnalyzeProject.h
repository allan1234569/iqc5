/********************************************************************************
** Form generated from reading UI file 'AnalyzeProject.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEPROJECT_H
#define UI_ANALYZEPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalyzeProject
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *inputKeyword;
    QTreeWidget *treeWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *ruleGroup;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *singleRuleContainer;
    QComboBox *inputN;
    QPushButton *btnAddRule;
    QPushButton *btnImport;
    QPushButton *dataImport;
    QCheckBox *cbkShowAll;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;
    QSplitter *splitter;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_Z;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *layout_z;

    void setupUi(QMainWindow *AnalyzeProject)
    {
        if (AnalyzeProject->objectName().isEmpty())
            AnalyzeProject->setObjectName(QStringLiteral("AnalyzeProject"));
        AnalyzeProject->resize(749, 559);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        AnalyzeProject->setWindowIcon(icon);
        centralwidget = new QWidget(AnalyzeProject);
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

        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        ruleGroup = new QGroupBox(widget);
        ruleGroup->setObjectName(QStringLiteral("ruleGroup"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ruleGroup->sizePolicy().hasHeightForWidth());
        ruleGroup->setSizePolicy(sizePolicy1);
        ruleGroup->setMinimumSize(QSize(0, 0));
        ruleGroup->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(ruleGroup);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        singleRuleContainer = new QHBoxLayout();
        singleRuleContainer->setObjectName(QStringLiteral("singleRuleContainer"));

        horizontalLayout_2->addLayout(singleRuleContainer);

        inputN = new QComboBox(ruleGroup);
        inputN->setObjectName(QStringLiteral("inputN"));
        inputN->setEditable(false);

        horizontalLayout_2->addWidget(inputN);

        btnAddRule = new QPushButton(ruleGroup);
        btnAddRule->setObjectName(QStringLiteral("btnAddRule"));

        horizontalLayout_2->addWidget(btnAddRule);

        btnImport = new QPushButton(ruleGroup);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        QFont font;
        font.setPointSize(8);
        btnImport->setFont(font);
        btnImport->setFlat(false);

        horizontalLayout_2->addWidget(btnImport);

        dataImport = new QPushButton(ruleGroup);
        dataImport->setObjectName(QStringLiteral("dataImport"));

        horizontalLayout_2->addWidget(dataImport);

        cbkShowAll = new QCheckBox(ruleGroup);
        cbkShowAll->setObjectName(QStringLiteral("cbkShowAll"));

        horizontalLayout_2->addWidget(cbkShowAll);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(ruleGroup);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(0, 60));
        listWidget->setMaximumSize(QSize(16777215, 60));

        verticalLayout_2->addWidget(listWidget);


        verticalLayout_3->addWidget(ruleGroup);

        splitter = new QSplitter(widget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 0));
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidget = new QTabWidget(groupBox_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setIconSize(QSize(16, 16));

        verticalLayout_5->addWidget(tabWidget);

        splitter->addWidget(groupBox_2);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget_Z = new QWidget(groupBox);
        widget_Z->setObjectName(QStringLiteral("widget_Z"));
        widget_Z->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setKerning(true);
        widget_Z->setFont(font1);
        verticalLayout_4 = new QVBoxLayout(widget_Z);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        layout_z = new QVBoxLayout();
        layout_z->setSpacing(0);
        layout_z->setObjectName(QStringLiteral("layout_z"));

        verticalLayout_4->addLayout(layout_z);


        horizontalLayout_3->addWidget(widget_Z);

        splitter->addWidget(groupBox);

        verticalLayout_3->addWidget(splitter);

        splitter->raise();
        ruleGroup->raise();

        horizontalLayout->addWidget(widget);

        AnalyzeProject->setCentralWidget(centralwidget);

        retranslateUi(AnalyzeProject);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(AnalyzeProject);
    } // setupUi

    void retranslateUi(QMainWindow *AnalyzeProject)
    {
        AnalyzeProject->setWindowTitle(QApplication::translate("AnalyzeProject", "\350\264\250\346\216\247\345\210\206\346\236\220", 0));
        groupBox_3->setTitle(QApplication::translate("AnalyzeProject", "\350\257\267\351\200\211\346\213\251\351\241\271\347\233\256", 0));
        ruleGroup->setTitle(QApplication::translate("AnalyzeProject", "\350\257\267\351\200\211\346\213\251\346\226\271\346\241\210", 0));
        inputN->clear();
        inputN->insertItems(0, QStringList()
         << QApplication::translate("AnalyzeProject", " n = 1", 0)
         << QApplication::translate("AnalyzeProject", " n = 2", 0)
         << QApplication::translate("AnalyzeProject", " n = 3", 0)
         << QApplication::translate("AnalyzeProject", " n = 4", 0)
         << QApplication::translate("AnalyzeProject", " n = 5", 0)
         << QApplication::translate("AnalyzeProject", " n = 6", 0)
        );
        btnAddRule->setText(QApplication::translate("AnalyzeProject", "\346\267\273\345\212\240\350\247\204\345\210\231", 0));
        btnImport->setText(QApplication::translate("AnalyzeProject", "\345\257\274\345\205\245", 0));
        dataImport->setText(QApplication::translate("AnalyzeProject", " \346\225\260\346\215\256\345\275\225\345\205\245", 0));
        cbkShowAll->setText(QApplication::translate("AnalyzeProject", "\346\211\200\346\234\211\350\264\250\346\216\247\345\223\201", 0));
#ifndef QT_NO_TOOLTIP
        listWidget->setToolTip(QApplication::translate("AnalyzeProject", "\345\217\214\345\207\273\345\217\257\345\210\240\351\231\244\350\257\245\350\247\204\345\210\231", 0));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("AnalyzeProject", "Levey-Jenning\350\264\250\346\216\247\345\233\276", 0));
        groupBox->setTitle(QApplication::translate("AnalyzeProject", "Z\345\210\206\346\225\260\350\264\250\346\216\247\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class AnalyzeProject: public Ui_AnalyzeProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEPROJECT_H
