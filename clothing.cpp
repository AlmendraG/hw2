#include <sstream>
#include <string>
#include <set>
#include <fstream>
#include <iomanip>

#include "util.h"
#include "clothing.h"

Clothing::Clothing( const string category, const string name, double price, int qty, 
		const string size, const string brand):Product( category, name, price, qty )
{
	size_ = size;
	brand_ = brand; 
}

set<string> Clothing::keywords() const
{
	set<string> keywords = parseStringToWords(name_);
	set<string> keywords2 = parseStringToWords(brand_);
	
	//combining together keywords for name of article and brand 
	keywords = setUnion<string>( keywords, keywords2);

	return keywords;
}

string Clothing::displayString() const
{
	//creating a string to store all the constant data fields for books 
	string info = name_ + "\n" + "Brand: " + brand_ + " " 
		+ "Size: " + size_ + "\n";

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

void Clothing::dump(ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
		<< "\n" << brand_ << "\n" << size_ << "\n";
}

const string Clothing::getBrand() const
{
	return brand_;
}

const string Clothing::getSize() const
{
	return size_;
}