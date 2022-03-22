#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <cmath>
#include <math.h>
#include <string>
#include <time.h>
#include <random>
#include <memory.h>
#include <bitset>
using namespace std;
using namespace sf;

class Drawer
{
	mt19937 rnd;

	int windowX, windowY, sh;

	vector <int> unite(vector <int> v1, vector <int> v2);

	void scaleCoords();

	void readFiles();

	Text text, textCluster;
	Font font;

	vector <pair<double, double> > dat;

	vector <vector <vector <int> > > clusters_1;
	vector <vector <Color> > clusterColors_1;
	vector <vector <int> > isConnected_1;

	vector <vector <vector <int> > > clusters_2;
	vector <vector <Color> > clusterColors_2;
	vector <vector <int> > isConnected_2;

	vector <vector <vector <int> > > clusters_3;
	vector <vector <Color> > clusterColors_3;
	vector <vector <int> > isConnected_3;

	vector <vector <vector <int> > > clusters;
	vector <vector <Color> > clusterColors;
	vector <vector <int> > isConnected;
	
	int currentPos;


	Clock clock;
	double timer;

	Event event;


	bool switchEvent(Event event, RenderWindow& window);
	void draw(RenderWindow& window);

	void process(RenderWindow& window);

public:

	Drawer();

	

	void show();

};