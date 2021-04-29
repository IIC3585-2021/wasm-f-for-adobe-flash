import {loadGraph} from './drawer.js';

class Node {
    constructor(val){
        this.val = val;
        this.connections = [];
    }
}
// 漢字
const abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

class Graph {
    constructor(matrix){
        this.matrix = matrix;
        this.nodes = [];
        for (let i = 0; i < matrix.length; i++) {
            this.nodes.push(new Node(abc[i]))
        }
        for (let i = 0; i < matrix.length; i++) {
            for (let j = 0; j < matrix[0].length; j++) {
                if (matrix[i][j] > 0) {
                    let from = this.nodes[i];
                    let to = this.nodes[j];
                    from.connections.push(to);
                }
            }
        }
    }
}