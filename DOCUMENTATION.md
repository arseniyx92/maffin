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
**********************ERROR**********************

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