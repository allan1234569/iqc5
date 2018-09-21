#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>

class DateDelagate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DateDelagate(QObject *parent = 0);

signals:
    void sig_dateChanged(const QDate &date);

public slots:
    void slt_dateChanged(const QDate & date);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // DATEDELEGATE_H
