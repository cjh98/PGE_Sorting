#pragma once

#include "olcPixelGameEngine.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

constexpr size_t LEN = 8;

class Sort
{
public:
	olc::PixelGameEngine* pge;

	int width;
	int height;
	int rectWidth;
	int heightScale;

	int arr[LEN];

	Sort()
	{
		width = pge->ScreenWidth();
		height = pge->ScreenHeight();

		rectWidth = width / LEN;
		heightScale = height / LEN;

		for (int i = 0; i < LEN; i++)
		{
			int val = (rand() % LEN) + 1;
			arr[i] = val;
		}
	}

	void BubbleSort()
	{
		for (int i = 0; i < LEN; i++)
		{
			for (int j = i + 1; j < LEN; j++)
			{
				if (arr[i] > arr[j])
				{
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

		Display();
	}

	void Display()
	{
		std::cout << "DISPLAY\n";
		for (int rect = 0; rect < LEN; rect++)
		{
			int rectHeight = arr[rect] * heightScale;
			olc::vi2d pos = { rect * rectWidth, height - rectHeight };
			olc::vi2d size = { rectWidth, rectHeight };

			//if (rect == j)
			//{
			//	pge->FillRect(pos, size, olc::RED);
			//	pge->DrawRect(pos, size, olc::BLACK);
			//}
			//else if (rect == i)
			//{
			//	pge->FillRect(pos, size, olc::DARK_BLUE);
			//	pge->DrawRect(pos, size, olc::BLACK);
			//}
			//else
			//{
				pge->FillRect(pos, size, olc::GREY);
				pge->DrawRect(pos, size, olc::BLACK);
			//}
		}
	}
};