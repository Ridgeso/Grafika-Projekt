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

	void PhotoManager::SetSteganografImage(wxImage&& newSteganograf, bool decryptEncrypt)
	{
		if (decryptEncrypt)
			m_DecryptSteganografImage = std::move(newSteganograf);
		else
			m_EncryptSteganografImage = std::move(newSteganograf);
	}

	void PhotoManager::SetKryptografImage(wxImage&& newKryptograf)
	{
		m_DecryptKryptografImage = std::move(newKryptograf);
	}

	void PhotoManager::SetKryptografImage(wxImage&& newKryptografFisrt, wxImage&& newKryptografSecond)
	{
		m_EncryptKryptografImage = std::make_pair(std::move(newKryptografFisrt), std::move(newKryptografSecond));
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