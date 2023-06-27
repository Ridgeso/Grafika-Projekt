#include "HPpch.h"

#include "Cryptor.h"


namespace Cryptor
{

	PhotoManager::PhotoManager()
	{
	}

	PhotoManager::~PhotoManager()
	{
	}

	const wxImage& PhotoManager::GetSteganografImage() const
	{
		return m_EncryptSteganografImage;
	}

	const wxImage& PhotoManager::GetSteganografDecryptImage() const
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

	const wxImage& PhotoManager::GetKryptografImage() const
	{
		return m_EncryptKryptografImage;
	}

	const std::pair<wxImage, wxImage>& PhotoManager::GetKryptografDecryptImage() const
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

	uint8_t* PhotoManager::GetRealSteganografData()
	{
		return nullptr;
	}

	std::pair<uint8_t*, uint8_t*> PhotoManager::GetRealKryptografData()
	{
		return std::pair<uint8_t*, uint8_t*>();
	}

	CryptionManager::CryptionManager()
	{
	}

	CryptionManager::~CryptionManager()
	{
	}

}