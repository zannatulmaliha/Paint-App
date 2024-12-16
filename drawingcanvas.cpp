#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
    : wxWindow(parent, id, pos, size), penSize(5)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->SetBackgroundColour(wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

    this->Bind(wxEVT_PAINT, &DrawingCanvas::OnPaint, this);
    this->Bind(wxEVT_LEFT_DOWN, &DrawingCanvas::OnMouseDown, this);
    this->Bind(wxEVT_MOTION, &DrawingCanvas::OnMouseMove, this);
    this->Bind(wxEVT_LEFT_UP, &DrawingCanvas::OnMouseUp, this);
    this->Bind(wxEVT_LEAVE_WINDOW, &DrawingCanvas::OnMouseLeave, this);

    BuildContextMenu();

    this->Bind(wxEVT_CONTEXT_MENU, &DrawingCanvas::OnContextMenuEvent, this);
}

void DrawingCanvas::OnPaint(wxPaintEvent &)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        for (const auto &pair : squiggles)
        {
            // const auto &pointsVector = pair.first;
            // const auto &color = pair.second;

            const auto &points = pair.points;
            const auto &color = pair.color;
            const auto &penType = pair.penType;
            int size = pair.Size;

            wxPen pen = pair.penType; // Use the currentPen
                                      // wxPen pen = PenManager::GetPen(penType);

            pen.SetColour(color);
            pen.SetWidth(size);
            // Set the color of the pen
            // pen.SetStyle(pair.penType);
            gc->SetPen(pen);

            // gc->SetPen(wxPen(color, 8));
            if (points.size() > 1)
            {
                gc->StrokeLines(points.size(), points.data());
            }
        }

        delete gc;
    }
}

void DrawingCanvas::OnMouseDown(wxMouseEvent &)
{
    squiggles.push_back(Squiggle{{}, penColor, currentPen, penSize});
    squiggles.back().color = penColor; // Set the current pen color for this squiggle
    isDrawing = true;

    // squiggles.push_back({});
    // squiggles.back().second = penColor; // Set the current pen color for this squiggle
    // isDrawing = true;
}

void DrawingCanvas::OnMouseMove(wxMouseEvent &event)
{
    if (isDrawing)
    {
        auto pt = event.GetPosition();
        auto &currentSquiggle = squiggles.back().points;

        currentSquiggle.push_back(pt);
        Refresh();
    }
}

void DrawingCanvas::OnMouseUp(wxMouseEvent &)
{
    isDrawing = false;
}

void DrawingCanvas::OnMouseLeave(wxMouseEvent &)
{
    isDrawing = false;
}

void DrawingCanvas::BuildContextMenu()
{
    auto clear = contextMenu.Append(wxID_ANY, "&Clear");
    contextMenu.Append(wxID_ANY, "Save &As...");

    this->Bind(
        wxEVT_MENU,
        [this](wxCommandEvent &)
        {
            this->squiggles.clear();
            this->Refresh();
        },
        clear->GetId());
}

void DrawingCanvas::OnContextMenuEvent(wxContextMenuEvent &e)
{
    auto clientPos = e.GetPosition() == wxDefaultPosition
                         ? wxPoint(this->GetSize().GetWidth() / 2, this->GetSize().GetHeight() / 2)
                         : this->ScreenToClient(e.GetPosition());
    PopupMenu(&this->contextMenu, clientPos);
}

void DrawingCanvas::SetPenColor(const wxColour &color)
{
    penColor = color; // Update the pen color
                      // Refresh();
}

void DrawingCanvas::SetPenType(PenType type)
{
    currentPen = PenManager::GetPen(type);
    Refresh(); // Refresh the canvas to reflect changes
}

void DrawingCanvas::SetPenSize(int size)
{
    penSize = size;

    // Update the pen drawing settings with the new size
    Refresh(); // Repaint the canvas if needed
}