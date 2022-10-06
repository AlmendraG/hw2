#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <deque>

#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"

using namespace std;

class MyDataStore : public DataStore 
{
    public:
				//constructor and deconstructor 
        MyDataStore();
        ~MyDataStore();

        void addProduct( Product* p);
        void addUser( User* u);

        vector<Product*> search( vector<string>& terms, int type);
        void dump( ostream& ofile );

        //cart commands 
        void addCart( string user, Product* p);
        void buyCart( string name);
        void viewCart( string user);
        
				//this is to check if the user is in my user vector 
				bool amazonUser( string user );


    private:
				//will use these vectors for the deconstructor process 
        vector<Product*> prodInfo;
				vector<User*> userInfo;
	
				//my maps
        map< string, set<Product*> > prodKeys;
				map< string, vector<Product*> > shoppingCart;
};
#endif

