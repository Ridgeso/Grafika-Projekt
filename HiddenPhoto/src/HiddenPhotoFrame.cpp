#include "HPpch.h"

#include <wx/filedlg.h>

#include "HiddenPhotoFrame.h"

const wxSize HiddenPhotoFrame::s_MinWindowSize = { 1280, 720};

HiddenPhotoFrame::HiddenPhotoFrame()
    : wxFrame(nullptr, ID_HiddenPhoto, "Hidden Photo | Graphics Lab Project"),
    m_SteganoImage(), m_KryptoImage{}
{
    m_PhotoManager = std::make_unique<PhotoCryptor::PhotoManager>();
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
        _("Dekodowanie"),
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
    m_CO_EncryptionType->SetSelection(0);
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
    Repaint();
}

void HiddenPhotoFrame::OnEbcryptionTypeChange(wxCommandEvent& event)
{
    Repaint();
}

void HiddenPhotoFrame::OnLoadImages(wxCommandEvent& event)
{
    wxImage image;
    OpenImage(&image);
    if (!image.IsOk())
        return;

    //true if decrypting, false if encrypting
    bool decrypt = m_CB_EncryptDecrypt->GetValue();

    switch (m_CO_EncryptionType->GetSelection())
    {
        case wxNOT_FOUND:
        {
            wxMessageBox(wxT("Nieprawid³owy typ kodowania."), "Error", wxOK | wxICON_ERROR);
            break;
        }
        case EncryptionType::Steganograficzna:
        {
            wxImage referenceImage;
            OpenImage(&referenceImage, "Otwórz plik referencyjny");

            bool allOk = m_PhotoManager->SetSteganografImage(image, referenceImage, !decrypt);
            if (!allOk)
            {
                wxMessageBox(wxT("B³¹d wczytywania obrazów lub\nobrazy maj¹ ró¿ne rozmiary"), "Error", wxOK | wxICON_ERROR);
                break;
            }
            if (!decrypt)
            {
                if (m_PhotoManager->IsImageBlackAndWhite(image) != true)
                {
                    wxMessageBox(wxT("Obraz do zakodowania zostanie przetransformowany na czarno-bia³y."), "Error", wxOK | wxICON_INFORMATION);
                    m_PhotoManager->ConvertToBlackAndWhite(image, 180);
                    //check is not needed here as it was performed earlier
                    m_PhotoManager->SetSteganografImage(image, referenceImage, !decrypt);
                }
            }
            break;
        }
        case EncryptionType::Kryptograficzna:
        {
            if (!decrypt)
                m_PhotoManager->SetKryptografEncryptImage(image);
            else
            {
                wxImage encrypted2;
                OpenImage(&encrypted2);

                m_PhotoManager->SetKryptografDecryptImages(image, encrypted2);
            }
            break;
        }
    }

    Repaint();
}

void HiddenPhotoFrame::OnStartEncryption(wxCommandEvent& event)
{
    bool decrypt = m_CB_EncryptDecrypt->GetValue();

    switch (m_CO_EncryptionType->GetSelection())
    {
        case wxNOT_FOUND:
        {
            wxMessageBox(wxT("Nieprawid³owy typ kodowania."), "Error", wxOK | wxICON_ERROR);
            break;
        }
        case EncryptionType::Steganograficzna:
        {
            bool allOk = true;
            if (!decrypt)
            {
                if (m_PhotoManager->GetSteganografEncImage().IsOk() && m_PhotoManager->IsSteganografReady())
                    m_CryptionManager->EncryptSteganograficzna(*m_PhotoManager);
                else
                    allOk = false;
            }
            else
            {
                if (m_PhotoManager->GetSteganografDecImage().IsOk() && m_PhotoManager->IsSteganografReady())
                    m_CryptionManager->DecryptSteganograficzna(*m_PhotoManager);
                else
                    allOk = false;
            }
            if(!allOk)
                wxMessageBox(wxT("Operacja nie mog³a zostaæ rozpoczêta.\nUpewnij siê, ¿e obrazy s¹ za³adowane odpowiednio."), "Error", wxOK | wxICON_ERROR);
            break;
        }
        case EncryptionType::Kryptograficzna:
        {
            if (!decrypt)
            {
                if (m_PhotoManager->GetKryptografEncImage().IsOk())
                    m_CryptionManager->EncryptKryptograficzna(*m_PhotoManager);
            }
            else
            {
                auto& validatorKryptografDec = m_PhotoManager->GetKryptografDecImage();
                if (validatorKryptografDec.first.IsOk() && validatorKryptografDec.second.IsOk())
                    m_CryptionManager->DecryptKryptograficzna(*m_PhotoManager);
            }
            break;
        }
    }

    Repaint(true);
}

