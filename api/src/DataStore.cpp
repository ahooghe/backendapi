#include "../inc/DataStore.hpp"

DataStore::DataStore()
{
}

DataStore::~DataStore()
{
    sqlite3_close(db);
}

void DataStore::init(const std::string& password, const std::string& filename)
{
    int rc = sqlite3_open(filename.c_str(), &db);
    if (rc)
        throw std::runtime_error("Can't open database: " + std::string(sqlite3_errmsg(db)));

    std::string pragmaKey = "PRAGMA key = '" + password + "';";
    rc = sqlite3_exec(db, pragmaKey.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to set encryption key: " + std::string(sqlite3_errmsg(db)));

    const char* sql = "CREATE TABLE IF NOT EXISTS Person ("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "Name TEXT NOT NULL,"
                      "Age INTEGER NOT NULL);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::string error = "SQL error: " + std::string(errMsg);
        sqlite3_free(errMsg);
        throw std::runtime_error(error);
    }
}

void DataStore::addPerson(std::string name, int age)
{
    const char* sql = "INSERT INTO Person (Name, Age) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, age);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
        throw std::runtime_error("Failed to execute statement: " + std::string(sqlite3_errmsg(db)));

    sqlite3_finalize(stmt);
}

Person DataStore::searchPerson(std::string name)
{
    const char* sql = "SELECT Name, Age FROM Person WHERE Name = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    Person person;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) 
    
    {
        person.setName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        person.setAge(sqlite3_column_int(stmt, 1));
    } 
    else 
        return Person();

    sqlite3_finalize(stmt);
    return person;
}