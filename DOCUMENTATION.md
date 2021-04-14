# DOCUMENTATION

---

## VARIABLES AND OPERATIONS

`int`
`longint`
`float`

To use them you should write:
```asm
int a;
longint b = 3;
float c = 1.0;
```
Here `1.0` is inevitable, don't used `1` or `1.`,
it'll cause an error

Then you can do any **operations** from the list
you want:

`+`
`-`
`*`
`/`

So it'll look like this:

```asm
int a = 3;
a = a + 3;
longint b = 3 - 6;
float c = 1.523;
c = c / 8.0;
print(a, b, c);
```

**WARNING:** `longint` is quite unstable
(if it hurts use `int` instead)

## FUNCTIONS

Function structure is pretty simple:

```asm
func f
{
    return 0;
}
```

**WARNING:** You always need to
return something, if it's void
return anything you want, like 0

**PARAMETERS** of the function lie in `array`
`Args` and it's a reserved name. The most
marvelous benefit of **maffin** is it's
function parameters, you don't have to assign
restricted type, you can use anything you want

```asm
func f{
    print(get(get(Args, 0), 0));
    return 0;
}

array arr[4];
stack lol;
set(arr, 5, 0);
push(lol, 3);
f(arr);
f(lol);
```

output:
```c
5
3
```

or another example

```asm
func lol
{
    int i = get(Args, 0);
    int j = get(Args, 1);
    if (i >= j) { return 0; }
    print(i);
    lol(i+1, j);
}
lol(0, 5);
```

output:
```c
0
1
2
3
4 
```

## WHILE LOOP

It's the most common thing:

```asm
int i = 0;
while (i < 10){
    print(i);
    i = i + 1;
}
```

output:
```c
0
1
2
3
4
5
6
7
8
9 
```

## DATA STRUCTURES

### array

`set(array_name, key, position);`

`get(array_name, position);`

`sizeof(array_name);`

```asm
array arr[5];
set(arr, 5, 0);
int x = get(arr, 0);
print(x);
```

output:
```c
5
```

### stack

`set(stack_name, key, position);`

`get(stack_name, position);`

`push(stack_name, key);` pushing back

`pop(stack_name);` pop back

`sizeof(stack_name);`

`capacity(stack_name);`

```asm
stack st;
push(st, 3);
print(sizeof(st));
print(capacity(st));
push(st, 5);
print(sizeof(st));
print(capacity(st));
push(st, 6);
print(sizeof(st));
print(capacity(st));
print(0, 0, 0, 0, 0, 0);
print(get(st, 0));
print(get(st, 1));
print(get(st, 2));
pop(st);
pop(st);
print(sizeof(st));
print(capacity(st));
```

output:
```c
1
2
2
2
3
4
0 0 0 0 0 0
3
5
6
1
4 
```

### skiplist

`set(stack_name, key, position);`

`get(stack_name, position);`

`insert(stack_name, key, position);`

`erase(stack_name, position);`

`sizeof(stack_name);`

`capacity(stack_name);`

```asm
skiplist lst;
insert(lst, 3, 0);
insert(lst, 5, 0);
insert(lst, 9, 1);
print(get(lst, 0));
print(get(lst, 1));
print(get(lst, 2));
erase(lst, 0);
print(get(lst, 0));
print(get(lst, 1));
set(lst, 228, 1);
print(get(lst, 0));
print(get(lst, 1));
```

output:
```c
5 
9 
3 
9 
3 
9 
228 
```