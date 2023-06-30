#include "HPpch.h"

#include "PhotoCryptor.h"


namespace PhotoCryptor
{

	const wxImage& PhotoManager::GetSteganografEncImage() const
	{
		return m_EncryptSteganografImage;
	}

	const wxImage& PhotoManager::GetSteganografDecImage() const
	{
		return m_DecryptSteganografImage;
	}

	bool PhotoManager::SetSteganografImage(const wxImage& newSteganograf, const wxImage& referenceImage, bool decryptEncrypt)
	{
		//create copies of images to store in photoManager instance
		m_ReferenceSteganografImage = referenceImage;
		if (decryptEncrypt)
		{
			m_EncryptSteganografImage = newSteganograf;
		}
		else
		{
			m_DecryptSteganografImage = newSteganograf;
		}
		//pass the copies(!) to stegaManager for processing
		const wxImage* sourceImage = decryptEncrypt ? &m_EncryptSteganografImage : &m_DecryptSteganografImage;
		bool imagesOk = stegaManager.SetImages(&m_ReferenceSteganografImage, sourceImage);

		if (!imagesOk)
		{
			stegaManager.SetDefault();
			m_ReferenceSteganografImage = wxImage();
			m_EncryptSteganografImage = wxImage();
			m_DecryptSteganografImage = wxImage();
			return false;
		}
		return true;
	}


	const wxImage& PhotoManager::GetKryptografEncImage() const
	{
		return m_EncryptKryptografImage;
	}

	const std::pair<wxImage, wxImage>& PhotoManager::GetKryptografDecImage() const
	{
		return m_DecryptKryptografImage;
	}

	bool PhotoManager::SetKryptografEncryptImage(const wxImage& newKryptograf)
	{
		m_EncryptKryptografImage = newKryptograf;
		bool imageOk = kryptografManager.SetImageForEncryption(&m_EncryptKryptografImage);
		if (!imageOk)
		{
			kryptografManager.SetDefault();
			m_EncryptKryptografImage = wxImage();
			m_DecryptKryptografImage = std::make_pair(wxImage(), wxImage());
			return false;
		}
		return true;
	}

	bool PhotoManager::SetKryptografDecryptImages(const wxImage& newKryptografFisrt, const wxImage& newKryptografSecond)
	{
		m_DecryptKryptografImage = std::make_pair(newKryptografFisrt, newKryptografSecond);
		bool imagesOk = kryptografManager.SetImagesForDecryption(&m_DecryptKryptografImage.first, &m_DecryptKryptografImage.second);
		if (!imagesOk)
		{
			kryptografManager.SetDefault();
			m_DecryptKryptografImage = std::make_pair(wxImage(), wxImage());
			m_EncryptKryptografImage = wxImage();
			return false;
		}
		return true;
	}

	std::pair<const Cryptor::Image, const Cryptor::Image> PhotoManager::GetRealSteganografEncData() const
	{
		return stegaManager.GetCryptorData();
	}

	void PhotoManager::SetRealSteganografEncData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_EncryptSteganografImage.SetData(newData.Data, newData.Width, newData.Height);
	}

	std::pair<const Cryptor::Image, const Cryptor::Image> PhotoManager::GetRealSteganografDecData() const
	{
		return stegaManager.GetCryptorData();
	}

	void PhotoManager::SetRealSteganografDecData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_DecryptSteganografImage.SetData(newData.Data, newData.Width, newData.Height);
	}

	Cryptor::Image PhotoManager::GetRealKryptografEncData() const
	{
		return kryptografManager.GetCryptorData();
	}

	void PhotoManager::SetRealKryptografEncData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_EncryptKryptografImage.SetData(newData.Data, newData.Width, newData.Height);
	}

	std::pair<Cryptor::Image, Cryptor::Image> PhotoManager::GetRealKryptografDecData() const
	{
		return kryptografManager.GetDecryptorData();
	}

	void PhotoManager::SetRealKryptografDecData(std::pair<Cryptor::Image, Cryptor::Image> newData)
	{
		if (newData.first.Data != nullptr && newData.second.Data != nullptr)
		{
			m_DecryptKryptografImage.first.SetData(newData.first.Data, newData.first.Width, newData.first.Height);
			m_DecryptKryptografImage.second.SetData(newData.second.Data, newData.second.Width, newData.second.Height);
		}
	}

	bool PhotoManager::IsImageBlackAndWhite(const wxImage& image) const
	{
		const uint8_t* data = image.GetData();
		unsigned dataSize = image.GetWidth() * image.GetHeight() * 3;
		
		for (unsigned i = 0; i < dataSize; i++)
		{
			if (data[i] != 0xFF && data[i] != 0)
				return false;
		}
		return true;
	}

	bool PhotoManager::ConvertToBlackAndWhite(wxImage& image, uint8_t threshold) const
	{
		if (image.IsOk() != true)
			return false;

		unsigned dataSize = image.GetWidth() * image.GetHeight() * 3;
		uint8_t* data = image.GetData();
		
		for (unsigned i = 0; i < dataSize; i += 3)
		{
			unsigned pixelAvg = (data[i] + data[i + 1] + data[i + 2]) / 3;
			uint8_t newValue = 0;
			if (pixelAvg >= threshold)
				newValue = 255;
			for (int j = 0; j < 3; j++)
				data[i + j] = newValue;
		}
		return true;
	}
}