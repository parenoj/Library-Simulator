/***************************************************
 * Author: Justin Pareno
 * Date: March 11, 2015
 * Description: This Menu utilizes the Book, Patron
 * 		and Library classes and operates as
 * 		a Library simulator.
 **************************************************/

#include "Library.hpp"
#include "Book.hpp"
#include "Patron.hpp"

#include <iostream>

using namespace std;

int main()
{

	int choice;
	Library myLibrary;
	
	cout << "Welcome to the Library Simulator!" << endl;

	//MENU
	//every option corresponds to a Library class member function
	//some require input before the function can be called
	//It is all very self-documenting
	do
	{
		cout << "	Please make your choice: " << endl;
		cout << "	[1] ADD BOOK" << endl;
		cout << "	[2] ADD PATRON" << endl;
		cout << "	[3] CHECK OUT BOOK" << endl;
		cout << "	[4] RETURN BOOK" << endl;
		cout << "	[5] REQUEST BOOK" << endl;
		cout << "	[6] INCREASE DATE" << endl;
		cout << "	[7] PAY FINE" << endl;
		cout << "	[8] VIEW PATRON INFO" << endl;
		cout << "	[9] VIEW BOOK INFO" << endl;
		cout << "	[0] QUIT" << endl;
		cin >> choice;
		cin.ignore();
		
		if(choice == 1)
		{
			myLibrary.addBook();
		}

		else if(choice == 2)
		{
			myLibrary.addMember();	
		}
	
		else if(choice == 3)
		{
			string tempPatron, tempBook;
			cout << "Please enter the ID for the Patron." << endl;
			getline(cin, tempPatron);
			cout << "Please enter the ID for the Book." << endl;
			getline(cin, tempBook);
			myLibrary.checkOutBook(tempPatron, tempBook);	
		}

		else if(choice == 4)
		{
			string tempBook;
			cout << "Please enter to Book ID that you wish to return: ";
			getline(cin, tempBook);
			myLibrary.returnBook(tempBook);
		}

		else if(choice == 5)
		{
			string tempPatron, tempBook;
			cout << "Please enter the ID for the Patron." << endl;
			getline(cin, tempPatron);
			cout << "Please enter the ID for the Book." << endl;
			getline(cin, tempBook);
			myLibrary.requestBook(tempPatron, tempBook);
		}			

		else if(choice == 6)
		{
			myLibrary.incrementCurrentDate();
		}

		else if(choice == 7)
		{
			string tempPatron;
			double tempPayment;
			cout << "Please enter the ID for the Patron." << endl;
			getline(cin, tempPatron);
			cout << "How much to pay? ";
			cin >> tempPayment;
			cin.ignore();
			myLibrary.payFine(tempPatron, tempPayment);
		}	
	
		else if(choice == 8)
		{
			string tempPatron;
			cout << "Please enter the ID of the Patron you wish to view: ";
			getline(cin, tempPatron);
			myLibrary.viewPatronInfo(tempPatron);
		}

		else if(choice == 9)
		{
			string tempBook;
			cout << "Please enter the ID of the Book you wish to view: ";
			getline(cin, tempBook);
			myLibrary.viewBookInfo(tempBook);
		}
	
	}
	while(choice !=0);

	return 0;
}
