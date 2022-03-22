#include "Drawer.h"

vector <int> Drawer::unite(vector <int> v1, vector <int> v2)
{
	vector <int> res;

	for (auto it : v1)
	{
		res.push_back(it);
	}

	for (auto it : v2)
	{
		res.push_back(it);
	}

	return res;
}

void Drawer::scaleCoords()
{
	double sizeX = windowX - 2.0 * sh;
	double sizeY = windowY - 2.0 * sh;

	double minX = dat[0].first, minY = dat[0].second, maxX = dat[0].first, maxY = dat[0].second;
	double scaleX, scaleY;

	for (auto it : dat)
	{
		minX = min(minX, it.first);
		minY = min(minY, it.second);
		maxX = max(maxX, it.first);
		maxY = max(maxY, it.second);
	}

	scaleX = sizeX / (maxX - minX);
	scaleY = sizeY / (maxY - minY);

	for (auto& it : dat)
	{
		it.first = (it.first - minX) * scaleX + sh;
		it.second = (it.second - minY) * scaleY + sh;
	}
}

void Drawer::readFiles()
{
	ifstream datF("PCA.csv");

	int pcaN;
	datF >> pcaN;
	for (int i = 0; i < pcaN; i++)
	{
		double x, y;

		datF >> x >> y;
		dat.push_back({ x, -y });
	}
	
	scaleCoords();

	datF.close();

	// read1
	{
		ifstream fh1("1.txt");

		int n1;
		fh1 >> n1;

		clusters_1.resize(n1 + 1);
		clusterColors_1.resize(n1 + 1);
		isConnected_1.resize(n1 + 1);

		vector < vector <int> > tmp1;
		vector <Color> color1;
		for (int i = 0; i < dat.size(); i++)
		{
			tmp1.push_back(vector <int>());
			tmp1.back().push_back(i);

			color1.push_back(Color(30 + rnd() % 196, 30 + rnd() % 196, 30 + rnd() % 196));
		}

		clusters_1[n1] = tmp1;
		clusterColors_1[n1] = color1;
		isConnected_1[n1] = vector <int>(color1.size(), 0);

		for (int i = 0; i < n1; i++)
		{
			int a, b;

			fh1 >> a >> b;

			if (a > b)
			{
				swap(a, b);
			}

			if (tmp1[a].size() < tmp1[b].size())
			{
				color1[a] = color1[b];
			}

			tmp1[a] = unite(tmp1[a], tmp1[b]);
			tmp1.erase(tmp1.begin() + b);
			color1.erase(color1.begin() + b);

			clusters_1[n1 - i - 1] = tmp1;
			clusterColors_1[n1 - i - 1] = color1;
			isConnected_1[n1 - i - 1] = vector<int>(color1.size(), 0);
			isConnected_1[n1 - i][a] = 1;
			isConnected_1[n1 - i][b] = 1;
		}

		fh1.close();
	}

	// read2
	{
		ifstream fh1("2.txt");

		int n1;
		fh1 >> n1;

		clusters_2.resize(n1 + 1);
		clusterColors_2.resize(n1 + 1);
		isConnected_2.resize(n1 + 1);

		vector < vector <int> > tmp1;
		vector <Color> color1;
		for (int i = 0; i < dat.size(); i++)
		{
			tmp1.push_back(vector <int>());
			tmp1.back().push_back(i);

			color1.push_back(Color(30 + rnd() % 196, 30 + rnd() % 196, 30 + rnd() % 196));
		}

		clusters_2[n1] = tmp1;
		clusterColors_2[n1] = color1;
		isConnected_2[n1] = vector <int>(color1.size(), 0);

		for (int i = 0; i < n1; i++)
		{
			int a, b;

			fh1 >> a >> b;

			if (a > b)
			{
				swap(a, b);
			}

			if (tmp1[a].size() < tmp1[b].size())
			{
				color1[a] = color1[b];
			}

			tmp1[a] = unite(tmp1[a], tmp1[b]);
			tmp1.erase(tmp1.begin() + b);
			color1.erase(color1.begin() + b);

			clusters_2[n1 - i - 1] = tmp1;
			clusterColors_2[n1 - i - 1] = color1;
			isConnected_2[n1 - i - 1] = vector<int>(color1.size(), 0);
			isConnected_2[n1 - i][a] = 1;
			isConnected_2[n1 - i][b] = 1;
		}

		fh1.close();
	}

	// read3
	{
		ifstream fh1("3.txt");

		int n1;
		fh1 >> n1;

		clusters_3.resize(n1 + 1);
		clusterColors_3.resize(n1 + 1);
		isConnected_3.resize(n1 + 1);

		vector < vector <int> > tmp1;
		vector <Color> color1;
		for (int i = 0; i < dat.size(); i++)
		{
			tmp1.push_back(vector <int>());
			tmp1.back().push_back(i);

			color1.push_back(Color(30 + rnd() % 196, 30 + rnd() % 196, 30 + rnd() % 196));
		}

		clusters_3[n1] = tmp1;
		clusterColors_3[n1] = color1;
		isConnected_3[n1] = vector <int>(color1.size(), 0);

		for (int i = 0; i < n1; i++)
		{
			int a, b;

			fh1 >> a >> b;

			if (a > b)
			{
				swap(a, b);
			}

			if (tmp1[a].size() < tmp1[b].size())
			{
				color1[a] = color1[b];
			}

			tmp1[a] = unite(tmp1[a], tmp1[b]);
			tmp1.erase(tmp1.begin() + b);
			color1.erase(color1.begin() + b);

			clusters_3[n1 - i - 1] = tmp1;
			clusterColors_3[n1 - i - 1] = color1;
			isConnected_3[n1 - i - 1] = vector<int>(color1.size(), 0);
			isConnected_3[n1 - i][a] = 1;
			isConnected_3[n1 - i][b] = 1;
		}

		fh1.close();
	}
}

