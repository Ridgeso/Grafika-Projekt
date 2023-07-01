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

		unsigned stride = result.Channel;
		unsigned dataSize = result.Width * result.Height * stride;

		result.Data = new uint8_t[dataSize];
		std::memcpy(result.Data, refImage.Data, dataSize);

		for (unsigned i = 0; i < dataSize; i += stride)
			result.Data[i] += encImage.Data[i] == 255 ? 1 : 0;

		return result;
	}

	Image CryptionManager::DecryptSteganograficznaImpl(std::pair<const Image, const Image> decrypt) const
	{
		const Image& decImage = decrypt.first;
		const Image& refImage = decrypt.second;

		Image result = { .Width = 0, .Height = 0, .Channel = 0, .Data = nullptr };

		if (CheckStegaInputData(decImage, refImage) != true)
			return result;

		result.Height = refImage.Height;
		result.Width = refImage.Width;
		result.Channel = refImage.Channel;

		unsigned stride = result.Channel;
		unsigned dataSize = result.Width * result.Height * stride;

		result.Data = new uint8_t[dataSize];
		
		for (unsigned i = 0; i < dataSize; i += stride)
		{
			uint8_t pixelVal = decImage.Data[i] - refImage.Data[i];
			pixelVal *= 255;

			for (unsigned j = 0; j < stride; j++)
			{
				if (i + j >= dataSize)	//this condition is to remove buffer overrun warning, the condition itself should never be true
					break;
				result.Data[i + j] = pixelVal;
			}
		}

		return result;
	}

	std::pair<Image, Image> CryptionManager::EncryptKryptograficznaImpl(Image encrypt) const
	{
		Image first = { .Width = 0, .Height = 0, .Channel = 0, .Data = nullptr };
		Image second = { .Width = 0, .Height = 0, .Channel = 0, .Data = nullptr };

		if (encrypt.Data == nullptr)
			return std::make_pair(first, second);

		int stride = encrypt.Channel;
		unsigned originalSize = encrypt.Height * encrypt.Width * stride;
		int encryptedWidth = encrypt.Width * 2, encryptedHeight = encrypt.Height * 2;

		uint8_t* dataFirst = new uint8_t[originalSize * 4];
		uint8_t* dataSecond = new uint8_t[originalSize * 4];

		first = { .Width = encryptedWidth, .Height = encryptedHeight, .Channel = stride, .Data = dataFirst };
		second = { .Width = encryptedWidth, .Height = encryptedHeight, .Channel = stride, .Data = dataSecond };

		const uint8_t blockC1[2][2] = { { 0, 255 }, { 255, 0 } };
		const uint8_t blockC2[2][2] = { { 255, 0 }, { 0, 255 } };
		
		for (unsigned i = 0; i < originalSize; i += stride)
		{
			unsigned originalX = (i / 3) % encrypt.Width, originalY = (i / 3) / encrypt.Width;
			unsigned encryptedX = originalX * 2, encryptedY = originalY * 2;

			bool firstBlock = rand() % 2;
			bool isWhite = encrypt.Data[i] == 0xFF;

			if (isWhite)
			{
				InsertValueInPos(encryptedY, encryptedX, first, firstBlock ? blockC1[0][0] : blockC2[0][0]);
				InsertValueInPos(encryptedY, encryptedX + 1, first, firstBlock ? blockC1[0][1] : blockC2[0][1]);
				InsertValueInPos(encryptedY + 1, encryptedX, first, firstBlock ? blockC1[1][0] : blockC2[1][0]);
				InsertValueInPos(encryptedY + 1, encryptedX + 1, first, firstBlock ? blockC1[1][1] : blockC2[1][1]);

				InsertValueInPos(encryptedY, encryptedX, second, firstBlock ? blockC1[0][0] : blockC2[0][0]);
				InsertValueInPos(encryptedY, encryptedX + 1, second, firstBlock ? blockC1[0][1] : blockC2[0][1]);
				InsertValueInPos(encryptedY + 1, encryptedX, second, firstBlock ? blockC1[1][0] : blockC2[1][0]);
				InsertValueInPos(encryptedY + 1, encryptedX + 1, second, firstBlock ? blockC1[1][1] : blockC2[1][1]);
			}
			else
			{
				InsertValueInPos(encryptedY, encryptedX, first, firstBlock ? blockC1[0][0] : blockC2[0][0]);
				InsertValueInPos(encryptedY, encryptedX + 1, first, firstBlock ? blockC1[0][1] : blockC2[0][1]);
				InsertValueInPos(encryptedY + 1, encryptedX, first, firstBlock ? blockC1[1][0] : blockC2[1][0]);
				InsertValueInPos(encryptedY + 1, encryptedX + 1, first, firstBlock ? blockC1[1][1] : blockC2[1][1]);

				InsertValueInPos(encryptedY, encryptedX, second, firstBlock ? blockC2[0][0] : blockC1[0][0]);
				InsertValueInPos(encryptedY, encryptedX + 1, second, firstBlock ? blockC2[0][1] : blockC1[0][1]);
				InsertValueInPos(encryptedY + 1, encryptedX, second, firstBlock ? blockC2[1][0] : blockC1[1][0]);
				InsertValueInPos(encryptedY + 1, encryptedX + 1, second, firstBlock ? blockC2[1][1] : blockC1[1][1]);
			}
		}

		std::pair<Image, Image> result(first, second);
		return result;
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

	void CryptionManager::InsertValueInPos(unsigned y, unsigned x, Image& image, uint8_t value) const
	{
		if (image.Data == nullptr || y >= image.Height || x >= image.Width)
			return;

		int stride = image.Channel;
		unsigned pos = (y * image.Width + x) * stride;

		for (int i = 0; i < stride; i++)
		{
			image.Data[pos + i] = value;
		}
	}

}