#include "HPpch.h"
#include "SteganografManager.h"


bool SteganografManager::SetImages(const wxImage* referenceImage, const wxImage* sourceImage)
{
    SetDefault();

    if (referenceImage == nullptr || sourceImage == nullptr)
        return false;

    if (referenceImage->IsOk() != true || sourceImage->IsOk() != true)
        return false;

    //ref image and src image must have the same size (algorithm requirement, no other way to determine the end of an image)
    wxSize refSize = referenceImage->GetSize(), srcSize = sourceImage->GetSize();
    if (refSize != srcSize)
        return false;

    this->_referenceImage = referenceImage;
    this->_sourceImage = sourceImage;
    //create a properly sized destination image
    this->_destImage = wxImage(*sourceImage);

    return true;
}

void SteganografManager::SetDefault()
{
    this->_sourceImage = nullptr;
    this->_referenceImage = nullptr;
    this->_destImage = wxImage();

}

bool SteganografManager::IsReady() const
{
    if (this->_sourceImage == nullptr || this->_referenceImage == nullptr)
        return false;

    if (this->_sourceImage->IsOk() != true)
        return false;
    if (this->_referenceImage->IsOk() != true)
        return false;

    return true;
}

std::pair<const Cryptor::Image, const Cryptor::Image> SteganografManager::GetCryptorData() const
{
    if (IsReady() != true)
        return std::pair<const Cryptor::Image, const Cryptor::Image>(Cryptor::Image(), Cryptor::Image());

    const Cryptor::Image refImage = {
        _referenceImage->GetWidth(),
        _referenceImage->GetHeight(),
        3,
        _referenceImage->GetData()
    };
    const Cryptor::Image srcImage = {
        _sourceImage->GetWidth(),
        _sourceImage->GetHeight(),
        3,
        _sourceImage->GetData()
    };

    return std::make_pair(srcImage, refImage);
}
