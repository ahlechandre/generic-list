/*
* MIT License © 2015 Alexandre Thebaldi
* github.com/ahlechandre/deque/review
*/

#include <stdio.h>

#define max 10

struct Dequeue
{
    int value[max], empty;
};

typedef struct Dequeue dequeue;

// get functions
int getValue();

// insert functions
void target( dequeue *, int );
void insert( dequeue *, int, int );

// remove functions
void clean( dequeue *, int );
void initialize( dequeue * );

// compact functions
void inject( int *, int, int, int );
void compact( dequeue * );

// check functions
int isEmptyDeque( dequeue * );
int isFullDeque( dequeue * );
int hasEqual( dequeue *, int );
int nextInvalidNode( int *, int );

// search functions
void showItens( int *, int );
int findItem( dequeue *, int );

// message functions
void showWarn( int );
void showErr( int );
void showSucess( int );

// debug functions
void debug( dequeue * );

int main()
{
    int resp;

    dequeue deque;
    initialize( &deque );

    do
    {
        // menu of options
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - free deque\n\n");
        scanf("%d",&resp);

        switch ( resp )
        {
        case 1:
        {
            // insert
            if ( !isFullDeque( &deque ) )
            {
                int value;
                do
                {
                    printf("\nselect value (value >= 0) to insert: ");
                    value = getValue();
                } while ( value < 0 );
                target( &deque, value );
            }
            else
            {
                // deque is full
                showWarn(0);
            }
            break;
        }
        case 2:
        {
            // show
            if ( !isEmptyDeque( &deque ) )
            {
                showItens( &deque.value, 0 );
            }
            else
            {
                // deque is empty
                showWarn(1);
            }
            break;
        }
        case 3:
        {
            // remove
            if ( !isEmptyDeque( &deque ) )
            {
                int value;
                do
                {
                    printf("\nselect value (value >= 0) to remove: ");
                    value = getValue();
                } while ( value < 0 );

                clean( &deque, value );
            }
            else
            {
                // stack is empty
                showWarn(1);
            }
            break;
        }
        case 4:
        {
            // free all nodes
            if ( !isEmptyDeque( &deque ) )
            {
                initialize( &deque );
                // free now
                showSucess(2);
            }
            else
            {
                // stack is empty
                showWarn(1);
            }
            break;
        }
        }
        // "0" to exit
    } while ( resp != 0 );
    return 0;
}

// insert functions
void target( dequeue *deque, int value )
{
    if ( isEmptyDeque( deque ) )
    {
        insert( deque, 0, value );
        return;
    }

    if ( hasEqual( deque, value ) )
    {
        // node already exists
        showWarn(3);
        return;
    }

    int i, last;

    for ( i = 0; i < max; i++ )
    {
        // recording last valid value
        if ( deque->value[i] != -1 )
        {
            last = i;
        }

        // searching first heigher value
        if ( value < deque->value[i] )
        {
            // case previous value is -1 just overwrite
            if ( deque->value[i - 1] == -1 )
            {
                insert( deque, (i - 1), value );
                return;
            }

            int index, query;

            // recording value to search after
            query = deque->value[i];

            compact( deque );

            // looking for value in the new position
            index = findItem( deque, query );

            inject( deque->value, 1, index, nextInvalidNode( deque->value, index ) );

            insert( deque, index, value );

            return;
        }
    }
    // if the last valid value is in the last position of the deque
    if ( last == (max - 1) )
    {
        // case value is less than the last
        if ( value < deque->value[last] )
        {
            int index;

            index = max - (deque->empty + 1);

            compact( deque );

            inject( deque->value, 1, index, nextInvalidNode( deque->value, index ));

            insert( deque, index, value );

            return;
        }

        // case value is greater than the last
        if ( value > deque->value[last] )
        {
            int index;

            index = max - deque->empty;

            compact( deque );

            insert( deque, index, value );

            return;
        }
    }
    // if the last valid value isn't in the last position of the deque
    else
    {
        // verify if value is greater than the last valid value
        int index;

        index = last + 1;

        insert( deque, index, value );

        return;
    }
}

