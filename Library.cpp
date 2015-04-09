/*************************************************************
 * Author: Justin Pareno
 * Date: March 11, 2015
 * Description: This is the Library class implementation file.
 *************************************************************/

#include "Library.hpp"
#include "Patron.hpp"
#include "Book.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

Library::Library()		//Default Constructor
{
	currentDate = 0;
	holdings.reserve(100);	//Increased capacity to 100
	members.reserve(100);	//Increased capacity to 100
}

/**************************************************
 * Description: The addBook function adds a book object
 * 		to the Library's holdings vector. It
 * 		checks that the ID is unique.
 * Parameters: none.
 **************************************************/

void Library::addBook()
{
	string tempIdCode, tempTitle, tempAuthor;		//Temporary variables for object creation.
	cout << "You've chosen to add a book to the Library's holdings." << endl;
	cout << "Please enter a unique ID Code for this book: ";
	getline(cin, tempIdCode);
	
	//Check that ID is Unique
	if(uniqueBook(tempIdCode))
	{
		cout << "Please enter the book's title: ";
		getline(cin, tempTitle);
		cout << "Please enter the book's author: ";
		getline(cin, tempAuthor);
		Book tempBook(tempIdCode, tempTitle, tempAuthor);	//create object with user-inputted information
		holdings.push_back(tempBook);				//add object to the holdings vector
	}
	else
	{
		cout << "Book ID already in use." << endl;
	}
}

/*************************************************
 * Description: The addMember function adds a Patron
 * 		object to the Library's members vector.
 * 		It checks that the ID is unique.
 * Parameters: none.
 **************************************************/

void Library::addMember()
{
	string tempIdCode, tempName;				//Temporary variables for object creation.
	cout << "You've chosen to add a Patron to the Library's system." << endl;
	cout << "Please enter a unique ID Code for the Patron: ";
	getline(cin, tempIdCode);

	//Check that ID is Unique
	if(uniquePatron(tempIdCode))	
	{
		cout << "Please enter the Patron's name: ";
		getline(cin, tempName);
		Patron tempPatron(tempIdCode, tempName);		//create object with user-inputted information
		members.push_back(tempPatron);				//add object to the members vector
	}
	else
	{
		cout << "Patron ID already in use." << endl;
	}
}

/***************************************************
 * Description: the checkOutBook function allows the
 * 		user to check out a specified book to
 * 		a specified patron. It also takes into
 * 		account if the book is on request or 
 * 		already checked out.
 * Parameters: patron ID of the patron wanting to check
 * 		out a book and the book ID of the book
 * 		being checked out.
 *****************************************************/	

void Library::checkOutBook(string patronId, string bookId)
{
	//Check for Valid Patron ID and Book ID
	if(!validPatron(patronId) || !validBook(bookId))
	{
		cout << "Invalid ID." << endl;
	}
	
	for(int index = 0; index < holdings.size(); index++)	//Iterate through holdings
	{
		if(holdings[index].getIdCode() == bookId)	//to find a match with the book ID
		{
			if(holdings[index].getLocation() == CHECKED_OUT)	//If book is already checked out
			{
				cout << "Book Already Checked Out." << endl;
			}
			else if(holdings[index].getLocation() == ON_HOLD_SHELF && holdings[index].getRequestedBy()->getIdNum() == patronId) //If book is on hold for patron wanting to check it out
			{
				holdings[index].setLocation(CHECKED_OUT);											//update Location
				holdings[index].getRequestedBy()->addBook(&holdings[index]);									//add book to Patron's checked out books vector
				holdings[index].setCheckedOutBy(holdings[index].getRequestedBy());								//update who has book checked out
				holdings[index].setDateCheckedOut(currentDate);											//set checked out date
				cout << holdings[index].getTitle() << " has been checked out to " << holdings[index].getRequestedBy()->getName() << endl;	
				holdings[index].setRequestedBy(NULL);												//reset requestedBy
			}

			else if(holdings[index].getLocation() == ON_HOLD_SHELF && holdings[index].getRequestedBy()->getIdNum() != patronId)	//If book is on hold for another Patron
			{
				cout << "Book is on hold for another Patron." << endl;
			}
			
			else if(holdings[index].getLocation() == ON_SHELF)	//If book is available
			{		
				for(int i = 0; i < members.size(); i++)		//Iterate through members
				{
					if(members[i].getIdNum() == patronId)	//to find a match with the patron ID
					{
						holdings[index].setLocation(CHECKED_OUT);								//update Location
						members[i].addBook(&holdings[index]);									//add book to Patron's checked out books vector
						holdings[index].setCheckedOutBy(&members[i]);								//update who has book checked out
						holdings[index].setDateCheckedOut(currentDate);								//set checked out date
						cout << holdings[index].getTitle() << " has been checked out to " << members[i].getName() << endl;
					}
				}
			}

		}
	}
}

