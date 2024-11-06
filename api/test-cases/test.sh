#!/bin/bash

# Prompt the user for the create path, search path, and port
read -p "Enter the create path (e.g., /create): " CREATE_PATH
read -p "Enter the search path (e.g., /search): " SEARCH_PATH
read -p "Enter the port (e.g., 8080): " PORT

# Base URL
BASE_URL="http://localhost:$PORT"

# Test data
NAME1="John"
AGE1=30
NAME2="Jane"
AGE2=25

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Arrays to store test results
PASSED_TESTS=()
FAILED_TESTS=()

# Function to print test result
print_result() {
    if echo "$1" | jq -e '.error' > /dev/null 2>&1; then
        FAILED_TESTS+=("$2: FAILED\nInput: $3\nResponse: $1")
    else
        PASSED_TESTS+=("$2: PASSED\nInput: $3\nResponse: $1")
    fi
}

# Function to perform a curl request and check the response
perform_curl() {
    RESPONSE=$(curl -s -X $1 "$BASE_URL$2" -H "Content-Type: application/json" -d "$3")
    print_result "$RESPONSE" "$4" "$3"
}

echo "Running tests...\n"

# Successful tests
perform_curl "POST" "$CREATE_PATH" "{\"name\":\"$NAME1\", \"age\":$AGE1}" "Create Person (POST)"
perform_curl "GET" "$SEARCH_PATH?name=$NAME1" "" "Search Person (GET)"

# Failed tests
perform_curl "POST" "$CREATE_PATH" "{\"name\":\"$NAME1\", \"age\":$AGE1}" "Create Duplicate Person (POST)"
perform_curl "GET" "$CREATE_PATH" "{\"name\":\"$NAME2\", \"age\":$AGE2}" "Create Person with GET"
perform_curl "PUT" "$CREATE_PATH" "{\"name\":\"$NAME2\", \"age\":$AGE2}" "Create Person with PUT"
perform_curl "GET" "$SEARCH_PATH?name=NonExistent" "" "Search Non-Existent Person (GET)"
perform_curl "POST" "$SEARCH_PATH?name=$NAME1" "" "Search Person with POST"
perform_curl "PUT" "$SEARCH_PATH?name=$NAME1" "" "Search Person with PUT"

# Print results
echo -e "\n${GREEN}Successful Tests:${NC}"
for test in "${PASSED_TESTS[@]}"; do
    echo -e "${GREEN}$test${NC}\n"
done

echo -e "\n${RED}Failed Tests:${NC}"
for test in "${FAILED_TESTS[@]}"; do
    echo -e "${RED}$test${NC}\n"
done