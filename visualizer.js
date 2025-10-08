function tickSimulation() {
    fetch('http://localhost:8888/tick', {method:'POST'})
    .then(response => response.json())
    .then(data => {
        document.getElementById('status').innerText = 'Simulation advanced';
        updateState();
    });
}

function induceBlockage() {
    fetch('http://localhost:8888/blockage', {method:'POST'})
    .then(response => response.json())
    .then(data => {
        document.getElementById('status').innerText = 'Blockage induced';
        updateState();
    });
}

function updateState() {
    fetch('http://localhost:8888/state')
    .then(response => response.json())
    .then(json => {
        let output = '';
        for (let node in json) {
            output += `Node ${node} has ${json[node]} cells\n`;
        }
        document.getElementById('output').innerText = output;
    });
}

// Initial state load
window.onload = updateState;
