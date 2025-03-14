#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <vector>
#include "sprite.h"
#include "custombutton2.h"

class AnimationCanvas : public wxPanel
{
public:
    AnimationCanvas(wxWindow *parent, wxWindow *mainMenu)
        : wxPanel(parent), mainMenu(mainMenu), selectedSprite(nullptr), drawingPath(false), pathMode(false)
    {

        SetBackgroundColour(wxColour(255, 240, 245));

        shapesButton = new CustomButton2(this, wxID_ANY, "Shapes", wxPoint(20, 30), wxSize(100, 35));
        pathButton = new CustomButton2(this, wxID_ANY, "Path", wxPoint(140, 30), wxSize(100, 35));
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
        Bind(wxEVT_RIGHT_DOWN, &AnimationCanvas::OnMouseRightDown, this); // Right-click binding for stopping path drawing
        Bind(wxEVT_MOTION, &AnimationCanvas::OnMouseMove, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent &) {});
        Bind(wxEVT_SIZE, &AnimationCanvas::OnResize, this);

        // Initialize the animation timer
        animationTimer = new wxTimer(this);
        Bind(wxEVT_TIMER, &AnimationCanvas::OnAnimationTimer, this);

        // Initialize the animation index
        animationIndex = 0;
    }

    ~AnimationCanvas()
    {
        for (auto sprite : sprites)
        {
            delete sprite;
        }
        delete animationTimer; // Delete the timer
    }

