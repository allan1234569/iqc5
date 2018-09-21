#include "ReadOnlyDelegate.h"

ReadOnlyDelegate::ReadOnlyDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;
}
