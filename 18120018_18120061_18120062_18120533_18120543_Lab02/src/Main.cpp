#include <iostream>
#include <functional>
#include <string>
#include "CV_Include.h"

int main() {
	[out = std::ref(std::cout << "Hello ")] (){out.get() << "world."; }();

	// Read the image file
	cv::Mat image = cv::imread("E:/illya.jpg");

	// Check for failure
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		std::cin.get(); //wait for any key press
		return -1;
	}

	std::string windowName = "My girl"; //Name of the window

	cv::namedWindow(windowName); // Create a window

	imshow(windowName, image); // Show our image inside the created window.

	cv::waitKey(0); // Wait for any keystroke in the window

	cv::destroyWindow(windowName); //destroy the created window
	return 0;
}