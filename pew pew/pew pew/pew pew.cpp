// pew pew.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <chrono>
#include <thread>
#include <functional>
#include "olcConsoleGameEngine.h"
using namespace std;


    class pewpew : public olcConsoleGameEngine
    {
    public:
        pewpew() {
            m_sAppName = L"pewpew";
        }
    private: struct sSpaceObject
    {
        int nSize;
        float x;
        float y;
        float dx;
        float dy;
        float angle;
    };

         
           vector<sSpaceObject> vecBullets;

           sSpaceObject player;
           sSpaceObject enemy;
           bool bIsDed = false;
           int nScore = 0;
           bool bGameRunning = true;
           vector<pair<float, float>> vecModelPlayer;
           vector<pair<float, float>> vecModelEnemy;

    protected : 
        virtual bool OnUserCreate()
        {
            vecModelPlayer =
            {
                {{0.0f, -5.0f},
                {-2.5f, 2.5f},
                {2.5f, 2.5f}
                }

            }; // Simple Isocoles triangle


            vecModelEnemy =
            {
               {{0.0f, -5.0f},
                {-2.5f, 2.5f},
                {2.5f, 2.5f}
                }

            }; // Same shape as the player, just will be a different color


            ResetGame();
            return true;
        };



        void ResetGame() {

            player.x = ScreenWidth() / 2;
            player.y = ScreenHeight() / 2;
            player.dx = 0.0f;
            player.dy = 0.0f;
            player.angle = 0.0f;

            enemy.x = ScreenWidth() / 3;
            enemy.y = ScreenHeight() / 3;
            enemy.dx = 0.0f;
            enemy.dy = 0.0f;
            enemy.angle = 0.0f;
            
           


            
            vecBullets.clear();

           

            bIsDed = false;
            bGameRunning = true;
            nScore = false;

        };

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


        bool OnUserUpdate(float fElapsedTime) override
        {
            if (bIsDed)
                ResetGame();

            Fill(0, 0, ScreenWidth(), ScreenHeight(), BG_BLACK, PIXEL_SOLID);

            if (m_keys[VK_LEFT].bHeld)
                player.angle -= 5.0f;
            if (m_keys[VK_RIGHT].bHeld)
                player.angle += 5.0f;

            if (m_keys[VK_UP].bHeld)
            {
                player.dx += sin(player.angle) * 20.0f * fElapsedTime;
                player.dy += -cos(player.angle) * 20.0f * fElapsedTime;
            }

            player.x += player.dx * fElapsedTime;
            player.y += player.dy * fElapsedTime;
            WrapCoordinates(player.x, player.y, player.x, player.y);



            enemy.angle = (atan(player.x / player.y) + atan(player.y / player.x)) - atan(player.y / player.x);





            if (m_keys[VK_SPACE].bReleased)
                vecBullets.push_back({ 0, player.x, player.y, 50.0f * sinf(player.angle), 50.0f * -cosf(player.angle), 100.0f });


            while ()
            {
                vecBullets.push_back({ 0, enemy.x, enemy.y, 50.0f * sinf(enemy.angle), 50.0f * -cosf(enemy.angle), 100.0f });
               

            }
            
            

            for (auto& b : vecBullets)
            {
                b.x += b.dx * fElapsedTime;
                b.y += b.dy * fElapsedTime;
                WrapCoordinates(b.x, b.y, b.x, b.y);
                b.angle -= 1.0f * fElapsedTime;
            }

            for (auto b : vecBullets)
                Draw(b.x, b.y);


            DrawWireFrameModel(vecModelPlayer, player.x, player.y, player.angle);
            DrawWireFrameModel(vecModelEnemy, enemy.x, enemy.y, enemy.angle);


            

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









    int main()
    {
       
        pewpew demo;
        if (demo.ConstructConsole(256, 240, 2, 2))
            demo.Start();
        return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
