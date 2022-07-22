#include <wx/wx.h>
#include <wx/sizer.h>

class EditPanel : public wxPanel {
public: 
    EditPanel(wxFrame* parent);
private:
    wxButton *brightnessButton;


    float brightness;

    void onSize(wxSizeEvent& event);
    void maxSize(wxMaximizeEvent& event);

    DECLARE_EVENT_TABLE()
};