void insert( dequeue *deque, int index, int value )
{
    deque->value[index] = value;
    deque->empty = deque->empty - 1;
    return;
}

// remove functions
void clean( dequeue *deque, int value )
{
    int item = findItem( deque, value );

    if ( item != -1 )
    {
        deque->value[item] = -1;
        deque->empty = deque->empty + 1;
        // removed
        showSucess(1);
//        debug( deque );
        return;
    }
    else
    {
        // not found
        showWarn(2);
        return;
    }
}

// remove functions
void initialize( dequeue *deque )
{
    int i;
    for ( i = 0; i < max; i++ )
    {
        deque->value[i] = -1;
    }
    // all is empty now
    deque->empty = max;
    return;
}

// compact functions
void inject( int *array, int injects, int begin, int end )
{
    int i, j;

    for ( i = 0; i < injects; i++ )
    {
        for ( j = end; j > begin; j-- )
        {
            array[j] = array[j-1];
        }
    }
    return;
}

void compact ( dequeue *deque )
{
    int i, j = 0;

    for ( i = 0; i < max; i++ )
    {
        if ( deque->value[i] != -1 )
        {
            deque->value[j] = deque->value[i];
            j++;
        }
    }

    for ( i = (max - deque->empty); i < max; i++  )
    {
        deque->value[i] = -1;
    }
}

// check functions
int isEmptyDeque( dequeue *deque )
{
    return ( deque->empty == max );
}

int isFullDeque( dequeue *deque )
{
    return ( deque->empty == 0 );
}

int hasEqual( dequeue *deque, int query )
{
    int i, flag = 0;

    for ( i = 0; i < max; i++ )
    {
        if ( deque->value[i] == query )
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

int nextInvalidNode( int *array, int index )
{
    if ( (index < 0) || (index >= max) )
    {
        showWarn(2);
        return;
    }

    int i = index + 1;

    while ( array[i] != -1)
    {
        i++;
    }

    return i;
}

// search functions
void showItens( int *array, int index )
{
    int i;

    if ( index >= max ) {
        showErr(0);
        return;
    }
    for ( i = index; i < max; i++ )
    {
        if ( array[i] != -1 )
        {
            printf("\n%d - value: %d\n", i, array[i]);
        }
    }
    return;
}

int findItem( dequeue *deque, int query)
{
    int i;

    for ( i = 0; i < max; i++ )
    {
        if ( deque->value[i] == query )
        {
            return i;
        }
    }
    return -1;
}

// get functions
int getValue()
{
    int x;
    scanf("%d",&x);
    return x;
}

// messages functions
void showWarn( int id )
{
    switch ( id )
    {
    case 0:
    {
        printf("\nHey! The deque is full.\n");
        break;
    }
    case 1:
    {
        printf("\nOps, the deque is empty!\n");
        break;
    }
    case 2:
    {
        printf("\nSorry but this node not found :(\n");
        break;
    }
    case 3:
    {
        printf("\nHey this node already exists.\n");
        break;
    }
    }
    return;
}

void showErr( int id )
{
    switch ( id )
    {
    case 0:
    {
        printf("\nOhhh! fatal error.\n");
        system("exit");
        break;
    }
    case 1:
    {
        //            printf("\nGood! Node removed with successfully!\n");
        break;
    }
    case 2:
    {
        //            printf("\nHahaha! The stack it is free now!\n");
        break;
    }
    }
    return;
}


void showSucess( int id )
{
    switch ( id )
    {
    case 0:
    {
        printf("\nWell! Node added with successfully!\n");
        break;
    }
    case 1:
    {
        printf("\nGood! Node removed with successfully!\n");
        break;
    }
    case 2:
    {
        printf("\nHahaha! The deque it is free now!\n");
        break;
    }
    }
    return;
}

// debug functions
void debug( dequeue *deque )
{
    printf("\n============ DEBUG ===========\n");
    printf("\nempty = %d\n", deque->empty);
    printf("\n============ END DEBUG ===========\n");

    return;
}

