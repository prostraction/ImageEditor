#include "MainFrame.h"

MyFrame::MyFrame(wxWindow *parent, 
                    wxWindowID id, 
                    const wxString& title, 
                    const wxPoint& pos, 
                    const wxSize& size, 
                    long style) : wxFrame(parent, id, title, pos, size, style) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );

    CreateStatusBar();

    SetStatusText("Welcome to wxWidgets!");

    // then simply create like this
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    drawPanel = new wxImagePanel(this);// this, wxT("image.jpg"), wxBITMAP_TYPE_JPEG);
    sizer->Add(drawPanel, 1, wxEXPAND);
    this->SetSizer(sizer);

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, 1);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this,
                                _("Open image file"),
                                "",
                                "",
                                "Image files (*.jpeg;*.jpg)|*.jpeg;*.jpg",
                                wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    drawPanel->loadImage(openFileDialog.GetPath(), wxBITMAP_TYPE_JPEG);

}