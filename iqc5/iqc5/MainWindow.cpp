#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QStyleOption>
#include <QPaintEvent>
#include <QString>
#include <QLabel>
#include <QMessageBox>

#ifdef QT_NO_DEBUG

#include "QtnOfficeDefines.h"
#include "QtnRibbonQuickAccessBar.h"

#endif

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "UI/ManageDevice.h"
#include "UI/ManageMaterial.h"

#include "UI/ManageMaterial.h"
#include "UI/ManageReagent.h"
#include "UI/ManageMaterialBatch.h"
#include "UI/ManageReagentBatch.h"
#include "UI/ManageType.h"
#include "UI/ManageDevice.h"
#include "UI/EditProject.h"
#include "UI/ManageProject.h"
#include "UI/ManageMethod.h"
#include "UI/AnalyzeProject.h"
#include "UI/AnalyzeRule.h"
#include "UI/NewProjectBatch.h"
#include "UI/InputDataMulti.h"
#include "UI/InputDataSingle.h"
#include "UI/NewProjectBatch.h"
#include "UI/ManageMaterialTestType.h"
#include "UI/ManageReagentTestType.h"
#include "UI/ManageMethodTestType.h"
#include "UI/NewMaterialBatch.h"
#include "UI/NewReagentBatch.h"
#include "UI/AnalyzeProject.h"
#include "UI/AnalyzeDevice.h"
#include "UI/Circle.h"
#include "UI/SixSigma_QCRulesScreening.h"
#include "UI/ManageDataImport.h"
#include "Pv_Accruacy.h"
#include "Pv_Precision.h"
#include "Pv_AccuracyPlot.h"
#include "Pv_ReportableRange.h"

#include <QPrintDialog>
#include <QPrinter>
#include <QPixmap>


class WorkspaceWidget : public QWidget
{
public:
    WorkspaceWidget()
    {
        setAttribute(Qt::WA_MouseTracking);
        setAutoFillBackground(true);
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(255, 255, 255));
        setPalette(pal);
    }
protected:
    virtual void mousePressEvent(QMouseEvent* event)
    {
        Q_UNUSED(event);
        setFocus();
    }
    virtual void paintEvent(QPaintEvent* event)
    {
        Q_UNUSED(event);
        QPainter p(this);
        QStyleOption opt;
        opt.init(this);
        if (event->rect().intersects(opt.rect))
            style()->drawPrimitive((QStyle::PrimitiveElement)CommonStyle::PE_Workspace, &opt, &p, this);
    }
};

bool MainWindow::canOpen = true;

#ifdef QT_NO_DEBUG
MainWindow::MainWindow(QWidget *parent) :
    Qtitan::RibbonMainWindow(parent)
{
    m_ribbonStyle = qobject_cast<Qtitan::RibbonStyle*>(qApp->style());
    m_ribbonStyle->setTheme(OfficeStyle::Office2007Blue);

    setWindowTitle(tr("智晟生物"));
    setCentralWidget(new WorkspaceWidget);
    ribbonBar()->setFrameThemeEnabled();
    ribbonBar()->setTitleBarVisible(false);
    createRibbon();
    createOptions();

    QRect geom = QApplication::desktop()->availableGeometry();
    move(QPoint(200, 200));
    resize(2 * geom.width() / 3, 2 * geom.height() / 3);
}
#else
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
{
    this->setWindowIcon(QIcon("://images/clipboard.png"));
    setWindowTitle(tr("智晟生物"));
//    setCentralWidget(new WorkspaceWidget);
    careteMenuBar();


    QRect geom = QApplication::desktop()->availableGeometry();
    move(QPoint(200, 200));
    resize(2 * geom.width() / 3, 2 * geom.height() / 3);
}
#endif


MainWindow::~MainWindow()
{
}

