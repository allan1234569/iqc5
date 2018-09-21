#ifndef CATEGORYSERVICE_H
#define CATEGORYSERVICE_H
#include "Category.h"
#include <QString>

class CategoryService
{
public:
    CategoryService();

    QVector<Category> GetCategories();
    QVector<Category> GetCategories(QString parentId);
};

#endif // CATEGORYSERVICE_H
