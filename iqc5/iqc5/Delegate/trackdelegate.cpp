#include "trackdelegate.h"

#include <QDebug>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

TrackDelegate::TrackDelegate(WidgetType type, QObject *parent) :
    QItemDelegate(parent),m_type(type)
{

}

void TrackDelegate::setList(QStringList list)
{
    m_List = list;
}

void TrackDelegate::slt_isEditing(const QString &txt)
{
    emit sig_editing(txt);
}

void TrackDelegate::slt_editFinished()
{
    emit sig_editFinished();
}

QWidget *TrackDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (m_type == LineEdit)
    {
        QLineEdit *lineEdit = new QLineEdit(parent);
        connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slt_isEditing(QString)));
        connect(lineEdit,SIGNAL(editingFinished()),SLOT(slt_editFinished()));

        return lineEdit;
    }
    else if (m_type == Combox)
    {
        QComboBox *combox = new QComboBox(parent);
        combox->addItems(m_List);
        return combox;
    }
}

void TrackDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (m_type == LineEdit)
    {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        lineEdit->setText(index.model()->data(index).toString());
    }
    else if (m_type == Combox)
    {
//        QComboBox *combox = qobject_cast<QComboBox>(editor);
    }


}

void TrackDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QItemDelegate::setModelData(editor,model,index);
}
