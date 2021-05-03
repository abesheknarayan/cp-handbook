struct Trie
{
  struct Node
  {
    vector<Node*> children;
    bool isleaf;
    ll val;
  };
  ll noc; // no of children
  Node *root;
  char neutral;

  Trie(ll _noc,char _neutral)
  {
    noc = _noc;
    root = getNode();
    neutral = _neutral;
  }

  struct Node *getNode(void)
  {
    struct Node *newNode = new Node;
    newNode->isleaf = false;
    newNode->val = 0;
    newNode->children = vector<Node*>(noc,NULL);
    return newNode;
  }

  void insert(string key)
  {
    struct Node* itNode = root;
    for(auto c:key)
    {
      ll indx = c-neutral;
      if(!itNode->children[indx])
      {
        itNode->children[indx]=getNode();
      }
      itNode->val++;
      itNode = itNode->children[indx];
    }
    itNode->val++;
    itNode->isleaf = true;
  }
  // returns no of words which has key as prefix
  ll search(string key)
  {
    struct Node *itNode = root;
    for(auto c:key)
    {
      ll indx = c-neutral;
      if(!itNode->children[indx])return 0ll;
      itNode = itNode->children[indx];
    }
    if(itNode!=NULL)
    {
      return itNode->val;
    }
    else{
      return 0ll;
    }
  }
};