#ifdef QT_DEBUG
void MainWindow::careteMenuBar()
{
    if(QMenu *menu =  menuBar()->addMenu(tr("项目")) )
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("批量新建")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("批量新建")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action,SIGNAL(triggered()),SLOT(FuncNewProjectBatch()));
            }

            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("数据录入")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(InputDataBatch()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("单项目")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("单项目")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(openProject()));
            }
        }

    }
    if(QMenu *menu =  menuBar()->addMenu(tr("质控图")) )
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("Level-Jennings质控图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("Level-Jennings质控图")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showLj()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("Z分数质控图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("Z分数质控图")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showZ()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("Zs图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("Zs图")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showCircle()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("直方图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("直方图")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showBar()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("靶点图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("靶点图")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showTarget()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("休哈特质控图")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("均值极差图")))
            {
                action->setPriority(QAction::LowPriority);
//                connect(action, SIGNAL(triggered()), this, SLOT());
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("均值标准差图")))
            {
                action->setPriority(QAction::LowPriority);
//                connect(action, SIGNAL(triggered()), this, SLOT());
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("中位数极差图")))
            {
                action->setPriority(QAction::LowPriority);
//                connect(action, SIGNAL(triggered()), this, SLOT());
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("单值移动极差图")))
            {
                action->setPriority(QAction::LowPriority);
//                connect(action, SIGNAL(triggered()), this, SLOT());
            }
        }
    }
    if (QMenu *menu = menuBar()->addMenu(tr("质控设计")))
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("质控设计")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("质控设计")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showFuncChart()));
            }
        }
    }
    if(QMenu *menu =  menuBar()->addMenu(tr("项目性能验证")) )
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("性能验证")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("精密验证")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showPrecisionTest()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("正确度验证")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showAccuracyTest()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("测量区间验证")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showMeasurementIntervalTest()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("参考区间验证")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(showReferenceIntervalTest()));
            }
        }
    }
    if(QMenu *menu =  menuBar()->addMenu(tr("检测方法确认")) )
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("方法确认")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("精密度")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("正确度")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("测量区间")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("分析灵敏度")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(ShowSensitivityAnalyze()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("分析特异性")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("干扰实验")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("携带污染实验")))
            {
                action->setPriority(QAction::LowPriority);
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("检出限和定量限")))
            {
                action->setPriority(QAction::LowPriority);
            }
        }
    }
    if(QMenu *menu =  menuBar()->addMenu(tr("系统设置")) )
    {
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("系统设置")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("项目管理")))

            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageTestType()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("质控品新建")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(newMaterialBatch()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("质控品管理")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageMaterial()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("试剂新建")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(newReagentBatch()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("试剂管理")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageReagent()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("仪器")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageDevice()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("测试方法")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageMethod()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("质控品和项目关系")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageMaterialTestType()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("试剂和项目关系")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageReagentTestType()));
            }
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("方法和项目关系")))
            {
                action->setPriority(QAction::LowPriority);
                connect(action, SIGNAL(triggered()), this, SLOT(manageMethodTestType()));
            }
        }
        if(QMenu *childMenu =  menu->addMenu(QIcon("images/clipboard.png"),tr("lis")))
        {
            if(QAction *action = childMenu->addAction(QIcon("images/clipboard.png"),tr("lis系统字典")))
            {
                action->setPriority(QAction::LowPriority);
            }
        }
    }
}
#endif

