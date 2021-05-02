import { createGraph, reDraw } from './draw.js';
import { solve } from './held-karp.js'

let chart = createGraph()

let nodesSet = new Set();
let edges = [];
let jsonData = {nodes: [], edges: []};
let jsons = []


function letter_to_index(letter) {
    function ord(str){return str.charCodeAt(0);}
    return ord(letter.toUpperCase())-ord("A");
}

function build_matrix_from_input(input) {
    let matrix = []
    let n = 26;
    for (let i = 0; i < n; i++){
        matrix[i] = []
        for (let j = 0; j < n; j++) {
            matrix[i][j] = Number.POSITIVE_INFINITY;
        }
        matrix[i][i] = -1;
    }

    let aux = input.split(", ");
    aux = aux.map((elem) => elem.split(" "));
    let from;
    let to;
    let distance;
    for (let i = 0; i < aux.length; i++) {
        [from, to, distance] = aux[i];
        from = letter_to_index(from)
        to = letter_to_index(to)
        matrix[from][from] = 0
        matrix[to][to] = 0
        matrix[from][to] = parseInt(distance)
        matrix[to][from] = parseInt(distance)
    }
    return matrix
}

function getNodesAndEdges(input) {
    if (!input) {
        return
    }
    let aux = input.split(", ");
    aux = aux.map((elem) => elem.split(" "));
    let from;
    let to;
    let distance;
    for (let i = 0; i < aux.length; i++) {
        [from, to, distance] = aux[i];
        nodesSet.add(from);
        nodesSet.add(to);
        edges.push({from: from, to: to, weight: distance})
    }
}

document.getElementById("add").addEventListener("click", getInput);
document.getElementById("clean").addEventListener("click", cleanGraph);
document.getElementById("calculate").addEventListener("click", calculateOptimal);


function getInput() {
    const inputElement = document.getElementById("graph")
    let input = inputElement.value;
    inputElement.value = "";
    getNodesAndEdges(input);
    let nodes = [];
    nodesSet.forEach(element => {
        nodes.push({"id": element});
    });
    jsonData = {nodes: nodes, edges: edges};
    chart = reDraw(chart, jsonData);
}

function cleanGraph() {
    jsonData = {nodes: [], edges: []};
    chart = reDraw(chart, jsonData)
    nodesSet = new Set();
    edges = [];
}

async function calculateOptimal() {
    // Calculo de solución y tiempo en Javascript
    // const secondsJS = new Date().getTime();
    // const javascriptSolution = solve()
    // const javascripTime = (new Date().getTime()) - secondsJS;
    const javascripTime = 1;

    // Calculo de solución y tiempo en C
    const secondsC = new Date().getTime();
    const optimalSolution = "abc";
    const cTime = (new Date().getTime()) - secondsC;

    const solutionElements = optimalSolution.split("")
    let solutionEdges = [];
    for (let i = 0; i < (solutionElements.length - 1); i++) {
        solutionEdges.push({from: solutionElements[i], to: solutionElements[i + 1]})
    }
    jsonData.edges.forEach((element, i) => {
        if (solutionEdges.some((solutionEdge) => (solutionEdge.from === element.from && solutionEdge.to === element.to))) {
            jsonData.edges[i] = {...element, stroke: {color: "#FFB27A", thickness: "3"}}
        }
    })
    jsons.push(jsonData)
    chart = reDraw(chart, jsonData)
    jsonData = {nodes: [], edges: []};

    const graphNumber = jsons.length

    const tableBody = document.getElementById("table-entries")
    const tableRow = document.createElement("tr")
    tableRow.addEventListener("click", () => {drawPrevious(graphNumber - 1)})

    const firstCol = document.createElement("td")
    firstCol.scope = "row"
    firstCol.appendChild(document.createTextNode(graphNumber))

    const secondCol = document.createElement("td")
    secondCol.appendChild(document.createTextNode(javascripTime))

    const thirdCol = document.createElement("td")
    thirdCol.appendChild(document.createTextNode(cTime))

    tableRow.appendChild(firstCol)
    tableRow.appendChild(secondCol)
    tableRow.appendChild(thirdCol)

    tableBody.appendChild(tableRow)
}

function drawPrevious(index) {
    chart = reDraw(chart, jsons[index])
}