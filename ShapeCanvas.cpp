#include "ShapeCanvas.h"
#include <cmath> // For polygon calculations

ShapeCanvas::ShapeCanvas(wxWindow* parent) : wxPanel(parent), m_currentColor(wxColour(255, 0, 0)) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* row1Sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* row2Sizer = new wxBoxSizer(wxHORIZONTAL);

    // Tool Panel (Column 1, Row 1)
    m_toolPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* toolSizer = new wxBoxSizer(wxVERTICAL);

    // Shape button
    m_shapeButton = new wxButton(m_toolPanel, wxID_ANY, "Shape");

    // Sides dropdown
    wxArrayString sides;
    sides.Add("3");
    sides.Add("4");
    sides.Add("5");
    sides.Add("6");
    sides.Add("7");
    sides.Add("8");
    m_sidesChoice = new wxChoice(m_toolPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, sides);
    m_sidesChoice->SetSelection(0); // Default to 3 sides

    // Color dropdown
    wxArrayString colors;
    colors.Add("Red");
    colors.Add("Green");
    colors.Add("Blue");
    colors.Add("Yellow");
    colors.Add("Black");
    m_colorChoice = new wxChoice(m_toolPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, colors);
    m_colorChoice->SetSelection(0); // Default to Red

    toolSizer->Add(m_shapeButton, 0, wxALL, 5);
    toolSizer->Add(new wxStaticText(m_toolPanel, wxID_ANY, "Sides:"), 0, wxALL, 5);
    toolSizer->Add(m_sidesChoice, 0, wxALL, 5);
    toolSizer->Add(new wxStaticText(m_toolPanel, wxID_ANY, "Color:"), 0, wxALL, 5);
    toolSizer->Add(m_colorChoice, 0, wxALL, 5);
    m_toolPanel->SetSizer(toolSizer);

    // Plot Panel (Column 2, Row 1)
    m_plotPanel = new wxPanel(this, wxID_ANY);
    m_plotPanel->SetBackgroundColour(wxColour(255, 255, 255));

    // Dimension Input (Column 1, Row 2)
    wxPanel* dimensionPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* dimensionSizer = new wxBoxSizer(wxHORIZONTAL);

    m_dimensionInput = new wxTextCtrl(dimensionPanel, wxID_ANY, "2.0");
    m_textInput = new wxTextCtrl(dimensionPanel, wxID_ANY, "Enter Text");
    m_plotButton = new wxButton(dimensionPanel, wxID_ANY, "Plot");
    m_clearButton = new wxButton(dimensionPanel, wxID_ANY, "Clear");

    dimensionSizer->Add(new wxStaticText(dimensionPanel, wxID_ANY, "Dimensions:"), 0, wxALL, 5);
    dimensionSizer->Add(m_dimensionInput, 0, wxALL, 5);
    dimensionSizer->Add(m_textInput, 0, wxALL, 5);
    dimensionSizer->Add(m_plotButton, 0, wxALL, 5);
    dimensionSizer->Add(m_clearButton, 0, wxALL, 5);
    dimensionPanel->SetSizer(dimensionSizer);

    // Add panels to sizers
    row1Sizer->Add(m_toolPanel, 1, wxEXPAND | wxALL, 5);
    row1Sizer->Add(m_plotPanel, 3, wxEXPAND | wxALL, 5);
    row2Sizer->Add(dimensionPanel, 1, wxEXPAND | wxALL, 5);

    mainSizer->Add(row1Sizer, 3, wxEXPAND);
    mainSizer->Add(row2Sizer, 1, wxEXPAND);
    SetSizer(mainSizer);

    // Bind events
    m_shapeButton->Bind(wxEVT_BUTTON, &ShapeCanvas::OnShapeButtonClick, this);
    m_plotButton->Bind(wxEVT_BUTTON, &ShapeCanvas::OnPlotButtonClick, this);
    m_clearButton->Bind(wxEVT_BUTTON, &ShapeCanvas::OnClearButtonClick, this);
    m_colorChoice->Bind(wxEVT_CHOICE, &ShapeCanvas::OnColorChoice, this);
    m_plotPanel->Bind(wxEVT_PAINT, &ShapeCanvas::OnPaint, this);
}

void ShapeCanvas::AddShape(int sides, double size) {
    // Convert size from cm to pixels (1 cm = 50 pixels)
    int radius = static_cast<int>(size * 25); // Radius for polygon

    // Center the shape in the plotting area
    wxSize plotSize = m_plotPanel->GetSize();
    int centerX = plotSize.GetWidth() / 2;
    int centerY = plotSize.GetHeight() / 2;

    // Calculate polygon points
    std::vector<wxPoint> points;
    for (int i = 0; i < sides; ++i) {
        double angle = 2 * M_PI * i / sides;
        int x = centerX + radius * cos(angle);
        int y = centerY + radius * sin(angle);
        points.push_back(wxPoint(x, y));
    }

    // Add the new shape to the front of the list (so it's drawn last)
    m_shapes.insert(m_shapes.begin(), points);
    m_plotPanel->Refresh();
}

void ShapeCanvas::AddText(const wxString& text) {
    // Add the new text to the front of the list (so it's drawn last)
    m_texts.insert(m_texts.begin(), std::make_pair(text, m_currentColor));
    m_plotPanel->Refresh();
}

void ShapeCanvas::ClearPlottingArea() {
    m_shapes.clear();
    m_texts.clear();
    m_plotPanel->Refresh();
}

void ShapeCanvas::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(m_plotPanel);

    // Draw shapes in reverse order (oldest first, newest last)
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it) {
        dc.SetPen(wxPen(m_currentColor));
        dc.SetBrush(wxBrush(m_currentColor));
        dc.DrawPolygon(it->size(), it->data());
    }

    // Draw text with respective colors
    int y = 10;
    for (const auto& text : m_texts) {
        dc.SetTextForeground(text.second); // Set text color
        dc.DrawText(text.first, wxPoint(10, y));
        y += 20;
    }
}

void ShapeCanvas::OnPlotButtonClick(wxCommandEvent& event) {
    // Plot text from the text input field
    wxString text = m_textInput->GetValue();
    if (!text.IsEmpty()) {
        AddText(text);
    }
}

void ShapeCanvas::OnShapeButtonClick(wxCommandEvent& event) {
    int sides = wxAtoi(m_sidesChoice->GetStringSelection());
    double size = wxAtof(m_dimensionInput->GetValue());

    // Plot the shape with the selected number of sides
    AddShape(sides, size);
}

void ShapeCanvas::OnClearButtonClick(wxCommandEvent& event) {
    ClearPlottingArea();
}

void ShapeCanvas::OnColorChoice(wxCommandEvent& event) {
    wxString color = m_colorChoice->GetStringSelection();
    if (color == "Red") {
        m_currentColor = wxColour(255, 0, 0);
    } else if (color == "Green") {
        m_currentColor = wxColour(0, 255, 0);
    } else if (color == "Blue") {
        m_currentColor = wxColour(0, 0, 255);
    } else if (color == "Yellow") {
        m_currentColor = wxColour(255, 255, 0);
    } else if (color == "Black") {
        m_currentColor = wxColour(0, 0, 0);
    }
}
