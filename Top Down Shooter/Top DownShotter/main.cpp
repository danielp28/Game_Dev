#include <iostream>
#include <string>
#include <algorithm>
#include "olcConsoleGameEngine.h"
using namespace std;


class olcEngine3D : public olcConsoleGameEngine
{
public:
	olcEngine3D()
	{
		m_sAppName = L"Top Down Shooter";
	}

private:
	struct Player
	{
		int nSize;
		float x;
		float y;
		float dx;
		float dy;
		float angle;
	};
	
	vector<Player> vecAsteroids;
	vector<Player> vecBullets;

	Player player;
	bool bDead = false;
	int nScore = 0;

	vector<pair<float, float>> vecModelShip;
	vector<pair<float, float>> vecModelAsteroid;


protected:
	virtual bool OnUserCreate() 
	{
		//Draw player
	vecModelShip =
	{
		{0.0f, -5.0f},
		{-2.5f, 2.5f},
		{2.5f, 2.5f}
	}; // Simple Isoceles triangle

	//Creating "jagged" circle for asteriods. We are checking collision against a perfect 
	//circle so they must be close
	int verts = 20;
	for (int i = 0; i < verts; i++)
	{
		float noise = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;
		vecModelAsteroid.push_back(make_pair(noise * sinf(((float)i / (float)verts) * 6.28318f),
			noise * cosf(((float)i / (float)verts) * 6.28318f)));
	}
	ResetGame();


		return true;
	}

	void ResetGame()
	{
		player.x = ScreenWidth() / 2.0f;
		player.y = ScreenHeight() / 2.0f;
		player.dx = 0.0f;
		player.dy = 0.f;
		player.angle = 0.0f;

		vecBullets.clear();
		vecAsteroids.clear();


		//Put in two asteroids
		vecAsteroids.push_back({ (int)16, 20.0f, 20.0f, 8.0f, -6.0f, 0.0f });
		vecAsteroids.push_back({ (int)16, 100.0f, 20.0f, -5.0f, 3.0f, 0.0f });


		//Reset Game States
		bDead = false;
		nScore = false;
	}



	//Implements to wrap around various in game systems
	void WrapCoordinates(float ix, float iy, float& ox, float& oy)
	{
		ox = ix;
		oy = iy;
		if (ix < 0.0f) ox = ix + (float)ScreenWidth();
		if (ix >= (float)ScreenWidth()) ox = ix - (float)ScreenWidth();
		if (iy < 0.0f) oy = iy + (float)ScreenHeight();
		if (iy >= (float)ScreenHeight()) oy = iy - (float)ScreenHeight();
	}

	//Overriden to handle toroidal drawing routines
	virtual void Draw(int x, int y, wchar_t c = 0x2588, short col = 0x00F)
	{
		float fx, fy;
		WrapCoordinates(x, y, fx, fy);
		olcConsoleGameEngine::Draw(fx, fy, c, col);
	}


