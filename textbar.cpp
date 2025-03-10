#include "TextBar.h"

TextBar::TextBar(wxWindow* parent) : wxPanel(parent) {
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(200, 30));
}

wxString TextBar::GetText() const {
    return m_textCtrl->GetValue();
}
