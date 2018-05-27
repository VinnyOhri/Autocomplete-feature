# include <iostream>
# define CHAR_SIZE 26
using namespace std;
typedef struct trieNode
{
  struct trieNode * chars[CHAR_SIZE];
  bool isLeaf;
}node;

//////////////////////////////////////////////////////////////////////////////////////

node * CreateNode()
{
  node * x = (node *)malloc(sizeof(node));
  x->isLeaf = false;
  for(int i=0 ; i<CHAR_SIZE ; i++)
    x->chars[i]=NULL;
  return x;
}

//////////////////////////////////////////////////////////////////////////////////////

void insert (node * root,const char * key)
{
  node * curr = root;
  while(* key)
  {
    if(curr->chars[*key - 'a']==NULL)
      curr->chars[*key - 'a'] = CreateNode();
    curr=curr->chars[*key - 'a'];
    key++;
  }
  curr->isLeaf = true;
}

/////////////////////////////////////////////////////////////////////////////////////

bool search( node * root ,const  char * key)
{
  if(root==NULL)
    return false;
  node * curr = root;
  while(*key)
  {
    curr=curr->chars[*key - 'a'];
    if(curr==NULL)
      return false;
    key++; 
  }
  return curr->isLeaf;
}

//////////////////////////////////////////////////////////////////////////////////////

bool haveChildren(node * curr)
{
  for(int i = 0 ; i < CHAR_SIZE ; i++)
    if(curr->chars[i])
      return true;  
  return false;
}

/////////////////////////////////////////////////////////////////////////////////////

void printSuggestions(node * curr, string suggestion)
{
  string str = suggestion;
  if(curr->isLeaf)
    cout<<suggestion<<endl;
  if(!haveChildren(curr))
    return;
   for(int i=0; i<CHAR_SIZE ;i++)
   {
      suggestion= str;
    if(curr->chars[i])
      {
        suggestion.push_back(97 + i);
        printSuggestions(curr->chars[i],suggestion);
      }
   }
}

//////////////////////////////////////////////////////////////////////////////////////

int autoComplete(node * curr, const char * key)
{
  const char * str = key;
  if(curr==NULL)
    return 0;
  while(* key)
  {
    if(curr->chars[*key-'a']==NULL)
      return -1;
    curr=curr->chars[*key-'a'];
    key++;
  }

  if(curr->isLeaf && !haveChildren(curr))
  {
    printf("%s\n",str );
      return -2;
  }
    
    string suggestion;
    while(*str)
    {
       suggestion.push_back(*str);
       str++;
    }
    printSuggestions(curr,suggestion);
    return -3;
  
}
//////////////////////////////////////////////////////////////////////////////////////

int main(){
  node* head = CreateNode();
  insert(head, "a");
  insert(head, "abs");
  insert(head, "absolute");
  insert(head, "b");
  insert(head, "bar");
  insert(head, "brock");
  insert(head, "brown");
  insert(head, "brownie");
  insert(head, "brownhair");
  insert(head, "buffalo");
  insert(head, "chess");
  insert(head, "cat");
  insert(head, "cattle");
  insert(head, "cub");
  insert(head, "cobbler");
  insert(head, "d");
  insert(head, "doll");
  insert(head, "dolphin");
  insert(head, "dog");
  insert(head, "doggler");
  insert(head, "down");
  insert(head, "drawn");
  insert(head, "dine");
  insert(head, "hello");
  insert(head, "andrew");
  insert(head, "helloworld");
  insert(head, "hold");
  insert(head, "heart");
  insert(head, "helloworldrajat");
  insert(head, "zebra");
  insert(head, "zebracrossing");

  int a = autoComplete(head,"zebracrossinge");
  if(a==0)
    printf("trie is empty\n" );
  if(a==-1)
    printf("no string with that prefix\n");
  if(a==-2)
    printf("no other string with that prefix\n");
  return 0;
}
