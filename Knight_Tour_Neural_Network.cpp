// Software: Knight's Tour - Neural Network
// Author: Hy Truong Son
// Major: BSc. Computer Science
// Class: 2013 - 2016
// Institution: Eotvos Lorand University
// Email: sonpascal93@gmail.com
// Website: http://people.inf.elte.hu/hytruongson/
// Copyright 2015 (c) Hy Truong Son. All rights reserved.

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>

#define Max_size 100
#define Max_nNeurons 8 * Max_size * Max_size
#define Max_nIterations 20000

using namespace std;

int size, nNeurons, nIterations;
vector<int> cell[Max_size][Max_size];
vector< pair<int, int> > adj[Max_size][Max_size];
int degree[Max_size][Max_size];
int label[Max_size][Max_size];

struct Neuron_Info {
	int x1, y1, x2, y2;
	int state, output;
	vector<int> adj;
};
Neuron_Info Neuron[Max_nNeurons];
int next_state[Max_nNeurons];
int next_output[Max_nNeurons];

int DX[] = {1, 2, 2, 1, -1, -2, -2, -1};
int DY[] = {-2, -1, 1, 2, 2, 1, -1, -2};

bool Final_Check;

void init(){
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cell[i][j].clear();
	
	nNeurons = 0;
	for (int x1 = 0; x1 < size; x1++)
		for (int y1 = 0; y1 < size; y1++){
			int i = x1 + y1 * size;
			
			for (int t = 0; t < 8; t++){
				int x2 = x1 + DX[t];
				int y2 = y1 + DY[t];
				
				if ((x2 >= 0) && (x2 < size) && (y2 >= 0) && (y2 < size)){
					int j = x2 + y2 * size;
					
					if (i < j){
						cell[x1][y1].push_back(nNeurons);
						cell[x2][y2].push_back(nNeurons);
						
						Neuron[nNeurons].x1 = x1;
						Neuron[nNeurons].y1 = y1;
						Neuron[nNeurons].x2 = x2;
						Neuron[nNeurons].y2 = y2;
						nNeurons++;
					}
				}
			}
		}
		
	for (int i = 0; i < nNeurons; i++) 
		Neuron[i].adj.clear();
	
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			for (int u = 0; u < cell[x][y].size(); u++){
				int i = cell[x][y][u];
				
				for (int v = u + 1; v < cell[x][y].size(); v++){
					int j = cell[x][y][v];
					
					Neuron[i].adj.push_back(j);
					Neuron[j].adj.push_back(i);
				}
			}
}

void randomize_neurons_output(){
	for (int i = 0; i < nNeurons; i++){
		Neuron[i].state = 0;
		Neuron[i].output = rand() % 2;
	}
}

void calculate_next_generation(){
	for (int i = 0; i < nNeurons; i++){
		next_state[i] = Neuron[i].state + 4 - Neuron[i].output;
		for (int j = 0; j < Neuron[i].adj.size(); j++){
			int v = Neuron[i].adj[j];
			next_state[i] -= Neuron[v].output;
		}
		
		if (next_state[i] < 0) next_output[i] = 0; else
			if (next_state[i] > 3) next_output[i] = 1; else
				next_output[i] = Neuron[i].output;
	}
}

pair<int, int> change_neurons(){
	int nChanges = 0, nActive = 0;
	
	for (int i = 0; i < nNeurons; i++){
		if (next_state[i] != Neuron[i].state)
			nChanges++;
			
		Neuron[i].state = next_state[i];
		Neuron[i].output = next_output[i];
		
		nActive += Neuron[i].output;
	}
	
	return make_pair(nChanges, nActive);
}

bool check_degree(){
	memset(degree, 0, sizeof(degree));
	for (int i = 0; i < nNeurons; i++)
		if (Neuron[i].output == 1){
			degree[Neuron[i].x1][Neuron[i].y1]++;
			degree[Neuron[i].x2][Neuron[i].y2]++;
		}
		
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (degree[i][j] != 2) return false;
	
	return true;
}

void visit(int i, int j, int count){
	label[i][j] = count;
	
	if (count == size * size)
		if (i * j != 2) Final_Check = false;
	
	for (int t = 0; t < adj[i][j].size(); t++){
		int u = adj[i][j][t].first;
		int v = adj[i][j][t].second;
		
		if (label[u][v] == 0){
			visit(u, v, count + 1);
			return;
		}
	}
}

int check_connection(){
	memset(label, 0, sizeof(label));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			adj[i][j].clear();
			
	for (int i = 0; i < nNeurons; i++)
		if (Neuron[i].output == 1){
			int x1 = Neuron[i].x1;
			int y1 = Neuron[i].y1;
			int x2 = Neuron[i].x2;
			int y2 = Neuron[i].y2;
			
			adj[x1][y1].push_back(make_pair(x2, y2));
			adj[x2][y2].push_back(make_pair(x1, y1));
		}
	
	Final_Check = true;
	int nComponents = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (label[i][j] == 0){
				nComponents++;
				visit(i, j, 1);
			}
			
	return nComponents;
}

void Write_Solution(){
	freopen("Solution.txt", "w", stdout);
	cout << size << endl;
	for (int j = 0; j < size; j++){
		cout << label[0][j];
		for (int i = 1; i < size; i++)
			cout << " " << label[i][j];
		cout << endl;
	}
}

void process(){
	bool even = false;
	int nTimes = 0;
	
	while (true){
		nTimes++;
		cout << endl << "Time " << nTimes << ":" << endl;
		
		randomize_neurons_output();
		
		cout << "Local Optimization." << endl;
		nIterations = 0;
		while (true){
			calculate_next_generation();
			pair<int, int> info = change_neurons();
			int nChanges = info.first;
			int nActive = info.second;
			
			if (nChanges == 0) break;
			if (check_degree()){
				even = true;
				break;
			}
		
			nIterations++;
			if (nIterations == Max_nIterations) break;
		}
		
		if (even){
			cout << "All original cell have degree 2." << endl;
			
			int nComponents = check_connection();
			cout << "Number of connected components: " << nComponents << endl;
			
			if (nComponents == 1)
				if (Final_Check){
					cout << "\nSolution is found!" << endl;
					Write_Solution();
					break;
				}else
					cout << "The solution cannot pass the final check." << endl;
		}
	}
}

int main(){
	srand(time(0));
	cout << "The size of chessboard: ";
	cin >> size;
	
	init();
	process();
}
