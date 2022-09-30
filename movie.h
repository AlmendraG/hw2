#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "user.h"

using namespace std;

class Movie : public Product
{
	public:
		Movie();
		Movie( const string category, const string name, double price, int qty, 
		const string genre, const string rating);

		//returns appropriate keywords to index the product 
		set<string> keywords() const;

		//to create string that contains the product info 
		string displayString() const;

		//to output the database format of the product info 
		void dump( ostream& os ) const;

		//public access to genre 
		const string getGenre() const;
		const string getRating() const;

		//public access to rating 

	private:
		string genre_;
		string rating_;
};
#endif