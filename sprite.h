#include <wx/wx.h>
#include <wx/dcbuffer.h>

class Sprite {
public:
    Sprite(const wxString& filePath, int x, int y)
        : x(x), y(y), width(100), height(100), isDragging(false), isResizing(false), isSelected(false) {

        wxImage image;
        if (image.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
         
            if (!image.HasAlpha()) {
                image.InitAlpha();
            }
            originalBitmap = wxBitmap(image);
            spriteBitmap = wxBitmap(image.Scale(width, height, wxIMAGE_QUALITY_HIGH));
        } else {
            wxLogError("Failed to load image: %s", filePath);
        }
    }

    void Draw(wxDC& dc) {
        if (spriteBitmap.IsOk()) {
           
            dc.DrawBitmap(spriteBitmap, x, y, true);

            if (isSelected) {
                dc.SetPen(*wxRED_PEN);
                dc.SetBrush(*wxTRANSPARENT_BRUSH);
                dc.DrawRectangle(x, y, width, height);
            }
        }
    }

    bool Contains(int mouseX, int mouseY) const {
        return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
    }

    void SetSelected(bool selected) {
        isSelected = selected;
    }

    bool IsSelected() const {
        return isSelected;
    }

    void StartDragging(int mouseX, int mouseY) {
        isDragging = true;
        dragOffsetX = mouseX - x;
        dragOffsetY = mouseY - y;
    }

    void StopDragging() {
        isDragging = false;
    }

    void MoveTo(int mouseX, int mouseY) {
        if (isDragging) {
            x = mouseX - dragOffsetX;
            y = mouseY - dragOffsetY;
        }
    }

    void StartResizing(int mouseX, int mouseY) {
        if (mouseX >= x + width - 10 && mouseY >= y + height - 10) {
            isResizing = true;
        }
    }

    void StopResizing() {
        isResizing = false;
    }

    void Resize(int mouseX, int mouseY) {
        if (isResizing) {
            width = mouseX - x;
            height = mouseY - y;

            // When scaling, ensure the alpha channel is preserved
            wxImage scaledImage = originalBitmap.ConvertToImage().Scale(width, height, wxIMAGE_QUALITY_HIGH);
            if (!scaledImage.HasAlpha()) {
                scaledImage.InitAlpha();  // Reinitialize alpha if needed
            }
            spriteBitmap = wxBitmap(scaledImage);
        }
    }

    bool IsResizing() const {
        return isResizing;
    }

private:
    wxBitmap originalBitmap;
    wxBitmap spriteBitmap;
    int x, y;
    int width, height;
    bool isDragging;
    bool isResizing;
    bool isSelected;

    int dragOffsetX;
    int dragOffsetY;
};
