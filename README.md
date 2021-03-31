# MAFFIN

![maffin.png](pictures/maffin.png)

For looking at the structure beneath:
 `@debug`

For changing float numbers' precision:
`@precision x`, where `x` is precision

If you need to print something:
`print( "something" )`

To compile text
`~`

## EXAMPLES

###V 0.2 (float implemented and `@debug` changed)
###### №1

```asm
    @debug
    @precision 30
    
    float a = 32.3423;
    print(a);
    ~
```

RETURNS

```c
    a(3) 13(2) 32.3423(3) =(2) (1) 
    print(2) a(3) ((2) (1) 
    (0) 
    32.3423000000000016029844118748 
```

###V 0.1
###### №1

```asm
    @debug

    int ok = 3;
    int op = 2;
    print(ok+op);
    
    ~
```

RETURNS

```c
    ok 0 3 =  
    op 0 2 =  
    print ok op + (  
     
    5 
```

###### №2

```asm
    @debug

    int lol = 2+3-4;
    print(lol-3);
    ~
```

RETURNS

```c
    lol 0 2 3 + 4 - =  
    print lol 3 - (  
 
    -2 
```

### FUNNY THINGS

![encoding.png](pictures/encoding_constant_into_variable.png)