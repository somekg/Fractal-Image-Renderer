#pragma once

namespace me {
	struct RGB {
		double r{ 0 };
		double g{ 0 };
		double b{ 0 };
	
		RGB(double r, double g, double b); 
		friend RGB operator-(const RGB& first, const RGB& second);
	};
	RGB operator-(const RGB& first, const RGB& second);
}
