#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include "Response.hpp"
#include "Request.hpp"
#include "DataStore.hpp"

class Handlers
{
    public:
        Handlers();
        ~Handlers();

        Response createPersonHandler(Request request, DataStore &store, Config config);
        Response searchPersonHandler(Request request, DataStore &store, Config config);

    private:
};

#endif // HANDLERS_HPP