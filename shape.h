#ifndef SHAPE_H
#define SHAPE_H

#include <wx/wx.h>
#include <vector>
#include <cmath> // For trigonometric functions in Polygon class

// Base class for shapes
class Shape {
public:
    virtual void Draw(wxDC& dc) = 0;  // Pure virtual function for drawing shapes
    virtual ~Shape();  // Virtual destructor
};

// Derived class for Square
class Square : public Shape {
public:
    Square(wxPoint start, wxPoint end);  // Constructor to initialize start and end points
    void Draw(wxDC& dc) override;  // Override the Draw function

private:
    wxPoint m_start, m_end;  // Start and end points
};

// Derived class for Rectangle
class Rectangle : public Shape {
public:
    Rectangle(wxPoint start, wxPoint end);  // Constructor to initialize start and end points
    void Draw(wxDC& dc) override;  // Override the Draw function

private:
    wxPoint m_start, m_end;  // Start and end points
};

// Derived class for Triangle
class Triangle : public Shape {
public:
    Triangle(wxPoint start, wxPoint end);  // Constructor to initialize start and end points
    void Draw(wxDC& dc) override;  // Override the Draw function

private:
    wxPoint m_start, m_end;  // Start and end points
};

// Derived class for Star
class Star : public Shape {
public:
    Star(wxPoint start, wxPoint end);  // Constructor to initialize start and end points
    void Draw(wxDC& dc) override;  // Override the Draw function

private:
    wxPoint m_start, m_end;  // Start and end points
};

// Derived class for Polygon (with customizable number of sides)
class Polygon : public Shape {
public:
    Polygon(wxPoint start, wxPoint end, int sides);  // Constructor to initialize start, end points, and number of sides
    void Draw(wxDC& dc) override;  // Override the Draw function

private:
    wxPoint m_start, m_end;  // Start and end points
    int m_sides;  // Number of sides of the polygon
};

#endif // SHAPE_H
