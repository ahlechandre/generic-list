/*
* MIT License © 2015 Alexandre Thebaldi
* github.com/ahlechandre
*/

#include <stdio.h>

#define max 10

struct Dequeue
{
    int value[max], empty, indexLargest;
};

typedef struct Dequeue dequeue;

// get functions
int getValue();

// insert functions
void insert( dequeue *, int );

// remove functions
void clean( dequeue *, int );
void initialize( dequeue * );

// compact functions
void eject( int *, int, int, int );
void inject( int *, int, int, int );

// check functions
int isEmptyDeque( dequeue * );
int isFullDeque( dequeue * );
int hasEqual( dequeue *, int );

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
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - search | 5 - free queue \n\n");
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
                insert( &deque, value );
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
            // search
            if ( !isEmptyDeque( &deque ) )
            {

                int item, query;

                do
                {
                    printf("\nvalue (>=0) to find at the deque: ");
                    query = getValue();
                } while ( query < 0 );

                item = findItem( &deque, query );

                if ( item != -1 )
                {
                    printf("\nresult:\n");
                    printf("\n%d - value: %d\n", item, deque.value[item]);
                }
                else
                {
                    // not found
                    showWarn(2);
                }
            }
            else
            {
                // deque is empty
                showWarn(1);
            }
            break;
        }

        case 5:
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
void insert( dequeue *deque, int value )
{
    // if empty deque, insert into 0 index
    if ( isEmptyDeque( deque ) )
    {
        deque->value[0] = value;
        deque->indexLargest = 0;
        deque->empty = deque->empty - 1;
        // added
        showSucess(0);
        debug( deque );
        return;
    }
    // if value is major that major in array, insert at the major + 1
    if ( value > deque->value[deque->indexLargest] )
    {
        deque->value[deque->indexLargest + 1] = value;
        deque->indexLargest = deque->indexLargest + 1;
        deque->empty = deque->empty - 1;
        // added
        showSucess(0);
        debug( deque );
        return;
    }
    // if value is less than value at the 0 index, inject 1 positions into array, insert into 0
    if ( value < deque->value[0] )
    {
        inject( deque->value, 1, 0, (deque->indexLargest + 1) );
        deque->value[0] = value;
        deque->indexLargest = deque->indexLargest + 1;
        deque->empty = deque->empty - 1;
        // added
        showSucess(0);
        debug( deque );
        return;
    }

    // if value is equal some node, do nothing
    if ( hasEqual( deque, value ) == 1 )
    {
        // node already exists
        showWarn(3);
        return;
    }
    else
    {
        int i, insertInto;

        for ( i = 0; i < deque->indexLargest; i++ )
        {
            if ( value > deque->value[i] && value < deque->value[i + 1] )
            {
                insertInto = i + 1;
                break;
            }
        }

        inject( deque->value, 1, insertInto, (deque->indexLargest + 1) );
        deque->value[insertInto] = value;
        deque->indexLargest = deque->indexLargest + 1;
        deque->empty = deque->empty - 1;
        // added
        showSucess(0);
        debug( deque );
        return;

    }
}

// remove functions
void clean( dequeue *deque, int value )
{
    int item = findItem( deque, value );

    if ( item != -1 )
    {
        // in the fallowing cases just overwrite index value by -1
        if ( deque->indexLargest == 0 || item == deque->indexLargest )
        {
            deque->value[item] = -1;

            if ( item == deque->indexLargest )
            {
                deque->indexLargest = deque->indexLargest - 1;
            }

            deque->empty = deque->empty + 1;
            // removed
            showSucess(1);
            debug( deque );
            return;
        }

        eject( deque->value, 1, deque->indexLargest, item );
        deque->indexLargest = deque->indexLargest - 1;
        deque->empty = deque->empty + 1;
        deque->value[(deque->indexLargest + 1)] = -1;
        // removed
        showSucess(1);
        debug( deque );
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
void eject( int *array, int ejects, int begin, int end )
{
    int i, j;

    for ( i = 0; i < ejects; i++ )
    {
        for ( j = end; j < (begin - i); j++ )
        {
            array[j] = array[j+1];
        }
    }
    return;
}

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

    for ( i = 0; i <= deque->indexLargest; i++ )
    {
        if ( deque->value[i] == query )
        {
            flag = 1;
            break;
        }
    }

    return flag;
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

    for ( i = 0; i <= deque->indexLargest; i++ )
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
    printf("\nindexLargest = %d\n", deque->indexLargest);
    printf("\n============ END DEBUG ===========\n");

    return;
}

