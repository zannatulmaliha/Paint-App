#include <wx/wx.h>
#include <wx/dcbuffer.h>

class CustomButton2 : public wxButton {
public:
    CustomButton2(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size)
        : wxButton(parent, id, label, pos, size, wxBORDER_NONE) {

        // Set double buffering to reduce flicker
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &CustomButton2::OnPaint, this);
        Bind(wxEVT_ENTER_WINDOW, &CustomButton2::OnMouseEnter, this);
        Bind(wxEVT_LEAVE_WINDOW, &CustomButton2::OnMouseLeave, this);

        // Initially, not hovered
        isHovered = false;
    }

private:
    bool isHovered;

    // Handle the painting of the button
    void OnPaint(wxPaintEvent& event) {
        wxAutoBufferedPaintDC dc(this);
        wxSize size = GetSize();

        // Colors for gradient background
        wxColour startColor = isHovered ? wxColour(255, 140, 0) : wxColour(30, 144, 255);  // Orange on hover, blue otherwise
        wxColour endColor = isHovered ? wxColour(255, 165, 0) : wxColour(70, 130, 180);   // Slightly darker on hover

        // Draw gradient background
        dc.GradientFillLinear(wxRect(0, 0, size.GetWidth(), size.GetHeight()), startColor, endColor, wxDOWN);

        // Draw rounded rectangle
        dc.SetPen(wxPen(wxColour(255, 255, 255), 2));  // White border
        dc.SetBrush(*wxTRANSPARENT_BRUSH);             // No internal fill
        dc.DrawRoundedRectangle(1, 1, size.GetWidth() - 2, size.GetHeight() - 2, 10); // Rounded corners

        // Draw button label text
        wxFont font = GetFont();
        dc.SetFont(font);
        dc.SetTextForeground(wxColour(255, 255, 255));  // White text color
        wxSize textSize = dc.GetTextExtent(GetLabel());
        dc.DrawText(GetLabel(), (size.GetWidth() - textSize.GetWidth()) / 2, (size.GetHeight() - textSize.GetHeight()) / 2);
    }

    // Handle mouse enter event
    void OnMouseEnter(wxMouseEvent& event) {
        isHovered = true;
        Refresh();  // Trigger a repaint
        event.Skip();
    }

    // Handle mouse leave event
    void OnMouseLeave(wxMouseEvent& event) {
        isHovered = false;
        Refresh();  // Trigger a repaint
        event.Skip();
    }
};
