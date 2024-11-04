#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person
{
    public:
        Person();
        ~Person();
        Person(std::string name, int age);

        void setAge(int age);
        void setName(std::string name);
        
        std::string toJson();

    private:
        std::string name;
        int age;
};

#endif // PERSON_HPP