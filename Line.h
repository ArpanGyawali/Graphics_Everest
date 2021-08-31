#pragma once

#include <cmath>
#include <GL/glut.h>
#include "Color.h"

void putPixel(int x, int y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glPointSize(1);     //setss the size in pixel
    glBegin(GL_POINTS); //writes pixel in the brame buffer 
    glVertex2i(x, y);   //sets vertices
    glEnd();
}

void Bressenham(float x1, float y1, float x2, float y2, Color color)
{
    float dx, dy;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    float lx, ly;
    if (x2 > x1)
        lx = 1;
    else
        lx = -1;

    if (y2 > y1)
        ly = 1;
    else
        ly = -1;

    float x = x1, y = y1;
    // slope < 1
    if (dx > dy)
    {
        float p = 2 * dy - dx;
        for (float k = 0; k <= dx; k++)
        {
            putPixel(round(x), round(y), color);
            if (p < 0)
            {
                x += lx;
                p += 2 * dy;
            }
            else
            {
                x += lx;
                y += ly;
                p += 2 * dy - 2 * dx;
            }
        }
    }
    else
    { //slope > 1
        float p = 2 * dx - dy;
        for (float k = 0; k <= dy; k++)
        {
            putPixel(round(x), round(y), color);
            if (p < 0)
            {
                y += ly;
                p += 2 * dx;
            }
            else
            {
                x += lx;
                y += ly;
                p += 2 * dx - 2 * dy;
            }
        }
    }
}



    

