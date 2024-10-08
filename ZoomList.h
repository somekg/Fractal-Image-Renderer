#pragma once
#include <vector>
#include <utility>
#include "Zoom.h"

using namespace std;
namespace me {
class ZoomList {
private:
	double m_xCenter{ 0 };
	double m_yCenter{ 0 };
	double m_scale{ 1.0 };

	int m_width{ 0 };
	int m_height{ 0 };

	vector<Zoom> zooms;
public:
	ZoomList(int width, int height);
	void add(const Zoom& zoom);
	pair<double,double> doZoom(int x, int y);
};
}
