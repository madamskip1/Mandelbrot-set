#pragma once
#include <vector>
class Mandelbrot
{
public:
	std::vector<std::vector<int>> Matrix;

	Mandelbrot() = delete;
	Mandelbrot(int resX, int resY, int depth);

	void setX(double min, double max);
	void setY(double min, double max);

	void calc();
private:
	int resolutionX;
	int resolutionY;
	int depthApproximation;
	double minX, maxX;
	double minY, maxY;

	int calcDepth(double real, double imaginary);
};

