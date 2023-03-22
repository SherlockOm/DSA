#include<iostream>
#include<list>
#include<vector>
#include<unordered_map>
#include<queue>
#include<climits>
#include<stack>
#include<set>
#include<utility>
using namespace std;

// class Node {
// 	public :
// 	string name;
// 	std::vector<string> nbrs;

// 	Node(string name):name{name}{}
// };

// class Graph{
// public:
// 	unordered_map<string, Node*> m;

// 	Graph(vector<string> cities){
// 		for(auto city: cities)
// 			m[city] = new Node(city);
// 	}
// 	void addEdge(string city1, string city2, bool undir=true){
// 		m[city1]->nbrs.push_back(city2);
// 		if(undir)
// 			m[city2]->nbrs.push_back(city1);
// 	}
// 	void printGraph(){
// 		for(auto elem : m){
// 			cout<<elem.first<<"-->";
// 			for(auto nbr : elem.second->nbrs)
// 				cout<<nbr<<",";
// 			cout<<endl;
// 		}
// 	}

// 	// void BFS()
// };

class Graph{
	

public:
	list<int> *l;
	list<pair<int,int>> *lw;
	int V;
	Graph(int v){
		V = v;
		l = new list<int> [V];
		lw = new list<pair<int,int>> [V];
	}

	void addEdge(int n1, int n2, bool undir = true){
		l[n1].push_back(n2);
		if(undir)
			l[n2].push_back(n1);
	}

	void addEdgeWt(int n1, int n2, int wt, bool undir = true){
		lw[n1].push_back({wt,n2});
		if(undir)
			lw[n2].push_back({wt,n1});
	}

	void printGraph(){
		for(int i=0;i<V;i++){
			cout<<i<<"-->";
			for(auto elem : l[i])
				cout<<elem<<",";
			cout<<endl;
		}
	}

	void BFS(int s){
		queue<int> q;
		q.push(s);
		bool * visited = new bool[V]{0};
		visited[s] = true;
		while(!q.empty()){
			int n = q.front();
			q.pop();
			cout<<n<<" ";
			for(auto nbr  : l[n])
				if(!visited[nbr]){
					q.push(nbr);
					visited[nbr] = true;
				}	
		}
		cout<<endl;
	}

	void DFS(int s){
		stack<int> st;
		st.push(s);
		bool * visited = new bool[V]{0};
		visited[s] = true;
		while(!st.empty()){
			int n = st.top();
			cout<<n<<" ";
			st.pop();
			for(auto nbr :l[n]){
				if(!visited[nbr]){
					st.push(nbr);
					visited[nbr] = true;
				}
			}
		}
		cout<<endl;
	}

	void recDFS(int node, vector<bool> &visited){
		visited[node] = true;
		cout<<node<<" ";
		for(auto nbr : l[node]){
			if(!visited[nbr]){
				recDFS(nbr, visited);
			}
		}
	}

	bool isCyclic(int s){
		stack<pair<int,int>> st;
		st.push({s,s});
		bool * visited = new bool[V]{0};
		visited[s] = true;
		while(!st.empty()){
			int n = st.top().second;
			int parent = st.top().first;
			st.pop();
			for(auto nbr :l[n]){
				if(visited[nbr] and nbr != parent)return 1;
				if(!visited[nbr] ){
					st.push({n, nbr});
					visited[nbr] = true;
				}
			}
		}
		return 0;
	}

	bool hasBackedgeHelper(int node, vector<bool> &visited, vector<bool> &inStack){
		visited[node] = true;
		inStack[node] = true;
		for(auto nbr : l[node]){
			if(inStack[nbr])
				return 1;
			else if(!visited[nbr]){
				if (hasBackedgeHelper(nbr, visited, inStack))
					return true;
			}
		}
		inStack[node] = false;
		return 0;
	}

	bool hasBackedge(){
		vector<bool> visited(V,0);
		vector<bool> inStack(V,0);

		for(int i=0;i<V;i++){
			if(!visited[i])	
				if (hasBackedgeHelper(i, visited, inStack))
					return 1;
		}
		return 0;
	}

	int DijkshtraShortPath(int src, int dst){
		set<pair<int,int>> s;
		vector<int> dist(V,INT_MAX);
		dist[src] = 0;
		s.insert({0,src});

		while(!s.empty()){
			auto it = s.begin();
			int node  = it->second;
			int distYet = it->first;
			s.erase(it);

			for(auto nbrPair : lw[node]){
				int nbr = nbrPair.second;
				int curEdge = nbrPair.first;

				int newDist = curEdge + distYet;
				if(dist[nbr] > newDist){
					dist[nbr] = newDist;
					if(s.find({dist[nbr], nbr}) != s.end())
						s.erase({dist[nbr], nbr});

					s.insert({newDist, nbr});
				}
			}
		}

		for(auto elem : dist){
			cout<<elem<<endl;
		}
		return dist[dst];
	}

};

