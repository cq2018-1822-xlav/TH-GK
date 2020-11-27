#include <iostream>
#include <functional>
#include <string>
#include "GeometricTransformer.h"

static int __str_cmp__(const char* string_1, const char* string_2)
{
	while (*string_1)
	{
		// if characters differ or end of second string is reached
		if (*string_1 != *string_2)
			break;

		// move to next pair of characters
		string_1++;
		string_2++;
	}

	// return the ASCII difference after converting char* to unsigned char*
	return *(const unsigned char*)string_1 - *(const unsigned char*)string_2 == 0 ? 1 : 0;
}


int main(int argc, char* argv[]) {
	// std::cout << "Hello world" << "\n";
	GeometricTransformer geometrixTransformer;

	cv::Mat translateMatrix = (cv::Mat_<float>(3, 3) << 1, 7, 2, 9, 1, 3, 0, 0, 1);

	std::cout << translateMatrix.ptr<float>(1)[0] << std::endl;

	/*
	cv::Mat matrix = cv::Mat::eye(3, 3, CV_32FC1);
	std::cout << translateMatrix << std::endl;

	for (int i = 0; i < translateMatrix.rows; i++) {
		for (int j = 0; j < translateMatrix.cols; j++) {
			std::cout << translateMatrix.at<float>(i, j) << " ";
		}
		std::cout << "\n";
	}

	matrix = matrix * translateMatrix;

	for (int i = 0; i < matrix.rows; i++) {
		for (int j = 0; j < matrix.cols; j++) {
			std::cout << matrix.at<float>(i, j) << " ";
		}
		std::cout << "\n";
	} */
	if (__str_cmp__(argv[1], "--zoom")) {
		if (__str_cmp__(argv[2], "--bl")) {

		}
		else if (__str_cmp__(argv[2], "--nn")) {

		}
		else {

		}
	}
	else if (__str_cmp__(argv[1], "--resize")) {
		if (__str_cmp__(argv[2], "--bl")) {

		}
		else if (__str_cmp__(argv[2], "--nn")) {

		}
		else {

		}
	}
	else if (__str_cmp__(argv[1], "--rotate")) {
		if (__str_cmp__(argv[2], "--bl")) {

		}
		else if (__str_cmp__(argv[2], "--nn")) {

		}
		else {

		}
	}
	else if (__str_cmp__(argv[1], "--rotateN")) {
		if (__str_cmp__(argv[2], "--bl")) {

		}
		else if (__str_cmp__(argv[2], "--nn")) {

		}
		else {

		}
	}
	else if (__str_cmp__(argv[1], "--flip")) {
		if (__str_cmp__(argv[2], "--bl")) {

		}
		else if (__str_cmp__(argv[2], "--nn")) {

		}
		else {

		}
	}
	else {

	}
	return 0;
}