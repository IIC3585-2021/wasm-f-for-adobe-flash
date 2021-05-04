import Module from './findbestWASM.js'


Module().then(function(mymodule) {
    let myStrValue = "A B 7, A C 3, A D 2, A E 8, A F 10, A G 1, A H 7, A I 3, A J 4, A K 10, A L 6, A M 3, A N 1, A O 1, B C 10, B D 2, B E 5, B F 5, B G 5, B H 6, B I 1, B J 8, B K 2, B L 2, B M 8, B N 3, B O 4, C D 2, C E 7, C F 8, C G 7, C H 4, C I 4, C J 7, C K 3, C L 5, C M 10, C N 4, C O 4, D E 5, D F 4, D G 6, D H 5, D I 10, D J 2, D K 2, D L 5, D M 2, D N 2, D O 6, E F 6, E G 1, E H 8, E I 10, E J 6, E K 5, E L 8, E M 1, E N 9, E O 3, F G 1, F H 4, F I 1, F J 6, F K 9, F L 2, F M 8, F N 3, F O 2, G H 9, G I 2, G J 10, G K 8, G L 7, G M 2, G N 8, G O 4, H I 8, H J 4, H K 5, H L 7, H M 9, H N 4, H O 8, I J 5, I K 5, I L 10, I M 10, I N 1, I O 6, J K 4, J L 4, J M 8, J N 9, J O 7, K L 3, K M 1, K N 4, K O 6, L M 7, L N 2, L O 7, M N 3, M O 5, N O 2"
    let ptr  = mymodule.allocate(mymodule.intArrayFromString(myStrValue), mymodule["ALLOC_NORMAL"]);
    console.log('output')
    console.log(mymodule.UTF8ToString(mymodule._findbest(ptr)))
})