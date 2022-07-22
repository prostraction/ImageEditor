#include "EditPanel.h"


BEGIN_EVENT_TABLE(EditPanel, wxPanel)
//Size event
EVT_SIZE(EditPanel::onSize)
EVT_MAXIMIZE(EditPanel::maxSize)
END_EVENT_TABLE()

EditPanel::EditPanel(wxFrame* parent) : wxPanel(parent) { 
    brightnessButton = new wxButton(this, wxID_ANY, "Brightness");

    brightness = 0.0f;
}




void EditPanel::onSize(wxSizeEvent& event) {
    //Refresh();
    event.Skip();
}

void EditPanel::maxSize(wxMaximizeEvent& event) {
    //Refresh();
    event.Skip();
}