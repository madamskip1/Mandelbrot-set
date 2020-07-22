#include "Cursor.h"

Cursor::Cursor() : clicking(false), released(false), right(false)
{
}

bool Cursor::isClicking()
{
    return clicking;
}

double Cursor::getStartX()
{
    return startX;
}

double Cursor::getStartY()
{
    return startY;
}

double Cursor::getEndX()
{
    return endX;
}

double Cursor::getEndY()
{
    return endY;
}

bool Cursor::isEnd()
{
    return released;
}

void Cursor::end()
{
    released = false;
    startX = startY = endX = endY = 0;
}

bool Cursor::rightClicked()
{
    if (right)
    {
        right = false;
        return true;
    }

    return false;
}

void Cursor::click(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &startX, &startY);
            clicking = true;
        }
        else if (action == GLFW_RELEASE)
        {
            glfwGetCursorPos(window, &endX, &endY);
            clicking = false;
            released = true;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
            right = true;
    }
}
