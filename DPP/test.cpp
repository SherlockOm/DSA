#include <list>
#include <iostream>
#include<unordered_map>
#include<climits>
#include<vector>
using namespace std;


//==================================================
int MCM(int matrices[], int i, int j, vector<vector<int>> &dp){
	if(i>=j)return 0;
	if(dp[i][j])return dp[i][j];

	int minCost{INT_MAX};
	for(int k=i;k<j;k++){
		int temp = MCM(matrices, i, k, dp) 
		+ MCM(matrices, k+1, j, dp)
		+ matrices[i-1]*matrices[j]*matrices[k];
		minCost = min(temp, minCost);
	}
	return dp[i][j] = minCost;
}

//========================================================
void towerOfHanoi(int n, char A, char B, char C){
	if(n==1){
		cout<<"from "<<A<<" to "<<C<<endl;
		return ;
	}
	towerOfHanoi(n-1, A,C,B);
	towerOfHanoi(1, A,B, C);
	towerOfHanoi(n-1, B,C,A);
}

//==============================================

int eggDroppingRec(int e, int f){
	if(f==0 or f==1 or e==1)return f;

	int minAttempts{INT_MAX};
	int tempAns;
	for(int k=1;k<=f;k++){
		tempAns= max(eggDroppingRec(e-1,k-1), eggDroppingRec(e,f-k)) +1 ;
		minAttempts = min(minAttempts, tempAns);
	}
	return minAttempts;
} 
//===============================================
int longestCommonSubsequence(string s1, string s2, int i, int j, vector<vector<int>> &dp){
	if(i<0 or j<0)
		return 0;
	if(dp[i][j])return dp[i][j];

	if(s1[i] == s2[j]){	
		// cout<<s1[i];
		return 1 + longestCommonSubsequence(s1, s2, i-1, j-1, dp);
	}
	int pickL = longestCommonSubsequence(s1, s2, i-1, j, dp);
	int pickR = longestCommonSubsequence(s1, s2, i, j-1, dp);
	return dp[i][j] =  max(pickL, pickR);
}
//=============================================================
int palindromePartitioning(string s, int n){
	for(int i=1;i<s.size();i++){

	}
}

//=============================================================
float medianOfSortedArrays(vector<int> arr1, vector<int> arr2){
	int n=arr1.size(), m = arr2.size();
	vector<int> temp(n+m);
	int i=0,j=0;
	int k=0;
	while(i<n and j<m){
		if(arr1[i]< arr2[j])
			temp[k++] = arr1[i++];
		else temp[k++] = arr2[j++];			
	}
	while(i<n)temp[k++] = arr1[i++];
	while(j<m)temp[k++] = arr2[j++];
	int mid = (n+m)/2;
	// return (n+m)%2? (temp[mid] + temp[mid +1])/2 : temp[mid+1];
}

//=============================================================

int main(){

	// int matrices[] = {40, 20, 30, 10, 30};
	// int n=sizeof(matrices)/sizeof(int);
	// vector<vector<int>> dp(n,vector<int> (n,0));
	// cout<<MCM(matrices, 1, n-1, dp);



	// int e{2}, f{10};
	// vector<vector<int>> dp(e, vector<int> (f, 0));
	// cout<<eggDroppingRec(1, 10);




	// towerOfHanoi(3,'A','B','C');




	// string s1 = "ABCGCDE";
	// string s2 = "ABCD";
	// vector<vector<int>> dp(s1.size(), vector<int> (s2.size(), 0));
	// cout<<longestCommonSubsequence(s1, s2, s1.length()-1, s2.length() -1, dp);
	// for(auto v : dp){
	// 	for(auto e : v)
	// 		cout<<e<<" ";
	// 	cout<<endl;
	// }






	// vector<int> arr1{1,2,3,4,5};
	// vector<int> arr2{6,7,8,9,10};
	// cout<<medianOfSortedArrays(arr1, arr2);




}