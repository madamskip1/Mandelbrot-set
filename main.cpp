#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Mandelbrot.h"
#include "Cursor.h"

void transforMatrixToGL(GLubyte* pixels, const std::vector<std::vector<int>>& vec, int width, int height);
void drawCursorRectangle(GLFWwindow* window, double startX, double startY, double endX, double endY, int width, int height);
double calcGLFWCoords(double coord, int size);

double transformGLFWCoordsX(double X, int width);
double transformGLFWCoordsY(double Y, int height);

int main()
{
	const int WIDTH = 500;
	const int HEIGHT = 500;
	const int GREY_SCALE_DEPTH = 255;
	const double startX1 = -2.0;
	const double startX2 = 0.5;
	const double startY1 = 1.25;
	const double startY2 = -1.25;




	Mandelbrot mandelbrot(WIDTH, HEIGHT, GREY_SCALE_DEPTH);
	double mandelbrotX1 = startX1;
	double mandelbrotX2 = startX2;
	double mandelbrotY1 = startY1;
	double mandelbrotY2 = startY2;
	double distanceX, distanceY;

	mandelbrot.setX(mandelbrotX1, mandelbrotX2);
	mandelbrot.setY(mandelbrotY1, mandelbrotY2);
	mandelbrot.calc();

	Cursor cursor;
	


	GLubyte* pixels = new unsigned char[WIDTH * HEIGHT];
	GLenum format = GL_LUMINANCE;
	GLenum type = GL_UNSIGNED_BYTE;

	transforMatrixToGL(pixels, mandelbrot.Matrix, WIDTH, HEIGHT);
	


	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WIDTH, HEIGHT, "Mandelbrot Set", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(window, &cursor);
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& cur = *static_cast<Cursor*>(glfwGetWindowUserPointer(window));
			cur.click(window, button, action, mods);
		});


	glfwMakeContextCurrent(window);
	

	double X, Y;
	double cursorStartX, cursorEndX;
	double cursorStartY, cursorEndY;
	double temp;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(500, 500, format, type, pixels);
		
		if (cursor.isClicking())
		{
			glfwGetCursorPos(window, &X, &Y);
			drawCursorRectangle(window, cursor.getStartX(), cursor.getStartY(), X, Y, WIDTH, HEIGHT);
		}
		else if (cursor.isEnd())
		{
			cursorStartX = cursor.getStartX();
			cursorStartY = cursor.getStartY();
			cursorEndX = cursor.getEndX();
			cursorEndY = cursor.getEndY();

			if (cursorStartX != cursorEndX && cursorStartY != cursorEndY)
			{
				if (cursorStartX > cursorEndX)
				{
					temp = cursorStartX;
					cursorStartX = cursorEndX;
					cursorEndX = temp;
				}

				if (cursorStartY > cursorEndY)
				{
					temp = cursorStartY;
					cursorStartY = cursorEndY;
					cursorEndY = temp;
				}

				distanceX = mandelbrotX2 - mandelbrotX1;
				distanceY = mandelbrotY2 - mandelbrotY1;

				mandelbrotX1 = cursorStartX / WIDTH * distanceX + mandelbrotX1;
				mandelbrotX2 = mandelbrotX2 - (1 - cursorEndX / WIDTH) * distanceX;


				mandelbrotY2 = cursorStartY / HEIGHT * distanceY - mandelbrotY2;
				mandelbrotY1 = cursorEndY / HEIGHT * distanceY + mandelbrotY1;
				

				mandelbrot.setX(mandelbrotX1, mandelbrotX2);
				mandelbrot.setY(mandelbrotY1, mandelbrotY2);
				mandelbrot.calc();

				transforMatrixToGL(pixels, mandelbrot.Matrix, WIDTH, HEIGHT);
			}

			cursor.end();
		}
		else if (cursor.rightClicked())
		{
			mandelbrotX1 = startX1;
			mandelbrotX2 = startX2;
			mandelbrotY1 = startY1;
			mandelbrotY2 = startY2;

			mandelbrot.setX(mandelbrotX1, mandelbrotX2);
			mandelbrot.setY(mandelbrotY1, mandelbrotY2);
			mandelbrot.calc();

			transforMatrixToGL(pixels, mandelbrot.Matrix, WIDTH, HEIGHT);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void transforMatrixToGL(GLubyte* pixels, const std::vector<std::vector<int>>& vec, int width, int height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
			(pixels)[y * width + x] = vec[x][y];
	}
}


void drawCursorRectangle(GLFWwindow * window, double startX, double startY, double endX, double endY, int width, int height)
{
	startX = transformGLFWCoordsX(startX, width);
	endX = transformGLFWCoordsX(endX, width);

	startY = transformGLFWCoordsY(startY, height);
	endY = transformGLFWCoordsY(endY, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0, 0, 1, 0.5);
	glRectd(startX, startY, endX, endY);
	glDisable(GL_BLEND);
}


double transformGLFWCoordsX(double X, int width)
{
	X = X - width / 2;
	X = X / width * 2;
	return X;
}
double transformGLFWCoordsY(double Y, int height)
{
	Y = transformGLFWCoordsX(Y, height);
	Y *= -1;
	return Y;
}