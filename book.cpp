#include "util.h"
#include "book.h"

#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include <iomanip>

using namespace std;

Book::Book( const string category, const string name, double price, int qty, 
		const string ISBN, const string author): Product( category, name, price, qty )
{
	ISBN_ = ISBN;
	author_ = author; 
}

set<string> Book::keywords() const
{
	set<string> keywords = parseStringToWords(name_);
	set<string> keywords2 = parseStringToWords(author_);
	
	//combining together keywords for name of book and author 
	keywords = setUnion<string>( keywords, keywords2);

	//clearing keywords2 to use it again 
	keywords2.clear();

	//inserting the IBSN into keywords 2
	keywords2.insert(ISBN_);

	//combining the IBSN with the name and author 
	keywords = setUnion<string>( keywords, keywords2 );

	return keywords;
}

string Book::displayString() const
{
	//creating a string to store all the constant data fields for books 
	string info = name_ + "\n" + "Author: " + author_ + " " 
		+ "ISBN: " + ISBN_ + "\n";

	//price and quantity variables 
	//temporary variables to check price and quantity 
	stringstream tempp, tempq;
	//string to store the price and quantity 
	string currp, currq;

	tempp << price_;
	tempp >> currp;

	//adding the price to the info string
	info += currp;
	info += " ";

	tempq << qty_;
	tempq >> currq;

	//adding the quantity to the info string 
	info += currq;
	info += " left";

	return info;
}

void Book::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << ISBN_ << "\n" << author_ << "\n";
}

const string Book::getAuthor() const
{
	return author_;
}

const string Book::getISBN() const
{
	return ISBN_;
}

