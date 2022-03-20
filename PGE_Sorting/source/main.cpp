#define OLC_PGE_APPLICATION

constexpr size_t LEN = 16;

#include "olcPixelGameEngine.h"
//#include "sorting.h"

#include <future>
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int width;
int height;
int rectWidth;
int heightScale;

bool started = false;

int arr[LEN];

class SortingDemo : public olc::PixelGameEngine
{
public:
	std::thread sortThread;

	SortingDemo()
	{
		sAppName = "Clicker";
	}

public:
	bool OnUserCreate() override
	{
		width = ScreenWidth();
		height = ScreenHeight();

		rectWidth = width / LEN;
		heightScale = height / LEN;

		for (int i = 0; i < LEN; i++)
		{
			int val = (rand() % LEN) + 1;
			arr[i] = val;
		}

		sortThread = std::thread(&SortingDemo::BubbleSort, this);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_GREY);

		Display();

		if (!started)
			sortThread.join();

		return true;
	}

	void BubbleSort()
	{
		started = true;
		for (int i = 0; i < LEN; i++)
		{
			for (int j = i + 1; j < LEN; j++)
			{
				if (arr[i] > arr[j])
				{
					sleep_for(100ms);
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

		sortThread.detach();
	}

	void Display()
	{
		for (int rect = 0; rect < LEN; rect++)
		{
			int rectHeight = arr[rect] * heightScale;
			olc::vi2d pos = { rect * rectWidth, height - rectHeight };
			olc::vi2d size = { rectWidth, rectHeight };

			FillRect(pos, size, olc::GREY);
			DrawRect(pos, size, olc::BLACK);
		}
	}
};

int main()
{
	SortingDemo demo;
	if (demo.Construct(1280, 720, 1, 1, false, true, false))
		demo.Start();

	return 0;
}