# backendapi

## Overview

`backendapi` is a C++ backend API server that uses SQLCipher for encrypted SQLite database management. The server provides endpoints to create and search for persons in the database. The configuration for the server can be set through a configuration file or default values.

## Features

- **Encrypted Database**: Uses SQLCipher for encrypted SQLite database management.
- **Configurable**: Configuration can be set through a configuration file or default values.
- **Endpoints**:
  - `POST /create`: Create a new person with a name and age.
  - `GET /search`: Search for a person by name.

## Requirements

- C++17
- SQLCipher

## Installation

1. **Install SQLCipher**:
   ```sh
   sudo apt-get install sqlcipher libsqlcipher-dev
   ```

2. **Clone the Repository**:
    ```sh
    git clone <repository-url>
    cd backendapi
    ```

3. **Build the Project**:
    ```sh
    make
    ```

## Configuration

The server can be configured using a configuration file. The configuration file should be in the following format:
```conf
SQLFile=data.db
SQLPass=password
CreateRoute=/create
SearchRoute=/search
MaxAgeEnabled=false
EnforceJSONFormat=false
Port=8080
MaxAge=100
```
Any values that are not in the config file will be set to the server defaults (The same values as in the example.)

- SQLFile: The name of the SQLite database file.
- SQLPass: The password used to encrypt the SQLite database.
- CreateRoute: The URL path for the endpoint to create a new person.
- SearchRoute: The URL path for the endpoint to search for a person.
- MaxAgeEnabled: A boolean value indicating whether the max age feature is enabled.
- EnforceJSONFormat: A boolean value indicating whether to enforce that the JSON field only holds the requested data.
- Port: The port number on which the server will listen for incoming requests.
- MaxAge: The maximum age value used if the max age feature is enabled.

## Usage

1. **Start the Server**:
    ```sh
    ./backendapi <path/to/config/file>
    ```
    If no configuration file is provided, the server will use the default values.

2. **Send Requests**:
You can now send requests to the server. 
    - A POST request can be used to create a person with the correct uri. 
        ex. using curl: 
        ```sh
        curl -X POST http://localhost:8080/create -H "Content-Type: application/json" -d '{"name":"Anthony", "age":25}'
        ```
    - A GET request can be used to search for a person with the correct uri.
        ex. using curl:
        ```sh
        curl -X GET http://localhost:8080/search -H "Content-Type: application/json" -d '{"name":"Anthony"}'
        ```

Any response will be a HTTP response with a JSON field in the body. 

## Code Structure

- src/: Contains the source code files.
    - main.cpp: The entry point of the server application.
    - Config.cpp: Handles the configuration settings.
    - DataStore.cpp: Manages the SQLite database operations.
    - Handlers.cpp: Contains the request handlers for the endpoints.
    - Request.cpp: Parses and manages HTTP requests.
    - Response.cpp: Constructs HTTP responses.
    - Router.cpp: Routes the incoming requests to the appropriate handlers.
    - Server.cpp: Manages the server operations and connections.

- inc/: Contains the header files.
    - Config.hpp: Header file for the configuration settings.
    - DataStore.hpp: Header file for the SQLite database operations.
    - Handlers.hpp: Header file for the request handlers.
    - Person.hpp: Header file for the Person class.
    - Request.hpp: Header file for the HTTP request management.
    - Response.hpp: Header file for the HTTP response construction.
    - Router.hpp: Header file for the request routing.
    - Server.hpp: Header file for the server operations.

- Makefile: The makefile to build the project.

## License
There is no license. This code was written for a job interview. It is complelely open source and you have my full permission to use any part of it as you like.

## Contact
For any questions or inquiries, please contact [anthonyhooghe@gmail.com].