/************************************************
 * Description: The returnBook function allows the
 * 		user to return a book that has been
 * 		checked out. 
 * Parameters: The book ID that is being returned.
 **************************************************/

void Library::returnBook(string bookID)
{
	//Check for Valid Book ID
	if(!validBook(bookID))
	{
		cout << "Invalid Book ID." << endl;
	}
	else
	{
		for(int index = 0; index < holdings.size(); index++)		//Iterate through holdings
		{
			if(holdings[index].getIdCode() == bookID)		//to find a match for the book ID
			{
				if(holdings[index].getLocation() != CHECKED_OUT)	//If book is not checked out
				{
					cout << "Book is not Checked Out." << endl;
				}
				else
				{
					holdings[index].getCheckedOutBy()->removeBook(&holdings[index]);	//remove the book from the Patron's checkedOut vector
					if(holdings[index].getRequestedBy() != NULL)	//If book is requested by another Patron
					{
						holdings[index].setLocation(ON_HOLD_SHELF);	//put it on the hold shelf
					}
					else							//otherwise
					{
						holdings[index].setLocation(ON_SHELF);		//put it back on the shelf
					}
					holdings[index].setCheckedOutBy(NULL);		//reset checkedOutBy
					cout << holdings[index].getTitle() << " has been returned." << endl;
				}
			}
		}
	}
}		

/**********************************************************
 * Description: The requestBook function allows for
 * 		a book to be requested. If the book is
 * 		already checked out, it will be put on
 * 		hold when it is returned, otherwise it
 * 		is put on hold immediately.
 * Parameters: the Patron ID that is requesting the book
 * 		and the book ID of the book being requested.
 **********************************************************/

void Library::requestBook(string patronID, string bookID)
{
	//Check for Valid Patron ID and Book ID
	if(!validPatron(patronID) || !validBook(bookID))
	{
		cout << "Invalid ID." << endl;
	}
	else
	{
		for(int index = 0; index < holdings.size(); index++)	//Iterate through holdings
		{
			if(holdings[index].getIdCode() == bookID)	//to find the book matching the Book ID
			{
				if(holdings[index].getRequestedBy() != NULL)	//If book is already requested by someone else
				{
					cout << "Book is already requested by another Patron" << endl;
				}
				else if(holdings[index].getCheckedOutBy() != NULL && holdings[index].getCheckedOutBy()->getIdNum() == patronID)	//If book is checked out by person trying to request
				{
					cout << "Book is Checked Out to Patron requesting." << endl;
				}	
				else	//otherwise
				{
					for(int i = 0; i < members.size(); i++)		//Iterate through members
					{
						if(members[i].getIdNum() == patronID)	//to find the matching Patron ID
						{
							holdings[index].setRequestedBy(&members[i]);	//set requestedBy
							if(holdings[index].getLocation() == ON_SHELF)	//If book is on shelf
							{
								holdings[index].setLocation(ON_HOLD_SHELF);	//place on hold shelf
							}
							cout << "Book is requested." << endl;
						}
					}
				}
			}
		}
	}
}
	
/**********************************************
 * Description: The incrementCurrentDate function
 * 		advances the current date by 1 and
 *		checks for overdue books. If any books
 *		are overdue, the amendFine function is
 *		called.
 * Parameters: none.
 *************************************************/

void Library::incrementCurrentDate()
{
	currentDate = currentDate + 1;
	cout << "Date advanced. " << endl;
	for(int index = 0; index < members.size(); index++)	//Iterate through members
	{
		for(int i = 0; i < members[index].getCheckedOutBooks().size(); i++)	//Iterate through every member's checked out books
		{
			if((currentDate - members[index].getCheckedOutBooks()[i]->getDateCheckedOut()) > Book::CHECK_OUT_LENGTH)	//looking for any that are overdue
			{			
				members[index].amendFine(0.1);		//if found, add 10 cents to their fine
			}
		}
	}
}

/******************************************************
 * Description: The payFine function allows for
 * 		a Patron's fine to be paid down by
 * 		a specific amount.
 * Parameters: the ID of the Patron paying their fines
 * 		and the payment amount.
 * ****************************************************/

void Library::payFine(string patronID, double payment)
{
	payment = 0 - payment;		//Make payment a negative so it can be subtracted from the fine
	if(!validPatron(patronID))
	{
		cout << "Invalid Patron ID." << endl;
	}
	else
	{
		for(int index = 0; index < members.size(); index++)	//Iterate through members
		{
			if(members[index].getIdNum() == patronID)	//to find the matching Patron ID
			{
				members[index].amendFine(payment);	//apply payment toward fine
			}
		}
	}
}

/***************************************************
 * Description: The viewPatronInfo function displays
 * 		Patron information.
 * Parameters: the Patron ID for the patron info that 
 * 		is to be displayed.
 ****************************************************/

