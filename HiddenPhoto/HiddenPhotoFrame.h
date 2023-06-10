#pragma once
#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>
#include <wx/clrpicker.h>
#include <wx/clipbrd.h>

class HiddenPhotoFrame : public wxFrame
{
public:
    HiddenPhotoFrame();

private:
    void OnExit(wxCommandEvent& e);

private:
    enum EntityID
    {
        ID_HiddenPhoto
    };
};