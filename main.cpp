#include "FractalCreator.h"
using namespace std;
using namespace me;

int main()
{	
	FractalCreator fractalCreator(800, 600);
	
	cout << "Please Stand By For A Moment While The Fractal Builds..." << endl;
	/*Default bluish color*/
	/*
	fractalCreator.addRange(0.0, RGB(0, 7, 100));    // Deep ocean blue
	fractalCreator.addRange(0.1, RGB(32, 107, 203)); // Lighter ocean blue
	fractalCreator.addRange(0.3, RGB(237, 255, 255)); // Almost white
	fractalCreator.addRange(0.6, RGB(255, 255, 255)); // Pure white
	fractalCreator.addRange(0.8, RGB(252, 183, 100)); // Warm yellow
	fractalCreator.addRange(0.9, RGB(204, 128, 52));  // Sandy brown
	fractalCreator.addRange(1.0, RGB(0, 0, 0));       // Black
	*/
	
	/*Burned Orange Palette*/
	fractalCreator.addRange(0.0, RGB(0, 0, 0)); 
	fractalCreator.addRange(0.1, RGB(200, 50, 10)); 
	fractalCreator.addRange(0.3, RGB(255, 200, 80)); 
	fractalCreator.addRange(0.6, RGB(240, 104, 25));  
	fractalCreator.addRange(0.8, RGB(200, 117, 40)); 
	fractalCreator.addRange(0.9, RGB(107, 0, 0));    
	fractalCreator.addRange(1.0, RGB(0, 0, 0));       
	
	//Example Zooms

	fractalCreator.addZoom(Zoom(467, 185, 0.001));

	/*
	fractalCreator.addZoom(Zoom(453, 299, 0.1));
	fractalCreator.addZoom(Zoom(389, 309, 0.1));
	fractalCreator.addZoom(Zoom(344, 293, 0.1));
	fractalCreator.addZoom(Zoom(351, 298, 0.1));
	fractalCreator.addZoom(Zoom(506, 458, 0.1));
	fractalCreator.addZoom(Zoom(403, 396, 0.1));
	*/
	fractalCreator.run("test.bmp");
	
	cout << "Finished! The .bmp should be in the project's folder. " << endl;
}
