#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordMaker(set<std::string>& words, string word, string floating, int place);
void wordRefiner(std::set<std::string>& refinedWords, string word, int place, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

		set<std::string> words;
		set<std::string> refinedWords;
		string floatingAdd = floating;		

		int fSize = floating.size();
		int emptyCount = 0;
		for(unsigned int i = 0; i < in.size(); i++)
		{

			if(in[i] == '-')
			{
				if(emptyCount >= fSize)
				{
					floatingAdd += '*';
				}
				else
				{
					emptyCount++;
				}
			}
		}

		wordMaker(words, in, floatingAdd, 0);

		for(set<std::string>::iterator it = words.begin(); it != words.end(); it++)
		{
			//cout << "this loop!" << endl;
			wordRefiner(refinedWords, *it, 0, dict);
		}


		return refinedWords;


}

// Define any helper functions here

void wordMaker(std::set<std::string>& words, string word, string floating, int place)
{
	if(word.length() == (unsigned)place)
	{
		words.insert(word);
	}
	else
	{
		//adding every other yellow character
		if(word[place] == '-')
		{
			for(unsigned int i = 0; i < floating.size(); i++)
			{
				string floatingFixed = floating;
				floatingFixed.erase(i, 1);

				word[place] = floating[i];
				wordMaker(words, word, floatingFixed, place + 1);
			}
		}
		else
		{
			wordMaker(words, word, floating, place + 1);
		}

	}

}

//cleans up leftover spaces
void wordRefiner(std::set<std::string>& refinedWords, string word, int place, const std::set<std::string>& dict)
{
	if(word.length() == (unsigned)place)
	{
		if(dict.find(word) != dict.end())
		{
			refinedWords.insert(word);
		}
	}
	else
	{
		
		if(word[place] == '*')
		{
			for(char letter = 'a'; letter <= 'z'; letter++)
			{
				word[place] = letter;
				wordRefiner(refinedWords, word, place + 1, dict);
			}
		}
		else
		{
			wordRefiner(refinedWords, word, place + 1, dict);
		}


	}
}