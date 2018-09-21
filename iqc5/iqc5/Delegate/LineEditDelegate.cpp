#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QDebug>

LineEditDelegate::LineEditDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void LineEditDelegate::slt_isEditing(const QString &txt)
{
    emit sig_editing(txt);
}

void LineEditDelegate::slt_editFinished()
{
    emit sig_editFinished();
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slt_isEditing(QString)));
    connect(lineEdit,SIGNAL(editingFinished()),SLOT(slt_editFinished()));

    return lineEdit;
}

void LineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
    lineEdit->setText(index.model()->data(index).toString());
}

void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QItemDelegate::setModelData(editor, model, index);
}
