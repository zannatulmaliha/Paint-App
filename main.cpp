#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/splitter.h>
#include <wx/colordlg.h>

#include <string>
#include <vector>

#include "colorpane.h"
#include "PenManager.h"
#include "PenSizePanel.h"

// #include "pensizepane.h"

#include "drawingcanvas.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnSelectColor(wxCommandEvent &event);

    wxPanel *BuildControlsPanel(wxWindow *parent);

    void SetupColorPanes(wxWindow *parent, wxSizer *sizer);
    // void SetupPenPanes(wxWindow *parent, wxSizer *sizer);

    void SelectColorPane(ColorPane *pane);
    // void SelectPenPane(PenSizePane *pane);

    std::vector<ColorPane *> colorPanes{};
    // std::vector<PenSizePane *> penPanes{};

    DrawingCanvas *canvas;

    PenManager *penManager;

    const std::vector<std::string> niceColors = {"#000000", "#ffffff", "#fd7f6f",
                                                 "#7eb0d5", "#b2e061", "#bd7ebe",
                                                 "#ffb55a", "#ffee65", "#beb9db",
                                                 "#fdcce5", "#8bd3c7"};

    // const std::vector<std::string> niceColors = {"#000000", "#ffffff", "#fd7f6f"};

    const int penCount = 6;

    const std::string lightBackground = "#f4f3f3";
    const std::string darkBackground = "#2c2828";

    PenSizePanel *penSizePanel = nullptr;
    wxSlider *penSizeSlider = nullptr;
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

void MyFrame::SetupColorPanes(wxWindow *parent, wxSizer *sizer)
{

    for (const auto &color : niceColors)
    {
        auto colorPane = new ColorPane(parent, wxID_ANY, wxColour(color));

        colorPane->Bind(wxEVT_LEFT_DOWN, [this, colorPane](wxMouseEvent &event)
                        { SelectColorPane(colorPane);
                          canvas->SetPenColor(colorPane->GetColor()); });

        colorPanes.push_back(colorPane);
        sizer->Add(colorPane, 0, wxRIGHT | wxBOTTOM, FromDIP(5));
    }
}

