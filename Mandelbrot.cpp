#include "Mandelbrot.h"
#include <iostream>
Mandelbrot::Mandelbrot(int resX, int resY, int depth) : resolutionX(resX), resolutionY(resY), depthApproximation(depth)
{
	Matrix.reserve(resX);
	for (int x = 0; x < resX; ++x)
	{
		Matrix.push_back(std::vector<int>(resY));
	}
}

void Mandelbrot::setX(double min, double max)
{
	minX = min;
	maxX = max;
}


void Mandelbrot::setY(double min, double max)
{
	minY = min;
	maxY = max;
}

void Mandelbrot::calc()
{
	double xStep = (maxX - minX) / resolutionX;
	double yStep = (maxY - minY) / resolutionY;

	double x = minX;
	double y = minY;

	for (int xCoord = 0; xCoord < resolutionX; ++xCoord)
	{
		for (int yCoord = 0; yCoord < resolutionY; ++yCoord)
		{
			Matrix[xCoord][yCoord] = calcDepth(x, y);
			y += yStep;
		}
		y = minY;
		x += xStep;
	}

}

int Mandelbrot::calcDepth(double real, double imaginary)
{
	int depth = 0;
	double z = 0;
	double zReal = 0;
	double zImaginary = 0;
	double tempReal = 0;
	double tempImaginary = 0;

	while (z < 4 && depth < depthApproximation)
	{
		tempReal = zReal * zReal - zImaginary * zImaginary + real;
		tempImaginary = 2 * zReal * zImaginary + imaginary;

		zReal = tempReal;
		zImaginary = tempImaginary;

		z = zReal * zReal + zImaginary * zImaginary;
		//std::cout << real << ", " << imaginary << " : " << z << std::endl;
		++depth;
	}

	return depth;
}
