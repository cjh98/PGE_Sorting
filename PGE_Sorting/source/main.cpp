#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <future>
#include <chrono>
#include <thread>

constexpr size_t LEN = 64;

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

class SortingDemo : public olc::PixelGameEngine
{
public:
	std::thread sortThread;
	int width;
	int height;
	int rectWidth;
	int heightScale;

	bool started = false;
	bool finished = false;

	int arr[LEN];

	int selected = 0;

	SortingDemo()
	{
		sAppName = "Clicker";
	}

	~SortingDemo()
	{
		if (!finished)
			sortThread.detach();
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

		sortThread = std::thread(&SortingDemo::CombSort, this);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_GREY);

		Display();

		if (!started)
		{
			sortThread.join();
		}

		return true;
	}

	void BubbleSort()
	{
		started = true;
		for (int i = 0; i < LEN; i++)
		{
			selected = i;
			for (int j = i + 1; j < LEN; j++)
			{
				if (arr[i] > arr[j])
				{
					sleep_for(25ms);
					int temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}

		finished = true;
		sortThread.detach();
	}

	void SelectionSort()
	{
		started = true;
		for (int i = 0; i < LEN - 1; i++)
		{
			int min = i;
			for (int j = i + 1; j < LEN; j++)
			{
				if (arr[j] < arr[min])
				{
					min = j;
				}
			}

			if (min != i)
			{
				selected = i;
				sleep_for(25ms);
				int temp = arr[i];
				arr[i] = arr[min];
				arr[min] = temp;
			}
		}

		finished = true;
		sortThread.detach();
	}

	void InsertionSort()
	{
		started = true;

		int i = 1;
		while (i < LEN)
		{
			int x = arr[i];
			int j = i - 1;
			while (j >= 0 && arr[j] > x)
			{
				selected = j;
				arr[j + 1] = arr[j];
				j--;
			}
			sleep_for(25ms);
			arr[j + 1] = x;
			i++;
		}

		finished = true;
		sortThread.detach();
	}

	void CombSort()
	{
		started = true;

		int gap = LEN;
		double shrink = 1.3;
		bool sorted = false;

		while (!sorted)
		{
			gap = std::floor(gap / shrink);
			if (gap <= 1)
			{
				gap = 1;
				sorted = true;
			}

			int i = 0;
			while (i + gap < LEN)
			{
				if (arr[i] > arr[i + gap])
				{
					selected = i;
					sleep_for(75ms);
					int temp = arr[i];
					arr[i] = arr[i + gap];
					arr[i + gap] = temp;
					sorted = false;
				}

				i++;
			}
		}

		finished = true;
		sortThread.detach();
	}

	void Display()
	{
		for (int rect = 0; rect < LEN; rect++)
		{
			int rectHeight = arr[rect] * heightScale;
			olc::vi2d pos = { rect * rectWidth, height - rectHeight };
			olc::vi2d size = { rectWidth, rectHeight };

			if (rect == selected)
			{
				FillRect(pos, size, olc::RED);
				DrawRect(pos, size, olc::BLACK);
			}
			else
			{
				FillRect(pos, size, olc::GREY);
				DrawRect(pos, size, olc::BLACK);
			}
			
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