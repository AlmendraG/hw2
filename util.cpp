#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	/**take a string of many words and split them into individual keywords
		split at punctuation 
		with at least 2 character words**/
	//will only implement for product name, book author, and clothing brand

  //making all the words lowercase 
	rawWords = convToLower(rawWords);

	set<string> keywords;
    
    //to split string based on whitespace 
	stringstream str(rawWords);
    //for storing each word 
    string word;

	//traverse through all words while loop until we get strings to store in string word
	while( str >> word )
		{
			int x = 0;
			
			//will check for words that have punctuation first 
			for( unsigned int i=0; i < word.size(); i++)
			{
					//spliting words that have punctuation 
					if( ispunct( word[i] ))
					{
						//creating a substring of words divided by punctuation 
						string sub = word.substr( x, i-x);
						x = i+1;

						//only add the substrings that have at least 2 characters 
						if( sub.length() >= 2)
						{
							keywords.insert(sub);
						}
					}
			}

			//will ignore the words that have punctuation, only check if they have at least 2 characters
			string sub = word.substr( x, word.size() );
			if( sub.size() >= 2)
			{
				keywords.insert(sub);
			}
    }

		/* used to check if it works - just ignore
    for( set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it )
        {
            cout << *it << endl;
        }
		*/

	//FOR BOOK ISBN AND MOVIE GENRE: should return verbatim - no punctuation or size analysis
	// (no parsing i guess?) 
	return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

/*
int main()
{
	string str = "Men's Tshirt small I'll J. Crew ";
	parseStringToWords( str );
	return 0;
}