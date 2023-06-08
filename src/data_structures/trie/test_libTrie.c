#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "libTrie.h"

/*Tests of Trie*/
void seg_peaceful_exit(int signum){
  printf("Segmentation Fault found\n");
  exit(1);
}

void abrt_peaceful_exit(int signum){
  printf("Aborted, Error!\n");
  exit(1);
}

int test_add_char(){
  TrieNode *trie = initTrieNode();
  insert("a", trie);
  int ret = search("a", trie);
  freeTrieNode(trie);
  return ret;
}

int test_add_word(){
  TrieNode *trie = initTrieNode();
  insert("abcd", trie);
  int ret = search("abcd", trie);
  freeTrieNode(trie);
  return ret;
}

int test_add_multiple_words(){
  /*we are going to add 6 words with different prefix*/
  TrieNode *trie = initTrieNode();
  insert("ab", trie);
  insert("bb", trie);
  insert("cb", trie);
  insert("db", trie);
  insert("eb", trie);
  insert("fb", trie);
  /*should be 0*/
  int ret0 = 1 - search("a", trie);
  int ret1 = search("bb", trie);
  int ret2 = search("fb", trie);
  freeTrieNode(trie);
  return ret0 + ret1 + ret2;
  }

int test_add_long_word(){
  TrieNode *trie = initTrieNode();
  insert("abcdefghi", trie);
  insert("abcdefgh", trie);
  insert("abcdefk", trie);
  int ret0 = search("abcdefk", trie);
  int ret1 = 1 - search("abc", trie);
  int ret2 = 1 - search("abcdefghij", trie);
  freeTrieNode(trie);
  return ret0 + ret1 + ret2;
}

int test_multiple_branches(){
  TrieNode *trie = initTrieNode();
  insert("abcde", trie);
  insert("abcdfgh", trie);
  insert("abcdefhj", trie);
  int ret = search("abcdefhj", trie);
  freeTrieNode(trie);
  return ret;
}

int main(){
  int total_passed = 0;
  signal(SIGSEGV, seg_peaceful_exit);
  signal(SIGABRT, abrt_peaceful_exit);
  
  total_passed += test_add_char();
  total_passed += test_add_word();
  total_passed += test_add_multiple_words();
  total_passed += test_add_long_word();
  total_passed += test_multiple_branches();

  printf("Score: %d/9 \n", total_passed);
}