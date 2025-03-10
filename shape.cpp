#include "Shape.h"
#include <cmath>

// Base class for shapes
Shape::~Shape() {}  // Virtual destructor

// Derived class for Square
Square::Square(wxPoint start, wxPoint end) : m_start(start), m_end(end) {}

void Square::Draw(wxDC& dc) {
    int size = abs(m_end.x - m_start.x);
    dc.DrawRectangle(m_start.x, m_start.y, size, size);
}

// Derived class for Rectangle
Rectangle::Rectangle(wxPoint start, wxPoint end) : m_start(start), m_end(end) {}

void Rectangle::Draw(wxDC& dc) {
    dc.DrawRectangle(m_start.x, m_start.y, abs(m_end.x - m_start.x), abs(m_end.y - m_start.y));
}

// Derived class for Triangle
Triangle::Triangle(wxPoint start, wxPoint end) : m_start(start), m_end(end) {}

void Triangle::Draw(wxDC& dc) {
    wxPoint points[3] = { {m_start.x, m_end.y}, {m_end.x, m_end.y}, {(m_start.x + m_end.x) / 2, m_start.y} };
    dc.DrawPolygon(3, points);
}

// Derived class for Star
Star::Star(wxPoint start, wxPoint end) : m_start(start), m_end(end) {}

void Star::Draw(wxDC& dc) {
    wxPoint points[5] = {
        {m_start.x, m_end.y}, {m_end.x, m_end.y},
        {m_end.x + (m_start.x - m_end.x) / 2, m_start.y},
        {m_start.x - (m_start.x - m_end.x) / 2, m_start.y},
        {(m_start.x + m_end.x) / 2, m_start.y}
    };
    dc.DrawPolygon(5, points);
}

// Derived class for Polygon
Polygon::Polygon(wxPoint start, wxPoint end, int sides) : m_start(start), m_end(end), m_sides(sides) {}

void Polygon::Draw(wxDC& dc) {
    std::vector<wxPoint> points;
    for (int i = 0; i < m_sides; ++i) {
        double angle = 2 * M_PI * i / m_sides;
        int x = m_start.x + cos(angle) * (abs(m_end.x - m_start.x) / 2);
        int y = m_start.y + sin(angle) * (abs(m_end.y - m_start.y) / 2);
        points.push_back(wxPoint(x, y));
    }
    dc.DrawPolygon(points.size(), points.data());
}
