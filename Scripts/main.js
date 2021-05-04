import { createGraph, reDraw } from './draw.js';
import { solve } from './held-karp.js';
import Module from './findbestWASM.js';

let chart = createGraph()

let nodesSet = new Set();
let edges = [];
let jsonData = {nodes: [], edges: []};
let jsons = []
let matrix = []
let temporalInput = "";
let n = 26;
for (let i = 0; i < n; i++){
    matrix[i] = []
    for (let j = 0; j < n; j++) {
        matrix[i][j] = Number.POSITIVE_INFINITY;
    }
    matrix[i][i] = -1;
}
function resetMatrix(){
    for (let i = 0; i < n; i++){
        matrix[i] = []
        for (let j = 0; j < n; j++) {
            matrix[i][j] = Number.POSITIVE_INFINITY;
        }
        matrix[i][i] = -1;
    }
}
function letter_to_index(letter) {
    function ord(str){return str.charCodeAt(0);}
    return ord(letter.toUpperCase())-ord("A");
}

function buildMatrix(input) {
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
    if (temporalInput === "") {
        temporalInput += input;
    } else {
        temporalInput = temporalInput + ", " + input;
    }
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
    temporalInput = "";
    resetMatrix();
    jsonData = {nodes: [], edges: []};
    chart = reDraw(chart, jsonData)
    nodesSet = new Set();
    edges = [];
}


async function calculateOptimal() {
    // Calculo de solución y tiempo en Javascript
    const secondsJS = new Date().getTime();
    buildMatrix(temporalInput);
    console.log('holi')
    const ptr_array = [];
    console.log(temporalInput)
    let javascriptSolution;
    let cost;
    [javascriptSolution, cost] = solve(matrix);
    const javascripTime = (new Date().getTime()) - secondsJS;
    // const javascripTime = 1;

    console.log(javascriptSolution)
    // Calculo de solución y tiempo en C
    const secondsC = new Date().getTime();
    Module().then(function(mymodule) {
        const ptr  = mymodule.allocate(mymodule.intArrayFromString(temporalInput), mymodule["ALLOC_NORMAL"]);
        const optimalSolutionC =(mymodule.UTF8ToString(mymodule._findbest(ptr)));
        console.log('Csolution',optimalSolutionC);
    })
    const cTime = (new Date().getTime()) - secondsC;
    //console.log(javascriptSolution[0])

    const solutionElements = javascriptSolution.split("")
    let solutionEdges = [];
    for (let i = 0; i < (solutionElements.length - 1); i++) {
        solutionEdges.push({from: solutionElements[i], to: solutionElements[i + 1]})
    }
    solutionEdges.push({from: solutionElements[0], to: solutionElements[solutionElements.length-1]})
    console.log(solutionEdges)
    jsonData.edges.forEach((element, i) => {
        if (solutionEdges.some((solutionEdge) => ((solutionEdge.from === element.from && solutionEdge.to === element.to) ||
        (solutionEdge.to === element.from && solutionEdge.from === element.to)))) {
            jsonData.edges[i] = {...element, stroke: {color: "#FFB27A", thickness: "3"}}
        }
        else if ((solutionEdges[solutionEdges.length-1].from === element.from && solutionEdges[solutionEdges.length-1].to === element.to) ||
                (solutionEdges[solutionEdges.length-1].to === element.from && solutionEdges[solutionEdges.length-1].from === element.to)) {
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
    secondCol.appendChild(document.createTextNode(cost))

    const thirdCol = document.createElement("td")
    thirdCol.appendChild(document.createTextNode(javascripTime))

    const fourthCol = document.createElement("td")
    fourthCol.appendChild(document.createTextNode(cTime))

    tableRow.appendChild(firstCol)
    tableRow.appendChild(secondCol)
    tableRow.appendChild(thirdCol)
    tableRow.appendChild(fourthCol)

    tableBody.appendChild(tableRow)
}

function drawPrevious(index) {
    chart = reDraw(chart, jsons[index])
}