# include <iostream>
# include <set>
# include <stdlib.h>
# include <string>

# define SIZE 26

using namespace std;

typedef struct TrieNode
{
  struct TrieNode * child[SIZE];
  set < string > s; // set to store strings
  //int countPrefix; // words with prefix from root to current node
  //int countWord; // complete words for this current node
  bool isLeaf;
}TrieNode;


TrieNode * getNode()
{
  //dont use malloc,use new bcoz malloc provides static memory allocation
  //either provide size of set before otherwise
  //when u insert element in set it will give segmentation fault.
  //bcoz u cannot change size in static space.    
  TrieNode * node= new TrieNode;
  // node->countWord=0;
  // node->countPrefix=0;
  int i=0;
  for(i=0;i<SIZE;i++)
    node->child[i]=NULL;
  node->isLeaf=false;
  return node;
}


void insert(TrieNode * node, const char * word)
{
  TrieNode * x= node;
  while(*word)
  {
    if(x->child[*word-'a']==NULL)
      x->child[*word-'a']=getNode();
    x = x->child[*word-'a'];
    const char * pos=word+1;
    if(*pos)
    {
      string str;
      while(* pos)
      {
        str.push_back(* pos);
        pos++;
      }
      x->s.insert(str);
    }
    word++;
  }
  x->isLeaf=true;
}


void autoComplete(TrieNode * node,const char * word)
{
  const char * str = word;
  TrieNode * back;
  if(node==NULL)
  {	
    cout<<"Trie is empty"<<endl;
    return ;
  }
  while(* word)
  {
    if(node->child[*word-'a']==NULL)
    {
      cout<<"no words with this prefix present"<<endl;
      return;
    }
    back= node;
    node = node->child[*word-'a'];
    word++;
  }
  if(node->isLeaf)
    cout<<str<<endl;
  for(set <string>::iterator i = node->s.begin(); i != node->s.end(); i++) 
  {
   		string element = *i;
   		printf("%s",str);
   		cout<<element<<endl;
  }
}


int main(){
  TrieNode * head= getNode();
  insert(head,"a");
  insert(head,"abs");
  insert(head,"absolute");
  insert(head,"b");
  insert(head,"bar");
  insert(head,"brock");
  insert(head,"d");
  insert(head,"doll");
  insert(head,"dolphin");
  autoComplete(head,"abso");

  return 0;
}
