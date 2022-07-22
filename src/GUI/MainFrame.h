#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "ImagePanel.h"

class MyFrame : public wxFrame
{
public:
    MyFrame(wxWindow *parent, 
            wxWindowID id, 
            const wxString& title, 
            const wxPoint& pos, 
            const wxSize& size, 
            long style);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    enum {
        ID_Hello = 1
    };

    wxImagePanel *drawPanel;
};
