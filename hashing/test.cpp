#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<unordered_map>
#include<map>
#include<climits>
using namespace std;

int gpTriplets(vector<int> v, int r){
	unordered_map<int,int> Left,Right;
	int totalTriplets{0};
	for(auto elem : v){
		Right[elem]++;
		Left[elem]=0;
	}
	for(int i =0;i<v.size();i++){
		Right[v[i]]--;
		int al= v[i]/r,ar= v[i]*r;
		if(v[i]%r==0)
			totalTriplets+= Left[al]*Right[ar];
		
		Left[v[i]]++;
	}	
	return totalTriplets;
}
//====================================================
int countRectangles(vector<vector<int>> v){
	set<vector<int>> points;
	for(auto point : v)
		points.insert(point);

	int count{0};
	for(int i=0;i<v.size();i++){
		for(int j=i+1;j<v.size();j++){
			if(v[i][0]==v[j][0] or v[i][1]==v[j][1])
				continue;
			vector<int> p1{v[i][0],v[j][1]};
			vector<int> p2{v[j][0],v[i][1]};

			if(points.find(p1)!=points.end() 
				and points.find(p2)!=points.end()){
				count++;
			}
		}
	}
	return count/2;
}
//or using Point class---------------------------------
class Point{
public:
	int x,y;
	Point(int x, int y):x{x},y{y}{}
};

class ComparePoints{
public:
	bool operator()(const Point P1, const Point P2){
		if(P1.x == P2.x)
			return P1.y < P2.y;
		return P1.x < P2.x;
	}
};

int countRec(vector<Point> v){
	set<Point,ComparePoints> points;
	for(auto point : v)
		points.insert(point);

	int count{0};
	for(auto it1 = points.begin();it1!=points.end();it1++){
		for(auto it2=next(it1);it2!=points.end();it2++){
			Point P1 = *it1;
			Point P2 = *it2;

			if(P1.x==P2.x or P1.y==P2.y){
				continue;
			}
			Point P3(P1.x, P2.y);
			Point P4(P2.x, P1.y);
			if(points.find(P3)!=points.end() and 
				points.find(P4)!=points.end())
				count++;
		}
	}
	return count/2;
}
//=======================================================

int countTraingles(vector<Point> v){
	unordered_map<int,int> countX, countY;
	for(auto point : v){
		countX[point.x]++;
		countY[point.y]++;
	}
	int count{0};
	for(auto point : v){
		int X = countX[point.x]-1;
		int Y = countY[point.y]-1;
		count+= X * Y;
	}
	return count;
}

//=================================================
vector<int> stringHash(string s , int i, int j){
	vector<int> hash(26,0);
	for(int x=i;x<=j;x++){
		int temp = s[x] - 'a';
		hash[temp]++;
	}
	return hash;
}

int anagramSubstrings(string s){
	int count{0};
	map<vector<int>, int> HashCount;
	for(int i=0;i<s.size();i++){
		for(int j=i;j<s.size();j++){
			vector<int> hash = stringHash(s,i,j);
			HashCount[hash]++;
		}
	}
	for(auto elem : HashCount)
		if(elem.second >=2){
			int val = elem.second;
			count+=( val*(val-1))/2;
		}
	return count;
}
//=================================================
int QBF(string s,unordered_set<string> &list, int idx,vector<int> dp){
	if(s[idx] == '\0')
		return 0;
	int ans{INT_MAX};
	string current_string = "";
	for(int i=idx;i<=s.size();i++){
		current_string += s[i];
		if(list.find(current_string)!=list.end()){
			if(dp[i+1]==-1)dp[i+1]= QBF(s,list,i+1,dp);
			if(dp[i+1]!=-1)
				ans = min(ans,dp[i+1] +1);
		}
	}
	if(ans==INT_MAX)
		return -1;
	return ans;
}	

//=================================================
int main(){
	// vector<int> v{1,5,20,4,16};
	// cout<<gpTriplets(v,4);
	
	// int n;cin>>n;
	// vector<Point> v;
	// int x, y;
	// for(int i=0;i<n;i++){
	// 	cin>>x>>y;
	// 	v.push_back(Point(x,y));
	// }
	// cout<<countRectangles(v);
	// cout<<countRec(v);


	// int n;cin>>n;
	// vector<Point> v;
	// int x, y;
	// for(int i=0;i<n;i++){
	// 	cin>>x>>y;
	// 	v.push_back(Point(x,y));
	// }
	// cout<<countTraingles(v);

	// cout<<anagramSubstrings("abba");

	// string s = "quickbrownfox"; 
	// vector<int> dp(s.size()+1,-1);
	// unordered_set<string> list {"quickbrown","the","fox","quick","brown"};
	// cout<<QBF(s, list, 0, dp) - 1;

	
}