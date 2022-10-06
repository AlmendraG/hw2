#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <utility>

#include "mydatastore.h"
#include "datastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{
	//constructor left empty of course 
}

MyDataStore::~MyDataStore()
{
	//DECONSTRUCTOR
	//start by deleting all the product info 
	for( vector<Product*>::iterator prodit = prodInfo.begin(); prodit != prodInfo.end(); ++prodit)
	{
		delete *prodit;
	}
	//bye bye users 
	for( vector<User*>::iterator userit = userInfo.begin(); userit != userInfo.end(); ++userit)
	{
		delete *userit;
	}
}

void MyDataStore::addProduct( Product* p)
{
	prodInfo.push_back( p );

	//matching keys for this product 
	set<string> keys = p->keywords();

	//does not exist yet - make a new product set 
	bool dne = false;

	//storing keys and products in a map 
	for( set<string>::iterator it1 = keys.begin(); it1 != keys.end(); ++it1 )
	{
		for( map<string, set<Product*> >::iterator it2 = prodKeys.begin(); it2 != prodKeys.end(); ++it2 )
		{
			if( it2->first != *it1 )
			{
				dne = true;
			}
			if( dne )
			{
				prodKeys[ *it1 ].insert(p);
			}
			else //exists so insert it to existing set 
			{
				prodKeys.find( *it1 )->second.insert(p);
			}
		}
	}
}

void MyDataStore::addUser( User* u )
{
	userInfo.push_back( u );
	//no duplicates in users idk edit later lol 
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) 
{
	//I'm going to push some product keys in here 
	vector<Product*> hits;
	//I'm going to store the result from setIntersection or setUnion here 
	set<Product*> myKeys;

	//case: there are no terms
	if( terms.size() == 0 )
	{
		return hits;
	}

	//"OR" will use the setIntersection 
	if (type == 0) 
	{ 
		//iterating through all the term vector 
		for (unsigned int i = 1; i < terms.size(); i++) 
		{
			myKeys = setIntersection( myKeys, prodKeys[ terms[i] ]);
		}	
	}
	//"AND" will use setUnion 
	else if (type == 1) 
	{ 
		//iterating through all the term vector 
		for (unsigned int i = 1; i < terms.size(); i++) 
    {
			myKeys = setUnion(myKeys, prodKeys[ terms[i] ]);
		}
	}
	//Now I'm going to store the previous set in a vector to return it 
	for( set<Product*>::iterator it = myKeys.begin(); it != myKeys.end(); ++it)
	{
		hits.push_back( *it );
	}
	return hits;
}

void MyDataStore::dump( ostream& ofile)
{
	//adding text to the file (basically saves the database)
	ofile << "<products>" << endl;
	for( unsigned int i = 0; i < prodInfo.size(); i++ )
	{
		prodInfo[i]->dump( ofile );
	}
	ofile << "</products>" << endl;
	//end of product section, now lets do the user section 
	ofile << "<users>" << endl;
	for( unsigned int j = 0; j < userInfo.size(); j++ )
	{
		userInfo[j]->dump(ofile);
	}
	ofile << "</users>" << endl;
}

void MyDataStore::addCart( string user, Product* p)
{
	//check if user exists 
	if( !amazonUser( user ) )
	{
		cout << "Invalid username" << endl;
		return;
	}
	//case 1: user has no cart or products in their cart 
	if( shoppingCart.find( user ) == shoppingCart.end() )
	{
		vector<Product*> temp;
		temp.push_back(p);
		//#WeLoveMakePairFunction
		shoppingCart.insert( make_pair( user, temp));
	}
	//case 2: user's cart already exists just add the product to it 
	else
	{
		shoppingCart.find( user )->second.push_back(p);
	}
}

void MyDataStore::buyCart( string user )
{
	//checking if user exists
	if( !amazonUser( user ) )
	{
		cout << "Invalid username" << endl;
		return;
	}

	//Im gonna use this iterator to track the users info 
	vector< User* >::iterator us;

	//im going to go through the users cart and see if they can buy it or not
	//lets make sure they have something in their cart first 
	if( shoppingCart.find( user ) != shoppingCart.end() )
	{
		vector< Product* >* yourCart = &shoppingCart.find( user )->second;

		for( unsigned int i = 0; i < yourCart->size(); i++ )
		{
			//first case: checking if user has sufficient funds and product is in stock 
			if( yourCart->at(i)->getQty() > 0 && ((*us)->getBalance() - yourCart->at(i)->getPrice()) >= 0 )
			{
				//deducting amount from user 
				(*us)->deductAmount( yourCart->at(i)->getPrice() );
				//subtracting the stock quantity  
				yourCart->at(i)->subtractQty(1);
				//removing from the users cart 
				yourCart->erase( yourCart->begin()+ i);
				i--; //reseting because I took it out of their cart 
			}
			//just continue to the next product if the user does not have enough funds 
			//or if the product is out of stock 
		}
	}
	else
	{
		return;
	}
}

void MyDataStore::viewCart( string user )
{
	//checking if user exists 
	if( !amazonUser( user ) )
	{
		cout << "Invalid username" << endl;
		return;
	}

	if( shoppingCart.find( user ) != shoppingCart.end() )
	{
		//setting up a vector for the specific user's cart 
		vector<Product*> yourCart = shoppingCart.find( user )->second;

		//snooping through the cart 
		for( unsigned int i = 0; i < yourCart.size(); i++)
		{
			cout << "Item " << i+1 << endl; 
			//some way of showing the order they added the products in 
			cout << yourCart[i]->displayString() << endl;
		} 
	}
	else
	{
		//empty cart 
		return;
	}
}

bool MyDataStore::amazonUser( string user )
{
	//this is to check if the user exists in order to print out "invalid username"
	//and for other implementations 
	for( vector< User* >::iterator it3 = userInfo.begin(); it3 != userInfo.end(); ++it3 )
	{
		if( (*it3)->getName() == user )
		{
			return true;
		}
	}
	return false; 
}













