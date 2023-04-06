#ifndef SPECCHARCLASS_H
#define SPECCHARCLASS_H

#include <QMap>
#include <QString>

class SpecCharClass
{
public:
    SpecCharClass();

    QString replace(QString text) const;
    QMap<QString, QString> variants;
};

#endif // SPECCHARCLASS_H