private:
    wxButton *playButton;
    CustomButton2 *shapesButton;
    CustomButton2 *pathButton;
    CustomButton2 *spriteButton;
    CustomButton2 *returntoMain;
    wxWindow *mainMenu;
    std::vector<Sprite *> sprites;
    Sprite *selectedSprite;
    bool drawingPath;
    bool pathMode;
    std::vector<wxPoint> drawnPath;

    // Timer for animation
    wxTimer *animationTimer;
    size_t animationIndex;

    void OnResize(wxSizeEvent &event)
    {
        wxSize size = GetClientSize();
        int playButtonWidth = playButton->GetSize().GetWidth();
        int playButtonHeight = playButton->GetSize().GetHeight();
        int newPosX = size.GetWidth() - playButtonWidth - 10;
        int newPosY = size.GetHeight() - playButtonHeight - 10;

        playButton->SetPosition(wxPoint(newPosX, newPosY));
        event.Skip();
    }

    void OnShapesClicked(wxCommandEvent &event)
    {
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

    void OnPlayClicked(wxCommandEvent &event)
    {
        if (selectedSprite && !drawnPath.empty())
        {
            AnimateSprite();
        }
        else
        {
            wxLogMessage("No path is drawn or sprite is selected.");
        }
    }

    void AnimateSprite()
    {
        if (!selectedSprite || drawnPath.empty())
            return;
        animationIndex = 0;        // Start from the first point
        animationTimer->Start(30); // Trigger every 30 milliseconds (adjust as needed)
    }

    void OnAnimationTimer(wxTimerEvent &event)
    {
        if (animationIndex < drawnPath.size())
        {
            const auto &point = drawnPath[animationIndex++];
            selectedSprite->MoveTo(point.x, point.y);
            Refresh();
        }
        else
        {
            animationTimer->Stop(); // Stop the timer when done
            drawnPath.clear();      // Clear the path after animation
        }
    }

    void OnCircleSelected(wxCommandEvent &event) { wxLogMessage("Circle selected!"); }
    void OnRectangleSelected(wxCommandEvent &event) { wxLogMessage("Rectangle selected!"); }
    void OnSquareSelected(wxCommandEvent &event) { wxLogMessage("Square selected!"); }
    void OnStarSelected(wxCommandEvent &event) { wxLogMessage("Star selected!"); }

    void OnPathClicked(wxCommandEvent &event)
    {
        pathMode = !pathMode;
        if (pathMode)
        {
            wxLogMessage("Path drawing mode enabled. Click and drag to draw a path.");
        }
        else
        {
            wxLogMessage("Path drawing mode disabled.");
        }
    }

    void OnAddSpriteClicked(wxCommandEvent &event)
    {
        wxMenu spriteMenu;
        spriteMenu.Append(101, "Add Micky");
        spriteMenu.Append(102, "Add Casper");
        spriteMenu.Append(103, "Add Cloud");

        Bind(wxEVT_MENU, &AnimationCanvas::OnAddFoxSprite, this, 101);
        Bind(wxEVT_MENU, &AnimationCanvas::OnAddCasperSprite, this, 102);
        Bind(wxEVT_MENU, &AnimationCanvas::OnAddCloudSprite, this, 103);

        PopupMenu(&spriteMenu, spriteButton->GetPosition());
    }

    void OnAddFoxSprite(wxCommandEvent &event)
    {
        Sprite *newSprite = new Sprite("image/micky.png", 50, 100); // Update the path as needed
        sprites.push_back(newSprite);
        Refresh();
    }

    void OnAddCasperSprite(wxCommandEvent &event)
    {
        Sprite *newSprite = new Sprite("image/micky.png", 100, 100);
        sprites.push_back(newSprite);
        Refresh();
    }

    void OnAddCloudSprite(wxCommandEvent &event)
    {
        Sprite *newSprite = new Sprite("image/micky.png", 150, 100);
        sprites.push_back(newSprite);
        Refresh();
    }

    void OnReturntoMainMenuClicked(wxCommandEvent &event)
    {
        this->GetParent()->Close();
        mainMenu->Show();
    }

    void OnPaint(wxPaintEvent &event)
    {
        wxBufferedPaintDC dc(this);
        dc.Clear();

        // Draw the sprite images
        for (auto sprite : sprites)
        {
            sprite->Draw(dc);
        }

        // Draw the path, if it exists
        if ((drawingPath || !drawnPath.empty()) && pathMode)
        {
            dc.SetPen(wxPen(wxColour(0, 0, 255), 2)); // Blue color for path
            for (size_t i = 1; i < drawnPath.size(); ++i)
            {
                dc.DrawLine(drawnPath[i - 1], drawnPath[i]);
            }
        }
    }

    void OnMouseLeftDown(wxMouseEvent &event)
    {
        int mouseX = event.GetX();
        int mouseY = event.GetY();

        if (pathMode)
        {
            // Start a new path
            drawnPath.clear(); // Clear any old path when starting a new one
            drawingPath = true;
            drawnPath.push_back(wxPoint(mouseX, mouseY));
            wxLogMessage("Started drawing path at (%d, %d)", mouseX, mouseY);
            Refresh(); // Refresh to show path immediately
        }
        else
        {
            // Regular sprite selection logic
            selectedSprite = nullptr; // Reset selected sprite
            for (auto sprite : sprites)
            {
                if (sprite->Contains(mouseX, mouseY))
                {
                    selectedSprite = sprite;
                    sprite->SetSelected(true);
                    sprite->StartResizing(mouseX, mouseY);
                    if (!sprite->IsResizing())
                    {
                        sprite->StartDragging(mouseX, mouseY);
                    }
                    wxLogMessage("Sprite selected.");
                    break; // Exit loop once sprite is found
                }
                else
                {
                    sprite->SetSelected(false);
                }
            }
            if (!selectedSprite)
            {
                wxLogMessage("No sprite selected.");
            }
            Refresh();
        }
    }

    void OnMouseRightDown(wxMouseEvent &event)
    {
        if (drawingPath)
        {
            drawingPath = false;
            wxLogMessage("Stopped drawing path. Total points: %lu", drawnPath.size());
        }
    }

    void OnMouseLeftUp(wxMouseEvent &event)
    {
        if (selectedSprite)
        {
            selectedSprite->StopDragging();
            selectedSprite->StopResizing();
            selectedSprite = nullptr;
        }
    }

    void OnMouseMove(wxMouseEvent &event)
    {
        int mouseX = event.GetX();
        int mouseY = event.GetY();

        if (drawingPath && pathMode)
        {
            drawnPath.push_back(wxPoint(mouseX, mouseY)); // Record path
            Refresh();                                    // Refresh to update the path drawing
        }

        if (event.Dragging() && selectedSprite)
        {
            if (selectedSprite->IsResizing())
            {
                selectedSprite->Resize(mouseX, mouseY);
            }
            else
            {
                selectedSprite->MoveTo(mouseX, mouseY);
            }
            Refresh();
        }
    }
};

class AnimationFrame : public wxFrame
{
public:
    AnimationFrame(wxWindow *parent)
        : wxFrame(parent, wxID_ANY, "Animation", wxDefaultPosition, wxSize(600, 400))
    {

        mainMenu = parent;
        new AnimationCanvas(this, mainMenu);
    }

private:
    wxWindow *mainMenu;
};