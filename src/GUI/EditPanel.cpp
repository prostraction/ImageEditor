#include "EditPanel.h"


BEGIN_EVENT_TABLE(EditPanel, wxPanel)
    EVT_COMMAND_SCROLL(10000, EditPanel::displaySliderChanged)

    //Size event
    EVT_SIZE(EditPanel::onSize)
    EVT_MAXIMIZE(EditPanel::maxSize)
END_EVENT_TABLE()

EditPanel::EditPanel(wxFrame* parent) : wxPanel(parent) { 
    verticalSizer = new wxBoxSizer(wxVERTICAL);

    rawDCTvalues = new wxGrid(this, 9999);
    rawDCTvalues->CreateGrid(8, 8);
    rawDCTvalues->HideColLabels();
    rawDCTvalues->HideRowLabels();

    for (int i = 0; i < 8; i++) {
        rawDCTvalues->SetColSize(i, 50);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            rawDCTvalues->SetCellValue(i, j, wxString::Format(wxT("%i"), 0));
            rawDCTvalues->SetCellAlignment(i, j, wxALIGN_CENTRE, wxALIGN_CENTRE);
        }
    }

    verticalSizer->Add(rawDCTvalues, 0, wxALL, 20);

    brightnessValue = 0;
    brightnessSizer         = new wxBoxSizer(wxHORIZONTAL);
    brightnessName          = new wxStaticText(this, wxID_ANY, "Brightness: ");
    brightnessSlider        = new wxSlider(this, 10000, 0, -100, 100, wxDefaultPosition, wxSize(290, 30));
    brightnessValueDisplay  = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%d"), brightnessValue)); 
    brightnessSizer->Add(brightnessName,            0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    brightnessSizer->Add(brightnessSlider,          0, wxALL | wxALIGN_CENTER_VERTICAL, 0);
    brightnessSizer->Add(brightnessValueDisplay,    0, wxALL | wxALIGN_CENTER_VERTICAL, 20);
    verticalSizer->Add(brightnessSizer, 0, wxEXPAND);


    this->SetSizer(verticalSizer);
}

void EditPanel::onSize(wxSizeEvent& event) {
    event.Skip();
}

void EditPanel::maxSize(wxMaximizeEvent& event) {
    event.Skip();
}

void EditPanel::displaySliderChanged(wxScrollEvent &event) {
    brightnessValue = brightnessSlider->GetValue();
    brightnessValueDisplay->SetLabel(wxString::Format(wxT("%d"), brightnessValue));
    event.Skip();
}