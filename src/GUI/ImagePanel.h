#include <wx/wx.h>
#include <wx/sizer.h>

class wxImagePanel : public wxPanel {  
public:
    wxImagePanel(wxFrame* parent);
    wxImagePanel(wxFrame* parent, 
                    wxString file, 
                    wxBitmapType format);

    bool loadImage(wxString file, 
                     wxBitmapType format);
    
    void paintEvent(wxPaintEvent & evt);
    void paintNow();   
    void render(wxDC& dc);

    void onSize(wxSizeEvent& event);
    void maxSize(wxMaximizeEvent& event);
    
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */
    
    DECLARE_EVENT_TABLE()
private:
    wxImage image;
    wxBitmap resized;
    int w, h;
    bool pictureLoaded;
    float ratio;
    float zoom; 
};