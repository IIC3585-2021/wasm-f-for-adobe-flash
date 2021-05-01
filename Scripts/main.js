import { createGraph, reDraw } from './draw.js';
// 漢字
const abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const chart = createGraph()

let nodesSet = new Set();
let edges = [];

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



function getInput() {
    const inputElement = document.getElementById("graph")
    let input = inputElement.value;
    inputElement.value = "";
    getNodesAndEdges(input);
    let nodes = [];
    nodesSet.forEach(element => {
        nodes.push({"id": element});
    });
    let jsonData = {nodes: nodes, edges: edges};
    chart = reDraw(chart, jsonData);
}

function cleanGraph() {
    reDraw(chart, {nodes: [], edges: []})
    nodesSet = new Set();
    edges = [];
}
