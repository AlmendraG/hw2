#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <fstream>

#include "product.h"
#include "user.h"

using namespace std;

class Book: public Product
{
	public:
		Book();
		Book( const string category, const string name, double price, int qty, 
		const string ISBN, const string author);

		//returns appropriate keywords to index the product 
		set<string> keywords() const;

		//to create string that contains the product info 
		string displayString() const;

		//to output the database format of the product info 
		void dump( ostream& os ) const;

		//public access to author 
		const string getAuthor() const;
		//public access to ibsn 
		const string getISBN() const;

	private:
		string ISBN_;
		string author_;
};
#endif