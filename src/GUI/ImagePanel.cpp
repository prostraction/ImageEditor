#include "ImagePanel.h"


BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(wxImagePanel::paintEvent)
//Size event
EVT_SIZE(wxImagePanel::onSize)
EVT_MAXIMIZE(wxImagePanel::maxSize)
END_EVENT_TABLE()


// some useful events
/*
 void wxImagePanel::mouseMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseDown(wxMouseEvent& event) {}
 void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {}
 void wxImagePanel::mouseReleased(wxMouseEvent& event) {}
 void wxImagePanel::rightClick(wxMouseEvent& event) {}
 void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
 void wxImagePanel::keyPressed(wxKeyEvent& event) {}
 void wxImagePanel::keyReleased(wxKeyEvent& event) {}
 */

wxImagePanel::wxImagePanel(wxFrame* parent) : wxPanel(parent){
    w = 0;
    h = 0;
    pictureLoaded = false;
}

wxImagePanel::wxImagePanel(wxFrame* parent, 
                            wxString file, 
                            wxBitmapType format) :  wxPanel(parent) {
    if (image.LoadFile(file, format)) {
        pictureLoaded = true;
        wxSize size = image.GetSize();
        w = size.GetWidth();
        h = size.GetHeight();
        zoom = 1.0f;
        ratio = float(w) / float(h);
    }
}

bool wxImagePanel::loadImage(wxString file, 
                                wxBitmapType format) {
    if (image.LoadFile(file, format)) {
        pictureLoaded = true;
        wxSize size = image.GetSize();
        w = size.GetWidth();
        h = size.GetHeight();
        zoom = 1.0f;
        ratio = float(w) / float(h);
        return true;
    }
    return false;
}

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
    // depending on your system you may need to look at double-buffered dcs
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow()
{
    // depending on your system you may need to look at double-buffered dcs
    wxClientDC dc(this);
    render(dc);
}

void wxImagePanel::render(wxDC&  dc)
{
    if (!pictureLoaded)
        return;

    int neww, newh;
    GetClientSize( &neww, &newh );
    if (neww > (float)newh * ratio)
        neww = (float)newh * ratio;
    else
        newh = (float)neww / ratio;
       
    if( ( neww != w || newh != h ) && (neww < (w*zoom) && newh < (h*zoom)) )  {
        resized = wxBitmap( image.Scale( neww*zoom, newh*zoom /*, wxIMAGE_QUALITY_HIGH*/ ) );
        dc.DrawBitmap( resized, 0, 0, false );
    } else {
        resized = wxBitmap( image.Scale( w*zoom, h*zoom /*, wxIMAGE_QUALITY_HIGH*/ ) );
        dc.DrawBitmap( resized, 0, 0, false );
    }
}

void wxImagePanel::onSize(wxSizeEvent& event){
    Refresh();
    event.Skip();
}

void wxImagePanel::maxSize(wxMaximizeEvent& event){
    Refresh();
    event.Skip();
}