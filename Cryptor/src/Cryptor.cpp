#include "Cpch.h"
#include "Cryptor.h"


namespace Cryptor
{

	uint8_t* CryptionManager::EncryptSteganograficznaImpl(uint8_t* encrypt) const
	{
		// TODO: Zakodowywanie dobrego zdjecia | Metoda 1
		return nullptr;
	}

	uint8_t* CryptionManager::DecryptSteganograficznaImpl(uint8_t* decrypt) const
	{
		// TODO: odkodowywanie zakodowanego zdjecia | Metoda 1
		return nullptr;
	}

	std::pair<uint8_t*, uint8_t*> CryptionManager::EncryptKryptograficznaImpl(uint8_t* encrypt) const
	{
		// TODO: Zakodowywanie dobrego zdjecia | Metoda 2
		return std::pair<uint8_t*, uint8_t*>();
	}

	uint8_t* CryptionManager::DecryptKryptograficznaImpl(std::pair<uint8_t*, uint8_t*> decrypt) const
	{
		// TODO: odkodowywanie zakodowanego zdjecia | Metoda 2
		return nullptr;
	}

}