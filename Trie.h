/*
A3 Hansol Kim CS3505
Trie is a data structure that has good performance retrieving dictionary words.
*/

#include <string>
#include <vector>
class Trie {
  /*
  this is the root node that points where nodes have internal storage for branches of the Trie
  there will be an extra entry other than 26 alphabets to represent a flag that determines if this node is a valid end of a word.
  */
  Trie *node[26];
  bool isValidEnd;

  //private helper function to add a character to the trie.
  void addWord (char charater);
  //private helper function to find the subtaret in the trie.
  bool isAWord(std::string subTarget , Trie* currentNode);
  //recursive helper function for destructor
  void deleteHelper (Trie* current);
public:
  //default constructor.
  Trie();

  //destructor
  ~Trie();

  //copy constructor
  Trie(const Trie& other);
  //=operator overload
  Trie & operator=(const Trie* other);

  // Adds a word to this trie.
  void addAWord (std::string wordToAdd);

  // returns true if there is target string in this trie
  bool isAWord (std::string target);

  //returns all of the words that starts with the prefix in this trie.
  std::vector<std::string> allWordsStartingWithPrefix (std::string prefix);
};
