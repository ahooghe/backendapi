#ifndef DATASTORE_HPP
#define DATASTORE_HPP

#include <string>
#include <sqlite3.h>
#include <stdexcept>

#include "Person.hpp"

class DataStore
{
    public:
        DataStore();
        ~DataStore();

        void init(const std::string& password, const std::string& filename);
        void addPerson(std::string name, int age);
        Person searchPerson(std::string name);

    private:
        sqlite3* db;
};

#endif // DATASTORE_HPP