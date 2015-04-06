/*
* MIT License © 2015 Alexandre Thebaldi
* github.com/ahlechandre/list/review
*/

#include <stdio.h>

#define max 10

struct genericList
{
    int value[max], empty;
};

typedef struct genericList List;

// get functions
int getValue();

// insert functions
void target( List *, int );
void insert( List *, int, int );

// remove functions
void clean( List *, int );
void initialize( List * );

// compact functions
void inject( int *, int, int, int );
void compact( List * );

// check functions
int isEmptyDeque( List * );
int isFullDeque( List * );
int hasEqual( List *, int );
int nextEmptyNode( int *, int );

// search functions
void showItens( int *, int );
int findItem( List *, int );

// message functions
void showWarn( int );
void showSucess( int );

// debug functions
void debug( List * );

int main()
{
    int resp;

    List list;
    initialize( &list );

    do
    {
        // menu of options
        printf("\n\n0 - exit | 1 - insert | 2 - show | 3 - remove | 4 - free list\n\n");
        scanf("%d",&resp);

        switch ( resp )
        {
        case 1:
        {
            // insert
            if ( !isFullDeque( &list ) )
            {
                int value;
                do
                {
                    printf("\nselect value (value >= 0) to insert: ");
                    value = getValue();
                } while ( value < 0 );
                target( &list, value );
            }
            else
            {
                // list is full
                showWarn(0);
            }
            break;
        }
        case 2:
        {
            // show
            if ( !isEmptyDeque( &list ) )
            {
                showItens( &list.value, 0 );
            }
            else
            {
                // list is empty
                showWarn(1);
            }
            break;
        }
        case 3:
        {
            // remove
            if ( !isEmptyDeque( &list ) )
            {
                int value;
                do
                {
                    printf("\nselect value (value >= 0) to remove: ");
                    value = getValue();
                } while ( value < 0 );

                clean( &list, value );
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
            if ( !isEmptyDeque( &list ) )
            {
                initialize( &list );
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
void target( List *list, int value )
{
    if ( isEmptyDeque( list ) )
    {
        insert( list, 0, value );
        // added
        showSucess(0);
        return;
    }

    if ( hasEqual( list, value ) )
    {
        // node already exists
        showWarn(3);
        return;
    }

    int i, last;

    for ( i = 0; i < max; i++ )
    {
        // recording last valid value
        if ( list->value[i] != -1 )
        {
            last = i;
        }

        // searching first heigher value
        if ( value < list->value[i] )
        {
            // case previous value is -1 just overwrite
            if ( list->value[i - 1] == -1 )
            {
                insert( list, (i - 1), value );
                // added
                showSucess(0);
                return;
            }

            int index, query;

            // recording value to search after
            query = list->value[i];

            compact( list );

            // looking for value in the new position
            index = findItem( list, query );

            inject( list->value, 1, index, nextEmptyNode( list->value, index ) );

            insert( list, index, value );
            // added
            showSucess(0);
            return;
        }
    }

    int index;

    // if the last valid value is in the last position of the list
    if ( last == (max - 1) )
    {
        compact( list );
        index = max - list->empty;
    }
    else
    {
        index = last + 1;
    }

    insert( list, index, value );
    // added
    showSucess(0);
    return;

}

void insert( List *list, int index, int value )
{
    list->value[index] = value;
    list->empty = list->empty - 1;
    return;
}

// remove functions
void clean( List *list, int value )
{
    int item = findItem( list, value );

    if ( item != -1 )
    {
        list->value[item] = -1;
        list->empty = list->empty + 1;
        // removed
        showSucess(1);
//        debug( list );
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
void initialize( List *list )
{
    int i;
    for ( i = 0; i < max; i++ )
    {
        list->value[i] = -1;
    }
    // all is empty now
    list->empty = max;
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
        begin++;
    }
    return;
}

void compact ( List *list )
{
    int i, j = 0;

    for ( i = 0; i < max; i++ )
    {
        if ( list->value[i] != -1 )
        {
            list->value[j] = list->value[i];
            j++;
        }
    }

    for ( i = (max - list->empty); i < max; i++  )
    {
        list->value[i] = -1;
    }
}

// check functions
int isEmptyDeque( List *list )
{
    return ( list->empty == max );
}

int isFullDeque( List *list )
{
    return ( list->empty == 0 );
}

int hasEqual( List *list, int query )
{
    int i, flag = 0;

    for ( i = 0; i < max; i++ )
    {
        if ( list->value[i] == query )
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

int nextEmptyNode( int *array, int index )
{
    int i = index + 1;

    while ( array[i] != -1 )
    {
        i++;
    }

    return i;
}

// search functions
void showItens( int *array, int index )
{
    int i, j = 0;

    for ( i = index; i < max; i++ )
    {
        if ( array[i] != -1 )
        {
            j++;
            printf("\n%d - value: %d\n", j, array[i]);
        }
    }
    return;
}

int findItem( List *list, int query)
{
    int i;

    for ( i = 0; i < max; i++ )
    {
        if ( list->value[i] == query )
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
        printf("\nHey! The list is full.\n");
        break;
    }
    case 1:
    {
        printf("\nOps, the list is empty!\n");
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
        printf("\nHahaha! The list it is free now!\n");
        break;
    }
    }
    return;
}

// debug functions
void debug( List *list )
{
    printf("\n============ DEBUG ===========\n");
    printf("\nempty = %d\n", list->empty);
    printf("\n============ END DEBUG ===========\n");

    return;
}
