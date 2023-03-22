#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;


int NKLadder(int n, int k){
	if(n == 0 or n==1 )
		return 1;

	int dp[n+1] ;
	dp[0] = dp[1] = 1;
	for(int i=2;i<=n;i++){
		dp[i] = 2*dp[i-1] ;
		if(i-k-1 >= 0)
			dp[i] -= dp[i-k-1];
	}
	return dp[n];

}


int recLadder(int n, int k, int dp[]){
	if (n==1 or n==0 )return dp[n] = 1;
	if(n<0)return 0;
	if(dp[n])return dp[n];

	for(int i= n-1;i>=n-k;i--){
		dp[n] += recLadder(i, k, dp);
	}
	return dp[n];
}
//=============================================================================================
int coinChange(int amount, int coins[], int n){
	if(amount=0)return 0;

	int dp[amount+1] = {0};

	
	for(int am=1;am<=amount;am++){
		int temp{INT_MAX};
		for(int i=0;i < n;i++){
			int coin = coins[i];
			if(am- coin>= 0){
				temp = min(temp, dp[am - coin]);
			}
		}
		dp[am] = temp+1;
	}

	return dp[amount]>0?dp[amount] : -1 ;
}
//=============================================================================================

int cuttingRod(int n, int price[]){
	int dp[n+1]{0};

	for(int len = 1;len<=n;len++){
		int ans{INT_MIN};
		for(int i=0;i<len;i++){
			int cut = i+1;
			int current = price[i] + dp[len - cut];
			ans = max(ans, current);
		}

		dp[len]=ans;
	}
	return dp[n];
}

//=============================================================================================

int minArrJumps(int arr[], int n){
	int dp[n+1] = {0};

	int minJumps{0};

	for(int i =0;i<n;i++){
		if(dp[i])

		int currentJump = arr[i];
		int jump{INT_MAX};
		for(int j=1;j<=arr[i];j++){
			if(dp[j])
				jump = min(jump, dp[j]);
		}
	}
}


int minJumps(int arr[], int n,int dp[], int i){
	if(i==n-1)
		return 0;

	if(dp[i])return dp[i];


	int currMinJumps{INT_MAX};
	for(int j=1;j<=arr[i];j++){
		if(i+j < n)
			currMinJumps = min(currMinJumps, minJumps(arr, n , dp, i+j));
	}
	return dp[i] = currMinJumps +1;
}

//=============================================================================================

int frogJumps(int heights[], int n, int i, int dp[]){
	if(i==n-1)
		return 0;
	
	if(dp[i]!=-1)return dp[i];

	int first = frogJumps(heights, n ,i+1, dp);
	int second = frogJumps(heights, n ,i+2, dp);
	first =first + abs(heights[i] - heights[i+1]);
	second = second + abs(heights[i] - heights[i+2]);


	return dp[i] = min(first, second);

}


int fJumps(int heights[], int n){
	int dp[n]= {-1};
	dp[0] = 0;
	dp[1] =abs( heights[1] - heights[0]);
	for(int i=2;i<n;i++){
		int first = dp[i-1] + abs(heights[i] - heights[i-1]);
		int second = dp[i-2] + abs(heights[i] - heights[i-2]);

		dp[i] = min(first, second);
	}

	return dp[n-1];
}

int fJumpsOpt(int heights[], int n){
	int prev = abs(heights[1] - heights[0]);
	int second_prev = 0;
	for(int i=2;i<n;i++){
		int first = prev+ abs(heights[i] - heights[i-1]);
		int second = second_prev + abs(heights[i] - heights[i-2]);
		second_prev = prev;
		prev  = min(first, second);
	}
	return prev;
}
//=============================================================================================
int maxNonAdj(int nums[], int ind, int dp[])
{
    if(ind <0) return 0;
    if(dp[ind] != -1) return dp[ind];
    int pick = nums[ind] + maxNonAdj(nums,ind-2,dp);
    int notPick = maxNonAdj(nums,ind-1,dp);
    return dp[ind] = max(pick,notPick);
}

int maxNonAdjSum(int arr[], int n){
	if(n==1)
		return max(0, arr[0]);
	if(n==2)
		return max(0, max(arr[0], arr[1]));

	int dp[n] = {0};
	dp[0] = max(0, arr[0]);
	dp[1] = max(0, max(arr[1], arr[0]));

	for(int i=2;i<n;i++){
		int inc = arr[i] + dp[i-2];
		int exc = dp[i-1];
		dp[i] = max(inc, exc);
	}
	return dp[n-1];
}


int maxNonAdjSumOpt(int arr[], int n){
	if(n==1)
		return max(0, arr[0]);
	if(n==2)
		return max(0, max(arr[0], arr[1]));

	int secPrev = max(0, arr[0]);
	int prev= max(0, max(arr[1], arr[0]));

	for(int i=2;i<n;i++){
		int inc = arr[i] + secPrev;
		int exc = prev;
		secPrev = prev;
		prev = max(inc, exc);
	}
	return prev;
}
//=============================================================================================

