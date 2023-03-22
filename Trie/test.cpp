#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Node{
public:
	char ch;
	unordered_map<char,Node*> m;
	bool isTerminal;

	Node(char ch):ch{ch},isTerminal{false}
	{}
};

class Trie{
public:
	Node *root;
	Trie(){
		root = new Node('\0');
	}

	void insert(string word){
		Node * temp = root;
		for(auto ch : word){
			if(temp->m.count(ch)==0){
				Node * n = new Node(ch);
				temp->m[ch] = n;
			}
			temp = temp->m[ch];
		}
		temp->isTerminal = true;
	}

	void insertBin(int num){
		Node * temp = root;
		int n;
		for (int i = 31; i >= 0; i--) {
	        n=(num>>i)&1;
	        if(n==0){
		        if(!temp->m.count(0))
		        	temp->m[0] = new Node(0);
		        temp = temp->m[0];
	    	
	    	}
	    	else {
	    		if(!temp->m.count(1))
	    			temp->m[1] = new Node(1);
	    		temp = temp->m[1];
	    	}
	    }
	}


	bool search(string word){
		Node * temp = root;
		for(auto ch : word){
			if(temp->m.count(ch)==0)
				return 0;
			temp = temp->m[ch];
		}
		return temp->isTerminal;
	}
};


void searchHelp(int i, string &doc, unordered_map<string,bool> &m, Node *root){
	Node * temp = root;
	string out = "";
	for(int j=i;j<doc.size();j++){
		char ch = doc[j];
		if(temp->m.count(ch)==0)
			return ;
		out += ch;
		temp = temp->m[ch];
		if(temp->isTerminal){
			m[out] = true;
		}
	}
}


void cuteCat(string &doc, vector<string> &v){
	Trie words;
	unordered_map<string, bool> mp;
	for(auto word : v){
		words.insert(word);
		mp[word] = false;
	}

	for(int i=0;i<doc.size();i++){
		searchHelp(i, doc, mp, words.root);
	}
	for(auto elem : mp)
		cout<<elem.first<< " "<<elem.second<<endl;
}


string decToBinary(int n){
	string num = "";
    for (int i = 31; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            num += "1";
        else
            num += "0";
    }
    return num;
}


int maxXorHelper(Node * root, int num){
	Node * temp = root;
	int bit;
	int curr_ans{0};
	for (int i = 31; i >= 0; i--) {
    	bit= (num>>i)&1;
    	if(bit==1){
    		if(temp->m.count(0)){
    			curr_ans += (1<<i);
    			temp = temp->m[0];
    		}
    		else {
    			temp = temp->m[1];
    		}
    	} 	
    	else {
    		if(temp->m.count(1)){
    			curr_ans += (1<<i);
    			temp = temp->m[1];
    		}
    		else {
    			temp = temp->m[0];
    		}
    	}
    }
    return curr_ans;

}

int maxXor(vector<int> &nums){
	Trie t;
	for(auto elem : nums)
		t.insertBin(elem);
	//O(N*32*32)

	int maxXor{-1},currXor;
	for(auto elem : nums){
		currXor = maxXorHelper(t.root, elem);
		maxXor = max(maxXor, currXor);		
	}//O(32*N)
	return maxXor;
}

int main(){
	// string arr[] = {"apple","ape","news","mango","notorious"};
	// Trie T;
	// for(auto word : arr)
	// 	T.insert(word);

	// int q;cin>>q;
	// while(q--){
	// 	string word;cin>>word;
	// 	cout<<T.search(word);
	// }

	// string document = "little cute cat loves to code in c++, java and python";
	// vector<string> v {"cute cat","ttle","cat","quick","big"};

	// cuteCat(document, v);

	vector<int> nums{5,8,10};

	cout<<maxXor(nums);
}