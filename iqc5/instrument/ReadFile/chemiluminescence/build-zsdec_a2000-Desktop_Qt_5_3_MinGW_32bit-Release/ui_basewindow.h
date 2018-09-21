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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
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
    QAction *action_ReceiveSetup;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *FilePath_LineEdit;
    QPushButton *Select_PushButton;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *main_VerticalLayout;
    QHBoxLayout *item_HorizontalLayout;
    QLabel *date_Label;
    QDateEdit *SampleDate_DateEdit;
    QLabel *item_Label;
    QComboBox *ItemCode_ComboBox;
    QLabel *FileSuffix_Label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *sample_horizontalLayout;
    QLabel *projectConfig_Label;
    QLineEdit *projectConfig_LineEdit;
    QPushButton *Allocation_PushButton;
    QCheckBox *autoAllocation_CheckBox;
    QLabel *nextSample_Label;
    QLabel *nextSampleNo_Label;
    QHBoxLayout *info_horizontalLayout;
    QGroupBox *result_GroupBox;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *Result_TableWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Refresh_PushButton;
    QPushButton *Import_PushButton;
    QComboBox *comboBox;
    QPushButton *Read_PushButton;
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
        BaseWindow->resize(721, 474);
        QIcon icon;
        icon.addFile(QStringLiteral(":/pics/analysis_128px.png"), QSize(), QIcon::Normal, QIcon::Off);
        BaseWindow->setWindowIcon(icon);
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
        action_ReceiveSetup = new QAction(BaseWindow);
        action_ReceiveSetup->setObjectName(QStringLiteral("action_ReceiveSetup"));
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

        FilePath_LineEdit = new QLineEdit(centralWidget);
        FilePath_LineEdit->setObjectName(QStringLiteral("FilePath_LineEdit"));
        FilePath_LineEdit->setReadOnly(true);

        horizontalLayout->addWidget(FilePath_LineEdit);

        Select_PushButton = new QPushButton(centralWidget);
        Select_PushButton->setObjectName(QStringLiteral("Select_PushButton"));
        sizePolicy.setHeightForWidth(Select_PushButton->sizePolicy().hasHeightForWidth());
        Select_PushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Select_PushButton);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        main_VerticalLayout = new QVBoxLayout();
        main_VerticalLayout->setSpacing(6);
        main_VerticalLayout->setObjectName(QStringLiteral("main_VerticalLayout"));
        item_HorizontalLayout = new QHBoxLayout();
        item_HorizontalLayout->setSpacing(6);
        item_HorizontalLayout->setObjectName(QStringLiteral("item_HorizontalLayout"));
        date_Label = new QLabel(centralWidget);
        date_Label->setObjectName(QStringLiteral("date_Label"));
        sizePolicy.setHeightForWidth(date_Label->sizePolicy().hasHeightForWidth());
        date_Label->setSizePolicy(sizePolicy);
        date_Label->setMinimumSize(QSize(60, 20));
        date_Label->setMaximumSize(QSize(60, 20));

        item_HorizontalLayout->addWidget(date_Label);

        SampleDate_DateEdit = new QDateEdit(centralWidget);
        SampleDate_DateEdit->setObjectName(QStringLiteral("SampleDate_DateEdit"));
        sizePolicy.setHeightForWidth(SampleDate_DateEdit->sizePolicy().hasHeightForWidth());
        SampleDate_DateEdit->setSizePolicy(sizePolicy);
        SampleDate_DateEdit->setMinimumSize(QSize(100, 20));
        SampleDate_DateEdit->setMaximumSize(QSize(100, 20));

        item_HorizontalLayout->addWidget(SampleDate_DateEdit);

        item_Label = new QLabel(centralWidget);
        item_Label->setObjectName(QStringLiteral("item_Label"));
        sizePolicy.setHeightForWidth(item_Label->sizePolicy().hasHeightForWidth());
        item_Label->setSizePolicy(sizePolicy);
        item_Label->setMinimumSize(QSize(60, 20));
        item_Label->setMaximumSize(QSize(60, 20));

        item_HorizontalLayout->addWidget(item_Label);

        ItemCode_ComboBox = new QComboBox(centralWidget);
        ItemCode_ComboBox->setObjectName(QStringLiteral("ItemCode_ComboBox"));
        sizePolicy.setHeightForWidth(ItemCode_ComboBox->sizePolicy().hasHeightForWidth());
        ItemCode_ComboBox->setSizePolicy(sizePolicy);
        ItemCode_ComboBox->setMinimumSize(QSize(100, 20));
        ItemCode_ComboBox->setMaximumSize(QSize(100, 20));
        ItemCode_ComboBox->setEditable(true);

        item_HorizontalLayout->addWidget(ItemCode_ComboBox);

        FileSuffix_Label = new QLabel(centralWidget);
        FileSuffix_Label->setObjectName(QStringLiteral("FileSuffix_Label"));
        sizePolicy.setHeightForWidth(FileSuffix_Label->sizePolicy().hasHeightForWidth());
        FileSuffix_Label->setSizePolicy(sizePolicy);
        FileSuffix_Label->setMinimumSize(QSize(60, 20));
        FileSuffix_Label->setMaximumSize(QSize(60, 20));
        FileSuffix_Label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        item_HorizontalLayout->addWidget(FileSuffix_Label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        item_HorizontalLayout->addItem(horizontalSpacer_2);


        main_VerticalLayout->addLayout(item_HorizontalLayout);

        sample_horizontalLayout = new QHBoxLayout();
        sample_horizontalLayout->setSpacing(6);
        sample_horizontalLayout->setObjectName(QStringLiteral("sample_horizontalLayout"));
        projectConfig_Label = new QLabel(centralWidget);
        projectConfig_Label->setObjectName(QStringLiteral("projectConfig_Label"));
        sizePolicy.setHeightForWidth(projectConfig_Label->sizePolicy().hasHeightForWidth());
        projectConfig_Label->setSizePolicy(sizePolicy);
        projectConfig_Label->setMinimumSize(QSize(60, 20));
        projectConfig_Label->setMaximumSize(QSize(60, 20));

        sample_horizontalLayout->addWidget(projectConfig_Label);

        projectConfig_LineEdit = new QLineEdit(centralWidget);
        projectConfig_LineEdit->setObjectName(QStringLiteral("projectConfig_LineEdit"));

        sample_horizontalLayout->addWidget(projectConfig_LineEdit);

        Allocation_PushButton = new QPushButton(centralWidget);
        Allocation_PushButton->setObjectName(QStringLiteral("Allocation_PushButton"));
        sizePolicy.setHeightForWidth(Allocation_PushButton->sizePolicy().hasHeightForWidth());
        Allocation_PushButton->setSizePolicy(sizePolicy);
        Allocation_PushButton->setMinimumSize(QSize(70, 20));
        Allocation_PushButton->setMaximumSize(QSize(70, 20));

        sample_horizontalLayout->addWidget(Allocation_PushButton);

        autoAllocation_CheckBox = new QCheckBox(centralWidget);
        autoAllocation_CheckBox->setObjectName(QStringLiteral("autoAllocation_CheckBox"));
        sizePolicy.setHeightForWidth(autoAllocation_CheckBox->sizePolicy().hasHeightForWidth());
        autoAllocation_CheckBox->setSizePolicy(sizePolicy);
        autoAllocation_CheckBox->setMinimumSize(QSize(70, 20));
        autoAllocation_CheckBox->setMaximumSize(QSize(70, 20));

        sample_horizontalLayout->addWidget(autoAllocation_CheckBox);

        nextSample_Label = new QLabel(centralWidget);
        nextSample_Label->setObjectName(QStringLiteral("nextSample_Label"));
        sizePolicy.setHeightForWidth(nextSample_Label->sizePolicy().hasHeightForWidth());
        nextSample_Label->setSizePolicy(sizePolicy);
        nextSample_Label->setMinimumSize(QSize(80, 20));
        nextSample_Label->setMaximumSize(QSize(80, 20));

        sample_horizontalLayout->addWidget(nextSample_Label);

        nextSampleNo_Label = new QLabel(centralWidget);
        nextSampleNo_Label->setObjectName(QStringLiteral("nextSampleNo_Label"));
        sizePolicy.setHeightForWidth(nextSampleNo_Label->sizePolicy().hasHeightForWidth());
        nextSampleNo_Label->setSizePolicy(sizePolicy);
        nextSampleNo_Label->setMinimumSize(QSize(60, 20));
        nextSampleNo_Label->setMaximumSize(QSize(60, 20));
        nextSampleNo_Label->setAlignment(Qt::AlignCenter);

        sample_horizontalLayout->addWidget(nextSampleNo_Label);


        main_VerticalLayout->addLayout(sample_horizontalLayout);

        info_horizontalLayout = new QHBoxLayout();
        info_horizontalLayout->setSpacing(1);
        info_horizontalLayout->setObjectName(QStringLiteral("info_horizontalLayout"));
        result_GroupBox = new QGroupBox(centralWidget);
        result_GroupBox->setObjectName(QStringLiteral("result_GroupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(result_GroupBox->sizePolicy().hasHeightForWidth());
        result_GroupBox->setSizePolicy(sizePolicy1);
        result_GroupBox->setMinimumSize(QSize(220, 0));
        result_GroupBox->setMaximumSize(QSize(220, 16777215));
        horizontalLayout_4 = new QHBoxLayout(result_GroupBox);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 1, 5, 5);
        listWidget = new QListWidget(result_GroupBox);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setDragDropMode(QAbstractItemView::NoDragDrop);

        horizontalLayout_4->addWidget(listWidget);


        info_horizontalLayout->addWidget(result_GroupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 1, 5, 5);
        Result_TableWidget = new QTableWidget(groupBox_2);
        if (Result_TableWidget->columnCount() < 7)
            Result_TableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Result_TableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        Result_TableWidget->setObjectName(QStringLiteral("Result_TableWidget"));
        Result_TableWidget->setStyleSheet(QStringLiteral(""));
        Result_TableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        Result_TableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        Result_TableWidget->verticalHeader()->setVisible(false);

        horizontalLayout_3->addWidget(Result_TableWidget);


        info_horizontalLayout->addWidget(groupBox_2);

        info_horizontalLayout->setStretch(0, 3);
        info_horizontalLayout->setStretch(1, 7);

        main_VerticalLayout->addLayout(info_horizontalLayout);


        horizontalLayout_7->addLayout(main_VerticalLayout);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        Refresh_PushButton = new QPushButton(widget);
        Refresh_PushButton->setObjectName(QStringLiteral("Refresh_PushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Refresh_PushButton->sizePolicy().hasHeightForWidth());
        Refresh_PushButton->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(Refresh_PushButton);

        Import_PushButton = new QPushButton(widget);
        Import_PushButton->setObjectName(QStringLiteral("Import_PushButton"));
        sizePolicy2.setHeightForWidth(Import_PushButton->sizePolicy().hasHeightForWidth());
        Import_PushButton->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(Import_PushButton);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        Read_PushButton = new QPushButton(widget);
        Read_PushButton->setObjectName(QStringLiteral("Read_PushButton"));

        verticalLayout_2->addWidget(Read_PushButton);

        verticalSpacer = new QSpacerItem(17, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(5, 7);

        horizontalLayout_7->addWidget(widget);


        verticalLayout_3->addLayout(horizontalLayout_7);

        BaseWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BaseWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 721, 23));
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
        menu_3->addAction(action_ReceiveSetup);
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
        action_ReceiveSetup->setText(QApplication::translate("BaseWindow", "\346\216\245\346\224\266\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("BaseWindow", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", 0));
        Select_PushButton->setText(QApplication::translate("BaseWindow", "\351\200\211\346\213\251", 0));
        date_Label->setText(QApplication::translate("BaseWindow", "\345\205\245\345\272\223\346\227\245\346\234\237\357\274\232", 0));
        SampleDate_DateEdit->setDisplayFormat(QApplication::translate("BaseWindow", "yyyy-MM-dd", 0));
        item_Label->setText(QApplication::translate("BaseWindow", "\351\241\271\347\233\256\357\274\232", 0));
        FileSuffix_Label->setText(QString());
        projectConfig_Label->setText(QApplication::translate("BaseWindow", "\351\241\271\347\233\256\350\256\276\347\275\256\357\274\232", 0));
        Allocation_PushButton->setText(QApplication::translate("BaseWindow", "\345\274\200\345\247\213\345\210\206\351\205\215", 0));
        autoAllocation_CheckBox->setText(QApplication::translate("BaseWindow", "\350\207\252\345\212\250\351\205\215\347\275\256", 0));
        nextSample_Label->setText(QApplication::translate("BaseWindow", "\344\270\213\344\270\200\344\270\252\346\240\267\346\234\254\345\217\267\357\274\232", 0));
        nextSampleNo_Label->setText(QApplication::translate("BaseWindow", "1001", 0));
        result_GroupBox->setTitle(QApplication::translate("BaseWindow", "\347\273\223\346\236\234\346\226\207\344\273\266", 0));
        groupBox_2->setTitle(QApplication::translate("BaseWindow", "\345\205\245\345\272\223\344\277\241\346\201\257", 0));
        QTableWidgetItem *___qtablewidgetitem = Result_TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BaseWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem1 = Result_TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BaseWindow", "\346\240\267\346\234\254\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem2 = Result_TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("BaseWindow", "\351\241\271\347\233\256\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem3 = Result_TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("BaseWindow", "\346\265\223\345\272\246\346\260\264\345\271\263", 0));
        QTableWidgetItem *___qtablewidgetitem4 = Result_TableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("BaseWindow", "\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem5 = Result_TableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("BaseWindow", "\346\227\245\346\234\237", 0));
        QTableWidgetItem *___qtablewidgetitem6 = Result_TableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("BaseWindow", "\347\212\266\346\200\201", 0));
        Refresh_PushButton->setText(QApplication::translate("BaseWindow", "\345\210\267 \346\226\260", 0));
        Import_PushButton->setText(QApplication::translate("BaseWindow", "\345\205\245 \345\272\223", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("BaseWindow", "\345\215\225\351\241\271\347\233\256\345\257\274\345\205\245", 0)
         << QApplication::translate("BaseWindow", "\345\244\232\351\241\271\347\233\256\345\257\274\345\205\245", 0)
        );
        Read_PushButton->setText(QApplication::translate("BaseWindow", "\350\257\273\345\217\226", 0));
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
