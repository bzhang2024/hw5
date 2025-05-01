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
void generateWords(string partialWord, string floatingLetters, const set<string>& dictionary, set<string>& validWords, int pos);

//note: returns list of all possible words that could work

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //DONE
    set<string> validWords;
    generateWords(in, floating, dict, validWords, 0);
    return validWords; 

}

// Define any helper functions here

void generateWords(string partialWord, string floatingLetters, const set<string>& dictionary, set<string>& validWords, int position){
  //base case
  //if word is fully filled then stop
  if (position == partialWord.length()){
    if (floatingLetters.empty() && dictionary.find(partialWord) != dictionary.end()){ //word exsts in dict
      validWords.insert(partialWord);
    }
    return;
  }

  if (partialWord[position] != '-'){
    generateWords(partialWord, floatingLetters, dictionary, validWords, position + 1); //RECURSE

  }
  else {
    for (char ch = 'a'; ch <= 'z'; ch++){
      partialWord[position] = ch;

      size_t floatingIndex = floatingLetters.find(ch);
      if (floatingIndex != string::npos){
        string updatedFloating = floatingLetters;
        updatedFloating.erase(floatingIndex, 1);
        generateWords(partialWord, updatedFloating, dictionary, validWords, position+1); //RECURSE

      }
      else {
        int openSpots = 0;
        for (int i = position+1; i < partialWord.size(); i++){
          if (partialWord[i] == '-'){
            openSpots++;
          }
          if (openSpots >= floatingLetters.size()){
            generateWords(partialWord, floatingLetters, dictionary, validWords, position+1); //RECURSE

          }
        }
      }
    }
  }
}
