#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include <iomanip>

#include "util.h"
#include "movie.h"

Movie::Movie( const string category, const string name, double price, int qty, 
		const string genre, const string rating):Product( category, name, price, qty )
{
	genre_ = genre;
	rating_ = rating; 
}

set<string> Movie::keywords() const
{
	set<string> keywords = parseStringToWords(name_);
	set<string> keywords2 = parseStringToWords(genre_);
	
	//combining together keywords for name of movie and genre 
	keywords = setUnion<string>( keywords, keywords2);

	return keywords;
}

string Movie::displayString() const
{
	//creating a string to store all the constant data fields for books 
	string info = name_ + "\n" + "Genre: " + genre_ + " " 
		+ "Rating: " + rating_ + "\n";

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

void Movie::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << genre_ << "\n" << rating_ << "\n";
}

const string Movie::getGenre() const
{
	return genre_;
}

const string Movie::getRating() const
{
	return rating_;
}