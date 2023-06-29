#pragma once

#include "Cryptor.h"

#include <wx/image.h>

#include <memory>
#include <stdint.h>
#include <utility>

#include "Cryptor.h"

namespace PhotoCryptor
{

	class PhotoManager : public Cryptor::DataManager<PhotoManager>
	{
	public:
		PhotoManager() = default;
		~PhotoManager() = default;

		const wxImage& GetSteganografEncImage() const;
		const wxImage& GetSteganografDecImage() const;
		void SetSteganografImage(const wxImage& newSteganograf, bool decryptEncrypt = true);
		
		const wxImage& GetKryptografEncImage() const;
		const std::pair<wxImage, wxImage>& GetKryptografDecImage() const;
		void SetKryptografImage(const wxImage& newKryptograf);
		void SetKryptografImage(const wxImage& newKryptografFisrt, const wxImage& newKryptografSecond);

	public:
		Cryptor::Image GetRealSteganografEncData() const;
		void SetRealSteganografEncData(Cryptor::Image newData);
		Cryptor::Image GetRealSteganografDecData() const;
		void SetRealSteganografDecData(Cryptor::Image newData);

		Cryptor::Image GetRealKryptografEncData() const;
		void SetRealKryptografEncData(Cryptor::Image newData);
		std::pair<Cryptor::Image, Cryptor::Image> GetRealKryptografDecData() const;
		void SetRealKryptografDecData(std::pair<Cryptor::Image, Cryptor::Image> newData);

	private:
		wxImage m_EncryptSteganografImage;
		wxImage m_DecryptSteganografImage;
		
		wxImage m_EncryptKryptografImage;
		std::pair<wxImage, wxImage> m_DecryptKryptografImage;
	};

}