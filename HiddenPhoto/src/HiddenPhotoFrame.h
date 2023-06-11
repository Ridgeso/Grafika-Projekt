#pragma once
#include <array>

#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>
#include <wx/clrpicker.h>
#include <wx/clipbrd.h>
#include <wx/file.h>

class HiddenPhotoFrame : public wxFrame
{
public:
    HiddenPhotoFrame();

private:
    void OnExit(wxCommandEvent& e);

    void OnEncryptionDecryptionChange(wxCommandEvent& e);
    void OnEbcryptionTypeChange(wxCommandEvent& e);
    void OnLoadImages(wxCommandEvent& e);
    void OnStartEncryption(wxCommandEvent& e);
    void OnSaveToFile(wxCommandEvent& e);

private:
    enum EntityID
    {
        ID_HiddenPhoto = 1001,
        ID_CB_EncryptDecrypt,
        ID_CO_EncryptionType,
        ID_BT_LoadImage,
        ID_BT_StartEncryption,
        ID_BT_SaveToFile,
        ID_P_Picture
    };
    enum EncryptionType
    {
        Steganograficzna,
        Kryptograficzna
    };
    
    wxBoxSizer* m_BS_MainLayout;
    wxBoxSizer* m_BS_ToolBox;
    wxBoxSizer* m_BS_StartSave;

    wxCheckBox* m_CB_EncryptDecrypt;
    wxComboBox* m_CO_EncryptionType;
    wxButton* m_BT_LoadImage;
    wxButton* m_BT_StartEncryption;
    wxButton* m_BT_SaveToFile;

    wxPanel* m_P_Picture;

    wxImage m_SteganoImage;
    std::array<wxImage, 2> m_KryptoImage;

    static const wxSize s_MinWindowSize;
};