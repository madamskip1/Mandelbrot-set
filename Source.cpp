#include "Mandelbrot.h"
#include <iostream>

int main()
{
	Mandelbrot mandelbrot(500, 500, 300);

	mandelbrot.setX(-2.0, 0.5);
	mandelbrot.setY(-1.25, 1.25);
	mandelbrot.calc();
	for (int x = 0; x < 500; ++x)
	{
		for (int y = 0; y < 500; ++y)
		{
			std::cout << x << ", " << y << " = " << mandelbrot.Matrix[x][y] << std::endl;
	}
	return 0;
}