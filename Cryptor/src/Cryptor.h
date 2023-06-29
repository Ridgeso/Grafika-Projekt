#pragma once
#include <stdint.h>
#include <utility>

namespace Cryptor
{
	struct Image
	{
		int32_t Widht, Height;
		int32_t Chanel;
		uint8_t* Data;
	};

	template<typename Derrived>
	struct DataManager
	{
		std::pair<const Image, const Image> GetSteganografEncData() const
		{
			return static_cast<const Derrived*>(this)->GetRealSteganografEncData();
		}

		void SetSteganografEncData(Image newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografEncData(newData);
		}

		Image GetKryptografEncData() const
		{
			return static_cast<const Derrived*>(this)->GetRealKryptografEncData();
		}

		void SetKryptografEncData(Image newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografEncData(newData);
		}

		std::pair<const Image, const Image> GetSteganografDecData() const
		{
			return static_cast<const Derrived*>(this)->GetRealSteganografDecData();
		}

		void SetSteganografDecData(Image newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografDecData(newData);
		}

		std::pair<Image, Image> GetKryptografDecData() const
		{
			return static_cast<const Derrived*>(this)->GetRealKryptografDecData();
		}

		void SetKryptografDecData(std::pair<Image, Image> newData)
		{
			static_cast<Derrived*>(this)->SetRealKryptografDecData(newData);
		}
	};


	template<typename Derrived>
	struct CryptorManager
	{
		template<typename DataHandler>
		void EncryptSteganograficzna(DataManager<DataHandler>& dataManager) const
		{
			std::pair<const Image, const Image> data = dataManager.GetSteganografEncData();
			Image decryptedData = static_cast<const Derrived*>(this)->EncryptSteganograficznaImpl(data);
			dataManager.SetSteganografDecData(decryptedData);
		}

		template<typename DataHandler>
		void DecryptSteganograficzna(DataManager<DataHandler>& dataManager) const
		{
			std::pair<const Image, const Image> data = dataManager.GetSteganografDecData();
			Image encryptedData = static_cast<const Derrived*>(this)->DecryptSteganograficznaImpl(data);
			dataManager.SetSteganografEncData(encryptedData);
		}

		template<typename DataHandler>
		void EncryptKryptograficzna(DataManager<DataHandler>& dataManager) const
		{
			Image data = dataManager.GetKryptografEncData();
			auto decryptedData = static_cast<const Derrived*>(this)->EncryptKryptograficznaImpl(data);
			dataManager.SetKryptografDecData(decryptedData);
		}

		template<typename DataHandler>
		void DecryptKryptograficzna(DataManager<DataHandler>& dataManager) const
		{
			auto data = dataManager.GetKryptografDecData();
			Image encryptedData = static_cast<const Derrived*>(this)->DecryptKryptograficznaImpl(data);
			dataManager.SetKryptografEncData(encryptedData);
		}
	};


	struct CryptionManager : public CryptorManager<CryptionManager>
	{
		Image EncryptSteganograficznaImpl(std::pair<const Image, const Image> encrypt) const;
		Image DecryptSteganograficznaImpl(std::pair<const Image, const Image> decrypt) const;
		std::pair<Image, Image> EncryptKryptograficznaImpl(Image encrypt) const;
		Image DecryptKryptograficznaImpl(std::pair<Image, Image> decrypt) const;
	};

}