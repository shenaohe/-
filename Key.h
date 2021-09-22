#pragma once
#include<iostream>
#include"Hash.h"
#include"Graph.h"
#include<fstream>
using namespace std;
extern struct EHash;
//extern struct Verxx;
extern HashTable<EHash> KEY;
//extern HashTable<Verxx> HH;
extern Graphic G;
//struct Verxx {
//	int key;
//	int x;
//	int y;
//	Verxx() { key = 0; x = y = 0;}
//	Verxx(int key, int a, int b) :key(key), x(a), y(b){}
//};
void init();
int findkey(int v1, int v2);
void Initialization(Graphic& G);


