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
