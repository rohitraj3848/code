#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
#include <list>
#include <utility>
using namespace std;

struct Node
{
    Node *next;
    Node *prev;
    int value;
    int key;
    Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val){};
    Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val){};
};

class Cache
{

protected:
    map<int, Node *> mp;            //map the key to the node in the linked list
    int cp;                         //capacity
    Node *tail;                     // double linked list tail pointer
    Node *head;                     // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0;       //get function
};

/*class LRUCache: public Cache
{
    public:
    LRUCache(int c) { cp = c; }
    
    void set(int k,int v)
    {
        Node *N;
        
        if(mp.empty()) //No nodes 
        {
            N = new Node(k,v);
            tail = head = N;
            mp[k] = N;
            
            return;
        }
        
        auto it = mp.find(k);
            
        if(it != mp.end()) //In hash table
        {
            it->second->value = v; // update value
            
            if(head == it->second) //head?
                return;
            
            it->second->prev->next = it->second->next;
            
            if(tail == it->second) //tail?
                tail = tail->prev;
            else                   //in between?
                it->second->next->prev = it->second->prev;
            
            it->second->next = head;
            it->second->prev = NULL;
            head->prev = it->second;
            head = it->second;
        }
        else               // No in hash table
        {
            N = new Node(head->prev,head,k,v); //new node
            head->prev = N; 
            head = N;
            mp[k] = N;
            
            if(mp.size() > cp) //capacity?
            {
                tail = tail->prev;
                mp.erase(tail->next->key);
                delete tail->next; 
                tail->next = NULL;
            }
            
        }

    }
    
    int get(int k)
    {
        auto it = mp.find(k);
        if(it != mp.end())
            return it->second->value;
        
        return -1;
    }
    
};*/
class LRUCache : public Cache
{
public:
    LRUCache(int capacity)
    {
        cp = capacity;
        head = NULL;
        tail = NULL;
    }
    void set(int key, int val)
    {
        if (mp.find(key) != mp.end())
        {
            mp[key]->value = val;
            for (auto i = mp.begin(); i != mp.end(); i++)
                cout << i->second->key << "  " << i->second->value << endl;
            }
        else
        {
            mp[key] = new Node(NULL, head, key, val);
            if (head)
                head->prev = mp[key];
            head = mp[key];
            if (!tail)
                tail = head;
            if (mp.size() > cp)
            {
                mp.erase(tail->key);
                tail = tail->prev;
                delete tail->next;
                tail->next = NULL;
            }
            for (auto i = mp.begin(); i != mp.end(); i++)
                cout << i->second->key << " -> " << i->second->value << endl; 
        }
    }
    int get(int key)
    {  
        if (mp.find(key) != mp.end())
        {
            if (mp[key]==head)
            {
                return mp[key]->value;
            }
            else if (mp[key]==tail && !mp[key]->prev)
            {
                Node *temp = mp[key];
                mp[key]->prev->next = NULL;
                head->prev = temp;
                temp->next = head;
                head = temp;
                return head->value;
            }
            else if (mp[key]->prev && mp[key]->next)
            {
                Node *temp = mp[key];
                mp[key]->prev->next = mp[key]->next;
                mp[key]->next->prev = mp[key]->prev;
                temp->next = head;
                head->prev = temp;
                head = temp;
                return head->value;
            }
        }
        return -1;
    }
};


int main()
{
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i < n; i++)
    {
        string command;
        cin >> command;
        if (command == "get")
        {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set")
        {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}