/**
 * @file main.cpp
 * @brief Fractal creator entry point.
 */

#include "FractalCreator.h"

using namespace std;

int main()
{	
	const int fourK_width = 3840;
	const int fourK_height = 2160;

	// 4K Resolution
	FractalCreator fractalCreator(fourK_width, fourK_height);
	
	cout << "Please Stand By For A Moment While The Fractal Builds..." << endl;

	Zoom(1920, 1080, 0.01);

	int duration = fractalCreator.run("output/test2.png");

	cout << "Finished! Time taken: " << duration << " s" << endl;
	cout << "The .bmp should be in the project's folder. " << endl;
}
