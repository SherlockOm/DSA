#include<bits/stdc++.h>
using namespace std;

//========================================
//========================================
void permutations(string in ,int s){
	if(s==in.size()){
		cout<<in<<endl;
		
	}
	for(int i=s;i<in.size();i++){
		swap(in[i],in[s]);
		permutations(in,s+1);
		swap(in[i],in[s]);
	}
}
//========================================
//Binary Tree//---------------------------

class Node {
public:
	Node *left;
	Node *right;
	int data;

	Node (int d):left{NULL},right{NULL},data{d}{}
};

Node *buildTree(){
	int d;cin>>d;
	if(d==-1)return NULL;

	Node *n = new Node(d);
	n->left = buildTree();
	n->right = buildTree();
	return n;
}

Node *levelOrderBuild(){
	queue<Node*> q;
	int d;cin>>d;
	Node *root = new Node(d);
	q.push(root);
	while(!q.empty()){
		Node *n = q.front();
		q.pop();
		int left,right;cin>>left>>right;
		if(left!=-1){
			n->left  = new Node(left);
			q.push(n->left);
		}
		if(right!=-1){
			n->right = new Node(right);
			q.push(n->right);
		}
	}
	return root;
}

void levelOrderPrint(Node *root){
	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		Node * n = q.front();
		q.pop();
		if(n == NULL){
			cout<<"\n";
			if(!q.empty())q.push(NULL);
		}
		else{
			cout<<n->data<<" ";
			if((*n).left)q.push(n->left);
			if(n->right)q.push(n->right);
		}
	}
}
//--------------------------------------------
int height(Node *root){
	if (root==NULL)return 0;
	int h1 = height(root->left);
	int h2 = height(root->right);
	return max(h1,h2) +1 ;
}
int maxDiameter(Node *root){
	if(root == NULL)
		return 0;
	
	int d = height(root->left) + height(root->right);
	int d1 = maxDiameter(root->left);
	int d2 = maxDiameter(root->right);
	return max(d,max(d1,d2));
}
//--------------------------------------------

pair<int,int> OptimisedDiameter(Node *root){
	pair<int,int> p;
	if(!root){
		p.first = p.second = 0;
		return p;
	}
	pair<int,int> left = OptimisedDiameter(root->left);
	pair<int,int> right = OptimisedDiameter(root->right);

	p.first = max(left.first,right.first) +1;

	int D = left.first + right.first  ;
	int D1 = left.second;
	int D2 = right.second;

	int diameter = max(D, max(D1,D2));
	p.second = diameter;
	return p;
}
//--------------------------------------------
//similar to "diameter"
//answer is stored in "ans" which is passed by reference 
int maxPathSum(Node *root, int &ans){
	if(root==NULL)return 0;		

	int l = maxPathSum(root->left, ans);
	int r = maxPathSum(root->right, ans);

	int curr = root->data;
	int h = max(curr, max(l, r) + curr);
	int d = max(h, curr + l + r);

	ans = max(ans, d);
	return h;
}

//--------------------------------------------
int decendantSum(Node *&root){
	if(!root)return 0;
	int sum = decendantSum(root->left)+  decendantSum(root->right);
	int self = root->data;	
	if(!root->left and !root->right)root->data = self;
	else root->data = sum;
	return self + sum;
}

//--------------------------------------------
pair<int,bool> isHeightBalanced(Node *root){
	if(!root){
		return {0,true};
	}
	pair<int,bool> pl = isHeightBalanced(root->left);
	pair<int,bool> pr = isHeightBalanced(root->right);

	int h = max(pl.first,pr.first) + 1;
	if(abs(pl.first - pr.first)<=1 and pl.second and pr.second){
		return {h,true};
	}
	return {h,false};
}
//-----------------------------------------
pair<int,int> maxSubtreeSum(Node *root){
	if(!root)return{0,0};
	
	pair<int,int> Left = maxSubtreeSum(root->left);
	pair<int,int> Right = maxSubtreeSum(root->right);

	int inc = root->data + Left.second + Right.second;
	int exc = max(Left.first, Left.second) + max(Right.first, Right.second);
	return {inc,exc}; 
}

//-----------------------------------------
void printAtK(int k, Node *root){
	if(!root)return;
	if(k==0){
		cout<<root->data<<" ";
		return;
	}
	k--;
	printAtK(k,root->left);
	printAtK(k,root->right);
}
//-----------------------------------------
int nodeAtK(Node * &root, int k, Node *&target){
	if(!root)return -1; 
	if(root==target){
		printAtK(k,root);
		return 0;
	}
	int dl = nodeAtK(root->left, k , target);
	if(dl!=-1){
		if(dl+1==k)cout<<root->data;
		else printAtK(k-2-dl,root->right);
		return dl +1;
	}
	int dr = nodeAtK(root->right, k , target);
	if(dr!=-1){
		if(dr+1==k)cout<<root->data;
		else printAtK(k-2-dr,root->left);
		return dr +1;
	}
	return -1;
}
//-----------------------------------------
void verticalTraversal(Node *root,map<int,vector<int>> &layers, int l){
	if(!root)return;
	layers[l].push_back(root->data);
	verticalTraversal(root->right,layers,l+1);
	verticalTraversal(root->left,layers,l-1);
}
void verticalPrint(Node * root){
	cout<<endl;
	map<int,vector<int>> layers;
	verticalTraversal(root,layers,0);
	for(auto layer : layers){
		for(auto elem : layer.second){
			cout<<elem<<" ";
		}
		cout<<endl;
	}
}
//=========================================
int main(){
	Node *root = buildTree();
	levelOrderPrint(root);

	// // Node *levelRoot = levelOrderBuild();
	// // levelOrderPrint(levelRoot);

	// cout<<endl<<maxDiameter(root)<<endl;
	// pair<int,int> p = OptimisedDiameter(root);
	// cout<<p.second<<endl;

	// if(isHeightBalanced(root).second)cout<<"height balanced";
	// else cout<<"Not height balanced";

 	// int sum = decendantSum(root);
	// levelOrderPrint(root);

	// pair<int,int> p = maxSubtreeSum(root);
	// cout<<max(p.first,p.second)<<endl;

	// printAtK(2,root);

	// Node * target = root->left->right;
	// nodeAtK(root,2,target);

	// int ans{INT_MIN};
	// maxPathSum(root, ans);
	// cout<<ans;

	verticalPrint(root);
}	