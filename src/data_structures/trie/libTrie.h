#include <string.h>

typedef struct TrieNode TrieNode;
typedef struct DictEntry DictEntry;

struct DictEntry{
  char key;
  TrieNode * trie;
};
/*dictionary containing the children of the trie, and what the characters point to*/
struct TrieNode{
  int char_len;
  int char_capacity;
  DictEntry * characters;
  int endOfWord; 
};
