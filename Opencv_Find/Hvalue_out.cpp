//#include "cvutils.h"
//#include <iostream>
//cv::Mat Himg;
//int tH = 100;
//void setMouseCall(int evt, int x, int y, int flag, void* data)
//{
//	if (evt == CV_EVENT_LBUTTONDOWN)
//	{
//		std::cout << (int)Himg.at<uchar>(y, x) << std::endl;
//		tH = Himg.at<uchar>(y, x);
//	}
//}
//int main()
//{
//	cv::namedWindow("test");
//	cv::setMouseCallback("test", setMouseCall, NULL);
//	cv::VideoCapture vc(0);
//	while (1)
//	{
//		std::vector<cv::Mat> chanels;
//		cv::Mat frame;
//		vc >> frame;
//		cv::Mat HSV;
//		cv::cvtColor(frame, HSV, CV_BGR2HSV);
//		split(HSV, chanels);
//		Himg = chanels[0].clone();
//		imshow("test", frame);
//		cv::Mat rangeimg;
//		cv::inRange(Himg, cv::Scalar(tH - 10), cv::Scalar(tH + 10), rangeimg);
//		cv::imshow("suspect Area", rangeimg);
//		cv::waitKey(1);
//
//	}
//	return 0;
//}
