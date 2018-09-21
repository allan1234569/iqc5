#include "DateDelegate.h"
#include <QDateEdit>

DateDelagate::DateDelagate(QObject *parent) :
    QItemDelegate(parent)
{
}

void DateDelagate::slt_dateChanged(const QDate &date)
{
    emit sig_dateChanged(date);
}

QWidget *DateDelagate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *dateEdit = new QDateEdit(parent);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");

    return dateEdit;
}

void DateDelagate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDateEdit *dateEdit = qobject_cast<QDateEdit*>(editor);
    dateEdit->setDate(QDate::fromString(index.model()->data(index).toString(), "yyyy-MM-dd"));
}

void DateDelagate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QItemDelegate::setModelData(editor, model, index);
}