	//Checking for collision
	bool IsPointInsideCirle(float cx, float cy, float radius, float x, float y)
	{
		return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		if (bDead)
			ResetGame();
		//Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		//Steering ship
		if (m_keys[VK_LEFT].bHeld)
			player.angle -= 5.0f * fElapsedTime;
		if (m_keys[VK_RIGHT].bHeld)
			player.angle += 5.0f * fElapsedTime;

		//Thrust? Apply ACCELERATION
		if (m_keys[VK_UP].bHeld)
		{
			//ACCELERATION changes VELOCITY with respect to time
			player.dx += sin(player.angle) * 20.0f * fElapsedTime;
			player.dy += -cos(player.angle) * 20.0f * fElapsedTime;
		}

		//VELOCITY changes POSITION (with respect to time)
		player.x += player.dx * fElapsedTime;
		player.y += player.dy * fElapsedTime;

		//Keep Player in gamespace
		WrapCoordinates(player.x, player.y, player.x, player.y);


		//Check player collision with asteroids
		for (auto& a : vecAsteroids)
			if (IsPointInsideCirle(a.x, a.y, a.nSize, player.x, player.y))
				bDead = true; //YOU SUCK
			
		// Fire bullet in direction player is facing
		if (m_keys[VK_SPACE].bReleased)
			vecBullets.push_back({ 0, player.x, player.y, 50.0f * sinf(player.angle), -50.0f * cosf(player.angle), 100.0f });


		//Update and Draw Asteroids
		for (auto& a : vecAsteroids)
		{
			//VELOCITY changes POSITION (with respect to time)
			a.x += a.dx * fElapsedTime;
			a.y += a.dy * fElapsedTime;
			a.angle += 0.5f + fElapsedTime; 

			WrapCoordinates(a.x, a.y, a.x, a.y);

			//Draw Asteroids
			DrawWireFrameModel(vecModelAsteroid, a.x, a.y, a.angle, (float)a.nSize, FG_YELLOW);
		}


		// Any new asteroids created after collision detection are stored
		// in a temporary vector, so we don't interfere with the asteroids
		// vector iterator in the for(auto)

		vector<Player> newAsteroids;

		//Update Bullets
		for (auto& b : vecBullets)
		{
			b.x += b.dx * fElapsedTime;
			b.y += b.dy * fElapsedTime;
			WrapCoordinates(b.x, b.y, b.x, b.y);
			b.angle -= 1.0f * fElapsedTime;

			//Check for collision w asteriods using a nested for loop
			for (auto& a : vecAsteroids)
			{
				if (IsPointInsideCirle(a.x, a.y, a.nSize, b.x, b.y))
				{
					//Asteroid hit - remove bullet
					b.x = -100;

					//Create Child asteroids
					if (a.nSize > 4)
					{
						float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						newAsteroids.push_back({ (int)a.nSize >> 1, a.x, a.y, 10.0f * sinf(angle1), 10.0f * cosf(angle1), 0.0f });
						newAsteroids.push_back({ (int)a.nSize >> 1, a.x, a.y, 10.0f * sinf(angle2), 10.0f * cosf(angle2), 0.0f });

					}

					//Remove Asteroid - Same approach as bullets, just send it off the screen
					a.x = -100;
					nScore += 100;
				}
			}

		}


		//Append new ASSteroids to existing vector
		for (auto a : newAsteroids)
			vecAsteroids.push_back(a);


		//CLear Dead Objects

		//Remove asteroids if they have been blown up
		if (vecAsteroids.size() > 0)
		{
			auto i = remove_if(vecAsteroids.begin(), vecAsteroids.end(), [&](Player o) {return (o.x < 0); });
			if (i != vecAsteroids.end())
				vecAsteroids.erase(i);
		}

		if (vecAsteroids.empty()) //no more asteroids? YOu win
		{
			//Level Clear
			nScore += 1000;
			vecAsteroids.clear();
			vecBullets.clear();


			// Add two new asteroids, but in a place where the player is not, we'll simply
			// add them 90 degrees left and right to the player, their coordinates will
			// be wrapped by th enext asteroid update

			vecAsteroids.push_back({ (int)16, 30.0f * sinf(player.angle - 3.14159f / 2.0f) + player.x,
											  30.0f * cosf(player.angle - 3.14159f / 2.0f) + player.y,
											  10.0f * sinf(player.angle), 10.0f * cosf(player.angle), 0.0f });

			vecAsteroids.push_back({ (int)16, 30.0f * sinf(player.angle + 3.14159f / 2.0f) + player.x,
											  30.0f * cosf(player.angle + 3.14159f / 2.0f) + player.y,
											  10.0f * sinf(-player.angle), 10.0f * cosf(-player.angle), 0.0f });
		}

		//Remove Bullets that have gone off screen
		for (auto b : vecBullets)
			Draw(b.x, b.y);
		//Draw ship
		DrawWireFrameModel(vecModelShip, player.x, player.y, player.angle);

		//Draw Score
		DrawString(2, 2, L"SCORE: " + to_wstring(nScore));

		return true;

	}


	void DrawWireFrameModel(const vector<pair<float, float>>& vecModelCoordinates, float x, float y, float r = 0.0f, float s = 1.0f, short col = FG_WHITE)
	{
		

		// Create translated model vector of coordinate pairs
		vector<pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);

		// Rotate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}

		// Scale
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
		}

		// Translate
		for (int i = 0; i < verts; i++)
		{
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++)
		{
			int j = (i + 1);
			DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second,
				vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, PIXEL_SOLID, col);
		}
	}
};






int main() {


	olcEngine3D demo;
	if (demo.ConstructConsole(256, 240, 2, 2))
		demo.Start();

	
	return 0;
}