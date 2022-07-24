#include <wx/wx.h>
#include <wx/sizer.h>

class EditPanel : public wxPanel {
public: 
    EditPanel(wxFrame* parent);
    int getBrightness() {return brightnessValue;}
private:
    wxBoxSizer *verticalSizer;

    wxCheckBox      *rawDCTenabled;

    wxStaticText    *brightnessName;
    wxSlider        *brightnessSlider;
    wxStaticText    *brightnessValueDisplay;
    wxBoxSizer      *brightnessSizer;
    void            displaySliderChanged(wxScrollEvent &event);
    int             brightnessValue;


    void onSize(wxSizeEvent& event);
    void maxSize(wxMaximizeEvent& event);

    DECLARE_EVENT_TABLE()
};