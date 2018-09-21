#ifndef UNIT_H
#define UNIT_H
#include <QString>

class Unit
{
public:
    Unit();

    QString UNITID;
    QString UNIT_TYPEID;
    QString ParentId;
    QString CategoryId;
    QString UNITCODE;
    QString UNITNAME;
    QString UNITREMARK;
    int STATUS;
};

#endif // UNIT_H