#ifdef QT_NO_DEBUG
void MainWindow::createRibbon()
{
    if (Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("项目")))
    {
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("批量新建")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("批量新建"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(FuncNewProjectBatch()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("数据录入"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(InputDataBatch()));

        }
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("单项目")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("单项目"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(openProject()));
        }
    }

    if (Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("质控图")))
    {
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("Levey-Jennings质控图")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("Levey-Jennings质控图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(showLj()));

        }
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("Z分数质控图")))
        {
            group->setVisible(false);
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("Z分数质控图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(showZ()));

        }
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("Zs图")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("Zs图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
//            action->setEnabled(false);
            connect(action, SIGNAL(triggered()), this, SLOT(showCircle()));

        }

        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("直方图")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("直方图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
//            action->setEnabled(false);
            connect(action, SIGNAL(triggered()), this, SLOT(showBar()));

        }

        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("靶点图")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("靶点图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
//            action->setEnabled(false);
            connect(action, SIGNAL(triggered()), this, SLOT(showTarget()));

        }

        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("休哈特质控图")))
        {
            group->setEnabled(false);

            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("均值极差图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("均值标准差图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("中位数极差图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("单值移动极差图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

        }
    }

    if (Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("质控设计")))
    {
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("质控设计")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("质控设计"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(showFuncChart1()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("功效函数图"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(showFuncChart()));
        }

    }

    if(Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("项目性能验证")))
    {
        if(Qtitan::RibbonGroup *group = pageButtons->addGroup(tr("性能验证")))
        {
//            group->setEnabled(false);

            QAction *action;
            action = group->addAction(QIcon("://images/clipboard.png"),tr("精密度验证"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action,SIGNAL(triggered()),this,SLOT(showPrecisionTest()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("正确度验证"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action,SIGNAL(triggered()),this,SLOT(showAccuracyTest()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("测量区间验证"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action,SIGNAL(triggered()),this,SLOT(showMeasurementIntervalTest()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("参考区间验证"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action,SIGNAL(triggered()),this,SLOT(showReferenceIntervalTest()));
        }

    }

    if(Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("检测方法确认")))
    {
        if(Qtitan::RibbonGroup *group = pageButtons->addGroup(tr("方法确认")))
        {

//            group->setEnabled(false);

            QAction *action;
            action = group->addAction(QIcon("://images/clipboard.png"),tr("精密度"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("正确度"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("测量区间"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("分析灵敏度"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
//            connect(action,SIGNAL(triggered()),this,SLOT(ShowSensitivityAnalyze()));

            action = group->addAction(QIcon("images/clipboard.png"),tr("分析特异性"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("干扰实验"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("携带污染实验"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("检出限和定量限"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
        }

    }


    if (Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("系统设置")))
    {
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("系统设置")))
        {
            QAction* action;
            //action = group->addAction(QIcon("images/clipboard.png"),tr("专业"), Qt::ToolButtonTextUnderIcon);
            //action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("项目管理"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageTestType()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("质控品新建"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(newMaterialBatch()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("质控品管理"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageMaterial()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("试剂新建"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(newReagentBatch()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("试剂管理"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageReagent()));

            //action = group->addAction(QIcon("images/clipboard.png"),tr("厂商"), Qt::ToolButtonTextUnderIcon);
            //action->setPriority(QAction::LowPriority);

            action = group->addAction(QIcon("://images/clipboard.png"),tr("仪器"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageDevice()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("测试方法"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageMethod()));

            //action = group->addAction(QIcon("images/clipboard.png"),tr("质控标准"), Qt::ToolButtonTextUnderIcon);
            //action->setPriority(QAction::LowPriority);
            //connect(action, SIGNAL(triggered()), this, SLOT(xxxx()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("质控品和项目关系"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageMaterialTestType()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("试剂和项目关系"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageReagentTestType()));

            action = group->addAction(QIcon("://images/clipboard.png"),tr("方法和项目关系"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action, SIGNAL(triggered()), this, SLOT(manageMethodTestType()));

        }
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("导入")))
        {
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("结果导入配置"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
            connect(action,SIGNAL(triggered()),this,SLOT(manageDataImport()));
        }
        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("lis")))
        {
            group->setEnabled(false);
            QAction* action = group->addAction(QIcon("://images/clipboard.png"),tr("lis系统字典"), Qt::ToolButtonTextUnderIcon);
            action->setPriority(QAction::LowPriority);
        }
    }

//    if (Qtitan::RibbonPage* pageButtons = ribbonBar()->addPage(tr("系统设置")))
//    {
//        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("常规")))
//        {
//            QAction* action;
//            action = group->addAction(QIcon("images/clipboard.png"),tr("质控批号维护"), Qt::ToolButtonTextUnderIcon);
//            action->setPriority(QAction::LowPriority);
//            connect(action, SIGNAL(triggered()), this, SLOT(manageMaterialBatch()));

//            action = group->addAction(QIcon("images/clipboard.png"),tr("试剂批号维护"), Qt::ToolButtonTextUnderIcon);
//            action->setPriority(QAction::LowPriority);
//            connect(action, SIGNAL(triggered()), this, SLOT(manageReagentBatch()));




//        }
//        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("权限")))
//        {
//            QAction* action = group->addAction(QIcon("images/clipboard.png"),tr("角色设置"), Qt::ToolButtonTextUnderIcon);
//            action->setPriority(QAction::LowPriority);

//            action = group->addAction(QIcon("images/clipboard.png"),tr("科室设置"), Qt::ToolButtonTextUnderIcon);
//            action->setPriority(QAction::LowPriority);

//        }
//        if (Qtitan::RibbonGroup* group = pageButtons->addGroup(tr("导入")))
//        {
//            QAction* action = group->addAction(QIcon("images/clipboard.png"),tr("结果导入配置"), Qt::ToolButtonTextUnderIcon);
//            action->setPriority(QAction::LowPriority);
//        }
//    }
}
#endif

#ifdef QT_NO_DEBUG
void MainWindow::createOptions()
{
    Qtitan::RibbonStyle::Theme themeId = Qtitan::RibbonStyle::Office2007Blue;
    if (m_ribbonStyle)
        themeId = m_ribbonStyle->getTheme();

    QMenu* menu = ribbonBar()->addMenu(tr("选项"));
    QAction* actionStyle = menu->addAction(tr("风格"));

    QMenu* menuStyle = new QMenu(ribbonBar());
    QActionGroup* styleActions = new QActionGroup(this);

    QAction* actionBlue = menuStyle->addAction(tr("Office 2007 Blue"));
    actionBlue->setCheckable(true);
    actionBlue->setChecked(themeId == Qtitan::RibbonStyle::Office2007Blue);
    actionBlue->setObjectName("Office2007Blue");


    QAction* actionSilver = menuStyle->addAction(tr("Office 2007 Silver"));
    actionSilver->setObjectName("Office2007Silver");
    actionSilver->setCheckable(true);
    actionSilver->setChecked(themeId == Qtitan::RibbonStyle::Office2007Silver);

    QAction* actionAqua = menuStyle->addAction(tr("Office 2007 Aqua"));
    actionAqua->setObjectName("Office2007Aqua");
    actionAqua->setCheckable(true);
    actionAqua->setChecked(themeId == Qtitan::RibbonStyle::Office2007Aqua);

    QAction* actionScenic = menuStyle->addAction(tr("Windows 7 Scenic"));
    actionScenic->setObjectName("Windows7Scenic");
    actionScenic->setCheckable(true);
    actionScenic->setChecked(themeId == Qtitan::RibbonStyle::Windows7Scenic);

    QAction* action2010Blue = menuStyle->addAction(tr("Office 2010 Blue"));
    action2010Blue->setObjectName("Office2010Blue");
    action2010Blue->setCheckable(true);
    action2010Blue->setChecked(themeId == Qtitan::RibbonStyle::Office2010Blue);

    QAction* action2010Silver = menuStyle->addAction(tr("Office 2010 Silver"));
    action2010Silver->setObjectName("Office2010Silver");
    action2010Silver->setCheckable(true);
    action2010Silver->setChecked(themeId == Qtitan::RibbonStyle::Office2010Silver);

    styleActions->addAction(actionBlue);
    styleActions->addAction(actionSilver);
    styleActions->addAction(actionAqua);
    styleActions->addAction(actionScenic);
    styleActions->addAction(action2010Blue);
    styleActions->addAction(action2010Silver);

    actionStyle->setMenu(menuStyle);
    connect(styleActions, SIGNAL(triggered(QAction*)), this, SLOT(options(QAction*)));

}


void MainWindow::options(QAction* action)
{
    if (m_ribbonStyle)
    {
        Qtitan::RibbonStyle::Theme themeId = Qtitan::RibbonStyle::Office2007Blue;
        if (action->objectName() == "Office2007Black")
            themeId = Qtitan::RibbonStyle::Office2007Black;
        else if (action->objectName() == "Office2007Silver")
            themeId = Qtitan::RibbonStyle::Office2007Silver;
        else if (action->objectName() == "Office2007Aqua")
            themeId = Qtitan::RibbonStyle::Office2007Aqua;
        else if (action->objectName() == "Windows7Scenic")
            themeId = Qtitan::OfficeStyle::Windows7Scenic;
        else if (action->objectName() == "Office2010Blue")
            themeId = Qtitan::OfficeStyle::Office2010Blue;
        else if (action->objectName() == "Office2010Silver")
            themeId = Qtitan::OfficeStyle::Office2010Silver;
        else if (action->objectName() == "Office2010Black")
            themeId = Qtitan::OfficeStyle::Office2010Black;

        if (QToolButton* button = ribbonBar()->getSystemButton())
        {
            if (themeId == Qtitan::OfficeStyle::Windows7Scenic ||
                    themeId == Qtitan::OfficeStyle::Office2010Blue ||
                    themeId == Qtitan::OfficeStyle::Office2010Silver ||
                    themeId == Qtitan::OfficeStyle::Office2010Black)
                button->setToolButtonStyle(Qt::ToolButtonTextOnly);
            else
                button->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        }

        m_ribbonStyle->setTheme(themeId);
    }
}

#endif

//新建项目(多个)
void MainWindow::FuncNewProjectBatch()
{
    if(canOpen)
    {
        canOpen = false;
        NewProjectBatch *window = new NewProjectBatch(this);
        window->showMaximized();
    }
}
//数据录入
void MainWindow::InputDataBatch()
{
    if(canOpen)
    {
        canOpen = false;
        InputDataMulti *window = new InputDataMulti(this);
        window->showMaximized();
    }
}

//新建项目
void MainWindow::newProject()
{
    if(canOpen)
    {
        canOpen = false;
        EditProject *window = new EditProject(this);
        window->showMaximized();
    }

}

//打开项目
void MainWindow::openProject()
{
    if(canOpen)
    {
        canOpen = false;
        InputDataSingle *window = new InputDataSingle(this);
        window->showMaximized();
    }
}

//导入项目
void MainWindow::importProject()
{
    //import();
}

//导入配置
void MainWindow::importConfig()
{
    //ImportConfig *window = new ImportConfig(this);
    //window->showMaximized();
}

//设计选择
void MainWindow::chooseMethod()
{
    //    AnalyzeRule *window = new AnalyzeRule(this);
    //    this->openedAnalyzeRuleWindow = window;
    //    window->showMaximized();
}

//Lj
void MainWindow::showLj()
{
        AnalyzeProject *window = new AnalyzeProject(this);
//        window->setWindowModality(Qt::ApplicationModal);
        window->SetMode(1);
        window->showMaximized();
}
void MainWindow::showZ()
{
        AnalyzeProject *window = new AnalyzeProject(this);
        window->SetMode(2);
        window->showMaximized();
}

void MainWindow::showBar()
{
        AnalyzeProject *window = new AnalyzeProject(this);
        window->SetMode(3);
        window->showMaximized();
}

void MainWindow::showTarget()
{
        AnalyzeProject *window = new AnalyzeProject(this);
        window->SetMode(4);
        window->showMaximized();
}

void MainWindow::showFuncChart()
{
    AnalyzeDevice *window1 = new AnalyzeDevice(this);
    window1->setWindowModality(Qt::ApplicationModal);
    window1->showMaximized();
}

void MainWindow::showFuncChart1()
{
    SixSigma_QCRulesScreening *window = new SixSigma_QCRulesScreening(this);

    window->setWindowModality(Qt::ApplicationModal);
    window->showMaximized();
}

void MainWindow::showCircle()
{
        Circle *window = new Circle(this);
        window->showMaximized();
}

//质控品管理
void MainWindow::manageMaterial()
{

    if(canOpen)
    {
        canOpen = false;
        //NewMaterialBatch *window = new NewMaterialBatch(this);
        ManageMaterial *window = new ManageMaterial(this);
        window->setWindowTitle(tr("质控品维护"));
        window->showMaximized();
    }
}

//质控品批量新建
void MainWindow::newMaterialBatch()
{
    if(canOpen)
    {
        canOpen = false;
        NewMaterialBatch *window = new NewMaterialBatch(this);
        window->showMaximized();
    }
}
//试剂批量新建
void MainWindow::newReagentBatch()
{
    if(canOpen)
    {
        canOpen = false;
        NewReagentBatch *window = new NewReagentBatch(this);
        window->setWindowTitle(tr("试剂批量新建"));
        window->showMaximized();
    }
}



void MainWindow::ShowSensitivityAnalyze()
{
//    if(canOpen)
//    {
////        canOpen = false;
////        AnalyzeSensitivity *window = new AnalyzeSensitivity(this);
////        window->showMaximized();
    //    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    emit close();
}

void MainWindow::showPrecisionTest()
{
    if(canOpen)
    {
//        if(this->centralWidget()->isActiveWindow())
//            this->takeCentralWidget();
        canOpen = false;
        Pv_Precision *window = new Pv_Precision(this);
//        this->setCentralWidget(window);
        window->show();
    }
}

void MainWindow::showAccuracyTest()
{

    if(canOpen)
    {
        canOpen = false;
        Pv_Accruacy *window = new Pv_Accruacy(this);
        window->show();
    }
}

void MainWindow::showMeasurementIntervalTest()
{
    if(canOpen)
    {
        canOpen = false;
        Pv_ReportableRange *window = new Pv_ReportableRange(this);
        window->show();
    }
}

void MainWindow::showReferenceIntervalTest()
{

}


//试剂管理
void MainWindow::manageReagent()
{
    if(canOpen)
    {
        canOpen = false;
        ManageReagent *window = new ManageReagent(this);
        window->setWindowTitle(tr("试剂维护"));
        window->showMaximized();
    }
}

//质控品批号管理
void MainWindow::manageMaterialBatch()
{
    if(canOpen)
    {
        canOpen = false;
        ManageMaterialBatch *window = new ManageMaterialBatch(this);
        window->setWindowTitle(tr("质控品批号维护"));
        window->showMaximized();
    }
}

//试剂批号管理
void MainWindow::manageReagentBatch()
{
    if(canOpen)
    {
        canOpen = false;
        ManageReagentBatch *window = new ManageReagentBatch(this);
        window->setWindowTitle(tr("试剂批号维护"));
        window->showMaximized();
    }
}

//质控类型管理
void MainWindow::manageTestType()
{
    if(canOpen)
    {
        canOpen = false;
        ManageType *window = new ManageType(this);
        window->showMaximized();
    }
}

//质控品项目管理
void MainWindow::manageMaterialTestType()
{
    if(canOpen)
    {
        canOpen = false;
        ManageMaterialTestType *window = new ManageMaterialTestType(this);
        window->setWindowTitle(tr("质控品项目管理"));
        window->showMaximized();
    }
}

//试剂项目管理
void MainWindow::manageReagentTestType()
{
    if(canOpen)
    {
        canOpen = false;
        ManageReagentTestType *window = new ManageReagentTestType(this);
        window->setWindowTitle(tr("试剂项目管理"));
        window->showMaximized();
    }
}
//方法项目管理
void MainWindow::manageMethodTestType()
{
    if(canOpen)
    {
        canOpen = false;
        ManageMethodTestType *window = new ManageMethodTestType(this);
        window->setWindowTitle(tr("方法项目管理"));
        window->showMaximized();
    }
}


//检测方法管理
void MainWindow::manageMethod()
{
    if(canOpen)
    {
        canOpen = false;
        ManageMethod *window = new ManageMethod(this);
        window->showMaximized();
    }
}

//仪器管理
void MainWindow::manageDevice()
{
    if(canOpen)
    {
        canOpen = false;
        ManageDevice *window = new ManageDevice(this);
        window->setWindowTitle(tr("仪器维护"));
        window->showMaximized();
    }
}

//结果导入配置
void MainWindow::manageDataImport()
{
    if(canOpen)
    {
        canOpen = false;
        ManageDataImport *window = new ManageDataImport(this);
        window->show();
    }
}

