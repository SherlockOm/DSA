#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;

//======================================================
class Car{
public:
	string name;
	int x,y;
	Car(string name, int x, int y):name{name},x{x},y{y}{}

	int dist()const {return x*x + y*y;}
};

class CompareCars{
public:
	bool operator()(const Car A, const Car B){
		return A.dist() < B.dist();
	}
};

void nearestCabs(int n, int k, vector<Car> cars){
	priority_queue<Car, vector<Car>, CompareCars> MaxHeap(cars.begin(),cars.begin()+k);
	for(int i=k;i<n;i++){
		if(cars[i].dist() < MaxHeap.top().dist()){
			MaxHeap.pop();
			MaxHeap.push(cars[i]);
		}
	}
	while(!MaxHeap.empty()){
		cout<<MaxHeap.top().name<<" ";
		MaxHeap.pop();
	}
}
//======================================================

int mergeRopes(int n, int ropes[]){
	priority_queue<int, vector<int>, greater<int>> 
					MinHeap(ropes, ropes+n);

	int cost{0};
	while(MinHeap.size()>1){
		int smallestRope1 = MinHeap.top();
		MinHeap.pop();
		int smallestRope2 = MinHeap.top();
		MinHeap.pop();

		int NewRope = smallestRope1 + smallestRope2;
		cost += NewRope;
		MinHeap.push(NewRope);
	}
	return cost;
}

//======================================================
void median(vector<int> v){
	
	priority_queue <int, vector<int>, greater<int>> Right;
	priority_queue <int> Left;

	float m = v[0];
	Left.push(m);
	cout<<m<<" ";

	for(int i=1;i<v.size();i++){
		int elem = v[i];
		if(Left.size() > Right.size()){
			if(elem < m){
				Right.push(Left.top());
				Left.pop();
				Left.push(elem);
			}
			else Right.push(elem);
			m = (Left.top()+Right.top())/2.0;
		}
		else if (Left.size() <Right.size()){
			if(elem > m){
				Left.push(Right.top());
				Right.pop();
				Right.push(elem);
			}
			else Left.push(elem);
			m = (Left.top()+Right.top())/2.0;
		}
		else {
			if(elem < m){
				Left.push(elem);
				m= Left.top();
			}
			else{
				Right.push(elem);
				m = Right.top();
			}
		}
		cout<<m<<" ";
	}	
}
//======================================================

class ComparePairs{
public:
	bool operator()(pair<pair<int,int>,int> A, pair<pair<int,int>,int> B){
		return A.second > B.second;
	}
};

void kMerge(vector<vector<int>> v){
	//use priority_queue of pair<pair<int,int>,int>
	//or priority_queue of vector<int>
	//vector<int> will have triplets 
	//triplet = element-->arr_idx-->elem_idx
	//vectors are compared by their first elements.
	priority_queue<pair<pair<int,int>,int>, vector<pair<pair<int,int>,int>>, ComparePairs> MinHeap;
	for(int i=0;i<v.size();i++){
		MinHeap.push({{i,0},v[i][0]});
	}

	while(!MinHeap.empty()){
		auto elem = MinHeap.top();
		int arrNo = elem.first.first;
		int elemNo = elem.first.second;

		cout<<elem.second<<" ";
		MinHeap.pop();
		if(elemNo+1<v[arrNo].size())
			MinHeap.push({{arrNo,elemNo+1},v[arrNo][elemNo+1]});
	}
}
//======================================================

int main(){
	// vector<Car> cars;
	// int n,k;cin>>n>>k;
	// string name;
	// int x,y;
	// for(int i =0;i<n;i++){
	// 	cin>>name>>x>>y;
	// 	cars.push_back(Car(name,x,y));
	// }
	// nearestCabs(n,k,cars);

	// int n;cin>>n;
	// int ropes[n];
	// for(int i =0;i<n;i++){
	// 	int rope;cin>>rope;
	// 	ropes[i] = rope;
	// }
	// cout<<mergeRopes(n,ropes);


	// vector<int> v{10,5,2,3,0,12,18,20,22};
	// median(v);


    vector<vector<int> > arr = {{10,15,20,30},
                                {2,5,8,14,24},
                                {0,11,60,90}};
	kMerge(arr);
}
