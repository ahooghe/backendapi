function showMessage(message, type) {
    const messageBox = document.createElement('div');
    messageBox.className = `message-box ${type}`;
    messageBox.innerText = message;

    const resultDiv = document.getElementById('result');
    resultDiv.appendChild(messageBox);

    // Trigger reflow to apply the transition
    messageBox.offsetHeight;
    messageBox.classList.add('show');

    setTimeout(() => {
        messageBox.classList.remove('show');
        setTimeout(() => {
            resultDiv.removeChild(messageBox);
        }, 500); // Match the transition duration
    }, 3000);
}

function showSuccess(message) {
    showMessage(message, 'success');
}

function showError(message) {
    showMessage(message, 'error');
}

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
    .then(response => response.json().then(data => ({ status: response.status, body: data })))
    .then(({ status, body }) => {
        if (status >= 200 && status < 300) {
            showSuccess(`Person created successfully.`);
        } else {
            showError(`Error: ${body.error}`);
        }
    })
    .catch(error => {
        showError('Error: ' + error);
    });
});

document.getElementById('searchPersonForm').addEventListener('submit', function(event) {
    event.preventDefault();
    const name = document.getElementById('searchName').value;

    const url = new URL(searchPersonUrl);
    url.searchParams.append('name', name);

    fetch(url, {
        method: 'GET'
    })
    .then(response => response.json().then(data => ({ status: response.status, body: data })))
    .then(({ status, body }) => {
        if (status >= 200 && status < 300) {
            showSuccess(`Person found with the name ${body.name}.\nThey're ${body.age} years old.`);
        } else {
            showError(`Error: ${body.error}`);
        }
    })
    .catch(error => {
        showError('Error: ' + error);
    });
});