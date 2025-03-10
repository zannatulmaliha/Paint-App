#ifndef TEXT_BAR_H
#define TEXT_BAR_H

#include <wx/wx.h>

class TextBar : public wxPanel {
public:
    TextBar(wxWindow* parent);

    wxString GetText() const;

private:
    wxTextCtrl* m_textCtrl;
};

#endif // TEXT_BAR_H

