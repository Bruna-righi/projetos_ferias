
const arr = [0,1,2,3,4,5,6,7,8,9,10]

const f1 =function(item, idx){
    console.log(item,idx)
    return item*item
}


//no geral, toda função do js retorna um novo array
const val = arr.reverse()
    .map(f1)
    .filter(function(item,idx){
        return idx%2==0
    })
    .reduce(function(acc,item){
        return acc*(item+1)
    },1)


arr.push('hi')
const f = arr.indexOf(6)

arr.splice(f,1)

console.log(val)
console.log(arr)
console.log(f)