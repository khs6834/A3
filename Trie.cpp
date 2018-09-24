#include "Trie.h"
//The default constructor. Initialize the root node with a new array of pointers in the heap.
//The size is 27 which is number of alphabets + 1 for the flag to determine whether this node is the end of a valid word.
Trie::Trie() {
  this->rootNode = new char* [27];
}

//Delete the root node from the heap.
//delete will delete all the internal branches as well.
Trie::~Trie() {
  delete []this->rootNode;
}

//copy constructor. copies the root node of other trie.
Trie::Trie(const Trie& other) {
  this->rootNode = other.rootNode;
}

//assign this to other
Trie& Trie::operator=(const char other) {
  swap(this->rootNode, other.rootNode);
  return *this;
}

// Adds a word to this trie.
void Trie::addAWord (std::string wordToAdd) {
  addWord(wordToAdd,this->rootNode);
}

// helper function to add a character to the Trie
void Trie::addWord (std::string subString, char*  currentNode) {
  //base case.
  if (subString.length() ==1) {
    if(currentNode[index] != nullptr) {
      return;
    }
    else {
      currentNode[index] = new char* [27];
      // add a check if its a valid word. If it is, then add the flag.
      return;
    }
  }


  int index = getIndexOfChar(subString.at(0));
  if(currentNode[index] != nullptr) {
    addWord(subString.substr(1,subString.length()), currentNode[index]);
  }
  else {
    currentNode[index] = new char [27];
    addWord(subString.substr(1,subString.length()), currentNode[index]);
  }
}


// returns true if there is target string in this trie
bool Trie::isAWord (std::string target) {
  return isAWord(target,this->rootNode);
}

// helper function that returns false if the first char of the string is not in the trie.
bool Trie::isAWord(std::string subTarget, char[] currentNode) {
  if (subTarget.at(0) == nullptr) {
    return false;
  }
  else if(subTarget.length() == 1 && subTarget.at(0) != nullptr) {
    return true;
  }
  else {
    return isAWord(subtarget.substr(1,subTarget.length()))
  }

}

//returns all of the words that starts with the prefix in this trie.
vector<std::string> Trie::allWordsStartingWithPrefix (std::string prefix) {
  if(!isValidPrefix) {
    return false;
  }

}

bool isValidPrefix (std::string prefix, char[] currentNode) {
  int index = getIndexOfChar(prefix.at(0));
  if (currentNode[index] == nullptr) {
    return false;
  }
  else if (prefix.length() == 1 && prefix.at(0) != nullptr) {
    return true;
  }
  else {
    return isValidPrefix(prefix.substr(0,prefix.length()));
  }
}

//2nd helper parameters: current prefix, current node, and the vector to return and has previous words
//check the 27th item in the array && each entry
//if 27th is true, add it to the  v;
//else if an entry is true, recursion.
// base case:: no more children

int getIndexOfChar (char character) {
  return (int)subString.at(0)-97;
}
