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

void Trie::deleteHelper (Trie* current) {
  for(int i =0; i<26; i++) {
    //if(current == nullptr)
    //std::cout<<"IT WAS NULL"<<std::endl;
    //else {
      //std::cout<<"IT WAS NOT NULL and the index was"<<i <<std::endl;
    //}
    if(current->node[i] != nullptr) {
      //std::cout<<"recursion with index"<<i<<std::endl;
      deleteHelper(node[i]);
    }
  }
  delete current;
}
//Delete the root node from the heap.
//delete will delete all the internal branches as well.
Trie::~Trie() {
  deleteHelper(this);
}


//copy constructor. copies the root node of other trie.
Trie::Trie(const Trie& other) {
  std::copy(std::begin(other.node),std::end(other.node),std::begin(this->node));
  this->isValidEnd = other.isValidEnd;
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
  // std::cout << index<<std::endl;
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
  //std::cout<<"got here with prefix " <<prefix <<std::endl;

  std::vector<std::string> result;
  if(prefix.length() == 0) {
    allWordsWithTheprefix(this,result,prefix);
    return result;
  }
  std::cout<<"isValidPrefix with "<<prefix << " was " <<isValidPrefix(prefix, this) <<std::endl;
  if(!isValidPrefix(prefix, this))
    return result;
  allWordsWithTheprefix(getTheNodeOfAfterPrefix(prefix,this),result,prefix);
  return result;
}

bool Trie::isValidPrefix (std::string prefix, Trie* currentTrie) {
  //std::cout<<"Got here isValidPrefix with prefix " <<prefix <<std::endl;

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


Trie* Trie::getTheNodeOfAfterPrefix (std::string prefix, Trie* currentTrie) {
  if(prefix.length() == 1)
    return currentTrie->node[getIndexOfChar(prefix.at(0))];
  return getTheNodeOfAfterPrefix(prefix.substr(1,prefix.length()-1),currentTrie->node[getIndexOfChar((char)prefix[0])]);
}
//2nd helper parameters: current prefix, current node, and the vector to return and has previous words
//check the 27th item in the array && each entry
//if 27th is true, add it to the  v;
//else if an entry is true, recursion.
// base case:: no more children


void Trie::allWordsWithTheprefix (Trie* currentTrie, std::vector<std::string>& result,std::string prefix) {
  for (int i =0;i<26;i++) {
    if(currentTrie->node[i]!=nullptr) {
      if(currentTrie->node[i]->isValidEnd){
        result.push_back(prefix+getCharOfIndex(i));
        // std::cout<<prefix+getCharOfIndex(i)<< " was the word added to the vector "<<std::endl;;
      }
      allWordsWithTheprefix(currentTrie->node[i], result, prefix+getCharOfIndex(i));
    }
  }
}



int Trie::getIndexOfChar (char character) {
  return (int)character-97;
}

char Trie::getCharOfIndex (int index) {
  return (char)index+97;
}
