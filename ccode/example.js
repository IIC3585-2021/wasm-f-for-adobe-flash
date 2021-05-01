import Module from './fibWASM.js'


Module().then(function(mymodule) {
    let myStrValue = "A B 10, A D 8, A E 7, B D 7, B C 12, C D 6, C F 7, C G 5, D E 9, D F 4, E G 11, F G 3"
    let ptr  = mymodule.allocate(mymodule.intArrayFromString(myStrValue), mymodule["ALLOC_NORMAL"]);
    console.log('holi')
    console.log(mymodule.UTF8ToString(mymodule._fib(ptr)))
})