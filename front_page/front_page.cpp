#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnMyFeature(wxCommandEvent &event);
    void OnFriendsFeature(wxCommandEvent &event);

    void SwitchToFeature(wxPanel *featurePanel);

    wxPanel *myFeaturePanel;
    wxPanel *friendsFeaturePanel;

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Hello = 1,
    ID_MyFeature = 2,
    ID_FriendsFeature = 3
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello, MyFrame::OnHello)
        EVT_MENU(wxID_EXIT, MyFrame::OnExit)
            EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
                EVT_MENU(ID_MyFeature, MyFrame::OnMyFeature)
                    EVT_MENU(ID_FriendsFeature, MyFrame::OnFriendsFeature)
                        wxEND_EVENT_TABLE()

                            wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("Feature Selector", wxPoint(50, 50), wxSize(600, 400));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Create a panel that will serve as the container for all features
    wxPanel *mainPanel = new wxPanel(this, wxID_ANY);

    // Create two feature panels, but only one will be shown at a time
    myFeaturePanel = new wxPanel(mainPanel, wxID_ANY);
    friendsFeaturePanel = new wxPanel(mainPanel, wxID_ANY);

    // Set their sizes and position them (they will be hidden by default)
    myFeaturePanel->SetSize(mainPanel->GetSize());
    friendsFeaturePanel->SetSize(mainPanel->GetSize());

    // Create the menu bar
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_MyFeature, "&My Feature");
    menuFile->Append(ID_FriendsFeature, "&Friend's Feature");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    // Create status bar
    CreateStatusBar();
    SetStatusText("Select a feature from the menu!");

    // Set the initial visible feature
    SwitchToFeature(myFeaturePanel);
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets' Feature Selector sample",
                 "About Feature Selector", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnMyFeature(wxCommandEvent &event)
{
    // Switch to My Feature panel
    SwitchToFeature(myFeaturePanel);
}

void MyFrame::OnFriendsFeature(wxCommandEvent &event)
{
    // Switch to Friend's Feature panel
    SwitchToFeature(friendsFeaturePanel);
}

void MyFrame::SwitchToFeature(wxPanel *featurePanel)
{
    // Hide both panels and only show the selected one
    myFeaturePanel->Hide();
    friendsFeaturePanel->Hide();
    featurePanel->Show();

    // Refresh the main frame to reflect changes
    Layout();
}
