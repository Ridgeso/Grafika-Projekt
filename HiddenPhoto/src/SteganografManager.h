#pragma once

#include "HPpch.h"

class SteganografManager
{
private:

	const wxImage* _referenceImage = nullptr;
	const wxImage* _sourceImage = nullptr;	//image for encryption or decryption

	wxImage _destImage;	//image for storing encryption/decryption results


public:

	bool SetImages(const wxImage* referenceImage, const wxImage* sourceImage);
	void SetDefault();

	bool IsReady() const;


};

