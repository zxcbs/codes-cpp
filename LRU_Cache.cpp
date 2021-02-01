#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

/* using given struct Node and class Cache
struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
    public:
        LRUCache(int cap){
            cp = cap;
            
            mp.clear();
            tail = NULL;
            head = NULL;
        }
        
        ~LRUCache(){
            Node* pNode = head;
            while(pNode){
                auto tmp = pNode->next;
                delete pNode;
                
                pNode = tmp;
            }
        }
    
        void set(int key, int val){
            auto search = mp.find(key);
            if(search != mp.end()){
                auto pNode = search->second;
                if(pNode) pNode->value = val;
                
                return;
            }
            
            Node* newNode = new Node(NULL, head, key, val);
            if(head) head->prev = newNode;
            head = newNode;
            mp.emplace(key, newNode);
            
            if(mp.size() > cp && tail){
                mp.erase(tail->key);

                Node* tmptail = tail->prev;
                tmptail->next = NULL;
                                
                delete tail;
                tail = tmptail;
            }
            
            if(mp.size() == 1){
                tail = newNode;   
            }
        }
        
        int get(int key){
            auto search = mp.find(key);
            if(search != mp.end()){
                auto pNode = search->second;
                if(pNode) return pNode->value;
                
                auto tmpNode = head->next;
                head->prev = pNode->prev;
                head->next = pNode->next;
                
                pNode->prev = NULL;
                pNode->next = tmpNode;
                head = pNode;
            }
            
            return -1;
        }   
};
*/
// /* using list
#include <list>

class LRUCache {// : public Cache {
    int cp;  //capacity
    // Node* tail; // double linked list tail pointer
    // Node* head; // double linked list head pointer
    
    // map<int,Node*> mp; //map the key to the node in the linked list
    map<int, list<std::pair<int, int>>::iterator> lruMap;
    list<std::pair<int, int>> lruList;
    
    public:
        LRUCache(int cap) : cp(cap){};
        
        void set(int key, int value){
            auto search = lruMap.find(key);
            if(search != lruMap.end()){
                // search->second->first = key;
                search->second->second = value;
                
                return;
            }
            
            lruList.push_front({key, value});
            lruMap.emplace(key, lruList.begin());
            
            if(lruList.size() > cp){
                lruMap.erase(lruList.back().first);
                lruList.pop_back();
            }
        }
        
        int get(int key){
            auto search = lruMap.find(key);
            if(search != lruMap.end()){
                lruList.push_front({search->first, search->second->second});
                lruList.erase(search->second);
                
                search->second = lruList.begin();
                
                return search->second->second;
            }
            
            return -1;
        }
        
};
// */

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
