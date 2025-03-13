#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include "ShapeCanvas.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    ShapeCanvas* m_canvas;

    void OnQuit(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
};

#endif // MAINFRAME_H
