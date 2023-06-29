#pragma once
#include <array>

#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>
#include <wx/clrpicker.h>
#include <wx/clipbrd.h>
#include <wx/file.h>

#include "Cryptor.h"
#include "PhotoCryptor.h"

class HiddenPhotoFrame : public wxFrame
{
public:
    HiddenPhotoFrame();

private:
    void OnExit(wxCommandEvent& event);

    void OnEncryptionDecryptionChange(wxCommandEvent& event);
    void OnEbcryptionTypeChange(wxCommandEvent& event);
    void OnLoadImages(wxCommandEvent& event);
    void OnStartEncryption(wxCommandEvent& event);
    void OnSaveToFile(wxCommandEvent& event);

    void Repaint(bool mode = false);
    void OpenImage(wxImage* const image, wxString dialogText = "Otwórz plik");

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
    enum EncryptionType : int32_t
    {
        Steganograficzna = 0,
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

    std::unique_ptr<PhotoCryptor::PhotoManager> m_PhotoManager;
    std::unique_ptr<Cryptor::CryptionManager> m_CryptionManager;

    static const wxSize s_MinWindowSize;
};