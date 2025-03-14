#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include "custombutton3.h"
#include <wx/filedlg.h>
#include <wx/textfile.h>
#include <wx/fontdlg.h>

class NotepadFrame : public wxFrame
{
public:
    NotepadFrame(wxWindow *parent, wxWindow *mainMenu)
        : wxFrame(parent, wxID_ANY, "Notepad", wxDefaultPosition, wxSize(600, 400)), mainMenu(mainMenu)
    {

        backgroundBitmap = wxBitmap("image/notes.jpg", wxBITMAP_TYPE_JPEG); // Ensure path is correct

        // Bind the paint event to draw the background
        Bind(wxEVT_PAINT, &NotepadFrame::OnPaint, this);

        // Create a wrapsizer for the buttons
        wxWrapSizer *buttonSizer = new wxWrapSizer(wxHORIZONTAL);

        // Create custom buttons and add them to the wrapsizer
        newButton = new CustomButton3(this, wxID_ANY, "New", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(newButton, 0, wxALL, 5);

        saveButton = new CustomButton3(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(saveButton, 0, wxALL, 5);

        fontButton = new CustomButton3(this, wxID_ANY, "Font Size", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(fontButton, 0, wxALL, 5);

        Calculator = new CustomButton3(this, wxID_ANY, "Calculator", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(Calculator, 0, wxALL, 5);

        Music = new CustomButton3(this, wxID_ANY, "Music", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(Music, 0, wxALL, 5);

        returntoMain = new CustomButton3(this, wxID_ANY, "Return", wxDefaultPosition, wxSize(80, 30));
        buttonSizer->Add(returntoMain, 0, wxALL, 5);

        // Create a wxTextCtrl to act as a simple text editor (without rich text features)
        textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(550, 280), wxTE_MULTILINE);
        wxColour notepadBackgroundColor(255, 253, 208); // Light yellow, like a notepad
        textCtrl->SetBackgroundColour(notepadBackgroundColor);
        textCtrl->SetFocus();

        // Create a box sizer to contain the wrapsizer and the text control
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxBOTTOM, 10);
        mainSizer->Add(textCtrl, 1, wxEXPAND | wxALL, 10);

        // Set the sizer for the frame
        SetSizer(mainSizer);

        // Bind button events to respective handlers
        Bind(wxEVT_BUTTON, &NotepadFrame::OnNewFile, this, newButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnSaveFile, this, saveButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnChangeFont, this, fontButton->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnCalculator, this, Calculator->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnPlayMusic, this, Music->GetId());
        Bind(wxEVT_BUTTON, &NotepadFrame::OnReturnToMain, this, returntoMain->GetId());
    }

private:
    wxWindow *mainMenu;
    wxBitmap backgroundBitmap;

    CustomButton3 *newButton;
    CustomButton3 *Music;
    CustomButton3 *Calculator;
    CustomButton3 *saveButton;
    CustomButton3 *fontButton;
    CustomButton3 *returntoMain;

    wxTextCtrl *textCtrl;

    // OnPaint event handler to draw the background image
    void OnPaint(wxPaintEvent &event)
    {
        wxPaintDC dc(this);
        wxSize size = GetClientSize();

        // Check if the background bitmap is valid
        if (backgroundBitmap.IsOk())
        {
            // Convert the bitmap to an image for scaling
            wxImage backgroundImage = backgroundBitmap.ConvertToImage();

            // Scale the image to fit the size of the frame
            wxImage scaledImage = backgroundImage.Scale(size.GetWidth(), size.GetHeight());

            // Convert the scaled image back to a bitmap
            wxBitmap scaledBitmap(scaledImage);

            // Draw the scaled bitmap as the background
            dc.DrawBitmap(scaledBitmap, 0, 0, true); // The third argument is 'useMask', set it to true if you have transparency
        }

        event.Skip(); // Continue processing the event (optional)
    }

    // Event handler for New Button
    void OnNewFile(wxCommandEvent &event)
    {
        textCtrl->Clear();
    }

    // Event handler for Save Button
    void OnSaveFile(wxCommandEvent &event)
    {
        wxFileDialog saveFileDialog(this, "Save Text file", "", "",
                                    "Text files (.txt)|.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (saveFileDialog.ShowModal() == wxID_CANCEL)
            return;

        wxString filePath = saveFileDialog.GetPath();
        wxTextFile file(filePath);
        if (file.Exists())
            file.Open();
        else
            file.Create();

        file.Clear();
        file.AddLine(textCtrl->GetValue());
        file.Write();
        file.Close();
    }

    // Event handler for changing font size
    void OnChangeFont(wxCommandEvent &event)
    {
        wxFontData fontData;
        fontData.EnableEffects(false); // Disable font effects like underline/strike
        wxFontDialog fontDialog(this, fontData);

        if (fontDialog.ShowModal() == wxID_OK)
        {
            wxFont selectedFont = fontDialog.GetFontData().GetChosenFont();
            textCtrl->SetFont(selectedFont);
        }
    }

    // Event handler for highlighting text
    void OnCalculator(wxCommandEvent &event)
    {
        wxTextEntryDialog calculatorDialog(this, "Enter an expression to calculate (e.g., 5 + 3 * 2):", "Calculator");
    }

    // Event handler to play music (dummy implementation)
    void OnPlayMusic(wxCommandEvent &event)
    {
        wxMessageBox("Music playing (dummy implementation).");
    }

    // Event handler for returning to main menu
    void OnReturnToMain(wxCommandEvent &event)
    {
        this->Close();
        mainMenu->Show();
    }
};
