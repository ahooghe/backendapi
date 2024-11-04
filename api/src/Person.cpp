#include "../inc/Person.hpp"

Person::Person(): age(0)
{
}

Person::~Person()
{
}

Person::Person(std::string name, int age): name(name), age(age)
{
}

void Person::setAge(int age)
{
    this->age = age;
}

void Person::setName(std::string name)
{
    this->name = name;
}

std::string Person::toJson()
{
    if (name.empty() || age == 0)
        return "";
    return "{\"name\": \"" + name + "\", \"age\": " + std::to_string(age) + "}";
}

