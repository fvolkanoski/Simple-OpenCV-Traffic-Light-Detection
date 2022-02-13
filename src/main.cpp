#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
	cv::Mat image = cv::imread("your image path", 1);
    cv::Mat editedImage = image;

    cv::Mat imgHSV;
    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);

    std::vector <int> lower_red1({0,100,100});
    std::vector <int> upper_red1({10,255,255});
    std::vector <int> lower_red2({160,100,100});
    std::vector <int> upper_red2({180,255,255});
    std::vector <int> lower_green({40,50,50});
    std::vector <int> upper_green({90,255,255});
    std::vector <int> lower_yellow({15,150,150});
    std::vector <int> upper_yellow({35,255,255});

    cv::Mat mask1; cv::inRange(imgHSV, lower_red1, upper_red1, mask1);
    cv::Mat mask2; cv::inRange(imgHSV, lower_red2, upper_red2, mask2);
    cv::Mat mask_g; cv::inRange(imgHSV, lower_green, upper_green, mask_g);
    cv::Mat mask_r; cv::add(mask1, mask2, mask_r);

    std::vector<cv::Vec3f> r_circles, 
						   g_circles;

    cv::HoughCircles(mask_r, r_circles, cv::HOUGH_GRADIENT, 1, 80, 90, 12, 6, 30);
    cv::HoughCircles(mask_g, g_circles, cv::HOUGH_GRADIENT, 1, 60, 50, 10, 0, 30);

    for( size_t i = 0; i < r_circles.size(); i++ )
    {
		// Outline the detected red circle.
        cv::Vec3i c = r_circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        circle( editedImage, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
        int radius = c[2];
        circle( editedImage, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
    }

    for( size_t i = 0; i < g_circles.size(); i++ )
    {
		// Outline the detected red circle.
        cv::Vec3i c = g_circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        circle( editedImage, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
        int radius = c[2];
        circle( editedImage, center, radius, cv::Scalar(255,0,255), 3, cv::LINE_AA);
    }