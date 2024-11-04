#include "../inc/Handlers.hpp"

Handlers::Handlers()
{
}

Handlers::~Handlers()
{
}

Response Handlers::createPersonHandler(Request request, DataStore &store, Config config)
{
    std::string ageStr = request.getJsonField("age");
    std::string name = request.getJsonField("name");

    int age = std::stoi(ageStr);

    Response response;
    if (age < 18)
    {
        response.setStatusCode(400);
        response.setHeader("Content-Type", "application/json");
        response.setBody("{\"error\": \"Invalid age\", \"message\": \"User too young.\"}");
        return response;
    }

    
    if (config.getMaxAgeEnabled())
    {
        int maxAge = config.getMaxAge();
        if (age > maxAge)
        {
            response.setStatusCode(400);
            response.setHeader("Content-Type", "application/json");
            response.setBody("{\"error\": \"Invalid age\", \"message\": \"User too old.\"}");
            return response;
        }
    }

    if (!store.searchPerson(name).toJson().empty())
    {
        response.setStatusCode(400);
        response.setHeader("Content-Type", "application/json");
        response.setBody("{\"error\": \"Someone with this name already exists\"}");
        return response;
    }

    store.addPerson(name, age);

    response.setStatusCode(201);
    response.setHeader("Content-Type", "application/json");
    response.setBody("{\"message\": \"Person created.\"}");
    return response;
}

Response Handlers::searchPersonHandler(Request request, DataStore &store, Config config)
{
    Person person = store.searchPerson(request.getJsonField("name"));

    Response response;
    if (person.toJson().empty())
    {
        response.setStatusCode(404);
        response.setHeader("Content-Type", "application/json");
        response.setBody("{\"error\": \"Person not found\"}");
        return response;
    }

    response.setStatusCode(200);
    response.setHeader("Content-Type", "application/json");
    response.setBody(person.toJson());
    return response;
}