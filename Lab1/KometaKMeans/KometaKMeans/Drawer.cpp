#include "Drawer.h"

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
	ifstream datF("data.txt");

	double x, y;

	while(datF >> x >> y)
	{
		dat.push_back({ x, -y });
	}

	datF.close();
	
	scaleCoords();
}

double Drawer::getDist(pair<double, double> p1, pair<double, double> p2)
{
	double dx = p1.first - p2.first;
	double dy = p1.second - p2.second;

	return sqrt(dx * dx + dy * dy);
}

void Drawer::initilClusters()
{
	set <int> s_centers;

	while (s_centers.size() < ncl)
	{
		s_centers.insert(rng() % dat.size());
	}

	int i = 0;
	for (auto it : s_centers)
	{
		centers[0][i] = dat[it];
		i++;
	}

	for (int i = 0; i < dat.size(); i++)
	{
		int myCenter;
		double d = 1e10;

		for (int j = 0; j < ncl; j++)
		{
			double tD = getDist(centers[0][j], dat[i]);

			if (tD < d)
			{
				d = tD;
				myCenter = j;
			}
		}

		clusters[0][myCenter].push_back(i);
	}
}

void Drawer::findNextClusters(int newPos)
{
	for (int i = 0; i < ncl; i++)
	{
		pair<double, double> newC = { 0.0, 0.0 };

		for (auto it : clusters[newPos - 1][i])
		{
			newC.first += dat[it].first;
			newC.second += dat[it].second;
		}

		newC.first /= clusters[newPos - 1][i].size();
		newC.second /= clusters[newPos - 1][i].size();

		double beta = double(newPos) / iters;
		double alpha = alpha1 * (1.0 - beta) + alpha2 * beta;

		centers[newPos][i].first = centers[newPos - 1][i].first * (1.0 - alpha) + newC.first * alpha;
		centers[newPos][i].second = centers[newPos - 1][i].second * (1.0 - alpha) + newC.second * alpha;
	}

	for (int i = 0; i < dat.size(); i++)
	{
		int myCenter;
		double d = 1e10;

		for (int j = 0; j < ncl; j++)
		{
			double tD = getDist(centers[newPos][j], dat[i]);

			if (tD < d)
			{
				d = tD;
				myCenter = j;
			}
		}

		clusters[newPos][myCenter].push_back(i);
	}
}

void Drawer::makeClustering()
{
	rng.seed(rngSeed);

	for (auto& it : clusters)
	{
		for (auto& itt : it)
		{
			itt.clear();
		}
	}

	initilClusters();

	for (int i = 1; i < iters; i++)
	{
		findNextClusters(i);
	}

	rngSeed++;
}

Drawer::Drawer() : rngSeed(0), autoPlay(0)
{
	windowX = 1900;
	windowY = 1000;
	sh = 50;

	readFiles();

	colors[0] = Color(255, 0, 0);
	colors[1] = Color(0, 255, 0);
	colors[2] = Color(0, 0, 255);
	colors[3] = Color(200, 30, 200);

	makeClustering();

	timer = 0;
	currentPos = 0;

	font.loadFromFile("font.ttf");

	text.setFont(font);
	text.setString("Iteration " + to_string(currentPos));
	text.setCharacterSize(40);
	text.setFillColor(Color::Black);
	text.setPosition(Vector2f(20, 20));

	text2.setFont(font);
	text2.setString("rngSeed = " + to_string(rngSeed));
	text2.setCharacterSize(40);
	text2.setFillColor(Color::Black);
	text2.setPosition(Vector2f(1200, 20));
}

bool Drawer::switchEvent(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		return false;
	}

	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::N)
		{
			currentPos = 0;
			makeClustering();
		}

		if (event.key.code == Keyboard::P)
		{
			autoPlay ^= 1;
		}
	}

	if (event.type == sf::Event::MouseWheelMoved)
	{
		currentPos += event.mouseWheel.delta;

		if (currentPos < 0)
		{
			currentPos = 0;
		}

		if (currentPos >= iters)
		{
			currentPos = iters - 1;
		}
	}

	return true;
}

void Drawer::draw(RenderWindow& window)
{
	const double r = 6.0;
	const double R = 14;

	window.clear(Color::White);

	int ii = 0;
	for (auto cluster : clusters[currentPos])
	{
		Color c = colors[ii];

		for (auto _ind : cluster)
		{
			CircleShape circle;
			circle.setPosition(Vector2f(dat[_ind].first - r / 2.0, dat[_ind].second - r / 2.0));
			circle.setRadius(r);
			circle.setFillColor(c);

			window.draw(circle);
		}

		RectangleShape rect;
		pair<double, double> cen = centers[currentPos][ii];
		rect.setOrigin(R / 2, R / 2);
		rect.setPosition(Vector2f(cen.first - R / 2.0, cen.second - R / 2.0));
		rect.setSize(Vector2f(R, R));
		rect.setFillColor(c);
		rect.setOutlineColor(Color::Black);
		rect.setOutlineThickness(7);
		rect.setRotation(45);

		window.draw(rect);

		ii++;
	}

	text.setString("Iteration " + to_string(currentPos));
	window.draw(text);

	text2.setString("rngSeed = " + to_string(rngSeed));
	window.draw(text2);

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

		if (timer > 40.0)
		{
			if (autoPlay == 1)
			{
				currentPos = min(currentPos + 1, iters - 1);
			}

			draw(window);

			timer = 0.0;
		}
	}
}

void Drawer::show()
{
	RenderWindow window(VideoMode(windowX, windowY), "Drawer");

	window.setPosition(Vector2i(0, 0));

	window.setKeyRepeatEnabled(0);

	process(window);
}