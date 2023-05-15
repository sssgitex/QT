#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QtDebug>

#include "dbhelper.h"

DbHelper *DbHelper::p_instance = 0;
DbHelperDestroyer DbHelper::destroyer;


DbHelperDestroyer::~DbHelperDestroyer()
{
    delete p_instance;
}

void DbHelperDestroyer::initialize( DbHelper* p )
{
    p_instance = p;
}

DbHelper& DbHelper::getInstance()
{
    if(!p_instance)
    {
        p_instance = new DbHelper();
        destroyer.initialize (p_instance);
    }

    return *p_instance;
}

DbHelper::DbHelper(QObject *parent) : QObject(parent)
{
    createConnection();
}

DbHelper::~DbHelper()
{
    closeConnection();
}


bool DbHelper::createConnection()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbName);

    if (!m_db.open())
    {
        qDebug() << "Cannot open database:" << m_db.lastError();
        return false;
    }

    // Creating of the data base
    QSqlQuery query(m_db);
    QString str = "CREATE TABLE IF NOT EXISTS list ("
                  "id INTEGER NOT NULL UNIQUE PRIMARY KEY,"
                  "name VARCHAR(200),"
                  "deadline VARCHAR(10),"
                  "progress INTEGER CHECK(typeof(progress) = 'integer' AND progress >= 0 AND progress <= 10)"
                  ");";

    if (!query.exec(str))
    {
        qDebug() << "Unable to create a table. Error:" << query.lastError().text();
        return false;
    }

    return true;
}

void DbHelper::closeConnection()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

QSqlQueryModel* DbHelper::getAllRecords() const
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString q = "SELECT * FROM list";
    model->setQuery(q, m_db);

    if (model->lastError().isValid())
    {
        QSqlError error = model->lastError();
        qDebug() << "Unable to read data. Error: " << error.text();
        return nullptr;
        // обработка ошибки, например, вывод сообщения об ошибке
    }

    return model;
}

bool DbHelper::removeOther(const QString& ids)
{
    QString queryStr = QString("DELETE FROM list WHERE id NOT IN (%1)").arg(ids);
    QSqlQuery query(m_db);

    if (!query.exec(queryStr))
    {
        qDebug() << "Error deleting from table. Error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DbHelper::saveRecord(Task* task)
{
    if (task->id() == -1)
        return addNewRecord(task);
    if (task->id() >= 0)
        return updateRecord(task);

    return false;
}

bool DbHelper::updateRecord(const Task* task)
{
    if (task->id() < 0)
        return false;

    QSqlQuery query(m_db);
    QString strQuery =  "UPDATE list SET name = :name, deadline = :deadline, progress = :progress "
                        "WHERE id = :id";
    query.prepare(strQuery);
    query.bindValue(":id", task->id());
    query.bindValue(":name", task->name());
    query.bindValue(":deadline", task->deadline().toString("dd.MM.yyyy"));
    query.bindValue(":progress", task->progress());

    if (!query.exec())
    {
        qDebug() << "Unable to update a record. Error:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DbHelper::addNewRecord(Task* task)
{
    if (task->id() != -1)
        return false;

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO list(name, deadline, progress) "
                  "VALUES (:name, :deadline, :progress)");
    query.bindValue(":name", task->name());
    query.bindValue(":deadline", task->deadline().toString("dd.MM.yyyy"));
    query.bindValue(":progress", task->progress());

    if (!query.exec())
    {
        qDebug() << "Unable to insert a new record. Error:" << query.lastError().text();
        return false;
    }

    // Установить в task получившийся в БД id этой записи
    query.clear();
    query.exec("SELECT MAX(id) FROM list");
    if (query.next())
    {
        int maxId = query.value(0).toInt();
        task->setId(maxId);
    }
    else
    {
        qDebug() << "Unable to get max id from db. Error:" << query.lastError().text();
        return false;
    }

    return true;
}

//bool DbHelper::removeRecord(const quint32& id)
//{

//    QSqlQuery query(m_db);
//    query.prepare("DELETE FROM list WHERE id=:id");
//    query.bindValue(":id", id);
//    if (!query.exec())
//    {
//        qDebug() << "Error deleting from table. Error:" << query.lastError().text();
//        return false;
//    }

//    return true;
//}
