
function solve(matrix) {
    let res = -1;
    let nodes = [];
    for (let i = 0; i < matrix.length; i++) {
        if (matrix[i][i] == 0){
            nodes.push(i);
        }
    }

    // [b,[x,y]] = min dist from a to node b passing through x and y
    let min_ways = {}; 

    // finds min distance from nodes[0] to node passing through all must_visit
    function find_min_way (node_ind, must_visit) {
        if (min_ways[[node_ind,must_visit]] !== undefined) {
            return min_ways[[node_ind,must_visit]]
        }
        if (must_visit.length === 0){
            min_ways[[node_ind,must_visit]] = matrix[0][node_ind]
            return min_ways[[node_ind,must_visit]]
        }
        let res = Number.POSITIVE_INFINITY;
        let some_way;
        let current;
        for (let i = 0; i < must_visit.length; i++) {
            current = must_visit[i]
            some_way = matrix[current][node_ind] + find_min_way(current,without(must_visit,current))
            res = Math.min(res, some_way)
        }
        min_ways[[node_ind,must_visit]] = res;
        return res
        
    }


    return find_min_way(nodes[0],[...nodes.slice(1,nodes.length)])
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
//     [0,1,20,1],
//     [1,0,1,20],
//     [20,1,0,1],
//     [1,20,1,0],
// ]

// console.log(solve(matrix))