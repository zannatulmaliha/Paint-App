#include <wx/wx.h>
#include <wx/dcbuffer.h>

class CustomButton3 : public wxButton {
public:
    CustomButton3(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size)
        : wxButton(parent, id, label, pos, size, wxBORDER_NONE) {


        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &CustomButton3::OnPaint, this);
        Bind(wxEVT_ENTER_WINDOW, &CustomButton3::OnMouseEnter, this);
        Bind(wxEVT_LEAVE_WINDOW, &CustomButton3::OnMouseLeave, this);
        Bind(wxEVT_LEFT_DOWN, &CustomButton3::OnMouseDown, this);
        Bind(wxEVT_LEFT_UP, &CustomButton3::OnMouseUp, this);

        isHovered = false;
        isClicked = false;
    }

private:
    bool isHovered;
    bool isClicked;


    void OnPaint(wxPaintEvent& event) {
        wxAutoBufferedPaintDC dc(this);
        wxSize size = GetSize();

        // Determine color based on state
        wxColour startColor;
        wxColour endColor;

        if (isClicked) {
            // Color when clicked
            startColor = wxColour(220, 20, 60); // Crimson red
            endColor = wxColour(178, 34, 34);   // Firebrick red
        } else if (isHovered) {
            // Colors when hovered
            startColor = wxColour(255, 114, 94); // Coral
            endColor = wxColour(255, 182, 135);  // Peach
        } else {
            // Default colors
            startColor = wxColour(72, 209, 204);  // Teal
            endColor = wxColour(64, 224, 208);    // Turquoise
        }

        // Draw gradient background
        dc.GradientFillLinear(wxRect(0, 0, size.GetWidth(), size.GetHeight()), startColor, endColor, wxDOWN);

        // Draw rounded rectangle with smooth borders
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

    // Handle mouse down (click) event
    void OnMouseDown(wxMouseEvent& event) {
        isClicked = true;
        Refresh();  // Trigger a repaint
        event.Skip();
    }

    // Handle mouse up (release click) event
    void OnMouseUp(wxMouseEvent& event) {
        isClicked = false;
        Refresh();  // Trigger a repaint
        event.Skip();
    }
};
