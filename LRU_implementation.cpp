#include<bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k,int v){
        key = k;
        value = v;
        prev = next =nullptr;
    }
};

class LRUCache{
    public:
        int capacity;
        unordered_map<int,Node *> mpp;
        Node * head;
        Node * tail;
        
        LRUCache(int cap)
        {
            this->capacity = cap;
            head = new Node(-1,-1);
            tail = new Node(-1,-1);
            head->next=tail;
            tail->prev=head;
        }
        
        int get(int key)
        {
            if(mpp.find(key)==mpp.end())
                return -1;
            Node * temp =mpp[key];
            remove1(temp);
            add(temp);
            return temp->value;
            
        }
        
        void put(int key,int value)
        {
            if(mpp.find(key)!=mpp.end())
            {
                Node * old = mpp[key];
                remove1(old);
                delete(old);
            }
            
            Node * newNode = new Node(key,value);
            mpp[key]=newNode;
            add(newNode);
            
            if(mpp.size()>capacity)
            {
                Node *nodeToDelete = tail->prev;
                remove1(nodeToDelete);
                mpp.erase(nodeToDelete->key);
                delete(nodeToDelete);
                
            }
        }
        void add(Node * temp){
            head->next->prev = temp;
            temp->next = head->next;
            head->next = temp;
            temp->prev = head;
        }
        void remove1(Node * temp){
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        
        void showCache()
        {
            cout << "\nCache (Most Recently Used -> Least Recently Used): ";
        Node* current = head->next;
        while (current != tail) {
            cout << current->key << " ";
            current = current->next;
        }
        cout << endl;
        }
};

int main()
{
    vector<int> arr = {7, 2, 7, 3, 2, 5, 3, 4, 6, 7, 7, 1, 5, 6, 1};
    LRUCache cache(4);

    int miss = 0, hit = 0;
    for (auto it : arr) {
        if (cache.get(it) == -1) {
            miss++;
        } else {
            hit++;
        }
        cache.put(it, it);
    }

    cache.showCache();
    cout << "Total Miss: " << miss << " | Total Hit: " << hit << endl;
    cout << "Cache implementation is completed." << endl;

    return 0;
}
