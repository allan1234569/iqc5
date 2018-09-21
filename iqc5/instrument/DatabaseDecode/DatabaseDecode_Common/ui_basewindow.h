/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QAction *action_DecodeSetup;
    QAction *action_Help;
    QAction *action_OriginalData;
    QAction *action_DecodeLog;
    QAction *action_ReadFile;
    QAction *action_ReHandle;
    QAction *action_Exit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *DbFilePath_LineEdit;
    QPushButton *Select_PushButton;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateEdit *SampleDate_DateEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *SampleRangeMin_LineEdit;
    QLabel *label_4;
    QLineEdit *SampleRangeMax_LineEdit;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *Original_TableWidget;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *After_TableWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *AutoIn_CheckBox;
    QPushButton *Import_PushButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;

    void setupUi(QMainWindow *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QStringLiteral("BaseWindow"));
        BaseWindow->resize(730, 474);
        action_DecodeSetup = new QAction(BaseWindow);
        action_DecodeSetup->setObjectName(QStringLiteral("action_DecodeSetup"));
        action_Help = new QAction(BaseWindow);
        action_Help->setObjectName(QStringLiteral("action_Help"));
        action_OriginalData = new QAction(BaseWindow);
        action_OriginalData->setObjectName(QStringLiteral("action_OriginalData"));
        action_DecodeLog = new QAction(BaseWindow);
        action_DecodeLog->setObjectName(QStringLiteral("action_DecodeLog"));
        action_ReadFile = new QAction(BaseWindow);
        action_ReadFile->setObjectName(QStringLiteral("action_ReadFile"));
        action_ReHandle = new QAction(BaseWindow);
        action_ReHandle->setObjectName(QStringLiteral("action_ReHandle"));
        action_Exit = new QAction(BaseWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        centralWidget = new QWidget(BaseWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        DbFilePath_LineEdit = new QLineEdit(centralWidget);
        DbFilePath_LineEdit->setObjectName(QStringLiteral("DbFilePath_LineEdit"));
        DbFilePath_LineEdit->setReadOnly(true);

        horizontalLayout->addWidget(DbFilePath_LineEdit);

        Select_PushButton = new QPushButton(centralWidget);
        Select_PushButton->setObjectName(QStringLiteral("Select_PushButton"));
        sizePolicy.setHeightForWidth(Select_PushButton->sizePolicy().hasHeightForWidth());
        Select_PushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Select_PushButton);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(60, 20));
        label_2->setMaximumSize(QSize(60, 20));

        horizontalLayout_2->addWidget(label_2);

        SampleDate_DateEdit = new QDateEdit(centralWidget);
        SampleDate_DateEdit->setObjectName(QStringLiteral("SampleDate_DateEdit"));
        sizePolicy.setHeightForWidth(SampleDate_DateEdit->sizePolicy().hasHeightForWidth());
        SampleDate_DateEdit->setSizePolicy(sizePolicy);
        SampleDate_DateEdit->setMinimumSize(QSize(100, 20));
        SampleDate_DateEdit->setMaximumSize(QSize(100, 20));

        horizontalLayout_2->addWidget(SampleDate_DateEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(70, 20));
        label_3->setMaximumSize(QSize(70, 20));

        horizontalLayout_2->addWidget(label_3);

        SampleRangeMin_LineEdit = new QLineEdit(centralWidget);
        SampleRangeMin_LineEdit->setObjectName(QStringLiteral("SampleRangeMin_LineEdit"));
        sizePolicy.setHeightForWidth(SampleRangeMin_LineEdit->sizePolicy().hasHeightForWidth());
        SampleRangeMin_LineEdit->setSizePolicy(sizePolicy);
        SampleRangeMin_LineEdit->setMinimumSize(QSize(100, 20));
        SampleRangeMin_LineEdit->setMaximumSize(QSize(100, 20));

        horizontalLayout_2->addWidget(SampleRangeMin_LineEdit);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(10, 20));
        label_4->setMaximumSize(QSize(10, 20));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_4);

        SampleRangeMax_LineEdit = new QLineEdit(centralWidget);
        SampleRangeMax_LineEdit->setObjectName(QStringLiteral("SampleRangeMax_LineEdit"));
        sizePolicy.setHeightForWidth(SampleRangeMax_LineEdit->sizePolicy().hasHeightForWidth());
        SampleRangeMax_LineEdit->setSizePolicy(sizePolicy);
        SampleRangeMax_LineEdit->setMinimumSize(QSize(100, 20));
        SampleRangeMax_LineEdit->setMaximumSize(QSize(100, 20));

        horizontalLayout_2->addWidget(SampleRangeMax_LineEdit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 1, 5, 5);
        Original_TableWidget = new QTableWidget(groupBox);
        if (Original_TableWidget->columnCount() < 5)
            Original_TableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Original_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Original_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Original_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Original_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        Original_TableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        Original_TableWidget->setObjectName(QStringLiteral("Original_TableWidget"));
        Original_TableWidget->setStyleSheet(QStringLiteral(""));
        Original_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Original_TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_4->addWidget(Original_TableWidget);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 1, 5, 5);
        After_TableWidget = new QTableWidget(groupBox_2);
        if (After_TableWidget->columnCount() < 5)
            After_TableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        After_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        After_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        After_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        After_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        After_TableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        After_TableWidget->setObjectName(QStringLiteral("After_TableWidget"));
        After_TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        After_TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        After_TableWidget->verticalHeader()->setVisible(true);

        horizontalLayout_3->addWidget(After_TableWidget);


        verticalLayout->addWidget(groupBox_2);


        horizontalLayout_5->addLayout(verticalLayout);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        AutoIn_CheckBox = new QCheckBox(widget);
        AutoIn_CheckBox->setObjectName(QStringLiteral("AutoIn_CheckBox"));
        sizePolicy.setHeightForWidth(AutoIn_CheckBox->sizePolicy().hasHeightForWidth());
        AutoIn_CheckBox->setSizePolicy(sizePolicy);
        AutoIn_CheckBox->setChecked(true);

        verticalLayout_2->addWidget(AutoIn_CheckBox);

        Import_PushButton = new QPushButton(widget);
        Import_PushButton->setObjectName(QStringLiteral("Import_PushButton"));
        sizePolicy.setHeightForWidth(Import_PushButton->sizePolicy().hasHeightForWidth());
        Import_PushButton->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(Import_PushButton);

        verticalSpacer = new QSpacerItem(17, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 7);

        horizontalLayout_5->addWidget(widget);


        verticalLayout_3->addLayout(horizontalLayout_5);

        BaseWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BaseWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 730, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        BaseWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action_Exit);
        menu_2->addAction(action_DecodeLog);
        menu_3->addAction(action_DecodeSetup);
        menu_4->addAction(action_Help);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "MainWindow", 0));
        action_DecodeSetup->setText(QApplication::translate("BaseWindow", "\350\256\276\347\275\256", 0));
        action_Help->setText(QApplication::translate("BaseWindow", "\345\270\256\345\212\251", 0));
        action_OriginalData->setText(QApplication::translate("BaseWindow", "\346\237\245\347\234\213\345\216\237\345\247\213\346\225\260\346\215\256", 0));
        action_DecodeLog->setText(QApplication::translate("BaseWindow", "\346\237\245\347\234\213\350\247\243\346\236\220\346\227\245\345\277\227", 0));
        action_ReadFile->setText(QApplication::translate("BaseWindow", "\350\257\273\345\217\226\346\226\207\344\273\266", 0));
        action_ReHandle->setText(QApplication::translate("BaseWindow", "\351\207\215\346\226\260\345\244\204\347\220\206\345\275\223\346\227\245\346\225\260\346\215\256", 0));
        action_Exit->setText(QApplication::translate("BaseWindow", "\351\200\200\345\207\272", 0));
        label->setText(QApplication::translate("BaseWindow", "\346\225\260\346\215\256\346\226\207\344\273\266\357\274\232", 0));
        Select_PushButton->setText(QApplication::translate("BaseWindow", "\351\200\211\346\213\251", 0));
        label_2->setText(QApplication::translate("BaseWindow", "\346\240\267\346\234\254\346\227\245\346\234\237\357\274\232", 0));
        SampleDate_DateEdit->setDisplayFormat(QApplication::translate("BaseWindow", "yyyy-MM-dd", 0));
        label_3->setText(QApplication::translate("BaseWindow", "\346\240\267\345\217\267\345\217\267\350\214\203\345\233\264\357\274\232", 0));
        label_4->setText(QApplication::translate("BaseWindow", "-", 0));
        groupBox->setTitle(QApplication::translate("BaseWindow", "\346\225\260\346\215\256\345\272\223\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem = Original_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BaseWindow", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = Original_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BaseWindow", "\351\241\271\347\233\256\344\273\243\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem2 = Original_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BaseWindow", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem3 = Original_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("BaseWindow", "\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem4 = Original_TableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("BaseWindow", "\345\215\225\344\275\215", 0));
        groupBox_2->setTitle(QApplication::translate("BaseWindow", "\345\267\262\345\205\245\345\272\223", 0));
        QTableWidgetItem *___qtablewidgetitem5 = After_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("BaseWindow", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem6 = After_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("BaseWindow", "\351\241\271\347\233\256\344\273\243\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem7 = After_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("BaseWindow", "\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem8 = After_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("BaseWindow", "\346\227\266\351\227\264", 0));
        QTableWidgetItem *___qtablewidgetitem9 = After_TableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QApplication::translate("BaseWindow", "\345\215\225\344\275\215", 0));
        AutoIn_CheckBox->setText(QApplication::translate("BaseWindow", "\350\207\252\345\212\250\345\205\245\345\272\223", 0));
        Import_PushButton->setText(QApplication::translate("BaseWindow", "\345\205\245 \345\272\223", 0));
        menu->setTitle(QApplication::translate("BaseWindow", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("BaseWindow", "\346\237\245\347\234\213", 0));
        menu_3->setTitle(QApplication::translate("BaseWindow", "\350\256\276\347\275\256", 0));
        menu_4->setTitle(QApplication::translate("BaseWindow", "\345\270\256\345\212\251", 0));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
