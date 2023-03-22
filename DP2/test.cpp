#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

int lcs(string s1, string s2, int i, int j, vector<vector<int>> &dp){
	if(i==s1.size() or j == s2.size())
		return 0;
	
	if(dp[i][j]!=-1)return dp[i][j];


	if(s1[i] == s2[j])
		return dp[i][j] = 1 + lcs(s1, s2, i+1, j+1, dp);

	return dp[i][j] =  max(lcs(s1, s2, i+1, j, dp), lcs(s1, s2, i, j+1, dp));
}


int LCS(string s1, string s2){
	int n= s1.size();
	int m = s2.size();

	vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s1[i-1]==s2[j-1])
				dp[i][j] = 1 + dp[i-1][j-1];
			else 
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
	
	vector<char> v;
	int i=n, j= m;
	while(i and j){
		if(dp[i][j] == dp[i-1][j])
			i--;
		else if (dp[i][j] == dp[i][j-1])
			j--;
		else {
			v.push_back(s1[i-1]);
			i--;
			j--;
		}	
	}
	reverse(v.begin(),v.end());
	for(auto e : v)cout<<e;
	return dp[n][m];
}
//==============================================================================

int sellingWines(int price[], int l, int r, int n, int y, vector<vector<int>> & dp){
	if (l==r)
		return dp[l][r] = y*price[l];
	
	if(dp[l][r])return dp[l][r];

	int pr1 = price[l]*y + sellingWines(price, l+1, r, n, y+1, dp);
	int pr2 = price[r]*y + sellingWines(price, l, r-1, n, y+1, dp);
	return  dp[l][r] = max(pr1, pr2);
}


int sellingWinesBU(int price[], int n){
	vector<vector<int>> dp(n, vector<int> (n,0));
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<n;j++){
			if(i==j)
				dp[i][j] = n*price[i];
			if(i<j){
				int y = n - (j-i);
				int pickLeft = price[i]*y + dp[i+1][j];
				int pickRight = price[j]*y + dp[i][j-1];
				dp[i][j] = max(pickRight, pickLeft);				
			}
		}
	}
	for(auto v : dp){
		for(auto e : v)
			cout<<e<<" ";
		cout<<endl;
	}
	return dp[0][n-1];	
}
//==============================================================================
int countSubseq(string s1, string s2, int i, int j, 
				vector<vector<int>> &dp){
	if(j==-1){
		if(i>=0)
			return dp[i][j+1] = 1;
		else return dp[i+1][j+1] = 1;
	}
	if(i==-1)
		return dp[i+1][j] =   0;

	if(dp[i][j])return dp[i][j];

	if(s1[i] != s2[j])
		return  dp[i][j] =  countSubseq(s1, s2, i-1, j, dp);
	else 
		return  dp[i][j] = countSubseq(s1, s2, i-1, j-1, dp) +
						 countSubseq(s1, s2, i-1, j, dp);
}


int countSubseqBU(string s1, string s2){
	int n= s1.size();
	int m= s2.size();
	vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

	for(int i=0;i<=n;i++)
		dp[i][0] = 1;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s1[i-1] != s2[j-1])
				dp[i][j] = dp[i-1][j];
			else 
				dp[i][j] = dp[i-1][j] + dp[i-1][j-1]; 
		}
	}

	for(auto v : dp){
		for(auto e: v)
			cout<<e<<" ";
		cout<<endl;
	}
	return dp[n][m];
}

//==============================================================================

int knapsack(int wts[], int price[], int w, int i, vector<vector<int>> &dp){
	if(i==0 or w==0)
		return dp[i][w] = 0;

	if(dp[i][w])return dp[i][w];
	int inc {0}, exc{0};
	inc = w >= wts[i-1] ?price[i-1] +  knapsack(wts, price, w-wts[i-1], i-1, dp):0;
	exc = knapsack(wts, price, w, i-1, dp);
	return dp[i][w] = max(inc, exc);
}

int knapsackBU(int wts[], int price[], int w, int n){
	vector<vector<int>> dp(n+1, vector<int> (w+1, 0));

	for(int i=1;i<=n;i++){
		for(int j=1;j<=w;j++){
			int inc{0}, exc{0};
			if(wts[i-1]<=j){
				inc = price[i-1] + dp[i-1][j - wts[i-1]];
			}
			exc = dp[i-1][j];
			dp[i][j] = max(inc, exc);
		}
	}
	cout<<endl;
	for(auto v : dp){
		for(auto e : v)
			cout<<e<<" ";
		cout<<endl;
	}
	return dp[n][w];
}
//==============================================================================

int main(){
	// string s1 = "ABCD";
	// string s2 = "ABEDG";

	// vector<vector<int>> dp(s1.size(),vector<int> (s2.size(), -1));
	// cout<<lcs(s1, s2, 0, 0, dp)<<endl;

	// for(auto v : dp){
	// 	for(auto e : v)
	// 		cout<<e<<" ";
	// 	cout<<endl;
	// }

	// cout<<LCS(s1, s2)<<endl;





	// int price[] = {2,3,5,1,4};
	// int price2[] = {2, 4, 6, 2, 5};
	// int n = sizeof(price)/sizeof(int);
	// vector<vector<int>> dp(n, vector<int> (n, 0));
	// cout<<sellingWines(price, 0, n-1, n, 1, dp)<<endl;
	// for(auto v : dp){
	// 	for(auto e : v)
	// 		cout<<e<<" ";
	// 	cout<<endl;
	// }

	// cout<<sellingWinesBU(price2, n);


	





	// string s1 = "ABCDCE", s2 = "ABC";
	// vector<vector<int>> dp(s1.size(), vector<int> (s2.size(),0));
	// cout<<countSubseq(s1, s2, s1.size()-1, s2.size()-1, dp)<<endl;
	// for(auto v : dp)
	// {
	// 	for(auto e : v)
	// 		cout<<e<<" ";
	// 	cout<<endl;
	// }

	// cout<<countSubseqBU(s1, s2);





	int wts[] = {2,7, 3, 4};
	int price[] = {5, 20, 20, 10};
	int w = 11;
	int n = sizeof(wts)/sizeof(int);
	vector<vector<int>> dp(n+1, vector<int> (w+1, 0));
	cout<<knapsack(wts, price, w, n, dp)<<endl;
	for(auto v : dp){
		for(auto e : v)
			cout<<e<<" ";
		cout<<endl; 
	}
	cout<<knapsackBU(wts, price, w, n);







	// int arr[] = {10,20,30,40,50,60};
	// int n = sizeof(arr)/sizeof(int);
	// int k=0;
	// int x = 30;
	// for(int b=n/2; b>=1;b/=2){
	// 	while(k+b < n and arr[k+b]<=x)k+= b;
	// }
	// if(arr[k]==x)cout<<"found x";

}