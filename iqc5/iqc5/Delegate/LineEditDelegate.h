#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QItemDelegate>

class LineEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit LineEditDelegate(QObject *parent = 0);

signals:

    void sig_editing(const QString &txt);

    void sig_editFinished();

public slots:

    void slt_isEditing(const QString &txt);

    void slt_editFinished();


    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // LINEEDITDELEGATE_H
