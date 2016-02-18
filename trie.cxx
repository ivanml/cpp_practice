#include <iostream>
#include "print.h"
#include <unordered_map>

using namespace std;

class TrieNode {
public:
  // Initialize your data structure here.
  TrieNode() : text(""), isWord(false) {}
  TrieNode(string str) : text(str), isWord(false) {}
  ~TrieNode() {
    for (unordered_map<string, TrieNode *>::iterator it = children.begin(); it != children.end(); ++ it) {
      if (it->second) {
        delete it->second;
        it->second = NULL;
      }
    }
  }

  bool isWord;
  string text;
  unordered_map<string, TrieNode *> children;
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }

  ~Trie() {
    delete root;
    root = NULL;
  }

  // insert a word from node
  void insertFrom(TrieNode * node, const string &word, int i) {
    if (i == word.size())
      return;

    string cur_text = node->text + word[i];
    unordered_map<string, TrieNode *>::iterator it = (node->children).find(cur_text);
    if (it != (node->children).end()) {
      if (i == word.size() - 1)
        it->second->isWord = true;
      insertFrom(it->second, word, i + 1);
      return;
    }

    // if no match till i, we need to insert word[0, i] first then insert recursively from word[0, i]
    (node->children)[cur_text] = new TrieNode(cur_text);
    if (i == word.size() - 1)
      (node->children)[cur_text]->isWord = true;
    insertFrom((node->children)[cur_text], word, i + 1);
  }

  // Inserts a word into the trie.
  void insert(const string &word) {
    insertFrom(root, word, 0);
  }
  
  // search "word" from node
  bool searchFrom(TrieNode * &node, const string &word, int i) {
    if (i == word.size()) return node->isWord;

    unordered_map<string, TrieNode *>::iterator it = (node->children).find(node->text + word[i]);
    if (it != (node->children).end()) {
      return searchFrom(it->second, word, i + 1);
    }

    return false;
  }

  // Returns if the word is in the trie.
  bool search(const string &word) {
    return searchFrom(root, word, 0);
  }

  // search prefix from node
  bool startsWithFrom(TrieNode * node, const string &prefix, int i) {
    if (i == prefix.size()) return true;

    unordered_map<string, TrieNode *>::iterator it = (node->children).find(node->text + prefix[i]);
    if (it == (node->children).end())
      return false;

    return startsWithFrom(it->second, prefix, i + 1);
  }
  
  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(const string &prefix) {
    return startsWithFrom(root, prefix, 0);
  }

  void printTrie() const {
    printTrie(root);
    cout << endl;
  }

private:
  TrieNode* root;

  void printTrie(TrieNode * node) const {
    if (!node) return;
    cout << "\"" << node->text;
    if (node->isWord)
      cout << "(true)";
    cout << "\"" << "->[";
    int cnt = (node->children).size();
    for (unordered_map<string, TrieNode *>::iterator it = (node->children).begin(); 
         it != (node->children).end(); ++ it) 
    {
      printTrie(it->second);
      cnt --;
      if (cnt > 0)
        cout << ", ";
    }
    cout << "]";
  }

};

int main() {

  /*
  Trie t;

  t.insert("a");
  t.insert("b");
  t.insert("c");
  t.insert("ab");
  t.insert("def");
  t.insert("dd");
  t.insert("dd");
  t.insert("deg");
  t.printTrie();
  cout << t.search("deg") << endl;

  cout << "starts with: " << endl;
  cout << t.startsWith("def") << endl;
  cout << t.startsWith("dt") << endl;

  t.insert("dtke");
  t.printTrie();  
  cout << t.startsWith("dt") << endl;
  */
  

  Trie t;
  t.insert("abc");
  t.insert("ab");
  cout << t.search("ab") << endl;
  cout << t.startsWith("ab") << endl;
  t.printTrie();

  return 0;
}
