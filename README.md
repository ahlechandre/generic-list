# Static deque in c

## Premise
> Create a static deck with 10 positions in whom the elements are inserted ordered increasingly. The list will be compacted only if necessary (only the necessary parts). The removal will finding the value sought by the user. The empty positions will be found with -1. The User can only enter worth more than 0.

### Struct
```c
#define max 10

struct Dequeue
{
    int value[max], empty, indexLargest;
};

typedef struct Dequeue dequeue;
```
#### Declaration

```c
  // example
  dequeue deque;
```
![Deque structure](https://github.com/ahlechandre/deque/blob/master/img/deque.png);

## Core functions

```c 
 initialize( dequeue * ); 
 insert( dequeue *, int );
 clean( dequeue *, int );
 ```
### initialize( *deque );
```c
  // initialize the structure before any other operation
  initialize( &deque  );
``` 
![Deque structure](https://github.com/ahlechandre/deque/blob/master/img/initialize.png);

### insert( dequeue *deque, int value );
```c
  // insert function call example
  int value = 17;
  insert( &deque, value );
``` 
![Deque structure](https://github.com/ahlechandre/deque/blob/master/img/insert.png);
### clean( dequeue *deque, int value );
```c
  // clean function call example
  int value = 7;
  clean( &deque, value );
``` 
![Deque structure](https://github.com/ahlechandre/deque/blob/master/img/clean.png);

## License

[MIT License](https://github.com/ahlechandre/deque/blob/master/LICENSE) © 2015 Alexandre Thebaldi 

