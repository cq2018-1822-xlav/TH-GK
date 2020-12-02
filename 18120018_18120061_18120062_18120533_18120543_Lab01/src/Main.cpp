#include <iostream>
#include <functional>
#include <string>
#include "ColorTransformer.h"

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
	ColorTransformer colorTransfer;
	Converter converter;
	if (__str_cmp__(argv[1], "--rgb2gray")) {
		// --rgb2gray
		// code 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC1);

		// Chuyển đổi
		converter.Convert(inputImage, outputImage, 0);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);

		cv::namedWindow("Show result image RGB to GrayScale", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image RGB to GrayScale", outputImage);
		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image RGB to GrayScale");
	}
	else if (__str_cmp__(argv[1], "--gray2rgb")) {
		// --gray2rgb
		// code 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC3);

		// Chuyển đổi
		converter.Convert(inputImage, outputImage, 1);


		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);
		cv::namedWindow("Show result image GrayScale to RGB", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image GrayScale to RGB", outputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image GrayScale to RGB");
	}
	else if (__str_cmp__(argv[1], "--rgb2hsv")) {
		// --rgb2hsv
		// code 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC3);

		// Chuyển đổi
		converter.Convert(inputImage, outputImage, 2);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);
		cv::namedWindow("Show result image RGB to HSV", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image RGB to HSV", outputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image RGB to HSV");
	}
	else if (__str_cmp__(argv[1], "--hsv2rgb")) {
		// --hsv2rgb
		// code 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = cv::Mat(inputImage.rows, inputImage.cols, CV_8UC3);

		// Chuyển đổi
		converter.Convert(inputImage, outputImage, 3);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);
		cv::namedWindow("Show result image HSV to RGB", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result image HSV to RGB", outputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result image HSV to RGB");
	}
	else if (__str_cmp__(argv[1], "--bright")) {
		// --bright
		// code 
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = inputImage.clone();

		// Thay đổi độ sáng
		if (argv[3] == nullptr) {
			std::cout << "Exception: No brightness input.\n";
			return 0;
		}
		else {
			colorTransfer.ChangeBrighness(inputImage, outputImage, atoi(argv[3]));
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result after change birghtness", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result after change birghtness", outputImage);
			cv::waitKey(0);
			cv::destroyWindow("Input image");
			cv::destroyWindow("Show result after change birghtness");
		}
	}
	else if (__str_cmp__(argv[1], "--contrast")) {
		// --contrast
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage = inputImage.clone();

		// Thay đổi độ sáng
		if (argv[3] == nullptr) {
			std::cout << "Exception: No contrast input.\n";
			return 0;
		}
		else {
			colorTransfer.ChangeContrast(inputImage, outputImage, (float)atof(argv[3]));

			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result after change contrast", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result after change contrast", outputImage);
			cv::waitKey(0);

			cv::destroyWindow("Input image");
			cv::destroyWindow("Show result after change contrast");
		}
	}
	else if (__str_cmp__(argv[1], "--hist")) {
		// --hist
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Tính histogram của ảnh
		cv::Mat histogram_inputImage;
		colorTransfer.CalcHistogram(inputImage, histogram_inputImage);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);

		cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result", histogram_inputImage);
		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result");

	}
	else if (__str_cmp__(argv[1], "--equalhist")) {
		// --equalhist
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Khởi tạo ảnh đầu ra
		cv::Mat outputImage;

		// Cân bằng lược đồ màu
		colorTransfer.HistogramEqualization(inputImage, outputImage);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);

		cv::namedWindow("Show result equalization", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show result equalization", outputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show result equalization");
	}
	else if (__str_cmp__(argv[1], "--drawhist")) {
		// --drawhist
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// Tính histogram của ảnh
		cv::Mat histogram_matrix_inputImage;
		colorTransfer.CalcHistogram(inputImage, histogram_matrix_inputImage);

		cv::Mat histogram_inputImage;
		colorTransfer.DrawHistogram(histogram_matrix_inputImage, histogram_inputImage);

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", inputImage);

		cv::namedWindow("Show histogram", cv::WINDOW_AUTOSIZE);
		cv::imshow("Show histogram", histogram_inputImage);

		cv::waitKey(0);

		cv::destroyWindow("Input image");
		cv::destroyWindow("Show histogram");
	}
	else if (__str_cmp__(argv[1], "--compare")) {
		// --compare
		// code
		// Đọc ảnh (image) đầu vào)
		cv::Mat inputImage1 = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);
		cv::Mat inputImage2 = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		// So sánh hai ảnh
		// TODO: add some code here.

		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image 1", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image 1", inputImage1);
		cv::namedWindow("Input image 2", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image 2", inputImage2);

		cv::waitKey(0);
		cv::destroyWindow("Input image 1");
		cv::destroyWindow("Input image 2");
	}
	else if (__str_cmp__(argv[1], "--testhsv")) {
		// Đọc ảnh (image) đầu vào)
		cv::Mat input_image = cv::imread(argv[2], cv::IMREAD_ANYCOLOR);

		cv::Mat temp;
		// Tính histogram của ảnh
		cv::Mat output_image;
		converter.Convert(input_image, temp, 2);
		converter.Convert(temp, output_image, 3);
		// Dispay ảnh ra màn hình
		cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
		cv::imshow("Input image", input_image);

		cv::namedWindow("RGB -> HSV -> RGB", cv::WINDOW_AUTOSIZE);
		cv::imshow("RGB -> HSV -> RGB", output_image);
		cv::waitKey(0);
	}
	else if ((__str_cmp__(argv[1], "--help")) || (__str_cmp__(argv[1], "--h"))) {
		std::cout << "Usage:  ColorTranform.exe [command] [input path] [command arguments]\n\n"
			<< "Options command & command arguments:\n"
			"--rgb2gray\t[no command arguments]\t\t Convert the image's color space from RGB to GrayScale.\n"
			"--gray2rgb\t[no command arguments]\t\t Convert the image's color space from GrayScale to RGB.\n"
			"--rgb2hsv\t[no command arguments]\t\t Convert the image's color space from RGB to HSV.\n"
			"--hsv2rgb\t[no command arguments]\t\t Convert the image's color space from HSV to RGB.\n"
			"--bright\t[b]\t\t\t\t Change image's brightness with intensity equal to [b] argument.\n"
			"--contrast\t[c]\t\t\t\t Change image's contrast with intensity equal to [c] argument.\n"
			"--hist\t\t[no command arguments]\t\t Calculate the histogram of RGB image, GrayScale image.\n"
			"--equalhist\t[no command arguments]\t\t Equilibrate the histogram of RGB image, GrayScale image.\n"
			"--drawhist\t[no command arguments]\t\t Draw the histogram of RGB image, GrayScale image.\n"
			"--compare\t[path img 1] [path img 2]\t\t Compare two image based on the histogram of them.\n"
			"\n\nDepartment of Computer Science, University of Science\nAuthor: Hoang-Duc Nguyen, Nhut-Nam Le, Hoang-Nam Nguyen, Bao-Son Duong Doan, Dai-Tai Tran"
			;
	}
	else {
		std::cout << "[Exception] Error arguments.\n";
	}
	//std::cin.get();
	return 0;
}