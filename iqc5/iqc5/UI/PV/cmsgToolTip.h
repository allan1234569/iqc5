#include <QtCore>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QFrame>

#if defined(MSGTOOLTIP_LIBRARY)
#  define MSGTOOLTIPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MSGTOOLTIPSHARED_EXPORT Q_DECL_IMPORT
#endif

class MSGTOOLTIPSHARED_EXPORT CMsgToolTip : public QWidget
{
    Q_OBJECT
public:
    explicit CMsgToolTip(QWidget *parent = 0);
    ~CMsgToolTip();
    void setArrowDirection(int);
    void setTipType(int);
    void setTipTitle(QString newSTipTitle);
    void setTipContent(QString newSTipContent);
    void setObjectP(QWidget*);
    void init();
    enum ArrowDirecion
    {
        Top     = 0x0000,
        Right   = 0x0001,
        Bottom  = 0x0002,
        Left    = 0x0003,
        Warm    = 0x0004,
        Error   = 0x0005,
        Info    = 0x0006,
        Success = 0x0007
    };
public slots:
    void closeDlg();
private:
    void _DrawBg();
    void _DrawArrow();
    void _DrawIcon();
    void _CalculateHeight();
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    /* 提示框箭头指向位置 */
    int nArrowDirection;

    /* 提示类型 */
    int nTipType;
    /* 提示的标题 */
    QString sTipTitle;
    /* 提示内容 */
    QString sTipContent;
    /* 对象指针 */
    QWidget* p_object;

    /* 提示框的总高度 */
    int nHeight;
    /* 起点X值 */
    int nPosX;
    /* 起点Y值 */
    int nPosY;
    /* 控件宽度 */
    int nWidgetWidth;
    /* 控件高度 */
    int nWidgetHeight;

    /* 动画类 */
    QPropertyAnimation* animation;

    QFrame* p_myframe;
};