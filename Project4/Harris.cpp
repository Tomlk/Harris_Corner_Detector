#include "Harris.h"


Harris::Harris()
{

	Max = 0;
}


Harris::~Harris()
{
}

void Harris::getGrayImg(Mat ImgSource)
{

	cvtColor(ImgSource, srcGray, CV_BGR2GRAY);
	//ImgSobelX = Mat(ImgSource.size().height, ImgSource.size().width, CV_32FC1, Scalar(0));
	cout << "imgSource:\t" << "height" << ImgSource.size().height << "\tweidth:\t" << ImgSource.size().width << endl;
}
void Harris::getSobelIxIy()
{
	
	Sobel(srcGray, ImgSobelX, CV_32F, 1, 0, 3);
	Sobel(srcGray, ImgSobelY, CV_32F, 0, 1, 3);// 1, 0, BORDER_DEFAULT);
	cout << "ImgSobelX:\t" << "height" << ImgSobelX.size().height << 
		"\tweidth:\t" << ImgSobelX.size().width << endl;

	//将梯度数组转换成8位无符号整型 
	convertScaleAbs(ImgSobelX, ImgSobelX);
	convertScaleAbs(ImgSobelY, ImgSobelY);
}
void Harris::getMandR(int kernel,double k)
{
	int expand_p=kernel/2;
	getSobelIxIy(); //获得梯度IxIy图像
	Operate_SX = Mat(ImgSobelX.size().height + 2 * expand_p, ImgSobelX.size().width + 2 * expand_p, CV_32FC1, Scalar(0));
	Operate_SY = Mat(ImgSobelY.size().height + 2 * expand_p, ImgSobelY.size().width + 2 * expand_p, CV_32FC1, Scalar(0));
	//定义窗口
	Rect rect = Rect(expand_p, expand_p, ImgSobelX.size().width, ImgSobelX.size().height);
	ImgSobelX.copyTo(Operate_SX(rect)); //更新可操作的SobelX
	ImgSobelY.copyTo(Operate_SY(rect));//更新可操作的SobelY

	resultImage = Mat(ImgSobelX.size().height , ImgSobelX.size().width , CV_32FC1, Scalar(0));

	for (int Y = expand_p; Y < resultImage.size().height; Y++)
	{
		for (int X = expand_p; X < resultImage.size().width; X++)
		{
			Rect rec = Rect(X - expand_p, Y - expand_p, kernel, kernel);
			Mat Ix = Operate_SX(rec);
			Mat Iy = Operate_SY(rec);
			Ixx = Ix.dot(Ix);
			Ixy = Ix.dot(Iy);
			Iyy = Iy.dot(Iy);

			R = Ixx*Iyy - Ixy*Ixy - k*(Ixx + Iyy)*(Ixx + Iyy);
			resultImage.at<int>(Y-expand_p, X-expand_p) = (int)R;


			if (R > Max) Max = R;
		}

	}
	thresh = 0.8*Max;
	cout << "thresh:" << thresh << endl;

}


void Harris::CLocalMaxPoint(int edgelength,int Thresh)
{
	int StartX,EndX;
	int StartY, EndY;
	Thresh = 20000 * Thresh;
	if (thresh > Thresh)
	{
		thresh = Thresh;
	}


	PointImage = Mat(ImgSobelX.size().height, ImgSobelX.size().width, CV_32SC1, Scalar(0));
	for (int  Y =0 ; Y < ImgSobelX.size().height; Y++)
	{
		for (int X = 0; X < ImgSobelX.size().width; X++)
		{
			if (resultImage.at<int>(Y, X) < Thresh) //小于阈值跳过
				continue;
			else
			{
				//需要局部最大
				if (X - edgelength < 0)
				{
					StartX = 0;
					EndX = X + edgelength;
				}
				else if (X + edgelength >= ImgSobelX.size().width)
				{
					StartX = X - edgelength;
					EndX = ImgSobelX.size().width;
				}
				else
				{
					StartX = X - edgelength;
					EndX = X + edgelength;
				}

				if (Y - edgelength < 0)
				{
					StartY = 0;
					EndY = Y + edgelength;
				}
				else if (Y + edgelength >= ImgSobelX.size().height)
				{
					StartY = Y - edgelength;
					EndY = ImgSobelX.size().height;
				}
				else
				{
					StartY = Y - edgelength;
					EndY = Y + edgelength;

				}
				int flag = 1;
				for (int y = StartY; y < EndY&&(flag==1); y++)
					for (int x = StartX; x < EndX; x++)
					{
					if (resultImage.at<int>(y, x) > resultImage.at<int>(Y, X))
						flag = 0;//不是局部最大
						break;
					}

				if (flag)
				{
					PointImage.at<int>(Y, X) = 255;
				}
			}
		}

	}
	
}

void Harris::DispResult(Mat sourceImg)
{
	 DispImg = sourceImg.clone();
	for (int Y=0; Y < ImgSobelX.size().height;Y++)
		for (int X = 0; X < ImgSobelX.size().width; X++)
		{
		if (PointImage.at<int>(Y, X) == 255)
		{
			circle(DispImg, Point(X, Y), 5, Scalar(0, 0, 255), 2, 8, 0);
		}

		}

}

Mat Harris::getimageSobelX()
{
	return ImgSobelX;

}
Mat Harris::getimageSobelY()
{
	return ImgSobelY;
}
Mat Harris::getDispImg()
{

	return DispImg;
}
