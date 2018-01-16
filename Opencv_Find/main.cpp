#ifdef __DEBUG
#pragma comment(lib, "opencv_world320d.lib")
#else
#pragma comment(lib, "opencv_world320.lib")
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>

int main()
{

//	cv::VideoCapture vc(0);
//	if (!vc.isOpened()) return 0;
	cv::Mat orgFrame= cv::imread("test2.png");

	while (1)
	{
		cv::Mat viewFrame = orgFrame.clone();
		cv::Mat canny_img;
		cv::Mat Gray_img;
		
		cv::cvtColor(orgFrame, Gray_img, CV_BGR2GRAY);
		cv::Canny(Gray_img, canny_img, 25, 75);	//왼쪽 오른쪽 경계 확인해서 흰색으로 바꿔줌
		
		//cv::Mat binary_img;
		//cv::threshold(Gray_img, binary_img, 125, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
		//CV_THRESH_BINARY_INV - threshold 값 초과는 255, 이하는 0
		//CV_THRESH_OTSU - 초기값과 무관하게 입력 영상에 대해 내부적으로 threshold 값을 구하고 이에 따라 선택된 픽셀들에 max_value값을 준다.
		// threshold 조건에 따른 영상 차이 http://leeway.tistory.com/902
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(canny_img.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//canny 해서 반전시키고 findcontours 리스트로 뽑아냄
		//hull 에서 defect 를 뺌
		//다른 도형 hull 에 많이 들어가면 탈락 
		
		std::vector<cv::Point2f> approx;
		cv::Mat img3 = orgFrame.clone();
		
		std::vector<cv::Point>::iterator itc;
		for (size_t i = 0; i < contours.size(); i++)
		{
			approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.01, true);
			int size = approx.size();
			itc = contours[i].begin();
			double x = 0, y = 0;
			int n = 0;
			while (itc != contours[i].end())
			{
				x += itc->x;
				y += itc->y;
				itc++;
				n++;
			}
			x = x / n;
			y = y / n;
			cv::Point tmpP;
			tmpP.x = x;
			tmpP.y = y;
			//std::cout << i << " 번째 " << x << " " << y << std::endl;
			cv::putText(viewFrame, std::to_string(size), tmpP, 2, 1.2, cv::Scalar(255, 0, 0));
		}
		//원 감지
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(Gray_img, circles, CV_HOUGH_GRADIENT, 1, 50, 150, 29, 15, 200);

		int num = 0;
		
		for(size_t i = 0; i < circles.size(); i++)
		{
			cv::Vec3i c = circles[i];
			circle(viewFrame, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
			num++;
		}
		//외곽선 그리기
		cv::drawContours(viewFrame, contours, -1, cv::Scalar(255, 0, 0), 3);
		////선감지
		//
		//std::vector<cv::Vec4i> lines;
		//cv::HoughLinesP(canny_img, lines, 1, CV_PI / 180, 30, 30, 5);
		//std::vector<cv::Vec4i>::const_iterator Lit = lines.begin();
		//
		//while (Lit != lines.end())
		//{
		//	cv::Point pt1((*Lit)[0], (*Lit)[1]);
		//	cv::Point pt2((*Lit)[2], (*Lit)[3]);
		//	cv::line(img, pt1, pt2, cv::Scalar(255, 0, 0), 5);
		//	++Lit;
		//}
		

		std::cout <<"원의 개수 : "<< num << std::endl;
		//cv::imshow("test", binary_img);
		cv::imshow("test2", viewFrame);
		cv::waitKey(0);
	}
}

//겹치는 도형 확인 각이 적은게 위에 있을 경우
// 허프 라인 각 이미지에 값 1 로 그려놓고, 하나의 이미지에 전부 더함.
//threshold 로 2이상인 점을 뽑아냄 그리고 그 점들을 이어주면 도형이 나옴

