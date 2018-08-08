#include <opencv2/core.hpp>
#include <opencv\highgui.h>
#include <opencv2\opencv.hpp>
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/ml/ml.hpp>  
#include <windows.h>
#include "hkcameradriver.h"
#include <string>    

using namespace std;
using namespace cv;

HKCamDriver m_CamDriver[2];

int main()
{
	m_CamDriver[0].InitHKNetSDK();
	m_CamDriver[0].SetScaleFactor(0.5f);

	Sleep(500);
	m_CamDriver[0].InitCamera("192.168.110.65", "admin", "DS-2CD3320D");

	Sleep(200);

	m_CamDriver[1].InitCamera("192.168.110.64", "admin", "DS-2CD3320D");

	Mat video[2];

	/* Wait */
	Sleep(1000);

	while (1)
	{
		if (m_CamDriver[0].GetCamMat(video[0], NULL, 1.0f)) {
			imshow("windows::im0", video[0]);
			if (m_CamDriver[1].GetCamMat(video[1], NULL, 1.0f)) {
				imshow("windows::im1", video[1]);
			}
			waitKey(30);
		}

		return 0;
	}
}