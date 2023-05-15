#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQueryModel>

#include "task.h"

class DbHelper;

// Улучшенная версия классической реализации Singleton [DbHelper].

// DbHelperDestroyer предназначен для
// автоматического разрушения объекта Singleton [[DbHelper]].

class DbHelperDestroyer
{
private:
    DbHelper* p_instance;
public:
    ~DbHelperDestroyer();
    void initialize(DbHelper* p);
};


class DbHelper : public QObject
{
    Q_OBJECT

private:
    static DbHelper* p_instance;
    static DbHelperDestroyer destroyer;
protected:
    DbHelper(QObject *parent = nullptr);
    DbHelper( const DbHelper& ) = delete; // Prevent copy-construction
    DbHelper& operator=( DbHelper& ) = delete; // Prevent assignment
    ~DbHelper(); // Prevent accidentally deleting

    friend class DbHelperDestroyer;
public:

    static DbHelper& getInstance();


    QSqlQueryModel* getAllRecords() const;
    bool saveRecord(Task* );
    bool removeOther(const QString& );
    //bool removeRecord(const quint32& );

private:
    bool addNewRecord(Task* );
    bool updateRecord(const Task* );

    bool createConnection();
    void closeConnection();

    const QString m_dbName = "ToDoDb.db";
    QSqlDatabase m_db;

};

#endif // DBHELPER_H
