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

#define iters 150
#define alpha1 0.05
#define alpha2 0.3
#define ncl 4

class Drawer
{
	mt19937 rng;

	int windowX, windowY, sh;

	void scaleCoords();
	void readFiles();

	double getDist(pair<double, double> p1, pair<double, double> p2);

	void initilClusters();
	void findNextClusters(int newPos);

	void makeClustering();

	Text text, text2;
	Font font;

	vector <pair<double, double> > dat;

	Color colors[ncl];

	pair<double, double> centers[iters][ncl];
	vector <int> clusters[iters][ncl];
	
	int currentPos;

	int rngSeed;

	int autoPlay;

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