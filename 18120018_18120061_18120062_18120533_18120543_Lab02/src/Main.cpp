#include <iostream>
#include <functional>
#include "GeometricTransformer.h"

int main(int argc, char* argv[]) {
	GeometricTransformer geometrixTransformer;
	PixelInterpolate* interpolate;

	if (strcmp(argv[1], "--zoom") == 0) {
		// program.exe --zoom --bl image_path he_so_zoom
		if (strcmp(argv[2], "--bl") == 0) {
			interpolate = new BilinearInterpolate();
			// Đọc ảnh (image) đầu vào)
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.Scale(inputImage, outputImage, (float)atof(argv[4]), (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);
		}
		// program.exe --zoom --nn image_path sx xy
		else if (strcmp(argv[2], "--nn") == 0) {
			interpolate = new NearestNeighborInterpolate();
			// Đọc ảnh (image) đầu vào)
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.Scale(inputImage, outputImage, (float)atof(argv[4]), (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);
		}
		else {
			std::cout << "[EXCEPTION] \n";
		}
	}
	else if (strcmp(argv[1], "--resize") == 0) {
		// program.exe --resize --bl image_path newWidth newHeight
		if (strcmp(argv[2], "--bl") == 0) {
			interpolate = new BilinearInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr || argv[5] == nullptr || (argv[4] == nullptr && argv[5] == nullptr)) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.Resize(inputImage, outputImage, atoi(argv[4]), atoi(argv[5]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);
		}
		else if (strcmp(argv[2], "--nn") == 0) {
			// program.exe --resize --nn image_path newWidth newHeight
			interpolate = new NearestNeighborInterpolate();
			// Đọc ảnh (image) đầu vào)
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr || argv[5] == nullptr || (argv[4] == nullptr && argv[5] == nullptr)) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.Resize(inputImage, outputImage, atoi(argv[4]), atoi(argv[5]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);

		}
		else {
			std::cout << "[EXCEPTION] \n";
		}
	}
	else if (strcmp(argv[1], "--rotate") == 0) {
		// program.exe --rotate --bl image_path angle
		if (strcmp(argv[2], "--bl") == 0) {
			interpolate = new BilinearInterpolate();

			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.RotateKeepImage(inputImage, outputImage, (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);

		}
		else if (strcmp(argv[2], "--nn") == 0) {
			// program.exe --rotate --nn image_path angle
			interpolate = new NearestNeighborInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.RotateKeepImage(inputImage, outputImage, (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);
		}
		else {
			std::cout << "[EXCEPTION] \n";
		}
	}
	else if (strcmp(argv[1], "--rotateN") == 0) {
		// program.exe --rotateN --bl image_path angle
		if (strcmp(argv[2], "--bl") == 0) {
			interpolate = new BilinearInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.RotateUnkeepImage(inputImage, outputImage, (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);

		}
		// program.exe --rotateN --nn image_path angle
		else if (strcmp(argv[2], "--nn") == 0) {
			interpolate = new NearestNeighborInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage;
			if (argv[4] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}
			else {
				geometrixTransformer.RotateUnkeepImage(inputImage, outputImage, (float)atof(argv[4]), interpolate);
			}
			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);

		}
		else {
			std::cout << "[EXCEPTION] \n";
		}
	}
	else if (strcmp(argv[1], "--flip") == 0) {
		// program.exe --flip --bl input_path direction
		if (strcmp(argv[2], "--bl") == 0) {
			interpolate = new BilinearInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);



			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage = inputImage.clone();
			if (strcmp(argv[4], "Ox") == 0) {
				geometrixTransformer.Flip(inputImage, outputImage, true, interpolate);
			}
			else {
				geometrixTransformer.Flip(inputImage, outputImage, false, interpolate);
			}

			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);
			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);

		}
		// program.exe --flip --nn input_path direction
		else if (strcmp(argv[2], "--nn") == 0) {
			interpolate = new NearestNeighborInterpolate();
			// Đọc ảnh (image) đầu vào)
			if (argv[3] == nullptr) {
				std::cout << "[Exception].\n";
				return 0;
			}

			cv::Mat inputImage = cv::imread(argv[3], cv::IMREAD_ANYCOLOR);

			// Khởi tạo ảnh đầu ra
			cv::Mat outputImage = inputImage.clone();
			if (strcmp(argv[4], "Ox") == 0) {
				geometrixTransformer.Flip(inputImage, outputImage, true, interpolate);
			}
			else {
				geometrixTransformer.Flip(inputImage, outputImage, false, interpolate);
			}

			// Dispay ảnh ra màn hình
			cv::namedWindow("Input image", cv::WINDOW_AUTOSIZE);
			cv::imshow("Input image", inputImage);

			cv::namedWindow("Show result", cv::WINDOW_AUTOSIZE);
			cv::imshow("Show result", outputImage);
			cv::waitKey(0);
		}
		else {
			std::cout << "[EXCEPTION] \n";
		}
	}
	else if (strcmp(argv[1], "--help") || strcmp(argv[1], "--h")) {
		std::cout << "Usage: <Program.exe> <Command> <Interpolate> <InputPath> <CmdArguments>\n"
			"\t<Program.exe>: \n"
			"\t<Command>: \n"
			"\t<Interpolate>:\n"
			"\t\t --bl: Bilinear interpolate\n"
			"\t\t --nn: Nearest neighbor interpolate\n"
			"\t<InputPath>: Input image's path\n"
			"\t<CmdArguments>: \n"
			"\t--zoom: \n"
			"\t--resize: \n"
			"\t--rotate: \n"
			"\t--rotateN: \n"
			"\t--flip: \n"
			"\n\nDepartment of Computer Science, University of Science\nAuthor: Hoang-Duc Nguyen, Nhut-Nam Le, Hoang-Nam Nguyen, Bao-Son Duong Doan, Dai-Tai Tran\n"
			;
	}
	else {
		std::cout << "[EXCEPTION] \n";
	}
	return 0;
}