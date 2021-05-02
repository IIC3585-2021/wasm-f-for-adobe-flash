
const abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


function solve(matrix) {
    let res = "";
    let nodes = [];
    for (let i = 0; i < matrix.length; i++) {
        if (matrix[i][i] == 0){
            nodes.push(i);
        }
    }
    res += `${nodes[0]}`
    // [b,[x,y]] = min dist from a to node b passing through x and y
    let min_ways = {}; 
    let parents = {}

    // finds min distance from nodes[0] to node passing through all must_visit
    function find_min_way (node_ind, must_visit) {
        if (min_ways[[node_ind,must_visit]] !== undefined) {
            return min_ways[[node_ind,must_visit]]
        }
        if (must_visit.length === 0){
            min_ways[[node_ind,must_visit]] = matrix[0][node_ind]
            parents[[node_ind,must_visit]] = nodes[0]
            return min_ways[[node_ind,must_visit]]
        }
        let res = Number.POSITIVE_INFINITY;
        let some_way;
        let current;
        let aux_parent;
        for (let i = 0; i < must_visit.length; i++) {
            current = must_visit[i]
            some_way = matrix[current][node_ind] + find_min_way(current,without(must_visit,current))
            if (some_way < res) {
                aux_parent = current
            }
            res = Math.min(res, some_way)
        }
        parents[[node_ind,must_visit]] = aux_parent;
        min_ways[[node_ind,must_visit]] = res;
        return res
        
    }

    find_min_way(nodes[0],[...nodes.slice(1,nodes.length)])

    // we construct the 
    current_key = [...nodes]
    for (let i = 0; i < nodes.length-1; i++) {
        res += `,${parents[current_key].toString()}`
        current_key = [parents[current_key], ...without(current_key.slice(1,current_key.length),parents[current_key])]
    }

    
    return  res.split(",").map(elem => abc[elem]?? null).join("")
}

function without(list, node){
    let res = [];
    for (let i = 0; i < list.length; i++) {
        if (list[i] !== node) {
            res.push(list[i])
        }
    }
    return res
}


// let matrix = [
//     [0,1,15,6],
//     [2,0,7,3],
//     [9,6,0,12],
//     [10,4,8,0],
// ]

// matrix = [
//     [0,1,20,1],
//     [1,0,1,20],
//     [20,1,0,1],
//     [1,20,1,0],
// ]

// console.log(solve(matrix))