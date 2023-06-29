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

	void PhotoManager::SetKryptografImage(const wxImage& newKryptograf)
	{
		m_EncryptKryptografImage = newKryptograf;
	}

	void PhotoManager::SetKryptografImage(const wxImage& newKryptografFisrt, const wxImage& newKryptografSecond)
	{
		m_DecryptKryptografImage = std::make_pair(newKryptografFisrt, newKryptografSecond);
	}

	Cryptor::Image PhotoManager::GetRealSteganografEncData() const
	{
		Cryptor::Image image = {
			m_EncryptSteganografImage.GetWidth(),
			m_EncryptSteganografImage.GetHeight(),
			m_EncryptSteganografImage.HasAlpha() ? 4 : 3,
			m_EncryptSteganografImage.GetData()
		};
		return image;
	}

	void PhotoManager::SetRealSteganografEncData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_EncryptSteganografImage.SetData(newData.Data, newData.Widht, newData.Height);
	}

	Cryptor::Image PhotoManager::GetRealSteganografDecData() const
	{
		Cryptor::Image image = {
			m_DecryptSteganografImage.GetWidth(),
			m_DecryptSteganografImage.GetHeight(),
			m_DecryptSteganografImage.HasAlpha() ? 4 : 3,
			m_DecryptSteganografImage.GetData()
		};
		return image;
	}

	void PhotoManager::SetRealSteganografDecData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_DecryptSteganografImage.SetData(newData.Data, newData.Widht, newData.Height);
	}

	Cryptor::Image PhotoManager::GetRealKryptografEncData() const
	{
		Cryptor::Image image = {
			m_EncryptKryptografImage.GetWidth(),
			m_EncryptKryptografImage.GetHeight(),
			m_EncryptKryptografImage.HasAlpha() ? 4 : 3,
			m_EncryptKryptografImage.GetData()
		};
		return image;
	}

	void PhotoManager::SetRealKryptografEncData(Cryptor::Image newData)
	{
		if (newData.Data != nullptr)
			m_EncryptKryptografImage.SetData(newData.Data, newData.Widht, newData.Height);
	}

	std::pair<Cryptor::Image, Cryptor::Image> PhotoManager::GetRealKryptografDecData() const
	{
		Cryptor::Image imageFirst = {
			m_DecryptKryptografImage.first.GetWidth(),
			m_DecryptKryptografImage.first.GetHeight(),
			m_DecryptKryptografImage.first.HasAlpha() ? 4 : 3,
			m_DecryptKryptografImage.first.GetData()
		};
		Cryptor::Image imageSecond = {
			m_DecryptKryptografImage.second.GetWidth(),
			m_DecryptKryptografImage.second.GetHeight(),
			m_DecryptKryptografImage.second.HasAlpha() ? 4 : 3,
			m_DecryptKryptografImage.second.GetData()
		};
		return std::make_pair(imageFirst, imageSecond);
	}

	void PhotoManager::SetRealKryptografDecData(std::pair<Cryptor::Image, Cryptor::Image> newData)
	{
		if (newData.first.Data != nullptr && newData.second.Data != nullptr)
		{
			m_DecryptKryptografImage.first.SetData(newData.first.Data, newData.first.Widht, newData.first.Height);
			m_DecryptKryptografImage.second.SetData(newData.second.Data, newData.second.Widht, newData.second.Height);
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