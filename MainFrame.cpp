#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    m_canvas = new ShapeCanvas(this);

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT, "E&xit");
    menuFile->Append(wxID_CLEAR, "&Clear");

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Shape Drawing App!");

    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnClear, this, wxID_CLEAR);
}

void MainFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnClear(wxCommandEvent& event) {
    m_canvas->ClearPlottingArea();
}
