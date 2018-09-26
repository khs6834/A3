#include <fstream>
#include "Trie.h"
#include <iostream>
int main (int argc, char *argv[]) {
  // std::cout <<"hi"<<std::endl;
  // std::cout <<argv[1]<<std::endl;
  // std::cout <<argv[2]<<std::endl;
  // std::cout <<argc<<std::endl;
  if (argc != 3) {
    std::cerr <<"argc was not 3" <<std::endl;
    exit(1);
  }
  std::ifstream words;
  std::ifstream queries;
  std::string x;
  words.open(argv[1]);//add location
  queries.open(argv[2]);
  if (!words) {
    std::cerr << "words could not be read" <<std::endl;
    exit(1);
  }
  if (!queries) {
    std::cerr << "queries could not be read" <<std::endl;
    exit(1);
  }

  Trie myTrie = Trie();
  while(words >> x) {
    std::cout << x << " is trying to be added" <<std::endl;
    myTrie.addAWord(x);
  }
  std::cout <<"done reading words" <<std::endl;
  while(queries >> x) {
    std::cout<<x <<" is trying to be read from q" <<std::endl;
    if(myTrie.isAWord(x)) {
      std::cout<<x << " is found" <<std::endl;
    }
    else {
      std::cout<<x << " is not found, did you mean:" <<std::endl;
      std::cout << "   ";
      std::vector<std::string> preFixedWords = myTrie.allWordsStartingWithPrefix(x);
      for (int i = 0; i <preFixedWords.size();i++) {
        std::cout<< preFixedWords[i] << ' ';
      }
      if(preFixedWords.size() ==0)
        std::cout << "no alternatives found"<<std::endl;
    }
  }
words.close();
queries.close();
}
