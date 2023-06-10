#include "HPpch.h"
#include "HiddenPhotoFrame.h"

HiddenPhotoFrame::HiddenPhotoFrame()
    : wxFrame(nullptr, ID_HiddenPhoto, "Hidden Photo | Graphics Lab Project")
{
    SetTitle(wxString::FromUTF8("Hidden Photo | Graphics Lab Project"));
    SetIcon(wxNullIcon);
    Center();

    // Events
    Bind(wxEVT_MENU, &HiddenPhotoFrame::OnExit, this, wxID_EXIT);
}

void HiddenPhotoFrame::OnExit(wxCommandEvent& e)
{
    Close(true);
}
