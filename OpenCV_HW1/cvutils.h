#pragma once

#ifdef _DEBUG
#pragma comment(lib, "opencv_world320d.lib")
#else
#pragma comment(lib, "opencv_world320.lib")
#endif

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>