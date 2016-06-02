/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 31, 2016
** Description:  Module 10 assignment
*********************************************************************/
#include "Patron.hpp"
#include <algorithm>

/*********************************************************************
** Description: Assignment 10
**
** Implementation for Patron.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Patron constructors
//

/////////////////////////////////////////////////////////////////
//
// Patron::Patron()
//
// Class constructor with default variables.
//

Patron::Patron(std::string idn, std::string n)
{
  this->idNum = idn;
  this->name = n;
  this->fineAmount = 0;
  this->checkedOutBooks.clear();
}

std::string Patron::getIdNum()
{
  return this->idNum;
}

std::string Patron::getName()
{
  return this->name;
}

std::vector<Book*> Patron::getCheckedOutBooks()
{
  return this->checkedOutBooks;
}

void Patron::addBook(Book* b)
{
  this->checkedOutBooks.push_back (b);
}

void Patron::removeBook(Book* b)
{
  this->checkedOutBooks.erase(std::remove (this->checkedOutBooks.begin(), this->checkedOutBooks.end(), b), this->checkedOutBooks.end());
}

double Patron::getFineAmount()
{
  return this->fineAmount;
}

void Patron::amendFine(double amount)
{
  this->fineAmount += amount;
}


#include <iostream>
void Patron::dump()
{
  std::cout << this->idNum << ":" << this->name << ":" << this->fineAmount << ":" << this->getCheckedOutBooks().size() << std::endl;
  for (int bookCounter = 0; bookCounter < this->getCheckedOutBooks().size(); bookCounter++)
  {
    this->getCheckedOutBooks()[bookCounter]->dump();
  }
}
