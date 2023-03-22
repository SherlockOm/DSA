#include <iostream>
#include<unordered_map>
#include<vector>
using namespace std;


class Node {
public:
	string key;
	int value;
	Node * next{NULL};
	Node * prev{NULL};

	Node(string k, int v): key{k},value{v}{}
};


class LRUcache{
public:
	int maxSize{1};
	int currentSize{0};
	Node * top{NULL};
	Node * bottom{NULL};
	unordered_map<string, Node *> hashmap;

	LRUcache(int size=1):maxSize{size}{}

	void insert(string key, int value){
		//if already present in cache
		if(hashmap[key]){
			Node *it = hashmap[key];
			it->value =  value;
			if(it == bottom and it->prev)bottom = it->prev;
			//removig from middle
			if(it->prev)it->prev->next = it->next;
			if(it->next)it->next->prev = it->prev;
			//placing on top, since most recently visited
			it->prev = NULL;
			it->next = top;
			top->prev = it;
			top = it;
		}
		//if not present in cache
		else {
			//if cache is full, then remove the bottom most element 
			if(currentSize >= maxSize){
				hashmap.erase(bottom->key);
				bottom = bottom->prev;
				delete(bottom->next);
				currentSize--;
			}
			Node * newNode = new Node(key, value);
			//placing on top
			if(top!=NULL){
				newNode->next = top;
				top->prev = newNode;
				top  = newNode;
				
			}else {
				top = bottom = newNode;
			}	
			hashmap[key] = top;
			currentSize ++;
		}
	}

	Node* getValue(string key){
		if(hashmap.find(key)!=hashmap.end()){

			//if key is already present 
			Node* it = hashmap[key];
			
			if(it->prev)it->prev->next = it->next;
			if(it->next)it->next->prev = it->prev;
			Node * newNode = new Node(key, it->value);
			
			// if(it==bottom and it->prev)bottom = it->prev;
			hashmap.erase(key);
			delete(it);
			
			newNode->next = top;
			top = newNode;
			hashmap[key] = top;
			return top;
		}
		return NULL;
	}

	string getMostRecentlyKey(){
		return top->key;
	}
};



int main(){
	LRUcache cache(3);
	cache.insert("google.com", 10);
	cache.insert("youtube.com", 20);
	cache.insert("9anime.gs", 50);
	cout<<cache.getMostRecentlyKey()<<endl;

	cache.insert("google.com", 15);
	cout<<cache.getMostRecentlyKey()<<endl;

	cache.insert("supercell.com", 25);
	cout<<cache.getMostRecentlyKey()<<endl;


	if(cache.getValue("youtube.com")==NULL)
		cout<<"youtube.com doesen't exist!"<<endl;
	else cout<<"EXIST!!";

	if(cache.getValue("9anime.gs")==NULL)
		cout<<"9anime.gs doesen't exist!"<<endl;
	else cout<<"EXIST!!";


	if(cache.getValue("supercell.com")==NULL)
		cout<<"supercell.com doesen't exist!"<<endl;
	else cout<<"EXIST!!";

	if(cache.getValue("google.com")==NULL)
		cout<<"google.com doesen't exist!"<<endl;
	else cout<<"EXIST!!";
}