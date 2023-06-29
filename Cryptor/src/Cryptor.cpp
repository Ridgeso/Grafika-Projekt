#include "Cpch.h"
#include "Cryptor.h"


namespace Cryptor
{

	Image CryptionManager::EncryptSteganograficznaImpl(std::pair<const Image, const Image> encrypt) const
	{
		// TODO: Zakodowywanie dobrego zdjecia | Metoda 1
		return (Image)0;
	}

	Image CryptionManager::DecryptSteganograficznaImpl(std::pair<const Image, const Image> decrypt) const
	{
		// TODO: odkodowywanie zakodowanego zdjecia | Metoda 1
		return (Image)0;
	}

	std::pair<Image, Image> CryptionManager::EncryptKryptograficznaImpl(Image encrypt) const
	{
		// TODO: Zakodowywanie dobrego zdjecia | Metoda 2
		return std::pair<Image, Image>((Image)0, (Image)0);
	}

	Image CryptionManager::DecryptKryptograficznaImpl(std::pair<Image, Image> decrypt) const
	{
		// TODO: odkodowywanie zakodowanego zdjecia | Metoda 2
		return (Image)0;
	}

}