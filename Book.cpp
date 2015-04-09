/*********************************************************
 * Author: Justin Pareno
 * Date: March 9, 2015
 * Description: This is the Book class implementation file.
 *********************************************************/

#include <iostream>

#include "Book.hpp"

Book::Book(std::string idc, std::string t, std::string a)	//Constructor
{
	idCode = idc;
	title = t;
	author = a;
	checkedOutBy = NULL;
	requestedBy = NULL;
	location = ON_SHELF;
}

std::string Book::getIdCode()
{
	return idCode;
}

std::string Book::getTitle()
{
	return title;
}

std::string Book::getAuthor()
{
	return author;
}

Locale Book::getLocation()
{
	return location;
}

void Book::setLocation(Locale lo)
{
	location = lo;
}

Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

void Book::setCheckedOutBy(Patron *p)
{
	checkedOutBy = p;
}
Patron* Book::getRequestedBy()
{
	return requestedBy;
}

void Book::setRequestedBy(Patron *p)
{
	requestedBy = p;
}

int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}

