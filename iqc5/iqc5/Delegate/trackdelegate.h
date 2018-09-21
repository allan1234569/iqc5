#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QItemDelegate>

#include <QListWidget>
#include <QStringList>

class TrackDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    typedef enum WidgetType{
        LineEdit,
        Combox
    }WidgetType;

public:
    explicit TrackDelegate(WidgetType type, QObject *parent = 0);

   void setList(QStringList list);

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

private:
    WidgetType m_type;
    QStringList m_List;
};

#endif // TRACKDELEGATE_H
