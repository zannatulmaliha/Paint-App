#ifndef SHAPE_CANVAS_H
#define SHAPE_CANVAS_H

#include <wx/wx.h>
#include <vector>

class ShapeCanvas : public wxPanel {
public:
    ShapeCanvas(wxWindow* parent);

    void AddShape(int sides, double size = 2.0);
    void AddText(const wxString& text);
    void ClearPlottingArea();

private:
    wxPanel* m_toolPanel;
    wxPanel* m_plotPanel;
    wxTextCtrl* m_dimensionInput;
    wxTextCtrl* m_textInput;
    wxButton* m_plotButton;
    wxButton* m_clearButton;
    wxButton* m_shapeButton;
    wxChoice* m_colorChoice;
    wxChoice* m_sidesChoice;

    std::vector<std::vector<wxPoint>> m_shapes; // Store polygon points
    std::vector<std::pair<wxString, wxColour>> m_texts; // Store text with color

    wxColour m_currentColor;

    void OnPaint(wxPaintEvent& event);
    void OnPlotButtonClick(wxCommandEvent& event);
    void OnShapeButtonClick(wxCommandEvent& event);
    void OnClearButtonClick(wxCommandEvent& event);
    void OnColorChoice(wxCommandEvent& event);
};

#endif // SHAPE_CANVAS_H
