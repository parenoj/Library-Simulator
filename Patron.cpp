/**************************************************************
 * Author: Justin Pareno
 * Date: March 10, 2015
 * Description: This is the Patron class implementation file.
 * ***********************************************************/

#include "Patron.hpp"
#include "Book.hpp"

Patron::Patron(std::string idn, std::string n)	//Constructor
{
	idNum = idn;
	name = n;
	fineAmount = 0.0;
}

std::string Patron::getIdNum()
{
	return idNum;
}

std::string Patron::getName()
{
	return name;
}

std::vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

/*******************************************************
 * Description: the addBook function adds
 * 		a Book pointer to the checkedOutBooks
 * 		vector.
 * Parameters: a pointer to a Book object that is being
 * 		added to the vector.
 ******************************************************/

void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

/*******************************************************
 * Description: the removeBook function removes
 * 		a Book pointer from the checkedOutBooks
 * 		vector.
 * Parameters: a pointer to a Book object that is being
 * 		removed from the vector.
 ******************************************************/


void Patron::removeBook(Book* b)
{
	for(int index = 0; index < checkedOutBooks.size(); index++)	//Iterate through checkedOutBooks
	{
		if(checkedOutBooks[index]->getIdCode() == b->getIdCode())	//to find a matching ID code
		{
			checkedOutBooks.erase(checkedOutBooks.begin() + index);	//and remove it from the vector based on the location in the vector given by index
		}
	}
}

double Patron::getFineAmount()
{
	return fineAmount;
}

/***************************************************
 * Description: The amendFine function is used to alter
 * 		the current fines of a Patron.
 * Parameters: the amount that the fine is being amended.
 ****************************************************/

void Patron::amendFine(double amount)
{
	fineAmount = fineAmount + amount;
}