int LongIncSubseq(int seq[], int n){
	int dp[n] = {1};
	for(int i=0;i<n;i++)dp[i] =1;

	int len =1;
	for(int i =1;i<n;i++){
		for(int j=0;j<i;j++){
			if(seq[j]<seq[i]){
				dp[i] = max(dp[j]+1,dp[i]);
			}
		}
		len = max(len, dp[i]);
	}
	return len;
}

int lis(vector<int>& nums,int ind,int prev, vector<vector<int>>&dp){
    if(ind==nums.size()){  //base case
        return 0;
    }
    if(dp[ind][prev+1]!=-1){   // memoization 
        return dp[ind][prev+1];
    }
    int len=0;
    if(prev==-1 || nums[ind]>nums[prev]){  //take 
        len=1+lis(nums,ind+1,ind,dp);
    }
    int dlen= lis(nums,ind+1,prev,dp);  // not take
    len=max(len,dlen); 
    return dp[ind][prev+1]=len;  //store value in dp and return 
}


int lengthOfLIS(vector<int>& nums) {
    vector<int>list;
    for(int i=0;i<nums.size();i++){
        auto it=lower_bound(list.begin(),list.end(),nums[i]);
        if(it==list.end()){
            list.push_back(nums[i]);
        }
        else{
            *it=nums[i];
        }
    }
    for(auto e : list)cout<<e<<" ";
    return list.size();
}

//=============================================================================================

bool sortHelper(vector<int> box1, vector<int> box2){
	return box1[2]<box2[2];
}


bool canPlace(vector<int> box1, vector<int> box2){
	if(box1[0]<box2[0] and
		box1[1]<box2[1] and 
		box1[2]<box2[2] )
		return 1;
	return 0;

}


int boxStack(vector<vector<int>> &boxes){
	sort(boxes.begin(), boxes.end(), sortHelper);
	int n= boxes.size();
	vector<int> dp(n,0);
	
	for(int i =0;i<n;i++)
		dp[i] = boxes[i][2];

	int maxH{0};
	for(int i =1;i<n;i++){
		for(int j=0;j<i;j++){
			if(canPlace(boxes[j], boxes[i])){
				int currentH = boxes[i][2];
				if(dp[i] < dp[j] + currentH)
					dp[i] = dp[j] + currentH;
			}
		}
		maxH = max(maxH, dp[i]);
	}
	for(auto e : dp)cout<<e<<" ";
	return maxH;
} 

//=============================================================================================
int countingTrees(int n){
	vector<int> dp(n+1,0);

	dp[0] = dp[1] = 1;
	for(int i =2;i<=n;i++){
		for(int j=1;j<=i;j++){
			dp[i] += dp[i-j] * dp[j-1];
		}
	}
	return dp[n];
}

int countTree(int i,vector<int> &dp){
	if(i==0 or i==1 )return 1;

	if(dp[i])return dp[i];
	
	for(int j =1;j<=i;j++){
		dp[i]+= countTree(j-1, dp) * countTree(i-j, dp);
	}

	return dp[i] ;
}
//=============================================================================================



//=============================================================================================

int main(){
	// int n,k; 
	// cin>>n>>k;
	// int dp[n+1] = {0};
	// cout<<recLadder(n,k,dp);
	// cout<<NKLadder(n,k);




	// int coins[] = {1,3,7,10};
	// int n = sizeof(coins)/sizeof(int);
	// cout<<coinChange(5, coins, n);




	// int price[] = {3,5,8,9,10,17,17,20};
	// cout<<cuttingRod(8, price);





	// int arr[] = {3,4,2,1,2,3,7,1,1,1,2,5};
	// int n = sizeof(arr)/sizeof(int);
	// // cout<<minArrJumps(arr, n);
	// int dp[n] = {0};
	// cout<<minJumps(arr, n, dp, 0);





	// int heights[] = {30,10,60,10,60,50};
	// int n= sizeof(heights)/sizeof(int);
	// int dp[n] = {0};
	// cout<<frogJumps(heights, n, 0, dp);
	// cout<<fJumps(heights, n);
	// cout<<fJumpsOpt(heights, n);





	// int arr[] = {1,2,3,1,3,5,8,1,9};
	// int n= sizeof(arr)/sizeof(int);
	// int dp[n];
	// for(int i=0; i<n; ++i) dp[i]=-1;
	// cout<<maxNonAdj(arr, n-1, dp);
	// cout<<maxNonAdjSum(arr, n);





	// int seq[] = {1,3,6,7,9,4,10,5,6};
	// int n = sizeof(seq)/sizeof(int);

	// int dp[n];
	// for(int i=0;i<n;i++)dp[i] = -1;
	// cout<<LongIncSubseq(seq, n)<<endl;

	// vector<int> nums = {50,4,10,8,30,100};
    // vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
	// cout<<lengthOfLIS(nums);
	// cout<<lis(nums, 0, -1, dp);




	// vector<vector<int>> boxes{
	// 	{2,1,2},
	// 	{3,2,3},
	// 	{2,2,8},
	// 	{2,3,4},
	// 	{2,2,1},
	// 	{4,4,5}};

	// cout<<boxStack(boxes)<<endl;





	int n =5 ;
	vector<int> dp(n+1, 0);
	dp[0] = dp[1] = 1;
	cout<<countTree(n, dp);
	cout<<countingTrees(n);



}