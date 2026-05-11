#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    int clicks = 0, perClick = 1, upgradeCost = 100;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void HoneyClicked(wxCommandEvent& event);
    void Upgrade(wxCommandEvent& event);
    wxStaticBox* Clicks = nullptr;
    wxString getClicks();
    wxButton* Honey = nullptr;
    wxButton* OnMenu = nullptr;
    wxDECLARE_EVENT_TABLE();
};
enum
{
   ID_Upgrade_Menu = 1
};
enum
{
    ID_Honey = 2
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(ID_Upgrade_Menu, MyFrame::Upgrade)
EVT_BUTTON(ID_Honey, MyFrame::HoneyClicked)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Honey Clicker")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&How to play");
    SetMenuBar(menuBar);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::HoneyClicked, this, 2);
    Clicks = new wxStaticBox(this, wxID_ANY, getClicks(), wxPoint(10, 10), wxSize(250, 20));
    OnMenu = new wxButton(this, 1, "100 honey - to double your honey per click", wxPoint(10, 35), wxSize(250, 20));
    Honey = new wxButton(this, 2, "$                     \n\\\\                 \n   _\\\\_________   \n/_____________\\\n/_____________ __\\\n|        HONEY        |\n \\======= ===/ \n \\________ _____ / ", wxPoint(10, 60), wxSize(250, 200));
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Welcome to Honey Clicker! Click the honey to make money, then spend that money on upgrades to get more honey, repeat.", "How to play Honey Clicker");
}
void MyFrame::HoneyClicked(wxCommandEvent& event)
{
    clicks = clicks + perClick;
    Clicks->Destroy();
    Clicks = new wxStaticBox(this, wxID_ANY, getClicks(), wxPoint(10, 10), wxSize(250, 20));
    event.Skip();
}
void MyFrame::Upgrade(wxCommandEvent& event)
{
    if (clicks < upgradeCost)
    {
        wxMessageBox("You do not have enough honey for this upgrade.", "Error not enough honey");
        event.Skip();
    }
    else
    {
        wxString u;
        clicks = clicks - upgradeCost;
        perClick = perClick * 2;
        upgradeCost = upgradeCost * 5;
        u << upgradeCost;
        Clicks->Destroy();
        Clicks = new wxStaticBox(this, wxID_ANY, getClicks(), wxPoint(10, 10), wxSize(250, 20));
        OnMenu->Destroy();
        OnMenu = new wxButton(this, 1, u + " honey - to double your honey per click", wxPoint(10, 35), wxSize(250, 20));
        event.Skip();
    }
}
wxString MyFrame::getClicks()
{
    wxString c;
    c << clicks;
    return c;
}