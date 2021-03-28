## MAFFIN

For looking at the structure beneath:
 `@debug`

If you need to print something:
`print( "something" )`

To compile text
`~`

### EXAMPLES


###### №1

```asm
    @debug

    int ok = 3;
    int op = 2;
    print(ok+op);
    
    ~
```

RETURNS

```asm
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

```asm
    lol 0 2 3 + 4 - =  
    print lol 3 - (  
 
    -2 
```