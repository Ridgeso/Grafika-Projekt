#include "HPpch.h"

#include <wx/filedlg.h>

#include "HiddenPhotoFrame.h"

const wxSize HiddenPhotoFrame::s_MinWindowSize = { 1280, 720};

HiddenPhotoFrame::HiddenPhotoFrame()
    : wxFrame(nullptr, ID_HiddenPhoto, "Hidden Photo | Graphics Lab Project"),
    m_SteganoImage(), m_KryptoImage{}
{
    m_PhotoManager = std::make_unique<Cryptor::PhotoManager>();
    m_CryptionManager= std::make_unique<Cryptor::CryptionManager>();

    SetIcon(wxNullIcon);

    // Layout
    m_BS_MainLayout = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_BS_MainLayout);
    SetAutoLayout(true);

    m_BS_ToolBox = new wxBoxSizer(wxVERTICAL);
    m_BS_MainLayout->Add(m_BS_ToolBox, 0, wxEXPAND | wxALL, 5);

    m_CB_EncryptDecrypt = new wxCheckBox(
        this,
        ID_CB_EncryptDecrypt,
        _("Kodowanie"),
        wxPoint(0, 0),
        wxSize(75, 30),
        0,
        wxDefaultValidator,
        _("m_CB_EncryptDecrypt")
    );
    m_BS_ToolBox->Add(m_CB_EncryptDecrypt, 0, wxALIGN_CENTER | wxALL, 5);
    
    const wxString encryptionOptions[] = { _("Steganograficzna"), _("Kryptograficzna") };
    m_CO_EncryptionType = new wxComboBox(
        this,
        ID_CO_EncryptionType,
        encryptionOptions[0],
        wxPoint(0, 0),
        wxSize(125, 20),
        { 2, encryptionOptions },
        0,
        wxDefaultValidator,
        _("m_CBShapes")
    );
    m_BS_ToolBox->Add(m_CO_EncryptionType, 0, wxALIGN_CENTER | wxALL, 5);
    
    m_BT_LoadImage = new wxButton(
        this,
        ID_BT_LoadImage,
        _("Za³aduj obraz"),
        wxPoint(0, 0),
        wxSize(100, 30),
        0,
        wxDefaultValidator,
        _("m_BT_LoadImage")
    );
    m_BS_ToolBox->Add(m_BT_LoadImage, 0, wxALIGN_CENTER | wxALL, 5);

    m_BS_StartSave = new wxBoxSizer(wxHORIZONTAL);
    m_BS_ToolBox->Add(m_BS_StartSave, 1, wxEXPAND | wxALL, 5);

    m_BT_StartEncryption = new wxButton(
        this,
        ID_BT_StartEncryption,
        _("Zakoduj obraz"),
        wxPoint(0, 0),
        wxSize(100, 30),
        0,
        wxDefaultValidator,
        _("m_BT_StartEncryption")
    );
    m_BS_StartSave->Add(m_BT_StartEncryption, 0, wxALIGN_BOTTOM | wxLEFT | wxRIGHT, 5);
    
    m_BT_SaveToFile = new wxButton(
        this,
        ID_BT_SaveToFile,
        _("Zapis do pliku"),
        wxPoint(0, 0),
        wxSize(100, 30),
        0,
        wxDefaultValidator,
        _("m_BT_SaveToFile")
    );
    m_BS_StartSave->Add(m_BT_SaveToFile, 0, wxALIGN_BOTTOM | wxLEFT, 5);

    m_P_Picture = new wxPanel(this, ID_P_Picture, wxPoint(0, 0), s_MinWindowSize - wxSize(200, 0));
    m_BS_MainLayout->Add(m_P_Picture, 1, wxEXPAND | wxALL, 5);

    Layout();
    GetSizer()->SetSizeHints(this);
    Center();

    // Events
    Bind(wxEVT_MENU, &HiddenPhotoFrame::OnExit, this, wxID_EXIT);

    Bind(wxEVT_CHECKBOX, &HiddenPhotoFrame::OnEncryptionDecryptionChange, this, ID_CB_EncryptDecrypt);
    Bind(wxEVT_COMBOBOX, &HiddenPhotoFrame::OnEbcryptionTypeChange, this, ID_CO_EncryptionType);
    Bind(wxEVT_BUTTON, &HiddenPhotoFrame::OnLoadImages, this, ID_BT_LoadImage);
    Bind(wxEVT_BUTTON, &HiddenPhotoFrame::OnStartEncryption, this, ID_BT_StartEncryption);
    Bind(wxEVT_BUTTON, &HiddenPhotoFrame::OnSaveToFile, this, ID_BT_SaveToFile);

    wxInitAllImageHandlers();
}

void HiddenPhotoFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void HiddenPhotoFrame::OnEncryptionDecryptionChange(wxCommandEvent& event)
{
}

void HiddenPhotoFrame::OnEbcryptionTypeChange(wxCommandEvent& event)
{
}

void HiddenPhotoFrame::OnLoadImages(wxCommandEvent& event)
{
}

void HiddenPhotoFrame::OnStartEncryption(wxCommandEvent& event)
{
}

void HiddenPhotoFrame::OnSaveToFile(wxCommandEvent& event)
{
}
