#include <wx/wx.h>
#include <wx/timer.h>

// A custom panel for drawing shapes (canvas)
class AnimationCanvas : public wxPanel {
public:
    AnimationCanvas(wxWindow* parent, wxWindow* mainMenu)
        : wxPanel(parent), mainMenu(mainMenu) { // Initialize mainMenu properly here

        // Create buttons on the canvas
        shapesButton = new wxButton(this, wxID_ANY, "Shapes", wxPoint(20, 300));
        selectButton = new wxButton(this, wxID_ANY, "Select", wxPoint(120, 300));
        animationButton = new wxButton(this, wxID_ANY, "Animation", wxPoint(220, 300));
        returntoMain = new wxButton(this, wxID_ANY, "Return to Main Menu", wxPoint(320, 300));

        // Bind button events to show submenus
        shapesButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnShapesClicked, this);
        selectButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnSelectClicked, this);
        animationButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnAnimationClicked, this);
        returntoMain->Bind(wxEVT_BUTTON, &AnimationCanvas::OnReturntoMainMenuClicked, this);
    }

private:
    wxButton* shapesButton;
    wxButton* selectButton;
    wxButton* animationButton;
    wxButton* returntoMain;
    wxWindow* mainMenu;  // To store the main menu pointer

    // Event handlers for button clicks
    void OnShapesClicked(wxCommandEvent& event) {
        // Implement functionality for the Shapes button here
    }

    void OnSelectClicked(wxCommandEvent& event) {
        // Implement functionality for the Select button here
    }

    void OnAnimationClicked(wxCommandEvent& event) {
        // Implement functionality for the Animation button here
    }

    void OnReturntoMainMenuClicked(wxCommandEvent& event) {
        this->Close();  // Hide the animation frame
        mainMenu->Show();  // Show the main menu
    }
};

// The main frame class that hosts the animation canvas
class AnimationFrame : public wxFrame {
public:
    AnimationFrame(wxWindow* parent)
        : wxFrame(parent, wxID_ANY, "Animation", wxDefaultPosition, wxSize(600, 400)) {

        mainMenu = parent; // Store the reference to the main menu (parent)

        // Create the custom animation canvas and pass the mainMenu pointer to it
        new AnimationCanvas(this, mainMenu);
    }

private:
    wxWindow* mainMenu;  // Store the main menu pointer
};
