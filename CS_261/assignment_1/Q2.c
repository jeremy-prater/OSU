/* CS261- Assignment 1 - Q.2*/
/* Name:
 * Date:
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = *a * 2;
    
    /*Set b to half its original value*/
    *b = *b / 2;
    
    /*Assign a+b to c*/
    c = *a + *b;
    
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
    int x = 5;
    int y = 6;
    int z = 7;
    
    /*Print the values of x, y and z*/
    printf ("x = %d\n", x);
    printf ("y = %d\n", y);
    printf ("z = %d\n", z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    z = foo (&x, &y, z);

    /*Print the value returned by foo*/
    printf ("foo(..) returned %d\n", z);

    /*Print the values of x, y and z again*/
    printf ("x = %d\n", x);
    printf ("y = %d\n", y);
    printf ("z = %d\n", z);
 
    /*Is the return value different than the value of z?  Why?*/
    printf ("foo(..) == z because I set z to the result of foo(...)\n");

    return 0;
}
