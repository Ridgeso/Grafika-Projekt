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

	void PhotoManager::SetSteganografImage(const wxImage& newSteganograf, bool decryptEncrypt)
	{
		if (decryptEncrypt)
			m_EncryptSteganografImage = newSteganograf;
		else
			m_DecryptSteganografImage = newSteganograf;
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

}