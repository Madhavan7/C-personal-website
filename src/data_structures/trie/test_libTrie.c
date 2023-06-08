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
  insert("a", trie, "val");
  int ret = search("a", trie);
  freeTrieNode(trie);
  return ret;
}

int test_add_word(){
  TrieNode *trie = initTrieNode();
  insert("abcd", trie, "val");
  int ret = search("abcd", trie);
  freeTrieNode(trie);
  return ret;
}

int test_add_multiple_words(){
  /*we are going to add 6 words with different prefix*/
  TrieNode *trie = initTrieNode();
  insert("ab", trie, "val");
  insert("bb", trie, "val");
  insert("cb", trie, "val");
  insert("db", trie, "val");
  insert("eb", trie, "val");
  insert("fb", trie, "val");
  /*should be 0*/
  int ret0 = 1 - search("a", trie);
  int ret1 = search("bb", trie);
  int ret2 = search("fb", trie);
  freeTrieNode(trie);
  return ret0 + ret1 + ret2;
  }

int test_add_long_word(){
  TrieNode *trie = initTrieNode();
  insert("abcdefghi", trie, "val");
  insert("abcdefgh", trie, "val");
  insert("abcdefk", trie, "val");
  int ret0 = search("abcdefk", trie);
  int ret1 = 1 - search("abc", trie);
  int ret2 = 1 - search("abcdefghij", trie);
  freeTrieNode(trie);
  return ret0 + ret1 + ret2;
}

int test_multiple_branches(){
  TrieNode *trie = initTrieNode();
  insert("abcde", trie, "val");
  insert("abcdfgh", trie, "val");
  insert("abcdefhj", trie, "val");
  int ret = search("abcdefhj", trie);
  freeTrieNode(trie);
  return ret;
}

int test_get(){
  TrieNode *trie = initTrieNode();
  insert("abcdef", trie, "val");
  insert("abcd", trie, "val2");
  insert("a", trie, "val3");
  int ret0 = strcmp((char *)get("abcdef",trie), "val") == 0 ? 1:0;
  int ret1 = strcmp((char *)get("abcd",trie), "val2") == 0 ? 1:0;
  int ret2 = strcmp((char *)get("a",trie), "val3") == 0 ? 1:0;
  freeTrieNode(trie);
  return ret0 + ret1 + ret2;
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
  total_passed += test_get();

  printf("Score: %d/12 \n", total_passed);
}