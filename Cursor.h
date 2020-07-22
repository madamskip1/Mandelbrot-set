#pragma once
#include <GLFW/glfw3.h>
class Cursor
{
	bool clicking;
	double startX;
	double startY;
	double endX;
	double endY;
	bool released;
	bool right;

public:
	Cursor();
	bool isClicking();
	double getStartX();
	double getStartY();
	double getEndX();
	double getEndY();
	bool isEnd();
	void end();
	bool rightClicked();
	void click(GLFWwindow* window, int button, int action, int mods);
};

