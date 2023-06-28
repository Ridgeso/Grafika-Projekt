#pragma once
#include <stdint.h>
#include <utility>

namespace Cryptor
{

	template<typename Derrived>
	struct DataManager
	{
		uint8_t* GetSteganografEncData() const
		{
			return static_cast<const Derrived*>(this)->GetRealSteganografEncData();
		}

		void SetSteganografEncData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografEncData(newData);
		}

		uint8_t* GetKryptografEncData() const
		{
			return static_cast<const Derrived*>(this)->GetRealKryptografEncData();
		}

		void SetKryptografEncData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografEncData(newData);
		}

		uint8_t* GetSteganografDecData() const
		{
			return static_cast<const Derrived*>(this)->GetRealSteganografDecData();
		}

		void SetSteganografDecData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetRealSteganografDecData(newData);
		}

		std::pair<uint8_t*, uint8_t*> GetKryptografDecData() const
		{
			return static_cast<const Derrived*>(this)->GetRealKryptografDecData();
		}

		void SetKryptografDecData(std::pair<uint8_t*, uint8_t*> newData)
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
			uint8_t* data = dataManager.GetSteganografEncData();
			uint8_t* decryptedData = static_cast<const Derrived*>(this)->EncryptSteganograficznaImpl(data);
			dataManager.SetSteganografDecData(decryptedData);
		}

		template<typename DataHandler>
		void DecryptSteganograficzna(DataManager<DataHandler>& dataManager) const
		{
			uint8_t* data = dataManager.GetSteganografDecData();
			uint8_t* encryptedData = static_cast<const Derrived*>(this)->DecryptSteganograficznaImpl(data);
			dataManager.SetSteganografEncData(encryptedData);
		}

		template<typename DataHandler>
		void EncryptKryptograficzna(DataManager<DataHandler>& dataManager) const
		{
			uint8_t* data = dataManager.GetKryptografEncData();
			auto decryptedData = static_cast<const Derrived*>(this)->EncryptKryptograficznaImpl(data);
			dataManager.SetKryptografDecData(decryptedData);
		}

		template<typename DataHandler>
		void DecryptKryptograficzna(DataManager<DataHandler>& dataManager) const
		{
			auto data = dataManager.GetKryptografDecData();
			uint8_t* encryptedData = static_cast<const Derrived*>(this)->DecryptKryptograficznaImpl(data);
			dataManager.SetKryptografEncData(encryptedData);
		}
	};


	struct CryptionManager : public CryptorManager<CryptionManager>
	{
		uint8_t* EncryptSteganograficznaImpl(uint8_t* encrypt) const;
		uint8_t* DecryptSteganograficznaImpl(uint8_t* decrypt) const;
		std::pair<uint8_t*, uint8_t*> EncryptKryptograficznaImpl(uint8_t* encrypt) const;
		uint8_t* DecryptKryptograficznaImpl(std::pair<uint8_t*, uint8_t*> decrypt) const;
	};

}