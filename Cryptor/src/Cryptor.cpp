#include "Cpch.h"
#include "Cryptor.h"


namespace Cryptor
{

	uint8_t* CryptionManager::EncryptSteganograficznaImpl(uint8_t* encrypt) const
	{
		return nullptr;
	}

	uint8_t* CryptionManager::DecryptSteganograficznaImpl(uint8_t* decrypt) const
	{
		return nullptr;
	}

	std::pair<uint8_t*, uint8_t*> CryptionManager::EncryptKryptograficznaImpl(uint8_t* encrypt) const
	{
		return std::pair<uint8_t*, uint8_t*>();
	}

	uint8_t* CryptionManager::DecryptKryptograficznaImpl(std::pair<uint8_t*, uint8_t*> decrypt) const
	{
		return nullptr;
	}

}