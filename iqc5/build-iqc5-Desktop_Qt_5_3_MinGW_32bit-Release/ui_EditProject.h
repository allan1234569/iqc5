/********************************************************************************
** Form generated from reading UI file 'EditProject.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROJECT_H
#define UI_EDITPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_EditProject
{
public:
    QGroupBox *groupBox;
    QLabel *label_6;
    QLabel *label_2;
    QComboBox *inputCategory;
    QComboBox *inputSubject;
    QLabel *label_3;
    QComboBox *inputTestType;
    QLabel *label_9;
    QComboBox *inputStandard;
    QLabel *label_11;
    QLabel *lblTestTypeInfo;
    QSpinBox *inputLevel;
    QLabel *label_15;
    QLineEdit *inputMethodName;
    QLineEdit *inputDeviceName;
    QLabel *inputDescription;
    QPushButton *btnOK;
    QPushButton *btnCancel;
    QPushButton *btnImport;
    QGroupBox *groupBox_4;
    QLabel *label_13;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *txtCustomName;
    QLineEdit *txtProjectName;
    QLineEdit *txtEnglishName;
    QGroupBox *groupBox_2;
    QComboBox *inputGroup;
    QLabel *label_7;
    QComboBox *inputOffice;
    QComboBox *inputSection;
    QLabel *label_4;
    QLabel *label_12;
    QLineEdit *txtCreator;
    QLabel *label_5;
    QComboBox *inputHospital;
    QLabel *label_8;
    QListWidget *lstProjectName;
    QCheckBox *ckbOnOpen;

    void setupUi(QDialog *EditProject)
    {
        if (EditProject->objectName().isEmpty())
            EditProject->setObjectName(QStringLiteral("EditProject"));
        EditProject->resize(644, 556);
        groupBox = new QGroupBox(EditProject);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 237, 621, 164));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 93, 81, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(310, 17, 81, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputCategory = new QComboBox(groupBox);
        inputCategory->setObjectName(QStringLiteral("inputCategory"));
        inputCategory->setGeometry(QRect(400, 17, 141, 22));
        inputSubject = new QComboBox(groupBox);
        inputSubject->setObjectName(QStringLiteral("inputSubject"));
        inputSubject->setGeometry(QRect(90, 17, 141, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 17, 81, 16));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputTestType = new QComboBox(groupBox);
        inputTestType->setObjectName(QStringLiteral("inputTestType"));
        inputTestType->setGeometry(QRect(90, 51, 141, 22));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 51, 51, 20));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputStandard = new QComboBox(groupBox);
        inputStandard->setObjectName(QStringLiteral("inputStandard"));
        inputStandard->setGeometry(QRect(400, 52, 141, 22));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(330, 52, 61, 20));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblTestTypeInfo = new QLabel(groupBox);
        lblTestTypeInfo->setObjectName(QStringLiteral("lblTestTypeInfo"));
        lblTestTypeInfo->setGeometry(QRect(360, 91, 31, 20));
        lblTestTypeInfo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        inputLevel = new QSpinBox(groupBox);
        inputLevel->setObjectName(QStringLiteral("inputLevel"));
        inputLevel->setGeometry(QRect(90, 128, 141, 22));
        inputLevel->setMinimum(1);
        inputLevel->setMaximum(100);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(50, 131, 51, 16));
        inputMethodName = new QLineEdit(groupBox);
        inputMethodName->setObjectName(QStringLiteral("inputMethodName"));
        inputMethodName->setGeometry(QRect(90, 91, 141, 20));
        inputDeviceName = new QLineEdit(groupBox);
        inputDeviceName->setObjectName(QStringLiteral("inputDeviceName"));
        inputDeviceName->setGeometry(QRect(400, 92, 141, 20));
        inputDescription = new QLabel(groupBox);
        inputDescription->setObjectName(QStringLiteral("inputDescription"));
        inputDescription->setGeometry(QRect(340, 76, 201, 16));
        inputDescription->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnOK = new QPushButton(EditProject);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(130, 448, 75, 23));
        btnCancel = new QPushButton(EditProject);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(220, 448, 75, 23));
        btnImport = new QPushButton(EditProject);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        btnImport->setGeometry(QRect(320, 448, 75, 23));
        groupBox_4 = new QGroupBox(EditProject);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 8, 621, 92));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(330, 20, 47, 20));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(groupBox_4);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 54, 52, 20));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_17 = new QLabel(groupBox_4);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(20, 20, 47, 20));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtCustomName = new QLineEdit(groupBox_4);
        txtCustomName->setObjectName(QStringLiteral("txtCustomName"));
        txtCustomName->setGeometry(QRect(80, 20, 151, 20));
        txtProjectName = new QLineEdit(groupBox_4);
        txtProjectName->setObjectName(QStringLiteral("txtProjectName"));
        txtProjectName->setGeometry(QRect(390, 20, 151, 20));
        txtEnglishName = new QLineEdit(groupBox_4);
        txtEnglishName->setObjectName(QStringLiteral("txtEnglishName"));
        txtEnglishName->setGeometry(QRect(80, 55, 151, 20));
        groupBox_2 = new QGroupBox(EditProject);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 109, 621, 120));
        inputGroup = new QComboBox(groupBox_2);
        inputGroup->setObjectName(QStringLiteral("inputGroup"));
        inputGroup->setGeometry(QRect(390, 48, 151, 22));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 49, 21, 20));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputOffice = new QComboBox(groupBox_2);
        inputOffice->setObjectName(QStringLiteral("inputOffice"));
        inputOffice->setGeometry(QRect(80, 48, 151, 22));
        inputSection = new QComboBox(groupBox_2);
        inputSection->setObjectName(QStringLiteral("inputSection"));
        inputSection->setGeometry(QRect(390, 14, 151, 22));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 10, 31, 20));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(30, 86, 43, 20));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtCreator = new QLineEdit(groupBox_2);
        txtCreator->setObjectName(QStringLiteral("txtCreator"));
        txtCreator->setGeometry(QRect(80, 87, 151, 20));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(360, 15, 21, 20));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        inputHospital = new QComboBox(groupBox_2);
        inputHospital->setObjectName(QStringLiteral("inputHospital"));
        inputHospital->setGeometry(QRect(80, 13, 151, 22));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(350, 50, 31, 20));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lstProjectName = new QListWidget(EditProject);
        lstProjectName->setObjectName(QStringLiteral("lstProjectName"));
        lstProjectName->setGeometry(QRect(400, 48, 151, 191));
        ckbOnOpen = new QCheckBox(EditProject);
        ckbOnOpen->setObjectName(QStringLiteral("ckbOnOpen"));
        ckbOnOpen->setGeometry(QRect(440, 451, 171, 16));
        QWidget::setTabOrder(txtCustomName, txtProjectName);
        QWidget::setTabOrder(txtProjectName, txtEnglishName);
        QWidget::setTabOrder(txtEnglishName, inputHospital);
        QWidget::setTabOrder(inputHospital, inputSection);
        QWidget::setTabOrder(inputSection, inputOffice);
        QWidget::setTabOrder(inputOffice, inputGroup);
        QWidget::setTabOrder(inputGroup, txtCreator);
        QWidget::setTabOrder(txtCreator, inputSubject);
        QWidget::setTabOrder(inputSubject, inputCategory);
        QWidget::setTabOrder(inputCategory, inputTestType);
        QWidget::setTabOrder(inputTestType, inputStandard);
        QWidget::setTabOrder(inputStandard, inputLevel);
        QWidget::setTabOrder(inputLevel, btnCancel);
        QWidget::setTabOrder(btnCancel, btnImport);
        QWidget::setTabOrder(btnImport, btnOK);

        retranslateUi(EditProject);

        QMetaObject::connectSlotsByName(EditProject);
    } // setupUi

    void retranslateUi(QDialog *EditProject)
    {
        EditProject->setWindowTitle(QApplication::translate("EditProject", "\346\226\260\345\273\272\351\241\271\347\233\256", 0));
        groupBox->setTitle(QString());
        label_6->setText(QApplication::translate("EditProject", "\346\243\200\346\265\213\346\226\271\346\263\225:", 0));
        label_2->setText(QApplication::translate("EditProject", "\344\272\232\344\270\223\344\270\232:", 0));
        label_3->setText(QApplication::translate("EditProject", "\344\270\223\344\270\232:", 0));
        label_9->setText(QApplication::translate("EditProject", "\351\241\271\347\233\256:", 0));
        label_11->setText(QApplication::translate("EditProject", "\351\200\211\346\213\251\346\240\207\345\207\206:", 0));
        lblTestTypeInfo->setText(QApplication::translate("EditProject", "\344\273\252\345\231\250:", 0));
        label_15->setText(QApplication::translate("EditProject", "\346\265\223\345\272\246:", 0));
        inputDescription->setText(QString());
        btnOK->setText(QApplication::translate("EditProject", "\344\277\235\345\255\230", 0));
        btnCancel->setText(QApplication::translate("EditProject", "\345\205\263\351\227\255", 0));
        btnImport->setText(QApplication::translate("EditProject", "\345\257\274\345\205\245", 0));
        groupBox_4->setTitle(QString());
        label_13->setText(QApplication::translate("EditProject", "\344\270\255\346\226\207\345\205\250\347\247\260", 0));
        label_16->setText(QApplication::translate("EditProject", "\350\213\261\346\226\207\347\256\200\347\247\260", 0));
        label_17->setText(QApplication::translate("EditProject", "\350\207\252\345\256\232\344\271\211", 0));
        groupBox_2->setTitle(QString());
        label_7->setText(QApplication::translate("EditProject", "\345\256\244", 0));
        label_4->setText(QApplication::translate("EditProject", "\345\214\273\351\231\242", 0));
        label_12->setText(QApplication::translate("EditProject", "\345\241\253\350\241\250\344\272\272", 0));
        label_5->setText(QApplication::translate("EditProject", "\347\247\221", 0));
        label_8->setText(QApplication::translate("EditProject", "\347\273\204", 0));
        ckbOnOpen->setText(QApplication::translate("EditProject", "\344\277\235\345\255\230\345\256\214\344\271\213\345\220\216\344\270\215\345\205\263\351\227\255\347\273\247\347\273\255\346\226\260\345\273\272", 0));
    } // retranslateUi

};

namespace Ui {
    class EditProject: public Ui_EditProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROJECT_H
