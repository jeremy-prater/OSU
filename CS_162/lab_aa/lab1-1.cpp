/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Lab Aa
*********************************************************************/

#include "summation.h"
#include "ncurses.h"

/*********************************************************************
** Description: Lab Aa lab1-1.cpp
**
** Implementation for lab1-1.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// int main (void)
//
// Program entry point for lab1-1.cpp
//

int main (void)
{
  int ch;
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  printw("Type any character to see it in bold\n");
  ch = getch();			/* If raw() hadn't been called
  * we have to press enter before it
  * gets to the program 		*/
  if(ch == KEY_F(1))		/* Without keypad enabled this will */
    printw("F1 Key pressed");/*  not get to us either	*/
    /* Without noecho() some ugly escape
    * charachters might have been printed
    * on screen			*/
  else
  {
    printw("The pressed key is ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh();			/* Print it on to the real screen */
  getch();			/* Wait for user input */
  endwin();			/* End curses mode		  */

  
  return 0;
}
