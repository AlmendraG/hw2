#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "user.h"

using namespace std;

class Clothing : public Product
{
	public:
		Clothing();
		Clothing( const string category, const string name, double price, int qty, 
		const string size, const string brand);

		//returns appropriate keywords to index the product 
		set<string> keywords() const;

		//to create string that contains the product info 
		string displayString() const;

		//to output the database format of the product info 
		void dump( ostream& os ) const;

		//public acces to size 
		const string getSize() const;
		//public access to brand 
		const string getBrand() const;

	private:
		string size_;
		string brand_;
};
#endif