int shortestPath(int s, int d, Graph g){
	unordered_map<int,vector<int>> visited;
	queue<int> q;
	q.push(s);
	visited[s].push_back(s) ;
	while(!q.empty()){
		int n = q.front();
		q.pop();
		for(auto nbr  : g.l[n]){
			if(visited.count(nbr) == 0){
				q.push(nbr);
				visited[nbr] = visited[n];
				visited[nbr].push_back(nbr);
			}
			if(nbr == d)
				return visited[nbr].size() -1;
		}
	}
	return -1;
}

void shortPath(int s, int d, Graph g ){
	queue<int> q;
	bool * visited = new bool[g.V]{0};
	int * distance = new int[g.V]{0};
	int * parent = new int[g.V];
	parent[s] = s;
	distance[s] = 0;

	q.push(s);
	visited[s] = true;

	while(!q.empty()){
		int n = q.front();
		q.pop();
		for(auto nbr  : g.l[n]){
			if(!visited[nbr]){
				q.push(nbr);
				parent[nbr] = n;
				visited[nbr] = true;
				distance[nbr] = distance[n] +1;
			}
		}
	}
	int dist = distance[d];
	cout<<"distance of"<<d<<" from "<<s<<" :"<<dist<<endl;
	int temp = d;
	while(temp!=s){
		cout<<temp<<"<--";
		temp = parent[temp];
	}cout<<s;
}

void snakeNLadder(int n, vector<pair<int,int>> snakes, vector<pair<int,int>> ladder){
	vector<int> board(n+1, 0);

	for(auto sk : snakes){
		int s = sk.first;
		int e = sk.second;
		board[s] = e - s;
	}

	for(auto ld : ladder){
		int s = ld.first;
		int e = ld.second;
		board[s] = e -s;
	}

	Graph g(n+1);
	for(int i=1;i<=n;i++){
		for(int dice = 1;dice<=6;dice++){
			int val = dice + i ;
			val += board[val];

			if(val<= n)
				g.addEdge(i,val);
		}
	}
	shortPath(1,n, g);
}
int main(){
	// vector<string> cities {"London","Paris","Jabalpur","New York"};
	// Graph g(cities);
	// g.addEdge("London","Paris");
	// g.addEdge("London","Jabalpur");
	// g.addEdge("New York","Jabalpur",false);
	// g.printGraph();
	



	// Graph g(7);
	// g.addEdge(0,1);
	// g.addEdge(0,4);
	// g.addEdge(2,1);
	// g.addEdge(3,4);
	// g.addEdge(4,5);
	// g.addEdge(2,3);
	// g.addEdge(3,5);
	// g.addEdge(5,6);
	// g.printGraph();
	// cout<<g.isCyclic(1);	



	// Graph g(7);
	// g.addEdge(0,1);
	// g.addEdge(1,2);
	// g.addEdge(2,4);
	// g.addEdge(2,5);
	// g.addEdge(1,3);
	// g.addEdge(3,6);
	// g.printGraph();
	// cout<<g.isCyclic(1);
	// vector<bool> visited(7, 0);
	// g.recDFS(0,visited);
	// g.DFS(0);



	// g.printGraph();
	// g.BFS(1);
	// g.DFS(1);
	// cout<<g.isCyclic(1);	
	// cout<<"distance :"<<shortestPath(0,5,g );
	// for(auto elem : visited){
	// 	cout<<elem.first<<"--> ";
	// 	for(auto num : elem.second)
	// 		cout<<num<<",";
	// 	cout<<endl;
	// }

	// shortPath(1,5,g);

	// vector<pair<int,int>> snakes{{34,12},{17,4},{20,6},{24,16},{32,30}};
	// vector<pair<int, int>> ladders{	{2,15},{5,7},{9,27},{18,29},{25,35}};

	// snakeNLadder(26 , snakes, ladders);



	// Graph g(6);
	// g.addEdge(0,1,false);
	// g.addEdge(1,2,false);
	// g.addEdge(2,3,false);
	// g.addEdge(3,0,false);
	// g.addEdge(0,4,false);
	// g.addEdge(0,5,false);
	// g.addEdge(5,4,false);
	// g.DFS(0);
	// g.recDFS(0,visited);
	// cout<<g.hasBackedge();


	Graph g(5);
	g.addEdgeWt(0,1,1);
	g.addEdgeWt(1,2,1);
	g.addEdgeWt(0,2,4);
	g.addEdgeWt(0,3,7);
	g.addEdgeWt(3,2,2);
	g.addEdgeWt(3,4,3);
	cout<<g.DijkshtraShortPath(0,4);
}