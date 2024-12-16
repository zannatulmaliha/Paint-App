#pragma once

#include <wx/wx.h>
#include <vector>
#include "PenManager.h"

class DrawingCanvas : public wxWindow
{
public:
    DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
    virtual ~DrawingCanvas() noexcept {}
    void SetPenColor(const wxColour &color); // Method to change pen color
    void SetPenType(PenType type);
    void SetPenSize(int size);

private:
    wxColour penColor = *wxBLACK;
    wxPen currentPen;
    int penSize;
    void OnPaint(wxPaintEvent &);
    void OnMouseDown(wxMouseEvent &);
    void OnMouseMove(wxMouseEvent &);
    void OnMouseUp(wxMouseEvent &);
    void OnMouseLeave(wxMouseEvent &);

    bool isDrawing{};

    struct Squiggle
    {
        std::vector<wxPoint2DDouble> points; // Points of the squiggle
        wxColour color;                      // Color of the squiggle
        wxPen penType;
        int Size;
        // Pen type of the squiggle
    };

    std::vector<Squiggle> squiggles; // Vector of all squiggles

    // std::vector<std::vector<wxPoint2DDouble>> squiggles;
    // std::vector<std::pair<std::vector<wxPoint2DDouble>, wxColour>> squiggles; // Now a vector of pairs

    wxMenu contextMenu;
    void BuildContextMenu();
    void OnContextMenuEvent(wxContextMenuEvent &);
};