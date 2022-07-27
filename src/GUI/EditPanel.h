#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

class EditPanel : public wxPanel {
public: 
    EditPanel(wxFrame* parent);
    int getBrightness() {return brightnessValue;}
private:
    wxBoxSizer*     verticalSizer;

    wxCheckBox*     rawDCTenabled;
    int*            rawDCTvalues;

    wxGrid *rawDCTvalues;

    wxStaticText*   brightnessName;
    wxSlider*       brightnessSlider;
    wxStaticText*   brightnessValueDisplay;
    wxBoxSizer*     brightnessSizer;
    int             brightnessValue;


    void onSize(wxSizeEvent& event);
    void maxSize(wxMaximizeEvent& event);
    void displaySliderChanged(wxScrollEvent &event);
    void rawDCTvaluesChanged();

    DECLARE_EVENT_TABLE()
};