#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "sprite.h"
#include "custombutton2.h"
#include <vector>

class AnimationCanvas : public wxPanel {
public:
    AnimationCanvas(wxWindow* parent, wxWindow* mainMenu)
        : wxPanel(parent), mainMenu(mainMenu), selectedSprite(nullptr) {

        SetBackgroundColour(wxColour(255, 240, 245));


        shapesButton = new CustomButton2(this, wxID_ANY, "Shapes", wxPoint(20, 30), wxSize(100, 35));
        selectButton = new CustomButton2(this, wxID_ANY , "Select", wxPoint(140, 30), wxSize(100, 35));
        spriteButton = new CustomButton2(this, wxID_ANY, "Add Sprite", wxPoint(260, 30), wxSize(100, 35));
        returntoMain = new CustomButton2(this, wxID_ANY, "Return to Main Menu", wxPoint(380, 30), wxSize(150, 35));


        shapesButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnShapesClicked, this);
        selectButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnSelectClicked, this);
        spriteButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnAddSpriteClicked, this);
        returntoMain->Bind(wxEVT_BUTTON, &AnimationCanvas::OnReturntoMainMenuClicked, this);


        Bind(wxEVT_PAINT, &AnimationCanvas::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &AnimationCanvas::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &AnimationCanvas::OnMouseLeftUp, this);
        Bind(wxEVT_MOTION, &AnimationCanvas::OnMouseMove, this);
           Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    }

    ~AnimationCanvas() {
        for (auto sprite : sprites) {
            delete sprite;
        }
    }

private:
    CustomButton2* shapesButton;
    CustomButton2* selectButton;
    CustomButton2* spriteButton;
    CustomButton2* returntoMain;
    wxWindow* mainMenu;
    std::vector<Sprite*> sprites;
    Sprite* selectedSprite;

    void OnShapesClicked(wxCommandEvent& event) {
        wxMenu menu;
        menu.Append(1, "Circle");
        menu.Append(2, "Rectangle");
        menu.Append(3, "Square");
        menu.Append(4, "Star");

        Bind(wxEVT_MENU, &AnimationCanvas::OnCircleSelected, this, 1);
        Bind(wxEVT_MENU, &AnimationCanvas::OnRectangleSelected, this, 2);
        Bind(wxEVT_MENU, &AnimationCanvas::OnSquareSelected, this, 3);
        Bind(wxEVT_MENU, &AnimationCanvas::OnStarSelected, this, 4);

        PopupMenu(&menu, shapesButton->GetPosition());
    }

    void OnCircleSelected(wxCommandEvent& event) { wxLogMessage("Circle selected!"); }
    void OnRectangleSelected(wxCommandEvent& event) { wxLogMessage("Rectangle selected!"); }
    void OnSquareSelected(wxCommandEvent& event) { wxLogMessage("Square selected!"); }
    void OnStarSelected(wxCommandEvent& event) { wxLogMessage("Star selected!"); }

    void OnSelectClicked(wxCommandEvent& event) {
        wxLogMessage("Click on a sprite to select.");
    }

    void OnAddSpriteClicked(wxCommandEvent& event) {
        wxMenu spriteMenu;
        spriteMenu.Append(101, "Add Fox");
        spriteMenu.Append(102, "Add Casper");
        spriteMenu.Append(103, "Add Cloud");

        Bind(wxEVT_MENU, &AnimationCanvas::OnAddFoxSprite, this, 101);
        Bind(wxEVT_MENU, &AnimationCanvas::OnAddCasperSprite, this, 102);
        Bind(wxEVT_MENU, &AnimationCanvas::OnAddCloudSprite, this, 103);

        PopupMenu(&spriteMenu, spriteButton->GetPosition());
    }

    void OnAddFoxSprite(wxCommandEvent& event) {
        sprites.push_back(new Sprite("fox.jpg", 50, 100));
        Refresh();  // Redraw the canvas
    }

    void OnAddCasperSprite(wxCommandEvent& event) {
        sprites.push_back(new Sprite("casper.jpg", 150, 100));
        Refresh();
    }

    void OnAddCloudSprite(wxCommandEvent& event) {
        sprites.push_back(new Sprite("cloud.jpg", 250, 100));
        Refresh();
    }

    void OnReturntoMainMenuClicked(wxCommandEvent& event) {
        this->GetParent()->Close();
        mainMenu->Show();
    }

    void OnPaint(wxPaintEvent& event) {
        wxBufferedPaintDC dc(this);
        dc.Clear();

        for (auto sprite : sprites) {
            sprite->Draw(dc);
        }
    }

    void OnMouseLeftDown(wxMouseEvent& event) {
        int mouseX = event.GetX();
        int mouseY = event.GetY();


        for (auto sprite : sprites) {
            if (sprite->Contains(mouseX, mouseY)) {
                selectedSprite = sprite;
                sprite->SetSelected(true);


                sprite->StartResizing(mouseX, mouseY);
                if (!sprite->IsResizing()) {
                    sprite->StartDragging(mouseX, mouseY);
                }
            } else {
                sprite->SetSelected(false);
            }
        }
        Refresh();
    }

    void OnMouseLeftUp(wxMouseEvent& event) {
        if (selectedSprite) {
            selectedSprite->StopDragging();
            selectedSprite->StopResizing();
            selectedSprite = nullptr;
        }
    }

    void OnMouseMove(wxMouseEvent& event) {
        if (event.Dragging() && selectedSprite) {
            int mouseX = event.GetX();
            int mouseY = event.GetY();


            if (selectedSprite->IsResizing()) {
                selectedSprite->Resize(mouseX, mouseY);
            } else {
                selectedSprite->MoveTo(mouseX, mouseY);
            }
            Refresh();
        }
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
