// Software: Knight's Tour - Back Tracking algorithm and Warnsdorf's rule heuristics
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
#include <fstream>

using namespace std;

int n;
string response;
int label[1000][1000];
int deg[1000][1000];
int DX[] = {1, 2, 2, 1, -1, -2, -2, -1};
int DY[] = {-2, -1, 1, 2, 2, 1, -1, -2};

void output_label(){
	for (int j = 0; j < n; j++){
		cout << label[0][j];
		for (int i = 1; i < n; i++)
			cout << " " << label[i][j];
		cout << endl;
	}
}

void output(){
	cout << "Solution:" << endl;
	output_label();
	
	freopen("Solution.txt", "w", stdout);
	cout << n << endl;
	output_label();
	
	exit(0);
}

void init(){
	int i, j, u, v, t;
	memset(deg, 0, sizeof(deg));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (t = 0; t < 8; t++){
				u = i + DX[t];
				v = j + DY[t];
				if ((u >= 0) && (u < n) && (v >= 0) && (v < n))
					deg[i][j]++;
			}
}

void BackTracking(int number, int i, int j){
	int u, v, t, nChoices;
	int d[8];
	int next[8];
	
	label[i][j] = number;
	
	if (number < n * n){
		nChoices = 0;
		for (t = 0; t < 8; t++){
			u = i + DX[t];
			v = j + DY[t];
			if ((u >= 0) && (u < n) && (v >= 0) && (v < n))
				if (label[u][v] == 0){
					d[nChoices] = deg[u][v];
					next[nChoices] = t;
					nChoices++;
					deg[u][v]--;
				}
		}
		
		for (u = 0; u < nChoices; u++)
			for (v = u + 1; v < nChoices; v++)
				if (d[u] > d[v]){
					swap(d[u], d[v]);
					swap(next[u], next[v]);
				}
		
		for (t = 0; t < nChoices; t++)
			BackTracking(number + 1, i + DX[next[t]], j + DY[next[t]]);
		
		for (t = 0; t < 8; t++){
			u = i + DX[t];
			v = j + DY[t];
			if ((u >= 0) && (u < n) && (v >= 0) && (v < n))
				if (label[u][v] == 0)
					deg[u][v]++;
		}
	}else{
		//Case 1: Only need to find a route
		if ((response[0] == 'r') || (response[0] == 'R')) output();
		
		//Case 2: Need to find a Hamilton circle
		if ((i != 0) && (j != 0))
			if (i + j == 3)
				output();
	}
	
	label[i][j] = 0;
}

int main(){
	cout << "N = ";
	cin >> n;
	cout << "Route or Circle: ";
	cin >> response;
	
	memset(label, 0, sizeof(label));
	init();
	
	if ((response[0] == 'r') || (response[0] == 'R')){
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				BackTracking(1, i, j);
	}else
		BackTracking(1, 0, 0);
	
	cout << "There is no solution." << endl;
}
