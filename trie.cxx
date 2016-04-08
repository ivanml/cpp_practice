#include <iostream>
#include "print.h"
#include <sstream>

using namespace std;

class TrieNode {
public:
  TrieNode(char c = '\0', bool b = false) : 
    val(c), 
    isWord(b), 
    children(vector<TrieNode *>(26)) {} 
  ~TrieNode() {}

  char val;
  bool isWord;
  vector<TrieNode *> children;  
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }

  ~Trie() {
  }

  // Inserts a word into the trie.
  void insert(const string &word) {
    if (word.size() <= 0) return;

    TrieNode * node = root;
    for (int i = 0; i < word.size(); ++ i) {
      if (!node->children[word[i] - 'a']) {
        node->children[word[i] - 'a'] = new TrieNode(word[i]);
      }
      node = node->children[word[i] - 'a'];
    }

    node->isWord = true;
  }

  bool search(const string &word, int idx, TrieNode * node, bool fullWord) {
    if (!node) return false;
    TrieNode * child = node->children[word[idx] - 'a'];
    if (!child) return false;

    if (idx == word.size() - 1) { 
      return fullWord ? child->isWord : true;
    }
    
    return search(word, idx + 1, child, fullWord);
  }

  // Returns if the word is in the trie.
  bool search(const string &word) {
    if (word.size() == 0) return true;
    return search(word, 0, root, true);
  }
  
  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(const string &prefix) {
    if (prefix.size() == 0) return true;
    return search(prefix, 0, root, false);
  }

  void printTrie() const {
    cout << "[";
    printTrie(root);
    cout << "]" << endl;
  }

private:
  TrieNode* root;

  void printTrie(TrieNode * node) const {
    if (!node) return;
    
    stringstream ss;
    if (node->isWord) {
      ss << "(" << node->isWord << ")";
    }
    cout << node->val << ss.str() << "->[";
    for (int i = 0; i < node->children.size(); ++ i) {
      TrieNode * child = node->children[i];
      if (child) {
        printTrie(child);
        cout << ", ";
      }
    }
    cout << "]";
  }

};

int main() { 

  Trie t;
  t.insert("abc");
  t.insert("abc");
  t.insert("abcd");
  t.insert("bcd");
  t.insert("cde");
  t.insert("acde");
  t.printTrie();

  cout << t.search("abc") << endl;
  cout << t.search("bcde") << endl;
  cout << t.search("bc") << endl;
  cout << t.search("cdef") << endl;

  cout << t.startsWith("abc") << endl;
  cout << t.startsWith("bcde") << endl;
  cout << t.startsWith("bc") << endl;
  cout << t.startsWith("c") << endl;

  return 0;
}
