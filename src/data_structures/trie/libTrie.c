#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "libTrie.h"

/** Below is methods for manipulating Tries **/

/*initializes trie node*/
TrieNode *initTrieNode(){
  TrieNode * trie = malloc(sizeof(TrieNode));
  trie->characters = malloc(5*sizeof(DictEntry));
  trie->char_capacity = 5;
  trie->char_len = 0;
  trie->endOfWord = 0;
  trie->value = NULL;
  return trie;
}
/*below inserts the word into the trie node, assuming its a null terminated string*/
void insert(char * word, TrieNode *trie, void *value){
  /*dont want to insert empty string*/
  if(*word == '\0'){
    return;
  }
  /*we are going to go with the iterative approach*/
  int i = 0;
  while(*(word + i)!='\0'){
    for(int j = 0; j < trie->char_len + 1;j++){
      if(j == trie->char_len){
        if(trie->char_len == trie->char_capacity){
          trie->characters = realloc(trie->characters, 2*trie->char_capacity*sizeof(DictEntry));
          trie->char_capacity *= 2;
        }
        trie->characters[j].key = *(word + i);
        trie->characters[j].trie = initTrieNode();
        trie->char_len++;
        trie = trie->characters[j].trie;
        break;
      }else if(trie->characters[j].key == *(word + i)){
        trie = trie->characters[j].trie;
        break;
      }
    }
    i++;
  }
  trie->value = value;
  trie->endOfWord = 1;
}

/*Helper function we use to avoid repeating code*/
TrieNode *searchHelper(char *word, TrieNode *trie){
  if(*word == '\0'){
    return NULL;
  }
  int i = 0;
  while(*(word + i)!='\0'){
    for(int j = 0; j < trie->char_len + 1; j ++){
      if(j == trie->char_len){
        return NULL;
      }else if(*(word + i) == trie->characters[j].key){
        trie = trie->characters[j].trie;
        break;
      }
    }
    i++;
  }
  return trie;
}

/*checks if word is in the Trie dictionary*/
int search(char *word, TrieNode *trie){
  trie = searchHelper(word, trie);
  if(trie == NULL){
    return 0;
  }
  return trie->endOfWord;
}

/*gets the value of the key, word*/
void *get(char *word, TrieNode *trie){
  trie = searchHelper(word, trie);
  if(trie == NULL||!trie->endOfWord){
    return NULL;
  }
  return trie->value;
}

/*I am probably not going to use delete much, so I may leave this unimplemented*/
void delete(char *word, TrieNode *trie){

}

void freeTrieNode(TrieNode * trie){
  for(int i = 0; i<trie->char_len;i++){
    freeTrieNode(trie->characters[i].trie);
  }
  free(trie->characters);
  free(trie);
}

