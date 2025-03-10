#include "ShapeDrawer.h"

ShapeDrawer::ShapeDrawer(wxWindow* parent) : wxPanel(parent) {
    Bind(wxEVT_PAINT, &ShapeDrawer::OnPaint, this);
    Bind(wxEVT_RIGHT_DOWN, &ShapeDrawer::OnRightClick, this);
}

void ShapeDrawer::AddShape(Shape* shape) {
    m_shapes.push_back(shape);
    Refresh();  // Redraw the panel
}

void ShapeDrawer::SetText(const wxString& text) {
    m_text = text;
    Refresh();  // Redraw the panel
}

void ShapeDrawer::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    // Draw all the shapes
    for (Shape* shape : m_shapes) {
        shape->Draw(dc);
    }

    // Draw the text
    if (!m_text.IsEmpty()) {
        dc.SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        dc.DrawText(m_text, wxPoint(100, 100));  // Example position for text
    }
}

void ShapeDrawer::OnRightClick(wxMouseEvent& event) {
    wxMenu menu;
    menu.Append(1001, "Add Rectangle");
    menu.Append(1002, "Add Square");
    menu.Append(1003, "Add Triangle");
    menu.Append(1004, "Add Star");
    menu.Append(1005, "Add Polygon");

    menu.Bind(wxEVT_MENU, [this](wxCommandEvent& e) {
        switch (e.GetId()) {
        case 1001:
            AddShape(new Rectangle(wxPoint(150, 150), wxPoint(250, 250)));
            break;
        case 1002:
            AddShape(new Square(wxPoint(200, 200), wxPoint(300, 300)));
            break;
        case 1003:
            AddShape(new Triangle(wxPoint(300, 300), wxPoint(400, 400)));
            break;
        case 1004:
            AddShape(new Star(wxPoint(350, 350), wxPoint(450, 450)));
            break;
        case 1005:
            AddShape(new Polygon(wxPoint(400, 400), wxPoint(500, 500), 6));
            break;
        }
        });

    PopupMenu(&menu);
}
