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
		Image& first = decrypt.first;
		Image& second = decrypt.second;
		Image decrypted = { .Width = 0, .Height = 0, .Channel = 0, .Data = nullptr };
		
		if (CheckKryptoInputData(first, second) != true)
			return decrypted;

		int stride = first.Channel;
		unsigned encryptedSize = first.Height * first.Width * stride;
		unsigned decryptedSize = encryptedSize / 4;

		uint8_t* dataDecryptedBig = new uint8_t[encryptedSize];
		for (unsigned i = 0; i < encryptedSize; i++)
		{
			unsigned val = first.Data[i] + second.Data[i];
			if (val == 0xFF)	//black pixel (different blocks)
				val = 0;
			else if (val == 0 || val == 2 * 0xFF)	//white pixel (identical blocks)
				val = 255;
			else	//randomize to avoid any uninitialized memory
				val = rand();	
			dataDecryptedBig[i] = (uint8_t)val;
		}
		const Image decryptedBig = { .Width = first.Width, .Height = first.Height, .Channel = stride, .Data = dataDecryptedBig };

		int decryptedWidth = first.Width / 2, decryptedHeight = first.Height / 2;

		uint8_t* dataDecrypted = new uint8_t[decryptedSize];
		for (unsigned i = 0; i < decryptedSize / stride; i++)
		{
			unsigned x = (i % decryptedWidth) * 2;
			unsigned y = (i / decryptedWidth) * 2;

			uint8_t val = GetValueAtPos(y, x, decryptedBig);

			for (int j = 0; j < stride; j++)
			{
				dataDecrypted[i * stride + j] = val;
			}
		}

		delete[] dataDecryptedBig;

		decrypted = { .Width = decryptedWidth , .Height = decryptedHeight, .Channel = stride, .Data = dataDecrypted };
		return decrypted;
	}

	bool CryptionManager::CheckStegaInputData(const Image& src, const Image& ref) const
	{
		if (AreDimensionsEqual(src, ref) == false)
			return false;
		if (src.Data == nullptr || ref.Data == nullptr)
			return false;
		return true;
	}

	bool CryptionManager::CheckKryptoInputData(const Image& image1, const Image& image2) const
	{
		if(AreDimensionsEqual(image1, image2) != true)
			return false;
		if (image1.Data == nullptr || image2.Data == nullptr)
			return false;
		return true;
	}

	bool CryptionManager::AreDimensionsEqual(const Image& image1, const Image& image2) const
	{
		if ((image1.Width != image2.Width) || (image1.Height != image2.Height) || (image1.Channel != image2.Channel))
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

	uint8_t CryptionManager::GetValueAtPos(unsigned y, unsigned x, const Image& image) const
	{
		if (image.Data == nullptr || y >= image.Height || x >= image.Width)
			return 0;

		int pos = (y * image.Width + x) * image.Channel;

		return image.Data[pos];
	}
}