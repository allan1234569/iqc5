#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>

class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit ReadOnlyDelegate(QObject *parent = 0);

signals:

public slots:


    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // READONLYDELEGATE_H
