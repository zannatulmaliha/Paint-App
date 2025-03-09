#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "custombutton3.h"  // Include the header file for CustomButton3

class NotepadFrame : public wxFrame {
public:
    NotepadFrame(wxWindow* parent)
        : wxFrame(parent, wxID_ANY, "Notepad", wxDefaultPosition, wxSize(600, 400)), mainMenu(parent) {

        // Load the background image
        backgroundBitmap = wxBitmap("notes.jpg", wxBITMAP_TYPE_JPEG); // Change to the path of your image

        // Bind the paint event to draw the background
        Bind(wxEVT_PAINT, &NotepadFrame::OnPaint, this);

        // Create custom buttons
        typeButton = new CustomButton3(this, wxID_ANY, "Type", wxPoint(20, 30), wxSize(100, 35));
        colorButton = new CustomButton3(this, wxID_ANY, "Color", wxPoint(140, 30), wxSize(100, 35));
        fontButton = new CustomButton3(this, wxID_ANY, "fontsize", wxPoint(260, 30), wxSize(100, 35));
        returntoMain = new CustomButton3(this, wxID_ANY, "Return to Main Menu", wxPoint(380, 30), wxSize(150, 35));

     textCtrl = new wxRichTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(550, 280), wxRE_MULTILINE);
        wxColour notepadBackgroundColor(255, 253, 208); // Light yellow, like a notepad
        textCtrl->SetBackgroundColour(notepadBackgroundColor);
        textCtrl->SetFocus();
    }

private:
    wxWindow* mainMenu;
    wxBitmap backgroundBitmap;

    CustomButton3* typeButton;
    CustomButton3* colorButton;
    CustomButton3* fontButton;
    CustomButton3* returntoMain;

     wxRichTextCtrl* textCtrl;

   void OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    wxSize size = GetClientSize();

    // Check if the background bitmap is valid
    if (backgroundBitmap.IsOk()) {
        // Convert the bitmap to an image for scaling
        wxImage backgroundImage = backgroundBitmap.ConvertToImage();

        // Scale the image to fit the size of the frame
        wxImage scaledImage = backgroundImage.Scale(size.GetWidth(), size.GetHeight());

        // Convert the scaled image back to a bitmap
        wxBitmap scaledBitmap(scaledImage);

        // Draw the scaled bitmap as the background
        dc.DrawBitmap(scaledBitmap, 0, 0, true); // The third argument is 'useMask', set it to true if you have transparency
    }

    event.Skip();  // Continue processing the event
}

};

