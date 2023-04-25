arr = [1, 2, 3, 2, 1, 3, 4, 2, 5];
arr_unique = []

for(var i = 0; i < arr.length; i++){
    same = true
    for(var j = i+1; j < arr.length; j++){
        if(arr[j] == arr[i]){
            same = false
        }
    }
    if(same){
        arr_unique.push(arr[i])
    }
}

console.log(arr_unique)