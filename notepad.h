#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>

class NotepadFrame : public wxFrame {
public:
    NotepadFrame(wxWindow* parent)
        : wxFrame(parent, wxID_ANY, "Notepad", wxDefaultPosition, wxSize(600, 400)), mainMenu(parent) {


        textCtrl = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(600, 350), wxTE_MULTILINE);


        textCtrl->SetFocus();


        wxMenuBar* menuBar = new wxMenuBar();

        wxMenu* fileMenu = new wxMenu();
        fileMenu->Append(wxID_NEW, "&New\tCtrl-N", "Create a new document");
        fileMenu->Append(wxID_OPEN, "&Open\tCtrl-O", "Open an existing document");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save the current document");
        fileMenu->Append(wxID_SAVEAS, "Save &As\tCtrl-Shift-S", "Save the document with a new name");
        fileMenu->AppendSeparator();
        fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the notepad");

        wxMenu* textColorMenu = new wxMenu();
        textColorMenu->Append(ID_TEXT_COLOR, "Text Color", "Change the text color");

        wxMenu* fontSizeMenu = new wxMenu();
        fontSizeMenu->Append(ID_FONT_SIZE, "Font Size", "Change the text size");

        wxMenu* fontStyleMenu = new wxMenu();
        fontStyleMenu->Append(ID_FONT_STYLE, "Font Style", "Change the text font style");

        menuBar->Append(fileMenu, "&File");
        menuBar->Append(textColorMenu, "&TextColor");
        menuBar->Append(fontSizeMenu, "&FontSize");
        menuBar->Append(fontStyleMenu, "&FontStyle");


        SetMenuBar(menuBar);

        Bind(wxEVT_MENU, &NotepadFrame::OnNew, this, wxID_NEW);
        Bind(wxEVT_MENU, &NotepadFrame::OnOpen, this, wxID_OPEN);
        Bind(wxEVT_MENU, &NotepadFrame::OnSave, this, wxID_SAVE);
        Bind(wxEVT_MENU, &NotepadFrame::OnSaveAs, this, wxID_SAVEAS);
        Bind(wxEVT_MENU, &NotepadFrame::OnExit, this, wxID_EXIT);

        Bind(wxEVT_MENU, &NotepadFrame::OnTextColor, this, ID_TEXT_COLOR);
        Bind(wxEVT_MENU, &NotepadFrame::OnFontSize, this, ID_FONT_SIZE);
        Bind(wxEVT_MENU, &NotepadFrame::OnFontStyle, this, ID_FONT_STYLE);
    }

private:
    wxRichTextCtrl* textCtrl;
    wxWindow* mainMenu;

    static const int ID_TEXT_COLOR = wxID_HIGHEST + 1;
    static const int ID_FONT_SIZE = wxID_HIGHEST + 2;
    static const int ID_FONT_STYLE = wxID_HIGHEST + 3;


    void OnNew(wxCommandEvent& event) {
        textCtrl->Clear();
    }

    void OnOpen(wxCommandEvent& event) {
        wxFileDialog openFileDialog(this, "Open Text File", "", "",
                                    "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openFileDialog.ShowModal() == wxID_OK) {
            textCtrl->LoadFile(openFileDialog.GetPath());
        }
    }

    void OnSave(wxCommandEvent& event) {
        wxFileDialog saveFileDialog(this, "Save Text File", "", "",
                                    "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_OK) {
            textCtrl->SaveFile(saveFileDialog.GetPath());
        }
    }

    void OnSaveAs(wxCommandEvent& event) {
        wxFileDialog saveFileDialog(this, "Save As Text File", "", "",
                                    "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_OK) {
            textCtrl->SaveFile(saveFileDialog.GetPath());
        }
    }

    void OnExit(wxCommandEvent& event) {
        this->Close();
        mainMenu->Show();
    }




void OnTextColor(wxCommandEvent& event) {

    wxColourDialog colorDlg(this);
    if (colorDlg.ShowModal() == wxID_OK) {
        wxColour color = colorDlg.GetColourData().GetColour();


        wxRichTextAttr attr;
        attr.SetTextColour(color);


    }
}





    void OnFontSize(wxCommandEvent& event) {

        wxTextEntryDialog dialog(this, "Enter font size:", "Font Size", "12");
        if (dialog.ShowModal() == wxID_OK) {

            long fontSize;
            if (dialog.GetValue().ToLong(&fontSize)) {
                wxFont font = textCtrl->GetFont();
                font.SetPointSize(fontSize);
                textCtrl->SetFont(font);
            }
        }
    }

    void OnFontStyle(wxCommandEvent& event) {
        wxFontDialog fontDlg(this);
        if (fontDlg.ShowModal() == wxID_OK) {
            wxFont font = fontDlg.GetFontData().GetChosenFont();
            textCtrl->SetFont(font);
        }
    }
};


