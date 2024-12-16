#include "PenManager.h"

wxPen PenManager::GetPen(PenType type)
{
    wxPen pen;
    switch (type)
    {
    case PenType::SOLID:
        pen.SetStyle(wxPENSTYLE_SOLID);
        pen.SetColour(*wxBLACK);
        pen.SetWidth(1);
        break;
    case PenType::DASHED:
        pen.SetStyle(wxPENSTYLE_LONG_DASH);
        pen.SetColour(*wxBLUE);
        pen.SetWidth(2);
        break;
    case PenType::DOTTED:
        pen.SetStyle(wxPENSTYLE_DOT);
        pen.SetColour(*wxRED);
        pen.SetWidth(1);
        break;
    case PenType::BRUSH:
        pen.SetStyle(wxPENSTYLE_SOLID);
        pen.SetColour(*wxGREEN);
        pen.SetWidth(5); // Thicker brush
        break;
    }
    return pen;
}
