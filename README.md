# Static deque in c

## Premise
> Create a static deck with 10 positions in whom the elements are inserted ordered increasingly. The list will be compacted only if necessary (only the necessary parts). The removal will finding the value sought by the user. The empty positions will be found with -1. The User can only enter worth more than 0.

### Struct
```c
#define max 10

struct genericList
{
    int value[max], empty;
};

typedef struct genericList List;

```
#### Declaration

```c
  // example
  List list;
```
## Core functions

```c 
 void initialize( List * ); 
 void target( List *, int );
 void clean( List *, int );
 ```
### initialize( *list );
```c
  // initialize the structure before any other operation
  initialize( &list  );
``` 

### target( List *list, int value );
```c
  // insert function call example
  int value = 17;
  target( &list, value );
``` 
### clean( List *list, int value );
```c
  // clean function call example
  int value = 7;
  clean( &list, value );
``` 

## License

[MIT License](https://github.com/ahlechandre/deque/blob/master/LICENSE) © 2015 Alexandre Thebaldi 

