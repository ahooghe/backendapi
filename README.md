# backendapi

## Overview

`backendapi` is a C++ backend API server that uses SQLCipher for encrypted SQLite database management. The server provides endpoints to create and search for persons in the database. The configuration for the server can be set through a configuration file or default values.

## Features

- **Encrypted Database**: Uses SQLCipher for encrypted SQLite database management.
- **Configurable**: Configuration can be set through a configuration file or default values.
- **Endpoints**:
  - `POST /create`: Create a new person with a name and age.
  - `GET /search`: Search for a person by name.

## API Documentation

### Create Person

- **URL**: `/create`
- **Method**: `POST`
- **Content-Type**: `application/json`
- **Request Body**:
    ```json
    {
        "name": "string",
        "age": integer
    }
    ```

- **Success Response**:
  - **Code**: `201 Created`
  - **Content**:
    ```json
    {
        "message": "Person created.",
        "name": "string",
        "age": integer
    }
    ```

- **Error Responses**:
  - **Code**: `400 Bad Request`
  - **Case**: Underaged
  - **Content**:
    ```json
    {
        "error": "User too young."
    }
    ```
  - **Code**: `400 Bad Request`
  - **Case**: Overaged
  - **Content**:
    ```json
    {
        "error": "User too old."
    }
    ```

### Search Person

- **URL**: `/search`
- **Method**: `GET`
- **Query Parameters**: 
  - `name`: The name of the person to search for.

- **Success Response**:
  - **Code**: `200 OK`
    ```json
    {
        "name": "string",
        "age": integer
    }
    ```

- **Error Responses**:
  - **Code**: `404 Not Found`
  - **Content**: 
    ```json
    {
        "error": "Person not found"
    }
    ```

### **Invalid Inputs**:
- **Wrong method or uri**:
  - **Code**: `405 Method Not Allowed`
  - **Content**:
     ```json
    {
        "error": "Method Not Allowed",
        "message": "The HTTP method or URI path is incorrect."
    }
     ```

- **Invalid Request**:
  - **Code**: `400 Bad Request`
  - **Content**:
    ```json
    {
        "error": "Bad Request",
        "message": "The HTTP request is invalid."
    }
    ```

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

### Configurable Options

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
        curl -X GET http://localhost:8080/search?name=Anthony
        ```

3. **Use Front-End Webapp**:
You can use the API with the front-end webapp located in `api/front-end/`. To launch the front-end webapp, you'll need to run a local webserver. 
The suggested solution is using a simple python3 command to run it, but this is not mandatory. If you wish to use python3, run this command inside the front-end directory.
    ```sh
    python3 -m http.server 3000
    ```
    After starting the local webserver, you can access the front-end webapp by navigating to http://localhost:3000 in your web browser.

Any response will be a HTTP response with a JSON field in the body. 

## Testing

To ensure the API is working correctly, you can run a series of automated tests using the provided `test.sh` script. This script will prompt you for the create path, search path, and port, and then execute a series of curl commands to test the API.

### Running the Tests

1. **Launch the API Server**:
    ```sh
    make
    ./backendapi <path/to/config/file>
    ```

2. **Make the Script Executable**:
    ```sh
    chmod +x test.sh
    ```

3. **Run the Script**:
    ```sh
    ./test.sh
    ```

4. **Follow the Prompts**: The script will ask for the create path, search path, and port. Enter the appropriate values.

5. **Reset the Database**: If the test is run multiple times, remember to reset the database by running:
    ```sh
    make resetdb
    ```
    If this is not done, the create test will fail in subsequent runs.

### Test Cases

The script will run the following test cases:

- **Create Person (POST)**: Tests creating a person with a POST request.
- **Create Duplicate Person (POST)**: Tests creating the same person again (should fail).
- **Create Person with GET**: Tests creating a person with a GET request (should fail).
- **Create Person with PUT**: Tests creating a person with a PUT request (should fail).
- **Search Person (GET)**: Tests searching for a person with a GET request.
- **Search Non-Existent Person (GET)**: Tests searching for a non-existent person (should fail).
- **Search Person with POST**: Tests searching for a person with a POST request (should fail).
- **Search Person with PUT**: Tests searching for a person with a PUT request (should fail).

The results of the tests will be displayed in the terminal, with successful tests shown in green and failed tests shown in red. Each test result will include the input data and the response from the server.

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
There is no license. This code was written for a job interview. It is completely open source and you have my full permission to use any part of it as you like.

## Contact
For any questions or inquiries, please contact [anthonyhooghe@gmail.com].

