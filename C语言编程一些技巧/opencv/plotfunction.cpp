#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  


using namespace std;
using namespace cv;

int main(void)
{
	Mat a = Mat::zeros(500,500, CV_8UC1);
	uchar* p;
	double y;
	for (double x = -10; x < 10; x+=0.04)
	{
		if (x == 0)continue;
		y = sin(x);
		if (y < -10 || y > 10)continue;
		p = a.ptr<uchar>((10 - y) * 25);
		p[(int)((x + 10) * 25)] = 255;
	}
	imshow("img", a);
	waitKeyEx(0);
	return(0);
}
