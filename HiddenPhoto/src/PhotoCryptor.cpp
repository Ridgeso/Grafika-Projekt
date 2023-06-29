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

	void PhotoManager::SetSteganografImage(const wxImage& newSteganograf, const wxImage& referenceImage, bool decryptEncrypt)
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
		}
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

	uint8_t* PhotoManager::GetRealSteganografEncData() const
	{
		return m_EncryptSteganografImage.GetData();
	}

	void PhotoManager::SetRealSteganografEncData(uint8_t* newData)
	{
		if (newData != nullptr)
			m_EncryptSteganografImage.SetData(newData);
	}

	uint8_t* PhotoManager::GetRealSteganografDecData() const
	{
		return m_DecryptSteganografImage.GetData();
	}

	void PhotoManager::SetRealSteganografDecData(uint8_t* newData)
	{
		if (newData != nullptr)
			m_DecryptSteganografImage.SetData(newData);
	}

	uint8_t* PhotoManager::GetRealKryptografEncData() const
	{
		return m_EncryptKryptografImage.GetData();
	}

	void PhotoManager::SetRealKryptografEncData(uint8_t* newData)
	{
		if (newData != nullptr)
			m_EncryptKryptografImage.SetData(newData);
	}

	std::pair<uint8_t*, uint8_t*> PhotoManager::GetRealKryptografDecData() const
	{
		return std::make_pair(
			m_DecryptKryptografImage.first.GetData(),
			m_DecryptKryptografImage.second.GetData()
		);
	}

	void PhotoManager::SetRealKryptografDecData(std::pair<uint8_t*, uint8_t*> newData)
	{
		if (newData.first != nullptr && newData.second != nullptr)
		{
			m_DecryptKryptografImage.first.SetData(newData.first);
			m_DecryptKryptografImage.second.SetData(newData.second);
		}
	}

}