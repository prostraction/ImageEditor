#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>

#define DEBUG_EDIT

class EditPanel : public wxPanel {
public: 
    EditPanel(wxFrame* parent);
    int getBrightness() {return brightnessValue;}
private:
    wxBoxSizer*     verticalSizer;

#ifdef DEBUG_EDIT
    wxCheckBox*     rawDCTenabled;
    int*            rawDCTvalues;
    wxGrid*         rawDCTvaluesGrid;
#endif

    wxStaticText*   brightnessName;
    wxSlider*       brightnessSlider;
    wxStaticText*   brightnessValueDisplay;
    wxBoxSizer*     brightnessSizer;
    int             brightnessValue;


    void onSize(wxSizeEvent& event);
    void maxSize(wxMaximizeEvent& event);
    void displaySliderChanged(wxScrollEvent &event);

#ifdef DEBUG_EDIT
    void rawDCTvaluesGridChanged(wxGridEvent& event);
#endif

    DECLARE_EVENT_TABLE()
};