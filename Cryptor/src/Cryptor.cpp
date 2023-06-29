#include "Cpch.h"
#include "Cryptor.h"


namespace Cryptor
{

	Image CryptionManager::EncryptSteganograficznaImpl(std::pair<const Image, const Image> encrypt) const
	{
		const Image& encImage = encrypt.first;
		const Image& refImage = encrypt.second;

		Image result = { .Width = 0, .Height = 0, .Channel = 0, .Data = nullptr };
		
		if(CheckStegaInputData(encImage, refImage) != true)
			return result;

		result.Height = refImage.Height;
		result.Width = refImage.Width;
		result.Channel = refImage.Channel;

		return result;
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

	bool CryptionManager::CheckStegaInputData(const Image& src, const Image& ref) const
	{
		if((src.Width != ref.Width) || (src.Height != ref.Height) || (src.Channel != ref.Channel))
			return false;
		if (src.Data == nullptr || ref.Data == nullptr)
			return false;
		return true;
	}

}