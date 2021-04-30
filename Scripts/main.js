import { loadGraph } from './draw.js';

class Node {
    constructor(val){
        this.val = val;
        this.connections = [];
    }
}
// 漢字
const abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// input = [[A,B,1], [A,C,2], [B,C,3]]
function draw_graph(input) {
    let aux = input.split(", ");
    aux = aux.map((elem) => elem.split(" "));

    let nodes = [];
    let edges = [];
    let from;
    let to;
    let distance;
    let nodes_set = new Set();
    for (let i = 0; i < aux.length; i++) {
        [from, to, distance] = aux[i];
        nodes_set.add(from);
        nodes_set.add(to);
        edges.push({from: from, to: to, weight: distance})
    }
    nodes_set.forEach(element => {
        nodes.push({"id": element})
    });
    let json_data = {nodes: nodes, edges: edges};
    loadGraph(json_data)
}

document.getElementById("calculate").addEventListener("click", getInput);

function getInput() {
    const input_element = document.getElementById("graph")
    let input = input_element.value;
    input_element.value = "";
    input = "A B 1, A C 2, B C 3"
    draw_graph(input)
}
