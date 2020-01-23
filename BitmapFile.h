//	MURUGAN@NDR	(2002/05/16)
//	CBitmapFile class header file implementation

#ifndef	_BITMAP_FILE_H_
#define	_BITMAP_FILE_H_

#define	HAVE_BOOLEAN
#define		BMP_FILE			0x00
#define		JPG_FILE			0x01

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus

#include "jpeglib.h"

#ifdef __cplusplus
	}
#endif // __cplusplus

class CBitmapFile
{
public:
	CBitmapFile();
	~CBitmapFile();

public:
	BOOL	SaveDesktopAsFile(LPCSTR szFile, int nFileType);
	BOOL	SaveWindowAsFile(LPCSTR szFile, CWnd *pWnd, int nFileType);

private:
	BOOL	WriteDIB( LPCSTR szFile, HANDLE hDIB);
	HANDLE	DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );
	void	DrawGreyScale( CDC *pDC, HANDLE hDIB );
	BOOL	BuildSamps(HANDLE                      hDib,
					int                         nSampsPerRow,
					struct jpeg_compress_struct cinfo,
					JSAMPARRAY                  jsmpArray,
					CString*                    pcsMsg);

	BOOL	JpegFromDib(HANDLE     hDib,     //Handle to DIB
						int        nQuality, //JPEG quality (0-100)
						CString    csJpeg,   //Pathname to target jpeg file
						CString*   pcsMsg);  //Error msg to return
	BOOL	DibToSamps(HANDLE		hDib,
					int			nSampsPerRow,
					struct		jpeg_compress_struct cinfo,
					JSAMPARRAY	jsmpPixels,
					CString*	pcsMsg);
	RGBQUAD	QuadFromWord(WORD b16);

};

#endif	//	_BITMAP_FILE_H_