wxPanel *MyFrame::BuildControlsPanel(wxWindow *parent)
{
    auto controlsPanel = new wxScrolled<wxPanel>(parent, wxID_ANY);
    controlsPanel->SetScrollRate(0, FromDIP(10));

    bool isDark = wxSystemSettings::GetAppearance().IsDark();

    controlsPanel->SetBackgroundColour(wxColour(isDark ? darkBackground : lightBackground));

    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add a spacer to push the button lower
    // mainSizer->AddSpacer(FromDIP(20));

    // auto text = new wxStaticText(controlsPanel, wxID_ANY, "Colors");
    // mainSizer->Add(text, 0, wxALL, FromDIP(5));

    auto colorPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    SetupColorPanes(controlsPanel, colorPaneSizer);

    mainSizer->Add(colorPaneSizer, 0, wxALL | wxEXPAND, FromDIP(5));
    // colorPaneSizer->Bind(wxEVT_BUTTON, &MyFrame::OnSelectColor, this);

    // text = new wxStaticText(controlsPanel, wxID_ANY, "Pens");
    // mainSizer->Add(text, 0, wxALL, FromDIP(5));

    // auto penPaneSizer = new wxWrapSizer(wxHORIZONTAL);
    //  SetupPenPanes(controlsPanel, penPaneSizer);
    // mainSizer->Add(penPaneSizer, 0, wxALL, FromDIP(5));

    auto button = new wxButton(controlsPanel, wxID_ANY, "Save As...");

    // Add the Select Color button
    wxImage rainbowImage(wxT("C:\\Users\\atiaz\\Downloads\\Screenshot_2024-12-07_111007-removebg-preview.png"), wxBITMAP_TYPE_PNG);
    rainbowImage.Rescale(FromDIP(45), FromDIP(45));
    wxBitmap rainbowBitmap(rainbowImage);

    // wxBitmap rainbowBitmap(wxT("C:\\Users\\atiaz\\OneDrive\\Pictures\\Screenshots\\Screenshot 2024-12-06 010320.png"), wxBITMAP_TYPE_PNG);

    auto rainbowButton = new wxBitmapButton(controlsPanel, wxID_ANY, rainbowBitmap);

    // auto colorButton = new wxButton(controlsPanel, wxID_ANY, "Select Color");
    colorPaneSizer->Add(rainbowButton, 0, wxALL, FromDIP(5));

    // mainSizer->Add(rainbowButton, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, FromDIP(5));

    // Bind the button to open the color dialog
    rainbowButton->Bind(wxEVT_BUTTON, &MyFrame::OnSelectColor, this);

    // mainSizer->AddStretchSpacer();
    // mainSizer->Add(button, 0, wxALL, FromDIP(5));
    mainSizer->AddSpacer(FromDIP(8));

    controlsPanel->SetSizer(mainSizer);

    wxBoxSizer *penTypeSizer = new wxWrapSizer(wxHORIZONTAL);

    // Load images for each pen type
    wxImage solidImage(wxT("C:\\Users\\atiaz\\Downloads\\brush.png"), wxBITMAP_TYPE_PNG);
    wxImage dashedImage(wxT("C:\\Users\\atiaz\\Downloads\\art-and-design.png"), wxBITMAP_TYPE_PNG);
    wxImage dottedImage(wxT("C:\\Users\\atiaz\\Downloads\\palette.png"), wxBITMAP_TYPE_PNG);
    wxImage brushImage(wxT("C:\\Users\\atiaz\\Downloads\\paint-brush.png"), wxBITMAP_TYPE_PNG);

    if (!brushImage.HasAlpha())
    {

        wxLogError("The image does not have an alpha channel.");
    }

    wxBitmap transparentBitmap(brushImage);

    // Rescale the images if needed
    solidImage.Rescale(FromDIP(30), FromDIP(30));
    dashedImage.Rescale(FromDIP(30), FromDIP(30));
    dottedImage.Rescale(FromDIP(30), FromDIP(30));
    brushImage.Rescale(FromDIP(30), FromDIP(30));

    // Create bitmap buttons for each pen type
    auto solidButton = new wxBitmapButton(controlsPanel, wxID_ANY, wxBitmap(solidImage));
    auto dashedButton = new wxBitmapButton(controlsPanel, wxID_ANY, wxBitmap(dashedImage));
    auto dottedButton = new wxBitmapButton(controlsPanel, wxID_ANY, wxBitmap(dottedImage));
    auto brushButton = new wxBitmapButton(controlsPanel, wxID_ANY, wxBitmap(brushImage));

    dashedButton->SetSize(dashedImage.GetWidth(), dashedImage.GetHeight());
    // Bind events to change pen type
    solidButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
                      { canvas->SetPenType(PenType::SOLID); });
    dashedButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
                       { canvas->SetPenType(PenType::DASHED); });
    dottedButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
                       { canvas->SetPenType(PenType::DOTTED); });
    brushButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent &event)
                      { canvas->SetPenType(PenType::BRUSH); });

    // Add buttons to the sizer
    penTypeSizer->Add(solidButton, 0, wxALL | wxEXPAND, FromDIP(5));
    penTypeSizer->Add(dashedButton, 0, wxALL | wxEXPAND, FromDIP(5));
    penTypeSizer->Add(dottedButton, 0, wxALL | wxEXPAND, FromDIP(5));
    penTypeSizer->Add(brushButton, 0, wxALL | wxEXPAND, FromDIP(5));

    // Add the pen type sizer to the main sizer
    mainSizer->Add(penTypeSizer, 0, wxRIGHT | wxBOTTOM, FromDIP(5));

    mainSizer->AddSpacer(FromDIP(3));
    mainSizer->Add(button, 0, wxALL, FromDIP(5));

    // auto penSizeButton = new wxButton(controlsPanel, wxID_ANY, "");
    wxImage img(wxT("C:\\Users\\atiaz\\Downloads\\pexels-deeanacreates-1646953.jpg"), wxBITMAP_TYPE_JPEG);
    img.Rescale(FromDIP(40), FromDIP(40)); // Resize image to fit your button size
    wxBitmap resizedBitmap(img);           // Convert the resized image to a bitmap
    auto penSizeButton = new wxBitmapButton(controlsPanel, wxID_ANY, wxBitmap(img));

    mainSizer->Add(penSizeButton, 0, wxALL, FromDIP(5));

    penSizeButton->Bind(wxEVT_BUTTON, [this, controlsPanel, mainSizer](wxCommandEvent &event)
                        {
                            if (penSizeSlider == nullptr)
                            {
                                penSizeSlider = new wxSlider(controlsPanel, wxID_ANY, 5, 1, 50, // Default pen size is 5, range from 1 to 50
                                                             wxDefaultPosition, wxDefaultSize,
                                                             wxSL_HORIZONTAL | wxSL_LABELS);

                                // Add the slider to the sizer
                                // mainSizer->Add(penSizeSlider, 0, wxALL | wxEXPAND, FromDIP(5));
                                wxSizer *buttonSizer = controlsPanel->GetSizer(); // Get the sizer managing controlsPanel
                                if (buttonSizer)
                                {
                                    buttonSizer->Add(penSizeSlider, 0, wxALL | wxEXPAND, FromDIP(5)); // Add slider with padding
                                }

                                penSizeSlider->Bind(wxEVT_SLIDER, [this](wxCommandEvent &event)
                                                    {
                                                        int penSize = event.GetInt(); // Get the current value from the slider
                                                        canvas->SetPenSize(penSize);  // Set the pen size on the canvas
                                                    });
                                controlsPanel->Layout();
                            }

                            else
                            {
                                // Toggle visibility of the slider
                                penSizeSlider->Show(!penSizeSlider->IsShown());
                                controlsPanel->Layout(); // Re-layout the panel
                            }
                            // Bind the slider to an event handler
                            // penSizeSlider->Bind(wxEVT_SLIDER, [this](wxCommandEvent &event)
                            //                     {
                            //                         int penSize = event.GetInt(); // Get the current value from the slider
                            //                         canvas->SetPenSize(penSize);  // Set the pen size on the canvas
                            //                     });
                        });
    controlsPanel->SetSizer(mainSizer);

    return controlsPanel;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    wxSplitterWindow *splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    splitter->SetMinimumPaneSize(FromDIP(150)); // sets a min pane size->cannot be less than 150

    auto controlsPanel = BuildControlsPanel(splitter);
    canvas = new DrawingCanvas(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    // penManager = new PenManager(canvas);

    splitter->SplitVertically(controlsPanel, canvas);
    splitter->SetSashPosition(FromDIP(220)); // initial position of divider. leaves 220 pixels for the left

    this->SetSize(FromDIP(800), FromDIP(500));      // sets the size of the window
    this->SetMinSize({FromDIP(400), FromDIP(200)}); // min size of window

    SelectColorPane(colorPanes[0]);

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    // wxButton *colorButton = new wxButton(panel, wxID_ANY, "Select Color", wxPoint(0, 100));

    // Bind the button click event to the handler
    // colorButton->Bind(wxEVT_BUTTON, &MyFrame::OnSelectColor, this);
    // SelectPenPane(penPanes[0]);
}

void MyFrame::SelectColorPane(ColorPane *pane)
{
    for (auto colorPane : colorPanes)
    {
        colorPane->selected = (colorPane == pane);

        colorPane->Refresh();
    }
}

void MyFrame::OnSelectColor(wxCommandEvent &event)
{
    wxColourData data;
    wxColourDialog dialog(this, &data);

    // Show the color dialog
    if (dialog.ShowModal() == wxID_OK)
    {
        // Get the color selected by the user
        wxColour selectedColor = dialog.GetColourData().GetColour();
        canvas->SetPenColor(selectedColor);

        // Example: Change the background color of the frame to the selected color
        // this->SetBackgroundColour(selectedColor);
        // this->Refresh(); // Refresh to apply the new background color
    }
}
// void MyFrame::SelectPenPane(PenSizePane *pane)
// {
//     for (auto penPane : penPanes)
//     {
//         penPane->selected = (penPane == pane);
//         penPane->Refresh();
//     }

//     canvas->currentWidth = pane->penWidth;
// }
