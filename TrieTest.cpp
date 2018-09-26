#include <fstream>
#include "Trie.h"
#include <iostream>
int main (int argc, char *argv[]) {
  if (argc != 2) {
    cerr <<"";
    exit(1);
  }
  ifstream words;
  ifstream queries;
  words.open(/home/hansol/A3/argv[0]);//add location
  queries.open(/home/hansol/A3/argv[1]);
  if (!words) {
    cerr << "";
    exit(1);
  }
  if (!queries) {
    cerr << "";
    exit(1);
  }

  Trie myTrie = Trie();
  while(words >> x) {
    myTrie.addWord(x);
  }

  while(words >> x) {
    if(myTrie.isAWord(x)) {
      cout << "word is found";
    }
  }
words.Close();
queries.Close();
}
