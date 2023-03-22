#include<iostream>
#include<unordered_map>
#include<climits>
#include<set>
#include<vector>
#include<queue>
#include<unordered_set>
using namespace std;
#define N 5
#define M 5


class Node {
public:
	char ch;
	unordered_map<char, Node*> m;
	bool isTerminal {false};
	string word;


	Node(char c):ch{c}, word{""}{}
};


class Trie{
public:
	Node *root;
	Trie(){
		root = new Node('\0');
	}

	void insert(string s){
		Node * temp = root;

		for (char c : s){
			if(temp->m.count(c) == 0)
				temp->m[c] = new Node(c);
			temp = temp->m[c];

		}

		temp->isTerminal = true;
		temp->word = s;
	}
};


void dfs8(Node * node, unordered_set<string> &output, bool visited[][M], char board[][M], int i, int j){
	char ch = board[i][j];
	if(node->m.count(ch) == 0)
		return ;

	node = node->m[ch];
	visited[i][j] = true;

	if (node->isTerminal)
		output.insert(node->word);

	int row[] = {0,1,-1};
	int col[] = {0,1,-1};


	for(auto r: row){
		for(auto c : col){
			if(r<N and r>-1 and c<M and c>-1 and !visited[r+i][c+j]);
			dfs8(node, output, visited, board, i+r, c+j);
		}
	}

	visited[i][j] = false;
}


class GraphNode{
public:
	int dist;
	int i,j;

	GraphNode(int x, int y, int d):dist{d}, i{x}, j{y}
	{}
};

class CompareNodes{
public:
	bool operator()(GraphNode a, GraphNode b){
		return a.dist <= b.dist;
	}

};


int shortest_path(vector<vector<int> > grid){
    int m = grid.size();
    int n = grid[0].size();

    vector<vector<int> > dist(m, vector<int>(n,INT_MAX));
    dist[0][0] = grid[0][0];

    set<GraphNode,CompareNodes> s;
    s.insert(GraphNode(0,0,dist[0][0]));

    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};

    while(!s.empty()){
    	auto it = s.begin();
    	int cx = it->i;
    	int cy = it->j;
    	int cd = it->dist;
    	s.erase(it);

    	for(int k=0;k<4;k++){
    		int nx = cx + dx[k];
    		int ny = cy + dy[k];

    		if(nx>=0 and nx<m and ny>=0 and ny<n and cd + grid[nx][ny] < dist[nx][ny]){
    			GraphNode temp(nx,ny,dist[nx][ny]);
    			if(s.find(temp)!=s.end()){
    				s.erase(temp);
    			}
    			int nd = grid[nx][ny] + cd;
    			dist[nx][ny] = nd;
    			s.insert(GraphNode(nx,ny,nd));
    		}

    	}

    }
    return dist[m-1][n-1];
    
}




int dfs4(vector<vector<int>> &grid, bool visited[][M], int i, int j){
	visited[i][j] = true;
	int count{1};

	int dx[] = {1,-1,0,0};
	int dy[] = {0,0,1,-1};

	for (int k=0;k<4;k++){
		int ni = i + dx[k];
		int nj = j + dy[k];

		if (ni>=0 and ni< N and nj>=0 and nj<M and grid[ni][nj] ==1 and  !visited[ni][nj]){
			int subcount = dfs4(grid, visited, ni, nj);
			count += subcount;

		}		
	}
	return count;
}


int largestIsland(vector<vector<int>> &grid){
	bool visited[N][M] {false};
	int MaxIsland = 0;

	visited[0][0]  = true;

	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(grid[i][j]==1 and !visited[i][j]){
				MaxIsland = max(MaxIsland, dfs4(grid, visited, i, j));
			}
		}
	}
	return MaxIsland;

}


void dfs42(vector<vector<int>> &v, vector<vector<int>> &lengths, vector<vector<bool>> &visited, int i, int j){
	visited[i][j] = true;

	int count{0};
	int dx[] = {0,0,1,-1};
	int dy[] = {1,-1,0,0};

	for(int k=0;k<4;k++){
		int ni = i + dx[k];
		int nj = j + dy[k];

		if(ni>=0 and nj>=0 and ni<v.size() and nj < v[0].size() and v[ni][nj] > v[i][j]){
			if(!visited[ni][nj])
				dfs42(v, lengths, visited, ni, nj);
			count = max(count, lengths[ni][nj]);
		}
	}
	lengths[i][j] = count+1;
}

int longestSubseq(vector<vector<int>> &v){
	int maxLength {0};
	vector<vector<int>> lengths (v.size(), vector<int> (v[0].size(), 0));
	vector<vector<bool>> visited(v.size(), vector<bool> (v[0].size(), false));
	for(int i=0;i<v.size(); i++){
		for(int j=0;j<v[0].size(); j++){
			if(!visited[i][j]){
				dfs42(v, lengths, visited, i, j);
				maxLength = max(maxLength, lengths[i][j]);
			}
		}
	}
	return maxLength;
}



int main(){
	// string words[] = {"SNAKE", "FOR", "QUEZ", "SNACK", "SNACKS", "GO","TUNES","CAT"};
    // char board[N][M] = { { 'S', 'E', 'R' ,'T'}, 
    //                   { 'U', 'N', 'K' ,'S'},
    //                   { 'T', 'C', 'A' ,'T'} };

    // Trie t;
    // for(auto word : words)
    // 	t.insert(word);

    // unordered_set<string> output;
    // bool visited[N][M] = {0};

    // for(int i=0; i<N;i++){
    //   	for(int j=0;j<M;j++){
    //   		dfs8(t.root, output , visited, board, i ,j);
    //   	}
    //   }

    // for(auto word : output)
    // 	cout<<word<<endl;







	// vector<vector<int>> v =	{{31,100,65,12,18},
	// 				{10,13,47,157,6},
	// 				{100,113,174,11,33},
	// 				{88,124,41,20,140},
	// 				{99,32,111,41,20}};

	// cout<<shortest_path(v);






	// vector<vector<int> > grid = 
	// 						{{1, 0, 0, 1, 0},
    //                         {1, 0, 1, 0, 0},
    //                         {0, 0, 1, 0, 1},
    //                         {1, 0, 1, 1, 1},
    //                         {1, 0, 1, 1, 0}};
    
    // cout<<largestIsland(grid);





    vector<vector<int>> v = {{0,2,4,3,2}, 
    						{7,6,5,5,1},
    						{8,9,7,18,14},
    						{5,10,11,12,13}};
    cout<<longestSubseq(v);

}