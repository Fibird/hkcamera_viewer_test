#ifndef _HKCAMDRIVER_H_
#define _HKCAMDRIVER_H_

#include "opencv2\opencv.hpp"                                  /*  OpenCV header                           */
#include "plaympeg4.h"                                         /*  Software decoder header                 */
#include "HCNetSDK.h"                                          /*  HCNet Camera SDK header                 */

using namespace cv;                                            /*  Need the OpenCV support                 */

#define MaxCameraNum 20                                        /*  Support the max number of camera is 20  */

typedef long CamHandle;                                        /*  Camera Handle is long int               */

															   /*   Multi-Thread Lock                                     */
static HANDLE hMutex[MaxCameraNum];

static long nPort[MaxCameraNum];

static IplImage* pImg[MaxCameraNum];

static float Scalefactor;

class HKCamDriver {
public:

	/*    Constructed function                                 */
	HKCamDriver();

	~HKCamDriver();

	/*   Init the HKNetSDK, and the function only be using by
	once                                                  */
	void InitHKNetSDK(void);

	/*    Supply IP Address,UserName and Password,return the   *
	camera hanlde                                        */
	CamHandle InitCamera(char *sIP, char *UsrName, char *PsW, int Port = 8000);

	int ReleaseCamera(void);

	/*    Supply Camera handle, and function return the Mat    */
	int GetCamMat(Mat &Img, CamHandle handle = NULL, float factor = 1.0f);

	/*    Supply camera handle, and function return  IPlImage  */
	IplImage* GetCamImage(CamHandle handle, float factor = 1.0f);

	/*    Exception Callback function                          */
	static void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);

	/*    Decode function, which convert yv12 to rgb           */
	static void CALLBACK DecCBFun(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);

	/*   Realtime decode function,which call mpeg4 to decode   */
	static void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);

	static void SetScaleFactor(float factor);

private:
	/*   Convert the video format yv12 to YUV format           */
	static void yv12toYUV(char *outYuv, char *inYv12, int width, int height, int widthStep);
	/*   Realtime Play handle                                  */
	LONG lRealPlayHandle;
	/*   Camera User ID                                        */
	LONG lUserID;
};
#endif