https://leetcode.com/studyplan/30-days-of-javascript/
# Basics
###### Hello World
```
var createHelloWorld = function() {
    return function(...args) {
        return "Hello World";
    }
};
```

###### Counter
```
var createCounter = function(n) {
    let count = n;
    return function() {
        return count++;
    };
};
```

###### To Be or Not To Be
```
var expect = function(val) {
    return {
        toBe : (value) => {
            if(value === val)
                return true;
            else
                throw "Not Equal";
        },
        notToBe : (value) => {
            if(value === val)
                throw "Equal";
            else
                return true;
        }
    }
};
```

###### Counter II
```
var createCounter = function(init) {
    let value = init;
    return {
        increment : () => {
            return ++value;
        },
        decrement : () => {
            return --value;
        },
        reset : () => {
            value = init;
            return value;
        }
    }
};
```

# Array Transformation

###### Apply Transform over Each Element
```
var map = function(arr, fn) {
    let newArr = [];
    arr.forEach((value, index) => {
        newArr.push(fn(value, index));
    });

    return newArr;
};
```

###### Filter Elements
```
var filter = function(arr, fn) {
    // return arr.filter((value,index) => {
    //     if(fn(value,index))
    //         return fn(value,index);
    // })
  
    let newArr = [];
    arr.forEach((value,index) => {
        if(fn(value,index)){
            newArr.push(value);
        }
    });
  
    return newArr;
};
```

###### Reduce Transformation
```
var reduce = function(nums, fn, init) {
    let result = init;
    nums.forEach((num) => {
        result = fn(result, num);
    })
    return result;
};
```

# Functions

###### Function Composition
```
var compose = function(functions) {
    return function(x) {
        let result = x;
        for(let i=functions.length-1; i>=0 ;i--)
            result = functions[i](result);
        return result;
    }
};
```

###### Argument Length
```
var argumentsLength = function(...args) {
    return args.length;
};
```

###### Once Call
```
var once = function(fn) {
    let called = false;
    return function(...args){
        if(!called){
            called = true;
            return fn(...args);
        }
    }
};
```

###### Memoize Function
```
function memoize(fn) {
    const cache = {};

    return function(...args) {
        const key = JSON.stringify(args);

        if(key in cache)
            return cache[key];

        let result = fn(...args);
        cache[key] = result;

        return result;
    }
}
```

# Promises

###### Add 2 Promises
```
var addTwoPromises = async function(promise1, promise2) {
    // const num1 = await promise1;
    // const num2 = await promise2;

    // return num1+num2;

    // Promise all method
    const [num1,num2] = await Promise.all([promise1, promise2]);
    return num1+num2;
};
```

###### Sleep
```
async function sleep(millis) {
    // Returns promise after millis time
    return await new Promise((resolve) => setTimeout(resolve,millis));
}
```

###### Timeout Cancellation
```

```

# JSON

###### Is Object Empty
```
var isEmpty = function(obj) {
    if(Array.isArray(obj))
        return obj.length === 0;
        
    return Object.keys(obj).length === 0;
};
```

###### Chunks of Array
```
var chunk = function(arr, size) {
    if(arr.length === 0) return [];

    let res = [];
    let temp = [];

    for(let i=0;i<arr.length;i++){
        temp.push(arr[i]);
        if(temp.length === size){
            res.push(temp);
            temp = [];
        }
    }

    if(temp.length>0) res.push(temp);

    return res;
};
```

Return -> [[SDE Prep Kit]]

