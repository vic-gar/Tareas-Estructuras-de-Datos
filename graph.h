#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;

public:
		Graph(int);
		Graph();
		void addEdgeAdjList(int, int);
		void addEdgeAdjMatrix(int, int);
		string printAdjList();
		string printAdjMat();
		string printAdjMat_clean();
		string DFS(int, int);
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);
		string BFS(int, int);
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);
		string print_visited(list<int>);
		string print_path(vector<vector<int>>&,int ,int);
		bool contains(list<int>, int);
		void sortAdjList();
		void loadGraphList(string, int);
		void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string input, int a){
	adjList = new vector<int>[a];
    nodes = a;
    int u, v;

    for (size_t i = 0; i + 4 < input.length(); i++){
        if (input[i] == '('){
            u = input[i+1] - '0';
            v = input[i+3] - '0';
            addEdgeAdjList(u, v);
        }
    }

    sortAdjList();
}

void Graph::loadGraphMat(string input, int a, int b){
	adjMatrix = new int[a*b];
    nodes = a;

    for (int i = 0; i < a*b; i++)
        adjMatrix[i] = 0;

    int u, v;
    for (size_t i = 0; i + 4 < input.length(); i++){
        if (input[i] == '('){
            u = input[i+1] - '0';
            v = input[i+3] - '0';
            addEdgeAdjMatrix(u, v);
        }
    }
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

string Graph::DFS(int start, int goal){
    if (start == goal) {
        stringstream aux;
        aux << "visited: " << start << " path: " << start;
        return aux.str();
    }

	stack<int> st;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1,-1));

	st.push(start);
	string ans = depthHelper(start, goal, st, visited, paths);

    if (ans == "Node not found") {
        return ans;
    }

	ans = ans + print_path(paths, start, goal);
	return ans;
}

string Graph::depthHelper(int current, int goal, stack<int> &st, list<int> &visited, vector<vector<int>> &paths){
	if (st.empty()){
		return "Node not found";
	} else {
		current = st.top();
		st.pop();
		visited.push_back(current);

        if (current == goal){
            return print_visited(visited);
        }

		for(int i = 0; i < adjList[current].size(); i++){
            int nxt = adjList[current][i];
			if(!contains(visited, nxt)){
				st.push(nxt);
				paths[nxt][0] = current;
			}
		}

		return depthHelper(current, goal, st, visited, paths);
	}
}

string Graph::BFS(int start, int goal){
    if (start == goal) {
        stringstream aux;
        aux << "visited: " << start << " path: " << start;
        return aux.str();
    }

	queue<int> qu;
	list<int> visited;
	vector<vector<int>> paths(nodes, vector<int>(1,-1));

	qu.push(start);
    paths[start][0] = start;

	string ans = breadthHelper(start, goal, qu, visited, paths);

	if (ans == "Node not found") {
        return ans;
    }

    ans = ans + print_path(paths, start, goal);
	return ans;
}


string Graph::breadthHelper(int current, int goal, queue<int> &qu, list<int> &visited, vector<vector<int>> &paths){
	if (qu.empty()){
		return "Node not found";
	} else {
		current = qu.front();
		qu.pop();
		visited.push_back(current);

        if (current == goal){
            return print_visited(visited);
        }

		for(int i = 0; i < adjList[current].size(); i++){
            int nxt = adjList[current][i];
			if(paths[nxt][0] == -1 && nxt != current){
				qu.push(nxt);
				paths[nxt][0] = current;
			}
		}

		return breadthHelper(current, goal, qu, visited, paths);
	}
}


bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}

string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
    aux << q.front() << " ";
    q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		aux << " " << reverse.top() ;
		reverse.pop();
  }
	return aux.str();
}
#endif

