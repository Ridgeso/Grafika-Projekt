#pragma once

#include "HPpch.h"
#include "Cryptor.h"

class KryptografManager
{
private:

	const wxImage* _sourceImage = nullptr;	//image for encryption
	const wxImage* _encrypted1 = nullptr;	//image 1 for decryption
	const wxImage* _encrypted2 = nullptr;	//image 2 for decryption

public:

	bool SetImageForEncryption(const wxImage* image);
	bool SetImagesForDecryption(const wxImage* image1, const wxImage* image2);
	void SetDefault();

	bool IsEncryptionReady() const;
	bool IsDecryptionReady() const;

	std::pair<const Cryptor::Image, const Cryptor::Image> GetDecryptorData() const;
	const Cryptor::Image GetCryptorData() const;
};

