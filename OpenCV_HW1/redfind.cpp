//#ifdef __DEBUG
//#pragma comment(lib, "opencv_world320d.lib")
//#else
//#pragma comment(lib, "opencv_world320.lib")
//#endif
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//#include <iostream>
//#include <vector>
//
//int main()
//{
//	cv::VideoCapture vc(0);
//	if (!vc.isOpened()) return 0;
//	cv::Mat img;
//	
//	while (1)
//	{
//				//	일단 빨간공 부분
//		vc >> img;
//
//		cv::Mat hsvImage;
//		cv::cvtColor(img, hsvImage, CV_BGR2HSV);
//
//		std::vector<cv::Mat> sImg;
//		cv::split(hsvImage, sImg);
//
//		cv::Mat RanImg;
//	
//		cv::inRange(hsvImage, cv::Scalar(45, 35, 40), cv::Scalar(75, 255, 255), RanImg);
//
//		std::vector<std::vector<cv::Point>> contours;
//		std::vector<cv::Vec4i> hierarchy;
//
//		cv::Mat tmp = RanImg.clone();
//				
//		cv::findContours(tmp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//		cv::Mat tmp2(tmp.size(), CV_8U, cv::Scalar(255));
//
//		std::vector<std::vector<cv::Point>> hull(contours.size());
//		for (int i = 0; i < contours.size(); i++)
//		{
//			cv::convexHull(contours[i], hull[i]);
//		}
//
//		drawContours(tmp2, contours, -1, cv::Scalar(0), 3);
//
//		std::vector<cv::Vec3f> circles;
//		cv::HoughCircles(tmp2, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0);
//
//		std::vector<cv::Rect> boundRect(contours.size());
//		std::vector<cv::Point2f> center(contours.size());
//		std::vector<float> radius(contours.size());
//		std::vector<cv::RotatedRect> rbbox(contours.size());
//
//		cv::Mat Img2=img.clone();
//		
//		for (int i = 0; i < contours.size(); i++)
//		{
//			boundRect[i] = cv::boundingRect(contours[i]);
//			rbbox[i] = cv::minAreaRect(contours[i]);
//			//cv::minEnclosingCircle(contours[i], center[i], radius[i]);
//		}
//		for (int i = 0; i < circles.size(); i++)
//		{
//			cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//			int radius = cvRound(circles[i][2]);
//			circle(Img2, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
//		}
//		
//		for (int i = 0; i < contours.size(); i++)
//		{
//			cv::rectangle(Img2, boundRect[i], cv::Scalar(0, 255, 0), 2);
//			cv::Point2f pts[4];
//			rbbox[i].points(pts);
//			for (int j = 0; j < 4; j++)
//			{
//				cv::line(Img2, pts[j], pts[(j + 1) % 4], cv::Scalar(0, 0, 255));
//			}
//		//	cv::circle(Img2, center[i], (int)radius[i], cv::Scalar(0, 255, 0), 2, 8, 0);
//		}
//		
//
//	
//		char c = cv::waitKey(33);
//
//		cv::imshow("view", Img2);
//		cv::imshow("view2", tmp2);
//		if (c == 'q')
//		{
//			break;
//		}
//	}
//	cv::destroyAllWindows();
//	return 0;
//}