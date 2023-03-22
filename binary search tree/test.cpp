#include<iostream>
#include<queue>
#include<climits>
using namespace std;

//Binary Search Tree
// Boilerplate Code
class Node {
public:
	int data;
	Node *left;
	Node *right;

	Node (int key):data{key},left{NULL},right{NULL}{}
};

Node *insert(Node *root,int data){
	if(!root)
		return new Node(data);
	if(data<root->data)root->left = insert(root->left,data);
	else root->right = insert(root->right,data);
	return root;
}

void printInOrder(Node *root){
	if(!root){
		return;
	}
	printInOrder(root->left);
	cout<<root->data<<" ";
	printInOrder(root->right);
}

Node * minHeightBST(Node *root, int arr[],  int s, int e){
	if(s>e)return NULL;
	int mid = (s+e)/2;
	root = new Node(arr[mid]);
	root->left = minHeightBST(root->left, arr, s, mid-1);
	root->right = minHeightBST(root->right, arr, mid+1, e);
	return root;
}

void printTree(Node *root){
	queue<Node *> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		Node * n = q.front();
		q.pop();
		if(n==NULL){
			if(!q.empty())q.push(NULL);
			cout<<endl;
			continue;
		}
		cout<<n->data<<" ";
		if(n->left)q.push(n->left);
		if(n->right)q.push(n->right);

	}
}

int closestInBST(Node *root, int target){
	int diff = INT_MAX;
	int closest ;

	Node * temp  = root;
	while(temp){
		if(temp->data ==target)
			return target;
		int current_diff = abs(temp->data - target);
		
		if(current_diff < diff){
			diff = current_diff;
			closest = temp->data;
		}

		if(target > temp->data)
			temp  = temp->right;
		else temp = temp->left;
	}
	return closest;
}
class LinkedList{
public :
	Node * head{NULL};
	Node * tail{NULL};
};

LinkedList BSTtoLL(Node *root){
	LinkedList HeadTail;
	if(!root->left and !root->right){
		HeadTail.head = HeadTail.tail = root;
		return HeadTail;
	}
	if(!root->left)
		HeadTail.head = root;
	else{ 
		LinkedList Left = BSTtoLL(root->left);
		Left.tail->right = root;
		HeadTail.head = Left.head;
	}
	if(!root->right)
		HeadTail.tail = root;
	else{ 	
		LinkedList Right = BSTtoLL(root->right);
		root->right = Right.head;
		HeadTail.tail = Right.tail;
	}
	return HeadTail;
}

int inorrderSuccessor(Node *root, int target){
	int successor;
	Node * temp = root;
	// successor = root->data;

	while(temp){
		if(target >= temp->data){
			temp = temp->right;
		}
		else {
			successor = temp->data;
			temp = temp->left;
		}
	}	
	return successor;
}

Node * inordSucc(Node * root, Node *target){
	if(target->right){
		Node * temp = target->right;
		while(temp->left){
			temp = temp->left;
		}
		return temp;
	}

	Node * temp = root;
	Node * successor {NULL};

	while(temp){
		if(target->data > temp->data)
			temp = temp->right;
		
		else if(target->data < temp->data){
			successor = temp;
			temp = temp->left;
		}
		else break;
	}
	return successor;
}
int main(){
	Node *root{NULL};
	int arr[] = {8,3,10,1,6,14,4,13};
	for(auto elem : arr){
		root = insert(root,elem);
	}
	
	// int arr[] = {1,2,3,4,5,6,7};
	// int n = sizeof(arr)/sizeof(int);
	// root = minHeightBST(root, arr, 0,n-1);
	
	// printInOrder(root);
	printTree(root);
	
	// cout<<"\n" <<closestInBST(root,5);

	// cout<<endl;
	// LinkedList linkedList = BSTtoLL(root);
	// Node * temp = linkedList.head;
	// while(temp){
	// 	cout<<temp->data<<" ";
	// 	temp = temp->right;
	// }

	// cout<<inorrderSuccessor(root,1);
	// Node * target = root->right;
	// Node * successor  = inordSucc(root,target);
	// cout<<successor->data;
}