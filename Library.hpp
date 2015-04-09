/******************************************
 * used and edited by Justin Pareno
 * Date: March 10, 2015
 * Description: Library class definition and
 * 		header file
 ******************************************/

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>

class Patron;  // forward declarations
class Book;

class Library
{
private:
    std::vector<Book> holdings;
    std::vector<Patron> members;
    int currentDate;
public:
    Library();
    void addBook();
    void addMember();
    void checkOutBook(std::string patronID, std::string bookID);
    void returnBook(std::string bookID);
    void requestBook(std::string patronID, std::string bookID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    void viewBookInfo(std::string bookID);
    bool validPatron(std::string patronID);
    bool validBook(std::string bookID);
    bool uniquePatron(std::string patronID);
    bool uniqueBook(std::string bookID);
};

#endif
