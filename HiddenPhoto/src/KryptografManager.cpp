#include "HPpch.h"
#include "KryptografManager.h"

bool KryptografManager::SetImageForEncryption(const wxImage* image)
{
    SetDefault();

    if (image == nullptr || image->IsOk() != true)
        return false;

    this->_sourceImage = image;

    return true;
}

bool KryptografManager::SetImagesForDecryption(const wxImage* image1, const wxImage* image2)
{
    SetDefault();
 
    if (image1 == nullptr || image2 == nullptr)
        return false;

    if (image1->IsOk() != true || image2->IsOk() != true)
        return false;

    this->_encrypted1 = image1;
    this->_encrypted2 = image2;
    
    return true;
}

void KryptografManager::SetDefault()
{
    this->_sourceImage = nullptr;
    this->_encrypted1 = nullptr;
    this->_encrypted2 = nullptr;
}

bool KryptografManager::IsEncryptionReady() const
{
    if (_sourceImage == nullptr || _sourceImage->IsOk() != true)
        return false;
    return true;
}

bool KryptografManager::IsDecryptionReady() const
{
    if (_encrypted1 == nullptr || _encrypted2 == nullptr)
        return false;
    if (_encrypted1->IsOk() != true || _encrypted2->IsOk() != true)
        return false;
    return true;
}

std::pair<const Cryptor::Image, const Cryptor::Image> KryptografManager::GetDecryptorData() const
{
    if(IsDecryptionReady() != true)
        return std::pair<const Cryptor::Image, const Cryptor::Image>();
    
    Cryptor::Image image1 = {
        .Width = _encrypted1->GetWidth(),
        .Height = _encrypted1->GetHeight(),
        .Channel = 3,
        .Data = _encrypted1->GetData()
    };
    Cryptor::Image image2 = {
        .Width = _encrypted2->GetWidth(),
        .Height = _encrypted2->GetHeight(),
        .Channel = 3,
        .Data = _encrypted2->GetData()
    };
    return std::make_pair(image1, image2);
}

const Cryptor::Image KryptografManager::GetCryptorData() const
{
    if(IsEncryptionReady() != true)
        return Cryptor::Image();

    Cryptor::Image image = {
        .Width = _sourceImage->GetWidth(),
        .Height = _sourceImage->GetHeight(),
        .Channel = 3,
        .Data = _sourceImage->GetData()
    };
    return image;
}
