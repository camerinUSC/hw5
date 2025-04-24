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


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

		std::string current = in; // copying given parameter so we can use it in recursion
		int index = 0;
		std::set<std::string> finalAnswer;

		wordleHelper(current, floating, dict, index, finalAnswer);


		return finalAnswer;
}

// Define any helper functions here

// current == current version of 'in' parameter
// index == place in word
// finalAnswer == final set of words that will be returned in wordle

void wordleHelper(
    std::string& current,
    const std::string& floating,
    const std::set<std::string>& dict,
		int index,
		std::set<std::string>& finalAnswer) 
		
		{
				// have i reached the end?

		if(index == current.size()){

			//have all floating letters been used?

			if(!floating.empty()){
				return;
			}

			// is the word in my given dictionary

			if(dict.find(current) != dict.end()){
				finalAnswer.insert(current);
			}
			return;
		}


			if(current[index] != '-'){		// green letter
				wordleHelper(current, floating, dict, index+1, finalAnswer); // proceed to next index
				return;
			}

			std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

			//yellow letter cases 
			for(int floatingIndex = 0; floatingIndex < floating.size(); floatingIndex++){

				char nextLetter = floating[floatingIndex];
				current[index] = nextLetter;

				std::string recFloating = floating;
				recFloating.erase(floatingIndex, 1);

				wordleHelper(current, recFloating, dict, index+1, finalAnswer); // proceed to next index

			}

			for(int greyIndex = 0; greyIndex < 26; greyIndex++){

				char nextLetter = alphabet[greyIndex];

				if(floating.find(nextLetter) != std::string::npos){
					continue;
				}

				//remaining chars left (must have more than remaining given floats)
				unsigned int dashes = 0;
				for(int x = index; x < current.size(); x++){
					if(current[x] == '-'){
						dashes++;
					}
				}

				if(dashes < floating.size()){
					continue;
				}

				current[index] = nextLetter;

				//std::string recAlphabet = alphabet;
				//recAlphabet.erase(greyIndex, 1)

				wordleHelper(current, floating, dict, index+1, finalAnswer); // proceed to next index

			}


		}