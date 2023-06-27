#pragma once
#include <wx/file.h>

#include <memory>
#include <stdint.h>
#include <utility>

namespace Cryptor
{
	template<typename Derrived>
	class DataManager
	{
	public:
		uint8_t* GetSteganografData()
		{
			return static_cast<Derrived*>(this)->GetRealSteganografData();
		}

		std::pair<uint8_t*, uint8_t*> GetKryptografData()
		{
			return static_cast<Derrived*>(this)->GetRealKryptografData();
		}

	private:

	};


	class PhotoManager : public DataManager<PhotoManager>
	{
	public:
		PhotoManager();
		~PhotoManager();

		void SetSteganografImage(wxImage&& newSteganograf, bool decryptEncrypt = true);
		void SetKryptografImage(wxImage&& newKryptograf);
		void SetKryptografImage(wxImage&& newKryptografFisrt,  wxImage&& newKryptografSecond);

	private:
		uint8_t* GetRealSteganografData();
		std::pair<uint8_t*, uint8_t*> GetRealKryptografData();

	private:
		wxImage m_DecryptSteganografImage;
		wxImage m_EncryptSteganografImage;
		
		wxImage m_DecryptKryptografImage;
		std::pair<wxImage, wxImage> m_EncryptKryptografImage;
	};


	class CryptionManager
	{
	public:
		CryptionManager();
		~CryptionManager();

		template<typename ImageHandler>
		void DecryptSteganograficzna(const std::unique_ptr<DataManager<ImageHandler>>& photoManager) const
		{

		}

		template<typename ImageHandler>
		void EncryptSteganograficzna(const std::unique_ptr<DataManager<ImageHandler>>& photoManager) const
		{

		}
		
		template<typename ImageHandler>
		void DecryptKryptograficzna(const std::unique_ptr<DataManager<ImageHandler>>& photoManager) const
		{

		}

		template<typename ImageHandler>
		void EncryptKryptograficzna(const std::unique_ptr<DataManager<ImageHandler>>& photoManager) const
		{

		}
	
	private:

	};

}