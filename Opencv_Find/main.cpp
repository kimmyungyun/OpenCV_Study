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
		cv::Canny(Gray_img, canny_img, 25, 75);	//���� ������ ��� Ȯ���ؼ� ������� �ٲ���
		
		//cv::Mat binary_img;
		//cv::threshold(Gray_img, binary_img, 125, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
		//CV_THRESH_BINARY_INV - threshold �� �ʰ��� 255, ���ϴ� 0
		//CV_THRESH_OTSU - �ʱⰪ�� �����ϰ� �Է� ���� ���� ���������� threshold ���� ���ϰ� �̿� ���� ���õ� �ȼ��鿡 max_value���� �ش�.
		// threshold ���ǿ� ���� ���� ���� http://leeway.tistory.com/902
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(canny_img.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		//canny �ؼ� ������Ű�� findcontours ����Ʈ�� �̾Ƴ�
		//hull ���� defect �� ��
		//�ٸ� ���� hull �� ���� ���� Ż�� 
		
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
			//std::cout << i << " ��° " << x << " " << y << std::endl;
			cv::putText(viewFrame, std::to_string(size), tmpP, 2, 1.2, cv::Scalar(255, 0, 0));
		}
		//�� ����
		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(Gray_img, circles, CV_HOUGH_GRADIENT, 1, 50, 150, 29, 15, 200);

		int num = 0;
		
		for(size_t i = 0; i < circles.size(); i++)
		{
			cv::Vec3i c = circles[i];
			circle(viewFrame, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 0), 3, cv::LINE_AA);
			num++;
		}
		//�ܰ��� �׸���
		cv::drawContours(viewFrame, contours, -1, cv::Scalar(255, 0, 0), 3);
		////������
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
		

		std::cout <<"���� ���� : "<< num << std::endl;
		//cv::imshow("test", binary_img);
		cv::imshow("test2", viewFrame);
		cv::waitKey(0);
	}
}

//��ġ�� ���� Ȯ�� ���� ������ ���� ���� ���
// ���� ���� �� �̹����� �� 1 �� �׷�����, �ϳ��� �̹����� ���� ����.
//threshold �� 2�̻��� ���� �̾Ƴ� �׸��� �� ������ �̾��ָ� ������ ����

