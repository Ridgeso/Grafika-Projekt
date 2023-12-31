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
    void SaveImageToFile(const wxImage& image, wxString dialogName = "Zapisz plik");

    void Repaint(bool mode = false);
    void OpenImage(wxImage* const image, wxString dialogText = "Otw�rz plik");

    wxString GetLoadedImagesString();

private:
    enum EntityID
    {
        ID_HiddenPhoto = 1001,
        ID_ST_EncryptionTypeLabel,
        ID_CB_EncryptDecrypt,
        ID_CO_EncryptionType,
        ID_BT_LoadImage,
        ID_ST_LoadedImagesLabel,
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

    wxStaticText* m_ST_EncryptionTypeLabel;
    wxComboBox* m_CO_EncryptionType;
    wxCheckBox* m_CB_EncryptDecrypt;
    wxButton* m_BT_LoadImage;
    wxStaticText* m_ST_LoadedImagesLabel;

    wxButton* m_BT_StartEncryption;
    wxButton* m_BT_SaveToFile;

    wxPanel* m_P_Picture;


    std::unique_ptr<PhotoCryptor::PhotoManager> m_PhotoManager;
    std::unique_ptr<Cryptor::CryptionManager> m_CryptionManager;


    static const wxSize s_MinWindowSize;
};