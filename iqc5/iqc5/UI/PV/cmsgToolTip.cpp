#include "cmsgtooltip.h"

CMsgToolTip::CMsgToolTip(QWidget *parent) :
    QWidget(parent)
{
}

void CMsgToolTip::init()
{

    _CalculateHeight();
    _DrawBg(); // 绘制背景
    _DrawArrow();
    _DrawIcon();

    int pos_x = 0, pos_y = 0,nWidgetWidth = 0,nWidhetHeight = 0;
    if(p_object!=NULL)
    {
        QPoint GlobalPoint(p_object->mapToParent(QPoint(0, 0)));
        pos_x = GlobalPoint.x();
        pos_y = GlobalPoint.y();
        nWidgetWidth = p_object->width();
        nWidhetHeight = p_object->height();
    }


    animation = new QPropertyAnimation(this,"pos");
    animation->setDuration(1000);
    if(nArrowDirection == CMsgToolTip::Top || nArrowDirection == CMsgToolTip::Bottom){

        if(nArrowDirection == CMsgToolTip::Top){
            // 当箭头向上时候
            // 有效实际y坐标 应该为当前控件的y坐标+当前控件的实际高度+偏差值(默认6)
            pos_y = pos_y+nWidhetHeight+6;
        }
        else{
            // 当箭头向下时候
            // 有效实际y坐标 应该为当前控件的y坐标 - 当前消息总高度 - 偏差值(默认6)
            pos_y = pos_y-nHeight-24;
        }
        // 实际有效的x坐标 应该为当前坐标的正中间，即 控件当前x坐标减去 消息固定宽度380与空间实际宽度差/4
        pos_x = pos_x - (380-nWidgetWidth)/4;

        animation->setKeyValueAt(0, QPoint(pos_x,pos_y));
        animation->setKeyValueAt(0.3, QPoint(pos_x,pos_y-5));
        animation->setKeyValueAt(0.6, QPoint(pos_x,pos_y));
        animation->setKeyValueAt(0.8, QPoint(pos_x,pos_y-5));
        animation->setKeyValueAt(1, QPoint(pos_x,pos_y));
    }else{

        if(nArrowDirection == CMsgToolTip::Right){
            // 当箭头向右时候
            // 有效实际x坐标 应该为当前控件的x坐标-消息实际宽度380 -偏差值(默认12)
            pos_x = pos_x-360;
        }
        else{
            // 当箭头向下时候
            // 有效实际x坐标 应该为当前控件的x坐标 + 当前控件的实际宽度 + 偏差值(默认12)
            pos_x = pos_x+nWidgetWidth+12;
        }
        // 实际有效的y坐标 应该为当前坐标的正中间，即 控件当前y坐标 - 窗体有效高/2 加上 当前控件高度的一半高度
        pos_y = pos_y -nHeight/2 +nWidhetHeight/2;

        animation->setKeyValueAt(0, QPoint(pos_x,pos_y));
        animation->setKeyValueAt(0.3, QPoint(pos_x-5,pos_y));
        animation->setKeyValueAt(0.6, QPoint(pos_x,pos_y));
        animation->setKeyValueAt(0.8, QPoint(pos_x-5,pos_y));
        animation->setKeyValueAt(1, QPoint(pos_x,pos_y));
    }

    animation->start();
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::_DrawBg()
// Purpose:    绘制消息框背景
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::_DrawBg()
{
    p_myframe = new QFrame(this);
    p_myframe->setStyleSheet("background-color:#fbfbfb;border-radius:4px;");

    if(nArrowDirection == CMsgToolTip::Left){
        p_myframe->setGeometry(12,0,338,nHeight);
    }else if(nArrowDirection == CMsgToolTip::Top){
        p_myframe->setGeometry(0,12,338,nHeight);
    }else if(nArrowDirection == CMsgToolTip::Bottom){
        p_myframe->setGeometry(0,0,338,nHeight);
    }else{
        p_myframe->setGeometry(0,0,338,nHeight);
    }

    QLabel* titleLabel = new QLabel(p_myframe);
    titleLabel->setText(sTipTitle);
    titleLabel->setStyleSheet("margin:20px 0px 0px 60px;font-size:12pt;font-weight:bold");
    if(!sTipContent.isEmpty()) // 当提示详细信息不为空的时候，绘制提示信息详细内容
    {
        QLabel* lineLabel = new QLabel(p_myframe);
        lineLabel->setText("");
        lineLabel->setStyleSheet("border:1px solid #cccccc;");
        lineLabel->setGeometry(25,55,300,1);

        QLabel* contentLabel = new QLabel(p_myframe);
        contentLabel->setText(sTipContent);
        contentLabel->setStyleSheet("margin:65px 0px 0px 25px;");
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::_DrawArrow()
// Purpose:    绘制三角形背景
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::_DrawArrow()
{
    QLabel* arrow = new QLabel(this);

    if(nArrowDirection == CMsgToolTip::Left){
        QPixmap pixmap(":/img/arrow-left.png");
        arrow->setPixmap(pixmap);
        arrow->setGeometry(0,(nHeight/2-10),12,19);
    }else if(nArrowDirection == CMsgToolTip::Top){
        QPixmap pixmap(":/img/arrow-top.png");
        arrow->setPixmap(pixmap);
        arrow->setGeometry(160,0,19,12);
    }else if(nArrowDirection == CMsgToolTip::Bottom){
        QPixmap pixmap(":/img/arrow-bottom.png");
        arrow->setPixmap(pixmap);
        arrow->setGeometry(160,nHeight,19,12);
    }else{
        QPixmap pixmap(":/img/arrow-right.png");
        arrow->setPixmap(pixmap);
        arrow->setGeometry(338,(nHeight/2-10),12,19);
    }

}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::_DrawIcon()
// Purpose:    绘制提示信息的类型图片
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::_DrawIcon()
{
    QLabel* icon = new QLabel(p_myframe);
    QString imgPath = QString();
    if(nTipType == CMsgToolTip::Error){
        imgPath = ":/img/error.png";
    }else if(nTipType == CMsgToolTip::Warm){
        imgPath = ":/img/warm.png";
    }else{
        imgPath = ":/img/info.png";
    }
    QPixmap pixmap(imgPath);
    icon->setPixmap(pixmap);
    icon->setStyleSheet("margin:15px 0px 0px 25px");
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::_CalculateHeight()
// Purpose:    计算对话框的高度
// Parameters:
// - newBFixedPostion
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::_CalculateHeight()
{
    // 对话框的高度 = title高度+content高度
    if(sTipContent.isEmpty())
    {
        nHeight = 60;
    }
    else
    {
        int m = sTipContent.count("\n");
        m++;
        nHeight = 80+m*20;
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::setNArrowDirection(int newNArrowDirection)
// Purpose:    Implementation of CMsgToolTip::setNArrowDirection()
// Parameters:
// - newNArrowDirection
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::setArrowDirection(int newNArrowDirection)
{
    nArrowDirection = newNArrowDirection;
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::setNPosY(int newNPosY)
// Purpose:    Implementation of CMsgToolTip::setNPosY()
// Parameters:
// - newNPosY
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::setTipType(int newNTipType)
{
    nTipType = newNTipType;
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::setSTipTitle(QString newSTipTitle)
// Purpose:    Implementation of CMsgToolTip::setSTipTitle()
// Parameters:
// - newSTipTitle
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::setTipTitle(QString newSTipTitle)
{
    sTipTitle = newSTipTitle;
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::setSTipContent(QString newSTipContent)
// Purpose:    Implementation of CMsgToolTip::setSTipContent()
// Parameters:
// - newSTipContent
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::setTipContent(QString newSTipContent)
{
    sTipContent = newSTipContent;
}

////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::setObjectP(QObject  *p)
// Purpose:    设置对象指针
// Parameters:
// - newSTipContent
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::setObjectP(QWidget *p)
{
    p_object = p;
}


void CMsgToolTip::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        closeDlg();
    }
}
////////////////////////////////////////////////////////////////////////
// Name:       CMsgToolTip::_CloseDlg()
// Purpose:    Implementation of CMsgToolTip::_CloseDlg()
// Return:     void
////////////////////////////////////////////////////////////////////////
void CMsgToolTip::closeDlg()
{
    // TODO : implement
   this->close();
}

///////////////////////////////////////////////////////////////////////////////////////////
// 释放资源函数
///////////////////////////////////////////////////////////////////////////////////////////
CMsgToolTip::~CMsgToolTip()
{
    delete animation;
    delete p_myframe;
}