Drawer::Drawer() : rnd(1)
{
	windowX = 1600;
	windowY = 800;
	sh = 50;

	readFiles();

	clusters = clusters_1;
	clusterColors = clusterColors_1;
	isConnected = isConnected_1;

	timer = 0;
	currentPos = 0;

	font.loadFromFile("font.ttf");

	text.setFont(font);
	text.setString("Centroid Linkage Clustering\n(distance between centroids)");
	text.setCharacterSize(40);
	text.setFillColor(Color::Black);
	text.setPosition(Vector2f(20, 20));

	textCluster.setFont(font);
	textCluster.setString("Number of clusters = " + to_string(currentPos + 1));
	textCluster.setCharacterSize(40);
	textCluster.setFillColor(Color::Black);
	textCluster.setPosition(Vector2f(1120, 20));
}


bool Drawer::switchEvent(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		return false;
	}
	
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Num1)
		{
			clusters = clusters_1;
			clusterColors = clusterColors_1;
			isConnected = isConnected_1;

			text.setString("Centroid Linkage Clustering\n(distance between centroids)");
		}

		if (event.key.code == Keyboard::Num2)
		{
			clusters = clusters_2;
			clusterColors = clusterColors_2;
			isConnected = isConnected_2;

			text.setString("Complete-Linkage Clustering\n(max distance)");
		}

		if (event.key.code == Keyboard::Num3)
		{
			clusters = clusters_3;
			clusterColors = clusterColors_3;
			isConnected = isConnected_3;

			text.setString("Single-Linkage Clustering\n(min distance)");
		}
	}

	if (event.type == sf::Event::MouseWheelMoved)
	{
		currentPos += event.mouseWheel.delta;

		if (currentPos < 0)
		{
			currentPos = 0;
		}

		if (currentPos >= clusters.size())
		{
			currentPos = clusters.size() - 1;
		}
	}



	return true;
}

void Drawer::draw(RenderWindow& window)
{
	window.clear(Color::White);

	int ii = 0;
	for (auto _clusters : clusters[currentPos])
	{
		Color c = clusterColors[currentPos][ii];
		int connected = isConnected[currentPos][ii];

		for (auto _ind : _clusters)
		{
			CircleShape circle;
			circle.setPosition(Vector2f(dat[_ind].first, dat[_ind].second));
			circle.setRadius(10);
			circle.setFillColor(c);

			if (connected)
			{
				circle.setOutlineColor(Color::Black);
				circle.setOutlineThickness(4);
			}

			window.draw(circle);
		}

		ii++;
	}

	window.draw(text);

	textCluster.setString("Number of clusters = " + to_string(currentPos + 1));
	window.draw(textCluster);

	window.display();
}

void Drawer::process(RenderWindow& window)
{
	while (window.isOpen())
	{
		timer += clock.getElapsedTime().asMicroseconds() / 1000.0;
		clock.restart();

		if (window.pollEvent(event))
		{
			if (!switchEvent(event, window))
			{
				window.close();
			}
		}

		if (timer > 50.0)
		{
			draw(window);

			timer = 0.0;
		}
	}
}

void Drawer::show()
{
	RenderWindow window(VideoMode(windowX, windowY), "Drawer");

	window.setKeyRepeatEnabled(0);

	process(window);
}