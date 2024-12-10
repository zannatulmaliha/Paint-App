#include <wx/wx.h>
#include <wx/timer.h>
#include "custombutton2.h"

class AnimationCanvas : public wxPanel {
public:
    AnimationCanvas(wxWindow* parent, wxWindow* mainMenu)
        : wxPanel(parent), mainMenu(mainMenu) {

         SetBackgroundColour(wxColour(255, 240,245));

         shapesButton = new CustomButton2(this, wxID_ANY, "Shapes", wxPoint(20, 30), wxSize(100, 50));
        selectButton = new CustomButton2(this, wxID_ANY, "Select", wxPoint(140, 30), wxSize(100, 50));
        animationButton = new CustomButton2(this, wxID_ANY, "Animation", wxPoint(260, 30), wxSize(100, 50));
        returntoMain = new CustomButton2(this, wxID_ANY, "Return to Main Menu", wxPoint(380, 30), wxSize(150, 50));

        shapesButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnShapesClicked, this);
        selectButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnSelectClicked, this);
        animationButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnAnimationClicked, this);
        returntoMain->Bind(wxEVT_BUTTON, &AnimationCanvas::OnReturntoMainMenuClicked, this);
    }

private:
     CustomButton2* shapesButton;
    CustomButton2* selectButton;
    CustomButton2* animationButton;
    CustomButton2* returntoMain;
    wxWindow* mainMenu;


    void OnShapesClicked(wxCommandEvent& event) {

    }

    void OnSelectClicked(wxCommandEvent& event) {

    }

    void OnAnimationClicked(wxCommandEvent& event) {

    }

    void OnReturntoMainMenuClicked(wxCommandEvent& event) {
        this->GetParent()->Close();
        mainMenu->Show();
    }
};


class AnimationFrame : public wxFrame {
public:
    AnimationFrame(wxWindow* parent)
        : wxFrame(parent, wxID_ANY, "Animation", wxDefaultPosition, wxSize(600, 400)) {

        mainMenu = parent;


        new AnimationCanvas(this, mainMenu);

    }

private:
    wxWindow* mainMenu;

};
