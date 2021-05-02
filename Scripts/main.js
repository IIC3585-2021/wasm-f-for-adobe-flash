import { createGraph, reDraw } from './draw.js';

let chart = createGraph()

let nodesSet = new Set();
let edges = [];
let jsonData = {nodes: [], edges: []};
let temporalInput = "";
let jsons = []

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
    temporalInput = inputElement.value;
    inputElement.value = "";
    getNodesAndEdges(temporalInput);
    let nodes = [];
    nodesSet.forEach(element => {
        nodes.push({"id": element});
    });
    jsonData = {nodes: nodes, edges: edges};
    chart = reDraw(chart, jsonData);
}

function cleanGraph() {
    jsonData = {nodes: [], edges: []};
    reDraw(chart, jsonData)
    nodesSet = new Set();
    edges = [];
}

function calculateOptimal() {
    const optimalSolution = "abc";
    const javascripTime = 2;
    const cTime = 1;
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
    reDraw(chart, jsonData)

    const tableBody = document.getElementById("table-entries")
    const tableRow = document.createElement("tr")
    // tableRow.id = "table-row-" + jsons.length.

    const firstCol = document.createElement("td")
    firstCol.scope = "row"
    firstCol.appendChild(document.createTextNode(jsons.length))

    const secondCol = document.createElement("td")
    secondCol.appendChild(document.createTextNode(javascripTime))

    const thirdCol = document.createElement("td")
    thirdCol.appendChild(document.createTextNode(cTime))

    tableRow.appendChild(firstCol)
    tableRow.appendChild(secondCol)
    tableRow.appendChild(thirdCol)

    tableBody.appendChild(tableRow)
}
