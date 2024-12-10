#include <wx/wx.h>
#include <wx/dcclient.h>
#include <wx/colour.h>
#include <wx/timer.h>

class CustomButton : public wxPanel {
public:
    CustomButton(wxWindow* parent, const wxString& label, const wxPoint& pos, const wxSize& size)
        : wxPanel(parent, wxID_ANY, pos, size), m_label(label), m_isHovered(false), m_isPressed(false) {


        SetBackgroundStyle(wxBG_STYLE_PAINT);

        Bind(wxEVT_ENTER_WINDOW, &CustomButton::OnMouseEnter, this);
        Bind(wxEVT_LEAVE_WINDOW, &CustomButton::OnMouseLeave, this);
        Bind(wxEVT_LEFT_DOWN, &CustomButton::OnMouseDown, this);
        Bind(wxEVT_LEFT_UP, &CustomButton::OnMouseUp, this);
        Bind(wxEVT_PAINT, &CustomButton::OnPaint, this);
    }

    void SetButtonLabel(const wxString& label) {
        m_label = label;
        Refresh();
    }

protected:

    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);


        wxColour buttonColor;
        if (m_isPressed) {
           buttonColor = wxColour(128, 0, 128);

        } else if (m_isHovered) {
  buttonColor = wxColour(204, 0, 0); // Lighter purple
        } else {


         buttonColor = wxColour(255, 102, 102);
        }


        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(wxBrush(buttonColor));


        dc.DrawRoundedRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight(), 15);


        dc.SetTextForeground(*wxWHITE);
        dc.SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxSize textSize = dc.GetTextExtent(m_label);
        dc.DrawText(m_label, (GetSize().GetWidth() - textSize.GetWidth()) / 2,
                    (GetSize().GetHeight() - textSize.GetHeight()) / 2);
    }


    void OnMouseEnter(wxMouseEvent& event) {
        m_isHovered = true;
        Refresh();
    }

    void OnMouseLeave(wxMouseEvent& event) {
        m_isHovered = false;
        Refresh();
    }

    void OnMouseDown(wxMouseEvent& event) {
        m_isPressed = true;
        Refresh();
    }

 void OnMouseUp(wxMouseEvent& event) {
    m_isPressed = false;
    Refresh();
    wxMessageBox("Button Clicked!", "Info", wxOK | wxICON_INFORMATION);


    wxCommandEvent clickEvent(wxEVT_BUTTON, GetId());
    GetEventHandler()->ProcessEvent(clickEvent);
}


private:
    wxString m_label;
    bool m_isHovered;
    bool m_isPressed;
};
