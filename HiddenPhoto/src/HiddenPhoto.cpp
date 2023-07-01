#include "HPpch.h"
#include "HiddenPhotoFrame.h"

class HiddenPhoto : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(HiddenPhoto);

bool HiddenPhoto::OnInit()
{
    srand(time(0));
    SetProcessDPIAware();
    HiddenPhotoFrame* frame = new HiddenPhotoFrame();
    frame->Show(true);
    return true;
}
