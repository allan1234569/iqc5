#include "menu.h"

#include <QHelpEvent>
#include <QEvent>
#include <QAction>
#include <QToolTip>
Menu::Menu(QWidget *parent) :
    QMenu(parent)
{
}

bool Menu::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::ToolTip:
        //show action tooltip instead of widget tooltip
    {
        QHelpEvent* he = dynamic_cast<QHelpEvent*>(e);
        QAction* act = actionAt(he->pos());
        if( act )
        {
            QToolTip::showText(he->globalPos(), act->toolTip(), this);
            return true;
        }
    }
        break;
    }
    QMenu::event(e);
}
