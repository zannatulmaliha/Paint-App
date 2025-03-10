#ifndef SHAPE_DRAWER_H
#define SHAPE_DRAWER_H

#include <wx/wx.h>
#include "Shape.h" // Include the Shape header

class ShapeDrawer : public wxPanel {
public:
    ShapeDrawer(wxWindow* parent);

    void AddShape(Shape* shape);
    void SetText(const wxString& text);

protected:
    void OnPaint(wxPaintEvent& event);
    void OnRightClick(wxMouseEvent& event);

private:
    std::vector<Shape*> m_shapes;
    wxString m_text;
};

#endif // SHAPE_DRAWER_H

