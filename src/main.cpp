/**
 * @file main.cpp
 * @brief Fractal creator entry point.
 */

#include "FractalCreator.hpp"
#include "Zoom.hpp"

using namespace std;

int main()
{	
	const int fourK_width = 3840;
	const int fourK_height = 2160;

	// 4K Resolution
	FractalCreator fractalCreator(fourK_width, fourK_height);
	
	cout << "Please Stand By For A Moment While The Fractal Builds..." << endl;

	int duration = fractalCreator.run("output/test3.png");

	cout << "Render-only time: " << duration << " s" << endl;
	cout << "Check output folder for the image." << endl;
}