void HiddenPhotoFrame::OnSaveToFile(wxCommandEvent& event)
{
    const wxImage* image = nullptr;
  
    bool decrypt = m_CB_EncryptDecrypt->GetValue();
    
    switch (m_CO_EncryptionType->GetSelection())
    {
    case EncryptionType::Steganograficzna:
    {
        //image was saved in the unused wxImage object
        if (decrypt)
        {
            image = &m_PhotoManager->GetSteganografEncImage();
        }
        else
        {
            image = &m_PhotoManager->GetSteganografDecImage();
        }
        break;
    }
    case EncryptionType::Kryptograficzna:
    {
        if (decrypt)
        {
            image = &m_PhotoManager->GetKryptografEncImage();
        }
        else
        {
            std::pair<const wxImage, const wxImage> images = m_PhotoManager->GetKryptografDecImage();
            SaveImageToFile(images.first, "Zapisz pierwszy zakodowany plik");
            SaveImageToFile(images.second, "Zapisz drugi zakodowany plik");
            return;
        }
        break;
    }
    default:
    {
        wxMessageBox(wxT("Nieprawod³owy rodzaj kodowania"), "Error", wxOK | wxICON_ERROR);
        return;
    }
    }
    if (image == nullptr)
    {
        wxMessageBox(wxT("B³¹d zapisu pliku"), "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxString dialogName = decrypt ? "Zapisz zdekodowany plik" : "Zapisz zakodowany plik";
    SaveImageToFile(*image, dialogName);
}

void HiddenPhotoFrame::SaveImageToFile(const wxImage& image, wxString dialogName)
{
    wxFileDialog saveFileDialog(
        this,
        dialogName,
        "",
        "",
        "PNG File (*.png;)|*.png;",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    auto result = saveFileDialog.ShowModal();
    
    if (result != wxID_OK)
        return;
    
    image.SaveFile(saveFileDialog.GetPath(), wxBITMAP_TYPE_PNG);
}

void HiddenPhotoFrame::Repaint(bool mode)
{
    wxClientDC dc(m_P_Picture);
    m_P_Picture->PrepareDC(dc);
    wxImage image;
    bool encryptDecryptMode = mode ^ m_CB_EncryptDecrypt->GetValue();

    switch (m_CO_EncryptionType->GetSelection())
    {
        case wxNOT_FOUND:
        {
            wxMessageBox(wxT("Nieprawid³owy typ kodowania."), "Error", wxOK | wxICON_ERROR);
            break;
        }
        case EncryptionType::Steganograficzna:
        {
            image = encryptDecryptMode ?
                m_PhotoManager->GetSteganografDecImage() : m_PhotoManager->GetSteganografEncImage();
            break;
        }
        case EncryptionType::Kryptograficzna:
        {
            if (encryptDecryptMode)
            {
                const auto& [decrypt1, decrypt2] = m_PhotoManager->GetKryptografDecImage();
                image = decrypt1;

                if (decrypt2.IsOk())
                {
                    wxBitmap bitmap(decrypt2);
                    dc.DrawBitmap(bitmap, s_MinWindowSize.x / 2, 0, true);
                }
            }
            else
                image = m_PhotoManager->GetKryptografEncImage();
            break;
        }
    }
    
    if (image.IsOk() != true)
    {
        return;
    }

    if (image.IsOk())
    {
        wxBitmap bitmap(image);
        dc.Clear();
        dc.DrawBitmap(bitmap, 0, 0, true);
    }
}

void HiddenPhotoFrame::OpenImage(wxImage* const image, wxString dialogText)
{
    if (image == nullptr)
    {
        wxMessageBox(wxT("Nie da siê przechowaæ obrazu."), "Error", wxOK | wxICON_ERROR);
        return;
    }

    wxFileDialog loadFileDialog(
        this,
        dialogText,
        "",
        "",
        "Image Files (*.bmp;*.png;*.jpg)|*.bmp;*.png;*.jpg",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (loadFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString imagePath = loadFileDialog.GetPath();
    if (!image->LoadFile(imagePath))
        wxMessageBox(wxT("Nie uda³o siê wczytaæ plik."), "Error", wxOK | wxICON_ERROR);
}
