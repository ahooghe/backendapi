const createPersonUrl = 'http://localhost:8080/create';
const searchPersonUrl = 'http://localhost:8080/search';

document.getElementById('createPersonForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const name = document.getElementById('createName').value;
    const age = document.getElementById('createAge').value;

    fetch(createPersonUrl, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ name: name, age: age })
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('createPersonResult').innerText = JSON.stringify(data);
    })
    .catch(error => {
        document.getElementById('createPersonResult').innerText = 'Error: ' + error;
    });
});

document.getElementById('searchPersonForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const name = document.getElementById('searchName').value;
    const age = document.getElementById('searchAge').value;

    fetch(searchPersonUrl, {
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ name: name, age: age })
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('searchPersonResult').innerText = JSON.stringify(data);
    })
    .catch(error => {
        document.getElementById('searchPersonResult').innerText = 'Error: ' + error;
    });
});