void Library::viewPatronInfo(string patronID)
{
	if(!validPatron(patronID))
	{
		cout << "Invalid Patron ID." << endl;
	}
	else
	{
		for(int index = 0; index < members.size(); index++)	//Iterate through members
		{
			if(members[index].getIdNum() == patronID)	//to find a matching ID
			{
				cout << "ID: " << members[index].getIdNum() << endl;
				cout << "Name: " << members[index].getName() << endl;
				cout << "Checked Out Books: ";
				for(int i = 0; i < members[index].getCheckedOutBooks().size(); i++)	//Iterate through checkedOutBooks
				{
					cout << members[index].getCheckedOutBooks()[i]->getTitle() << ".  ";
				}
				cout << endl;
				cout << fixed << showpoint << setprecision(2);
				cout << "Fines: $" << members[index].getFineAmount() << endl;
			}
		}
	}
}

/***************************************************************
 * Description: The viewBookInfo function displays information
 * 		about a book.
 * Parameters: the book ID for the book info that is to be
 * 		displayed.
 **************************************************************/

void Library::viewBookInfo(string bookID)
{
	if(!validBook(bookID))
	{
		cout << "Invalid Book ID." << endl;
	}
	else
	{
		for(int index = 0; index < holdings.size(); index ++)	//Iterate through holdings
		{
			if(holdings[index].getIdCode() == bookID)	//to find a matching book ID
			{
				cout << "ID: " << holdings[index].getIdCode() << endl;
				cout << "Title: " << holdings[index].getTitle() << endl;
				cout << "Author: " << holdings[index].getAuthor() << endl;
				if (holdings[index].getLocation() == ON_SHELF)
				{
					cout << "Location: On Shelf" << endl;
				}
				else if(holdings[index].getLocation() == ON_HOLD_SHELF)
				{
					cout << "Location: On Hold Shelf" << endl;
				}
				else
				{
					cout << "Location: Checked Out" << endl;
				}
				if(holdings[index].getRequestedBy() != NULL)
				{
					cout << "Requested By: " << holdings[index].getRequestedBy()->getName() << endl;
				}
				if(holdings[index].getCheckedOutBy() != NULL)
				{
					cout << "Checked Out By: " << holdings[index].getCheckedOutBy()->getName() << endl;
				}
				if(holdings[index].getLocation() == CHECKED_OUT)
				{
					if((holdings[index].getDateCheckedOut() + Book::CHECK_OUT_LENGTH) - currentDate >= 0)
					{
						cout << "Due in: " << (holdings[index].getDateCheckedOut() + Book::CHECK_OUT_LENGTH) - currentDate << " days" << endl;	//Display how long until book is due
					}
					else if((holdings[index].getDateCheckedOut() + Book::CHECK_OUT_LENGTH) - currentDate < 0)	//unless its overdue
					{
						cout << "OVERDUE" << endl;
					}
				}
			}
		}
	}
}

/********************************************************
 * Description: The validPatron function checks to
 * 		see if the Patron exists in the Library.
 * 		If yes, it returns true, otherwise false.
 * Parameters: the Patron ID to be checked.
 * ******************************************************/

bool Library::validPatron(string patronId)
{
	for(int index = 0; index < members.size(); index++)	//Iterate through members
	{
		if(members[index].getIdNum() == patronId)	//to find a match
		{
			return true;
		}
	}	
	return false;
}

/********************************************************
 * Description: The validBook function checks to
 * 		see if the book exists in the Library.
 * 		If yes, it returns true, otherwise false.
 * Parameters: the Book ID to be checked.
 * ******************************************************/

bool Library::validBook(string bookId)
{
	for(int index = 0; index < holdings.size(); index++)	//Iterate through holdings
	{
		if(holdings[index].getIdCode() == bookId)	//to find a match
		{
			return true;
		}
	}	
	return false;
}

/*******************************************************
 * Description: The uniquePatron function verifies that
 * 		the given Patron ID is unique and not
 * 		already present in the Library.
 * Parameters: the Patron ID to be checked.
 ******************************************************/

bool Library::uniquePatron(string patronID)
{
	for(int index = 0; index < members.size(); index++)	//Iterate through members
	{
		if(members[index].getIdNum() == patronID)	//If a match is found
		{
			return false;				//return false because ID is already in use
		}
		
	}
	return true;
}

/*******************************************************
 * Description: The uniqueBook function verifies that
 * 		the given Book ID is unique and not
 * 		already present in the Library.
 * Parameters: the Book ID to be checked.
 ******************************************************/

bool Library::uniqueBook(string bookID)
{
	for(int index = 0; index < holdings.size(); index++)	//Iterate through holdings
	{
		if(holdings[index].getIdCode() == bookID)	//If a match is found
		{
			return false;				//return false because ID is already in use
		}
		
	}
	return true;
}
