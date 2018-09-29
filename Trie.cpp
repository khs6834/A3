/*
A3 Hansol Kim CS3505
*/
#include "Trie.h"
#include <iostream>
//The default constructor. Initialize the root node with a new array of pointers in the heap.
//The size is 27 which is number of alphabets + 1 for the flag to determine whether this node is the end of a valid word.
Trie::Trie() {
  for(int i =0; i<26; i++) {
    this->node[i] = nullptr;
  }
  this->isValidEnd = false;
}

//Delete the root node from the heap.
//delete will delete all the internal branches as well.
Trie::~Trie() {
  for(int i =0; i<26; i++) {
    if(this->node[i] != nullptr) {
      delete this->node[i];
    }
  }
}


//copy constructor. copies the root node of other trie.
Trie::Trie(const Trie& other) {
  this->isValidEnd = other.isValidEnd;
  for(int i =0;i<26;i++) {
    this->node[i] = nullptr;
  }
  for(int i=0;i<26;i++) {
    if(other.node[i]!=nullptr) {
      this->node[i] = new Trie(*other.node[i]);
    }
  }
}

//assign this to other
Trie& Trie::operator=(Trie other) {
  std::swap(this->node, other.node);
  std::swap(this->isValidEnd, other.isValidEnd);
  return *this;
}



// helper function to add a character to the Trie
void Trie::addWord (std::string subString, Trie*  currentTrie) {
  //base case.
  if (subString.length() ==1) {
    int index = getIndexOfChar(subString.at(0));
    if(currentTrie->node[index] != nullptr) {
      currentTrie->node[index]->isValidEnd = true;
      return;
    }
    else {
      currentTrie->node[index] = new Trie();
      currentTrie->node[index]->isValidEnd = true;
      // add a check if its a valid word. If it is, then add the flag.
      return;
    }
  }


  int index = getIndexOfChar(subString.at(0));
  if(currentTrie->node[index] != nullptr) {
    addWord(subString.substr(1,subString.length()), currentTrie->node[index]);
  }
  else {
    currentTrie->node[index] = new Trie();
    addWord(subString.substr(1,subString.length()), currentTrie->node[index]);
  }
}

// Adds a word to this trie.
void Trie::addAWord (std::string wordToAdd) {
  if(wordToAdd.length() ==0)
    return;
  addWord(wordToAdd,this);
}


// returns true if there is target string in this trie
bool Trie::isAWord (std::string target) {
  if(target.length() == 0)
    return false;
  return isAWord(target,this);
}

// helper function that returns false if the first char of the string is not in the trie.
bool Trie::isAWord(std::string subTarget, Trie* currentTrie) {
  if (currentTrie->node[getIndexOfChar(subTarget.at(0))] == nullptr) {
    return false;
  }
  else if(subTarget.length() == 1 ) {
    return currentTrie->node[getIndexOfChar(subTarget.at(0))]->isValidEnd;
  }
  else {
    return isAWord(subTarget.substr(1,subTarget.length()),currentTrie->node[getIndexOfChar((char)subTarget[0])]);
  }
}

//returns all of the words that starts with the prefix in this trie.
std::vector<std::string> Trie::allWordsStartingWithPrefix (std::string prefix) {

  std::vector<std::string> result;
  if(prefix.length() == 0) {
    allWordsWithTheprefix(this,result,prefix);
    return result;
  }
  if(!isValidPrefix(prefix, this))
    return result;
  allWordsWithTheprefix(getTheNodeOfAfterPrefix(prefix,this),result,prefix);
  return result;
}

/*
returns true if the prefix exists in the Trie.
*/
bool Trie::isValidPrefix (std::string prefix, Trie* currentTrie) {
  int index = getIndexOfChar(prefix.at(0));
  if (currentTrie->node[index] == nullptr) {
    return false;
  }
  else if (prefix.length() == 1 && currentTrie->node[getIndexOfChar(prefix.at(0))] != nullptr) {
    return true;
  }
  else {
    return isValidPrefix(prefix.substr(1,prefix.length()-1),currentTrie->node[index]);
  }
}

/*
returns the node with the last char.
*/
Trie* Trie::getTheNodeOfAfterPrefix (std::string prefix, Trie* currentTrie) {
  if(prefix.length() == 1)
    return currentTrie->node[getIndexOfChar(prefix.at(0))];
  return getTheNodeOfAfterPrefix(prefix.substr(1,prefix.length()-1),currentTrie->node[getIndexOfChar((char)prefix[0])]);
}



/*
This is a recursive function adding all words after the prefix and that are valid.
*/
void Trie::allWordsWithTheprefix (Trie* currentTrie, std::vector<std::string>& result,std::string prefix) {
  for (int i =0;i<26;i++) {
    if(currentTrie->node[i]!=nullptr) {
      if(currentTrie->node[i]->isValidEnd){
        result.push_back(prefix+getCharOfIndex(i));
      }
      allWordsWithTheprefix(currentTrie->node[i], result, prefix+getCharOfIndex(i));
    }
  }
}


//returns the intdex of char
int Trie::getIndexOfChar (char character) {
  return (int)character-97;
}

//returns the char of index
char Trie::getCharOfIndex (int index) {
  return (char)index+97;
}

std::vector<std::string> Trie::wordsWithWildcardPrefix (std::string prefix) {
  return std::vector<std::string>();
}
