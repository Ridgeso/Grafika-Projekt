#pragma once
#include <stdint.h>
#include <utility>

namespace Cryptor
{

	template<typename Derrived>
	class DataManager
	{
	public:
		uint8_t* GetSteganografEncData() const
		{
			return static_cast<Derrived*>(this)->GetRealSteganografEncData();
		}

		void SetSteganografEncData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetReakSteganografEncData(newData);
		}

		uint8_t* GetKryptografEncData() const
		{
			return static_cast<Derrived*>(this)->GetRealKryptografEncData();
		}

		void SetKryptografEncData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetReakSteganografEncData(newData);
		}

		uint8_t* GetSteganografDecData() const
		{
			return static_cast<Derrived*>(this)->GetRealSteganografDecData();
		}

		void SetSteganografDecData(uint8_t* newData)
		{
			static_cast<Derrived*>(this)->SetReakSteganografDecData(newData);
		}

		std::pair<uint8_t*, uint8_t*> GetKryptografDecData() const
		{
			return static_cast<Derrived*>(this)->GetRealKryptografDecData();
		}

		void SetKryptografDecData(std::pair<uint8_t*, uint8_t*> newData)
		{
			static_cast<Derrived*>(this)->SetReakSteganografDecData(newData);
		}

	private:

	};


	template<typename Derrived>
	class CryptorManager
	{
	public:
		template<typename ImageHandler>
		void EncryptSteganograficzna(const std::unique_ptr<DataManager<ImageHandler>>& dataManager) const
		{
			uint8_t* data = dataManager->GetSteganografEncData();
			uint8_t* decryptedData = static_cast<Derrived*>(this)->EncryptSteganograficznaImpl(data);
			dataManager->SetSteganografDecData(decryptedData);
		}

		template<typename ImageHandler>
		void DecryptSteganograficzna(const std::unique_ptr<DataManager<ImageHandler>>& dataManager) const
		{
			uint8_t* data = dataManager->GetKryptografDecData();
			uint8_t* encryptedData = static_cast<Derrived*>(this)->DecryptSteganograficznaImpl(data);
			dataManager->SetSteganografEncData(encryptedData);
		}

		template<typename ImageHandler>
		void EncryptKryptograficzna(const std::unique_ptr<DataManager<ImageHandler>>& dataManager) const
		{
			uint8_t* data = dataManager->GetKryptografEncData();
			auto decryptedData = static_cast<Derrived*>(this)->EncryptKryptograficznaImpl(data);
			dataManager->SetKryptografDecData(decryptedData);
		}

		template<typename ImageHandler>
		void DecryptKryptograficzna(const std::unique_ptr<DataManager<ImageHandler>>& dataManager) const
		{
			auto data = dataManager->GetKryptografDecData();
			uint8_t* encryptedData = static_cast<Derrived*>(this)->DecryptKryptograficznaImpl(data);
			dataManager->SetKryptografEncData(encryptedData);
		}

	private:

	};


	class CryptionManager : public CryptorManager<CryptionManager>
	{
	public:

	private:
		uint8_t* EncryptSteganograficznaImpl(uint8_t* encrypt) const;
		uint8_t* DecryptSteganograficznaImpl(uint8_t* decrypt) const;
		std::pair<uint8_t*, uint8_t*> EncryptKryptograficznaImpl(uint8_t* encrypt) const;
		uint8_t* DecryptKryptograficznaImpl(std::pair<uint8_t*, uint8_t*> decrypt) const;
	};

}