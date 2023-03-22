#include <iostream>
#include<queue>
#include<climits>
#include<vector>
using namespace std;

class Node{
public:
	int data;
	Node *left{NULL};
	Node * right{NULL};

	Node(int val):data{val}{}
};	

class Tree{
public:
	Node * root{NULL};

	Tree(int val){
		root = new Node(val);
	}

	int height(Node *root){
		if(!root)return 0;
		int lh = height(root->left);
		int rh = height(root->right);
		return max(lh, rh) + 1;
	}
};

//==================================================

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

//==================================================

Node * LCA(Node *root, Node *n1, Node* n2){
	if(root==NULL)return NULL;

	if(root==n1 or root==n2)return root;

	Node * l = LCA(root->left, n1, n2);
	Node * r = LCA(root->right, n1, n2);

	if(l and r)return root;

	return l?l:r;
}

//==================================================
int burnTree(Node* root, Node *n, int &dist, int &res){
	if(root== NULL)return 0;

	if(root==n){
		dist = 0;
		return 1;
	}
	int ldist{-1}, rdist{-1};

	int lh = burnTree(root->left, n, ldist, res);
	int rh = burnTree(root->right, n, rdist, res);

	if(ldist!=-1){
		dist = ldist + 1;
		res = max(res, dist + rh);
	}
	else if (rdist!=-1){
		dist = rdist +1;
		res = max(res, dist + lh);
	}

	return max(lh, rh) + 1;
}

//==================================================

int main(){
	Tree binaryTree(1);
	Node * root = binaryTree.root;
	// root->left = new Node(9);
	// root->right= new Node(0);
	// root->left->left = new Node(-40);
	// root->left->right = new Node(-50);
	// root->right->left = new Node(3);
	// root->right->right = new Node(7);



    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->left->left->left = new Node(8);
    root->left->right->left = new Node(9);
    root->left->right->right = new Node(10);
    root->left->right->left->left = new Node(11);
	// int ans{INT_MIN};
	// maxPathSum(root, ans);
	// cout<<ans;




	// Node *n1 = root->right;
	// Node *n2 = root->right->right;
	// cout<< LCA(root, n1, n2)->data;




	int res{INT_MIN}, dist{-1};
	Node * n = root->left->right->left->left;
	burnTree(root, n, dist, res);
	cout<<res;
}