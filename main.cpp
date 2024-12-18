#include <wx/wx.h>
#include <wx/sound.h>
#include <wx/image.h>
#include <wx/statbmp.h>
#include "custombutton.h"
#include "notepad.h"
#include "animation.h"
#include "paint.h"


class MainMenuPanel : public wxPanel {
public:
    MainMenuPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY), backgroundSound("music.wav") {

        if (backgroundSound.IsOk()) {
            backgroundSound.Play(wxSOUND_ASYNC | wxSOUND_LOOP);
        } else {
            wxMessageBox("Failed to load sound file!", "Error", wxOK | wxICON_ERROR);
        }


        wxImage::AddHandler(new wxJPEGHandler());
        backgroundImage = wxBitmap("plankton.jpg", wxBITMAP_TYPE_JPEG);

        if (!backgroundImage.IsOk()) {
            wxMessageBox("Failed to load background image!", "Error", wxOK | wxICON_ERROR);
        }


        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);


        CustomButton* paintButton = new CustomButton(this, "Paint", wxDefaultPosition, wxSize(150, 40));
        CustomButton* notepadButton = new CustomButton(this, "Notepad", wxDefaultPosition, wxSize(150, 40));
        CustomButton* animationButton = new CustomButton(this, "Animation", wxDefaultPosition, wxSize(150, 40));
        CustomButton* menuButton = new CustomButton(this, "Main Menu", wxDefaultPosition, wxSize(150, 40));


        wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
        buttonSizer->Add(paintButton, 0, wxALIGN_CENTER | wxALL, 10);
        buttonSizer->Add(notepadButton, 0, wxALIGN_CENTER | wxALL, 10);
        buttonSizer->Add(animationButton, 0, wxALIGN_CENTER | wxALL, 10);
        buttonSizer->Add(menuButton, 0, wxALIGN_CENTER | wxALL, 10);


        mainSizer->AddSpacer(50);

        mainSizer->Add(buttonSizer, 1, wxALIGN_CENTER | wxALL, 20);

        SetSizer(mainSizer);

        Bind(wxEVT_PAINT, &MainMenuPanel::OnPaint, this);

        Bind(wxEVT_SIZE, &MainMenuPanel::OnResize, this);

        paintButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnPaintClicked, this);
        notepadButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnNotePadClicked, this);
        animationButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnAnimationClicked, this);
        menuButton->Bind(wxEVT_BUTTON, &MainMenuPanel::OnMenuClicked, this);
    }

private:
    wxBitmap backgroundImage;
    wxSound backgroundSound;

    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        RenderBackground(dc);
    }


    void OnResize(wxSizeEvent& event) {
        Refresh();
        event.Skip();
    }


    void RenderBackground(wxDC& dc) {
        if (backgroundImage.IsOk()) {
            wxSize panelSize = GetSize();
            wxSize imageSize = backgroundImage.GetSize();

            // Compute the scaling factor to ensure the image covers the entire window
            double scaleX = double(panelSize.GetWidth()) / double(imageSize.GetWidth());
            double scaleY = double(panelSize.GetHeight()) / double(imageSize.GetHeight());
            double scale = std::max(scaleX, scaleY);  // Scale to cover the entire window

            // Calculate new image dimensions
            int newWidth = int(imageSize.GetWidth() * scale);
            int newHeight = int(imageSize.GetHeight() * scale);

            // Scale the image to cover the panel size
            wxImage scaledImage = backgroundImage.ConvertToImage().Scale(newWidth, newHeight, wxIMAGE_QUALITY_HIGH);

            // Calculate position to center the image
            int x = (panelSize.GetWidth() - newWidth) / 2;
            int y = (panelSize.GetHeight() - newHeight) / 2;

            // Draw the scaled and centered background image
            dc.DrawBitmap(wxBitmap(scaledImage), x, y, false);
        }
    }
void OnPaintClicked(wxCommandEvent& event) {
  MyFrame *paintFrame = new MyFrame("Paint Application", wxDefaultPosition, wxSize(800, 600));

    paintFrame->Show(true);
    paintFrame->Raise();
    this->Hide();
}


    void OnNotePadClicked(wxCommandEvent& event) {
        NotepadFrame* notepadFrame = new NotepadFrame(this);
        notepadFrame->Show(true);
        notepadFrame->Raise();
        this->Hide();
    }

    void OnAnimationClicked(wxCommandEvent& event) {

        AnimationFrame* animationFrame=new AnimationFrame(this);
        animationFrame->Show(true);
        animationFrame->Raise();
        this->Close();
    }

    void OnMenuClicked(wxCommandEvent& event) {

    }
};

class MainFrame : public wxFrame {
public:
    MainFrame() : wxFrame(NULL, wxID_ANY, "Paint_App", wxDefaultPosition, wxSize(400, 400)) {
        MainMenuPanel* mainMenu = new MainMenuPanel(this);
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);
