#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "custombutton3.h"
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/fontdlg.h>

class NotepadFrame : public wxFrame {
public:
    NotepadFrame(wxWindow* parent,wxWindow* mainMenu)
        : wxFrame(parent, wxID_ANY, "Notepad", wxDefaultPosition, wxSize(600, 400)), mainMenu(mainMenu) {

        backgroundBitmap = wxBitmap("notes.jpg", wxBITMAP_TYPE_JPEG); // Ensure path is correct

        // Bind the paint event to draw the background
        Bind(wxEVT_PAINT, &NotepadFrame::OnPaint, this);

        // Create custom buttons
        newButton = new CustomButton3(this, wxID_ANY, "New", wxPoint(20, 30), wxSize(80, 30));
        saveButton = new CustomButton3(this, wxID_ANY, "Save", wxPoint(110, 30), wxSize(80, 30));
        fontButton = new CustomButton3(this, wxID_ANY, "Font Size", wxPoint(200, 30), wxSize(80, 30));
        highlight = new CustomButton3(this, wxID_ANY, "Highlight", wxPoint(290, 30), wxSize(80, 30));
        Music = new CustomButton3(this, wxID_ANY, "Music", wxPoint(380, 30), wxSize(80, 30)); // For playing music
        returntoMain = new CustomButton3(this, wxID_ANY, "Return", wxPoint(470, 30), wxSize(80, 30));
        // Create text control with a notepad-like background color
        textCtrl = new wxRichTextCtrl(this, wxID_ANY, "", wxPoint(20, 80), wxSize(550, 280), wxRE_MULTILINE);
        wxColour notepadBackgroundColor(255, 253, 208); // Light yellow, like a notepad
        textCtrl->SetBackgroundColour(notepadBackgroundColor);
        textCtrl->SetFocus();

        // Bind button events to respective handlers
        Bind(wxEVT_BUTTON, &NotepadFrame::OnNewFile, this, newButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnSaveFile, this, saveButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnChangeFont, this, fontButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnHighlightText, this, highlight->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnPlayMusic, this, Music->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnReturnToMain, this, returntoMain->GetId());


    }

private:
    wxWindow* mainMenu;
    wxBitmap backgroundBitmap;

    CustomButton3* newButton;
    CustomButton3* Music;
    CustomButton3* highlight;
    CustomButton3* saveButton;
    CustomButton3* fontButton;
    CustomButton3* returntoMain;

    wxRichTextCtrl* textCtrl;

    // OnPaint event handler to draw the background image
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

        event.Skip();  // Continue processing the event (optional)
    }

    // Event handler for New Button
    void OnNewFile(wxCommandEvent& event) {
        textCtrl->Clear();
    }

    // Event handler for Save Button
    void OnSaveFile(wxCommandEvent& event) {
        wxFileDialog saveFileDialog(this, "Save Text file", "", "",
            "Text files (*.txt)|*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

        if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

        wxString filePath = saveFileDialog.GetPath();
        wxTextFile file(filePath);
        if (file.Exists()) file.Open();
        else file.Create();

        file.Clear();
        file.AddLine(textCtrl->GetValue());
        file.Write();
        file.Close();
    }

    // Event handler for changing font size
    void OnChangeFont(wxCommandEvent& event) {
        wxFontData fontData;
        fontData.EnableEffects(false); // Disable font effects like underline/strike
        wxFontDialog fontDialog(this, fontData);

        if (fontDialog.ShowModal() == wxID_OK) {
            wxFont selectedFont = fontDialog.GetFontData().GetChosenFont();
            textCtrl->SetFont(selectedFont);
        }
    }

    // Event handler for highlighting text
 // Event handler for highlighting text
 void OnHighlightText(wxCommandEvent& event) {
        // Get the current selection range

    }


//     Event handler to play music (dummy implementation)
    void OnPlayMusic(wxCommandEvent& event) {
        wxMessageBox("Music playing (dummy implementation).");
    }

    // Event handler for returning to main menu
    void OnReturnToMain(wxCommandEvent& event) {
        this->Close();
        mainMenu->Show();
    }


};
