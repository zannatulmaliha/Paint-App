#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "sprite.h"
#include "custombutton2.h"
#include <vector>

class AnimationCanvas : public wxPanel {
public:
    AnimationCanvas(wxWindow* parent, wxWindow* mainMenu)
        : wxPanel(parent), mainMenu(mainMenu), selectedSprite(nullptr), drawingPath(false), pathMode(false) {

        SetBackgroundColour(wxColour(255, 240, 245));

        shapesButton = new CustomButton2(this, wxID_ANY, "Shapes", wxPoint(20, 30), wxSize(100, 35));
        pathButton = new CustomButton2(this, wxID_ANY , "Path", wxPoint(140, 30), wxSize(100, 35));
        spriteButton = new CustomButton2(this, wxID_ANY, "Add Sprite", wxPoint(260, 30), wxSize(100, 35));
        returntoMain = new CustomButton2(this, wxID_ANY, "Return to Main Menu", wxPoint(380, 30), wxSize(150, 35));

        playButton = new wxButton(this, wxID_ANY, "Play", wxPoint(0, 0), wxSize(100, 35));
        playButton->SetBackgroundColour(wxColour(255, 0, 0));
        playButton->SetForegroundColour(wxColour(255, 255, 255));

        // Bind button events
        shapesButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnShapesClicked, this);
        pathButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnPathClicked, this);
        spriteButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnAddSpriteClicked, this);
        returntoMain->Bind(wxEVT_BUTTON, &AnimationCanvas::OnReturntoMainMenuClicked, this);
        playButton->Bind(wxEVT_BUTTON, &AnimationCanvas::OnPlayClicked, this);

        // Bind window events
        Bind(wxEVT_PAINT, &AnimationCanvas::OnPaint, this);
        Bind(wxEVT_LEFT_DOWN, &AnimationCanvas::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &AnimationCanvas::OnMouseLeftUp, this);
        Bind(wxEVT_MOTION, &AnimationCanvas::OnMouseMove, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
        Bind(wxEVT_SIZE, &AnimationCanvas::OnResize, this);
    }

    ~AnimationCanvas() {
        for (auto sprite : sprites) {
            delete sprite;
        }
    }

private:
    wxButton* playButton;
    CustomButton2* shapesButton;
    CustomButton2* pathButton;
    CustomButton2* spriteButton;
    CustomButton2* returntoMain;
    wxWindow* mainMenu;
    std::vector<Sprite*> sprites;
    Sprite* selectedSprite;
    bool drawingPath;
    bool pathMode;
    std::vector<wxPoint> drawnPath;

    void OnResize(wxSizeEvent& event) {
        wxSize size = GetClientSize();
        int playButtonWidth = playButton->GetSize().GetWidth();
        int playButtonHeight = playButton->GetSize().GetHeight();
        int newPosX = size.GetWidth() - playButtonWidth - 10;
        int newPosY = size.GetHeight() - playButtonHeight - 10;

        playButton->SetPosition(wxPoint(newPosX, newPosY));
        event.Skip();
    }

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

    void OnPlayClicked(wxCommandEvent& event) {
        if (selectedSprite && !drawnPath.empty()) {
            // Animate the sprite along the path
            AnimateSprite();

            // Clear the path after animation starts
            drawnPath.clear();
        } else {
            wxLogMessage("No path is drawn or sprite is selected.");
        }
    }

    void AnimateSprite() {
        if (!selectedSprite || drawnPath.empty()) return;

        // Animate the sprite along the drawn path
        for (const auto& point : drawnPath) {
            selectedSprite->MoveTo(point.x, point.y);
            Refresh();
            wxMilliSleep(100);  // Pause to simulate animation
        }
    }

    void OnCircleSelected(wxCommandEvent& event) { wxLogMessage("Circle selected!"); }
    void OnRectangleSelected(wxCommandEvent& event) { wxLogMessage("Rectangle selected!"); }
    void OnSquareSelected(wxCommandEvent& event) { wxLogMessage("Square selected!"); }
    void OnStarSelected(wxCommandEvent& event) { wxLogMessage("Star selected!"); }

    void OnPathClicked(wxCommandEvent& event) {
        pathMode = true;
        wxLogMessage("Click to draw a path for the sprite.");
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
        Refresh();
    }

    void OnAddCasperSprite(wxCommandEvent& event) {
        sprites.push_back(new Sprite("casper.jpg", 52, 100));
        Refresh();
    }

    void OnAddCloudSprite(wxCommandEvent& event) {
        sprites.push_back(new Sprite("cloud.jpg", 53, 100));
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

        // Draw the path, if it exists
        if (drawingPath && !drawnPath.empty()) {
            dc.SetPen(wxPen(wxColour(0, 0, 255), 2));
            for (size_t i = 1; i < drawnPath.size(); ++i) {
                dc.DrawLine(drawnPath[i - 1], drawnPath[i]);
            }
        }
    }

    void OnMouseLeftDown(wxMouseEvent& event) {
        int mouseX = event.GetX();
        int mouseY = event.GetY();

        if (pathMode) {
            drawnPath.clear();  // Clear any previous path
            drawingPath = true;
            drawnPath.push_back(wxPoint(mouseX, mouseY));
        } else {
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
        }
        Refresh();
    }

    void OnMouseLeftUp(wxMouseEvent& event) {
        if (selectedSprite) {
            selectedSprite->StopDragging();
            selectedSprite->StopResizing();
            selectedSprite = nullptr;
        }
        drawingPath = false;  // Stop drawing the path
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

        if (drawingPath && pathMode) {
            int mouseX = event.GetX();
            int mouseY = event.GetY();
            drawnPath.push_back(wxPoint(mouseX, mouseY));
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
