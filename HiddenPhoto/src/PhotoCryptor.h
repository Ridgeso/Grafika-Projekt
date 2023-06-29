#pragma once

#include "Cryptor.h"
#include "SteganografManager.h"

#include <wx/file.h>

#include <memory>
#include <stdint.h>
#include <utility>

namespace PhotoCryptor
{

	class PhotoManager : public Cryptor::DataManager<PhotoManager>
	{
	public:
		PhotoManager() = default;
		~PhotoManager() = default;

		const wxImage& GetSteganografEncImage() const;
		const wxImage& GetSteganografDecImage() const;
		void SetSteganografImage(const wxImage& newSteganograf, const wxImage& referenceImage, bool decryptEncrypt = true);
		
		const wxImage& GetKryptografEncImage() const;
		const std::pair<wxImage, wxImage>& GetKryptografDecImage() const;
		void SetKryptografImage(const wxImage& newKryptograf);
		void SetKryptografImage(const wxImage& newKryptografFisrt, const wxImage& newKryptografSecond);

	public:
		uint8_t* GetRealSteganografEncData() const;
		void SetRealSteganografEncData(uint8_t* newData);
		uint8_t* GetRealSteganografDecData() const;
		void SetRealSteganografDecData(uint8_t* newData);

		uint8_t* GetRealKryptografEncData() const;
		void SetRealKryptografEncData(uint8_t* newData);
		std::pair<uint8_t*, uint8_t*> GetRealKryptografDecData() const;
		void SetRealKryptografDecData(std::pair<uint8_t*, uint8_t*> newData);

	private:
		wxImage m_EncryptSteganografImage;
		wxImage m_DecryptSteganografImage;
		wxImage m_ReferenceSteganografImage;
		
		wxImage m_EncryptKryptografImage;
		std::pair<wxImage, wxImage> m_DecryptKryptografImage;

		SteganografManager stegaManager;
	};

}