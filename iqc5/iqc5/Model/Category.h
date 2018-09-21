#ifndef CATEGORY_H
#define CATEGORY_H
#include <QString>

class Category
{
public:
    Category();

    QString CategoryId;
    QString CategoryName;
    QString parentId;
    QString parentName;
    QString Status;
};

#endif // CATEGORY_H
