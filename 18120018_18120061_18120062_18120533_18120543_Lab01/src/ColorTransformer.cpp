﻿#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const cv::Mat& sourceImage, cv::Mat& destinationImage, short b)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}
	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Mode
	int mode;

	// Check the source image is RGB type?
	if (sourceImage.type() == CV_8UC3) {
		mode = 3;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC3, cv::Scalar(0));
	}
	else if (sourceImage.type() == CV_8UC1) {
		mode = 1;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC1, cv::Scalar(0));
	}

	// Số channels của ảnh destination
	int destinationChannels = destinationImage.channels();

	// Widthstep của ảnh source
	size_t sourceWidthStep = sourceImage.step[0];

	// Widthstep của ảnh destination
	size_t destinationWidthStep = destinationImage.step[0];

	// Con trỏ quản lý vùng nhớ data ảnh source
	uchar* ptrSourceData = sourceImage.data;

	// Con trỏ quản lý vùng nhớ data ảnh destination
	uchar* ptrDestinationData = destinationImage.data;

	for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
		uchar* ptrSourceRow = ptrSourceData;
		uchar* ptrDestinationRow = ptrDestinationData;

		for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {
			if (mode == 3) {
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];

				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];

				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];

				blue = blue + b > 255 ? 255 : blue + b;
				green = green + b > 255 ? 255 : green + b;
				red = red + b > 255 ? 255 : red + b;

				// Gán giá trị độ xám vừa lấy được vào kênh màu Blue của ảnh destination
				ptrDestinationRow[0] = blue;
				// Gán giá trị độ xám vừa lấy được vào kênh màu Green của ảnh destination
				ptrDestinationRow[1] = green;
				// Gán giá trị độ xám vừa lấy được vào kênh màu Red của ảnh destination
				ptrDestinationRow[2] = red;
			}
			else if (mode == 1) {
				// Lấy giá trị kênh màu gray của ảnh source
				uchar gray = ptrSourceRow[0];

				gray = gray + b > 255 ? 255 : gray + b;

				// Gán giá trị độ xám vừa tính được vào kênh vào của ảnh destination
				ptrDestinationRow[0] = gray;
			}
			
		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_brightness.jpg", destinationImage);


	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: change brightness of image.\n";
	return 0;
}

int ColorTransformer::ChangeContrast(const cv::Mat& sourceImage, cv::Mat& destinationImage, float c)
{
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 1
	}
	// Tính số cột, số dòng của sourceImage
	int width = sourceImage.cols, height = sourceImage.rows;
	//tạo destinationImage là 1 bản sao của sourceImage
	destinationImage = sourceImage.clone();
	//Tính số channels
	int srcChannels = sourceImage.channels();
	int desChannels = destinationImage.channels();
	//Kiểm tra số channels của sourceImage
	if (srcChannels == 1) {
		for (int y = 0; y < height; y++)
		{
			//con trỏ quản lý dòng
			const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
			uchar* pDstRow = destinationImage.ptr<uchar>(y);

			for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += desChannels)
			{
				//lấy giá trị kênh màu nhân với c, sau đó gán qua destinationImage
				pDstRow[0] = cv::saturate_cast<uchar>(pSrcRow[0] * c);
			}


		}

	}
	else if (srcChannels == 3) {
		// Con trỏ quản lý vùng nhớ data ảnh sourceimage
		uchar* ptrSourceData = sourceImage.data;
		// Con trỏ quản lý vùng nhớ data ảnh destinationImage
		uchar* ptrdestinationData = destinationImage.data;
		//Tính widthstep
		int sourceWidthStep = sourceImage.step[0];
		int desWidthStep = destinationImage.step[0];


		for (int y = 0; y < height; y++, ptrSourceData += sourceWidthStep, ptrdestinationData += desWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDesRow = ptrdestinationData;

			for (int x = 0; x < width; x++, ptrSourceRow += srcChannels, ptrDesRow += desChannels) {

				// lấy giá trị kênh màu nhân với c, sau đó gán qua destinationImage

				ptrDesRow[0] = cv::saturate_cast<uchar>(ptrSourceRow[0] * c);

				ptrDesRow[1] = cv::saturate_cast<uchar>(ptrSourceRow[1] * c);

				ptrDesRow[2] = cv::saturate_cast<uchar>(ptrSourceRow[2] * c);


			}
		}

	}
	//Lưu ảnh destinationImage
	cv::imwrite("result_contrast.jpg", destinationImage);
	std::cout << "Sucess: change contrast of image.\n";
	return 1;

}

int ColorTransformer::CalcHistogram(const cv::Mat& sourceImage, cv::Mat& histMatrix)
{
	// Kiểm tra ảnh đầu vào
	if (!sourceImage.data) {
		std::cout << "Exception: Can not calculate the histogram of image.\n";
		return 0;
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Nếu ảnh đầu vào là ảnh GrayScale
	if (sourceImage.channels() == 1) {
		// Khởi tạo ảnh histogram matrix với thông số height = 1, width = 256
		histMatrix = cv::Mat(1, 256, CV_32S, cv::Scalar(0));

		// Số channels của ảnh destination
		int histMatrixChannels = histMatrix.channels();

		// Widthstep của ảnh source
		size_t sourceWidthStep = sourceImage.step[0];

		// Widthstep của ảnh destination
		size_t histMatrixWidthStep = histMatrix.step[0];

		// Con trỏ quản lý vùng nhớ data ảnh source
		uchar* ptrSourceData = sourceImage.data;

		// Con trỏ quản lý vùng nhớ data ảnh destination
		int* ptrHistMatrixData = histMatrix.ptr<int>(0);

		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels) {

				uchar gray = ptrSourceRow[0];
				ptrHistMatrixData[gray] += 1;
			}
		}

		int sum = 0;
		for (int i = 0; i < 256; i++) {
			sum += ptrHistMatrixData[i];
		}

		std::cout << sum << std::endl;

		std::cout << "Success: Calculated the histogram of image.\n";
		return 1;
	}

	// Nếu ảnh đầu vào là ảnh RGB
	else if (sourceImage.channels() == 3) {


		// Khởi tạo ảnh histogram matrix với thông số height = 3, width = 256
		histMatrix = cv::Mat(3, 256, CV_32S, cv::Scalar(0));
		// std::vector<std::vector<int>> histVector(3, std::vector<int>(256, 0));

		// Số channels của ảnh destination
		int histMatrixChannels = histMatrix.channels();

		// Widthstep của ảnh source
		size_t sourceWidthStep = sourceImage.step[0];

		// Widthstep của ảnh destination
		size_t histMatrixWidthStep = histMatrix.step[0];

		// Con trỏ quản lý vùng nhớ data ảnh source
		uchar* ptrSourceData = sourceImage.data;

		// Con trỏ quản lý vùng nhớ data ảnh destination
		int* blueHistMatrixData = histMatrix.ptr<int>(0);
		int* greenHistMatrixData = histMatrix.ptr<int>(1);
		int* redHistMatrixData = histMatrix.ptr<int>(2);

		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels) {

				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];

				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];

				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];

				// Blue
				blueHistMatrixData[blue] += 1;
				// Green
				greenHistMatrixData[green] += 1;
				// Red
				redHistMatrixData[red] += 1;
			}
		}

		int sum_blue = 0;
		for (int i = 0; i < 256; i++) {
			sum_blue += blueHistMatrixData[i];
		}

		std::cout << sum_blue << std::endl;
		int sum_green = 0;
		for (int i = 0; i < 256; i++) {
			sum_green += greenHistMatrixData[i];
		}

		std::cout << sum_green << std::endl;
		int sum_red = 0;
		for (int i = 0; i < 256; i++) {
			sum_red += redHistMatrixData[i];
		}

		std::cout << sum_red << std::endl;

		std::cout << "Success: Calculated the histogram of image.\n";
		return 1;
	}
	std::cout << "Exception: Can not calculate the histogram of image.\n";
	return 0;
}

int ColorTransformer::HistogramEqualization(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;
	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;
	// Diện tích area của ảnh
	int area = width * heigth;
	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Mode
	int mode;

	// Mảng chứa blue histogram có 256 phần tử
	int blueHistogram[256];
	// Mảng chứa green histogram có 256 phần tử
	int greenHistogram[256];
	// Mảng chứa red histogram có 256 phần tử
	int redHistogram[256];
	// Mảng chứa gray histogram có 256 phần tử
	int grayHistogram[256];

	// Vòng lặp khởi tạo giá trị cho các mảng trên có giá trị bằng 0
	for (int i = 0; i < 256; i++) {
		blueHistogram[i] = 0;
		greenHistogram[i] = 0;
		redHistogram[i] = 0;
		//
		grayHistogram[i] = 0;
	}

	// Check the source image is RGB type?
	if (sourceImage.type() == CV_8UC3) {
		mode = 3;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC3, cv::Scalar(0));

	}
	else if (sourceImage.type() == CV_8UC1) {
		mode = 1;
		// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC1, cv::Scalar(0));

	}
	// Số channels của ảnh destination
	int destinationChannels = destinationImage.channels();
	// Widthstep của ảnh source
	size_t sourceWidthStep = sourceImage.step[0];
	// Widthstep của ảnh destination
	size_t destinationWidthStep = destinationImage.step[0];
	// Con trỏ quản lý vùng nhớ data ảnh source
	uchar* ptrSourceData = sourceImage.data;
	// Con trỏ quản lý vùng nhớ data ảnh destination
	uchar* ptrDestinationData = destinationImage.data;

	// Tính histogram
	for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep) {
		uchar* ptrSourceRow = ptrSourceData;
		for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels) {
			if (mode == 3) {
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];
				blueHistogram[blue]++;

				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];
				greenHistogram[green]++;

				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];
				redHistogram[red]++;
			}
			else if (mode == 1) {
				// Lấy giá trị kênh màu gray của ảnh source
				uchar gray = ptrSourceRow[0];
				grayHistogram[gray]++;
			}

		}
	}

	// Con trỏ ptrSourceData nắm phần data của sourceImage
	ptrSourceData = sourceImage.data;

	// Nếu là ảnh grayscale: Cân bằng lược đồ xám
	if (mode == 1) {
		int grayEqualization[256];

		// T[0] = H[0]
		grayEqualization[0] = grayHistogram[0];

		for (int i = 1; i < 256; i++) {
			grayEqualization[i] = grayEqualization[i - 1] + grayHistogram[i];
		}

		for (int i = 0; i < 256; i++) {
			grayEqualization[i] = round(255 * grayEqualization[i] / area);
		}

		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDestinationRow = ptrDestinationData;

			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {
				// Lấy giá trị kênh màu Gray của ảnh source
				uchar gray = ptrSourceRow[0];

				// Gán giá trị độ xám vừa tính được vào kênh vào của ảnh destination
				ptrDestinationRow[0] = grayEqualization[gray];
			}
		}
	}
	else if (mode == 3) {
		int blueEqualization[256];
		int greenEqualization[256];
		int redEqualization[256];

		blueEqualization[0] = blueHistogram[0];
		greenEqualization[0] = greenHistogram[0];
		redEqualization[0] = redHistogram[0];

		for (int i = 1; i < 256; i++) {
			blueEqualization[i] = blueEqualization[i - 1] + blueHistogram[i];

			greenEqualization[i] = greenEqualization[i - 1] + greenHistogram[i];

			redEqualization[i] = redEqualization[i - 1] + redHistogram[i];

		}

		for (int i = 0; i < 256; i++) {
			blueEqualization[i] = round(255 * blueEqualization[i] / area);

			greenEqualization[i] = round(255 * greenEqualization[i] / area);

			redEqualization[i] = round(255 * redEqualization[i] / area);

		}


		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDestinationRow = ptrDestinationData;

			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];
				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];
				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];
				// Gán giá trị độ xám vừa lấy được vào kênh màu Blue của ảnh destination
				ptrDestinationRow[0] = blueEqualization[blue];
				// Gán giá trị độ xám vừa lấy được vào kênh màu Green của ảnh destination
				ptrDestinationRow[1] = greenEqualization[green];
				// Gán giá trị độ xám vừa lấy được vào kênh màu Red của ảnh destination
				ptrDestinationRow[2] = redEqualization[red];
			}
		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_histogram_equalization.jpg", destinationImage);


	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: equalize histograms of image.\n";
	return 0;
}

int ColorTransformer::DrawHistogram(const cv::Mat& histMatrix, cv::Mat& histImage)
{
	// Kiểm tra ma trận hist đầu vào
	if (histMatrix.empty())
	{
		std::cout << "[EXCEPTION] Error with input histogram matrix.\n";
		return 0;
	}

	cv::Mat hist = histMatrix.clone();

	// Vẽ histogram cho ảnh grayscale
	if (hist.rows == 1)
	{

		uchar* ptrHistMatrixData = hist.data;
		uchar max = *ptrHistMatrixData;

		for (int i = 0; i < hist.cols; i++)
		{
			max = max < *(ptrHistMatrixData + i) ? *(ptrHistMatrixData + i) : max;
		}

		for (int i = 0; i < hist.cols; i++)
		{
			*(ptrHistMatrixData + i) = *(ptrHistMatrixData + i) * 300 / max;
		}

		histImage = cv::Mat(300, 256, CV_8UC1, cv::Scalar(0));

		for (int j = 0; j < histImage.cols; j++)
		{
			line(histImage, cv::Point(j, histImage.rows - 1 - *(ptrHistMatrixData + j)),
				cv::Point(j, histImage.rows - 1), Color::white, 2);
		}

		cv::imwrite("result_histogram_gray.jpg", histImage);
		return 1;
	}
	// Vẽ histogram cho ảnh màu
	else if (hist.rows == 3)
	{
		uchar* ptrHistMatrixData = hist.data;

		uchar max = *ptrHistMatrixData;
		uchar* ptrSourceData = ptrHistMatrixData;
		for (int i = 0; i < hist.rows; i++, ptrSourceData += hist.step[0])
		{
			uchar* ptrSourceRow = ptrSourceData;
			for (int j = 0; j < hist.cols; j++)
			{
				max = max < *(ptrSourceRow + j) ? *(ptrSourceRow + j) : max;
			}
		}

		for (int i = 0; i < hist.rows; i++, ptrSourceData += hist.step[0])
		{
			uchar* ptrSourceRow = ptrSourceData;
			for (int j = 0; j < hist.cols; j++)
			{
				*(ptrHistMatrixData + i) = *(ptrHistMatrixData + i) * 300 / max;
			}
		}

		histImage = cv::Mat(300, 256 * 3, CV_8UC3, cv::Scalar(0));

		size_t histMatrixWidthStep = hist.step[0];
		uchar* blueHistMatrixData = ptrHistMatrixData;
		uchar* greenHistMatrixData = ptrHistMatrixData + histMatrixWidthStep;
		uchar* redHistMatrixData = ptrHistMatrixData + histMatrixWidthStep + histMatrixWidthStep;
		for (int j = 0; j < hist.cols; j++)
		{
			// cv::Scalar(255, 0, 0) đường màu xanh
			line(histImage, cv::Point(j, histImage.rows - 1 - *(blueHistMatrixData + j)),
				cv::Point(j, histImage.rows - 1), Color::blue, 2);
			line(histImage, cv::Point(256 + j, histImage.rows - 1 - *(greenHistMatrixData + j)),
				cv::Point(256 + j, histImage.rows - 1), Color::green, 2);
			line(histImage, cv::Point(512 + j, histImage.rows - 1 - *(redHistMatrixData + j)),
				cv::Point(512 + j, histImage.rows - 1), Color::red, 2);
		}

		cv::imwrite("result_histogram_rgb.jpg", histImage);
		return 1;
	}
	return 0;
}

float ColorTransformer::CompareImage(const cv::Mat& image1, cv::Mat& image2)
{
	if (!image1.data || !image2.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return -1; // Trả về 1
	}
	//khởi tạo 2 histogram
	cv::Mat hist1;
	cv::Mat hist2;
	//Tính histogram của 2 ảnh
	CalcHistogram(image1, hist1);
	CalcHistogram(image2, hist2);
	//Tính số channels của 2 histogram
	int hist1Channels = hist1.channels();
	int hist2Channels = hist2.channels();
	//Khởi tạo biến đếm tổng các phần tử trong histogram
	float sum1 = 0;
	float sum2 = 0;
	//Mảng 2 chiều lưu trữ các phần tử histogram
	float arr1[3][256];
	float arr2[3][256];
	//Biến kết quả
	float result = 0;
	if (image1.channels() == 1 && image2.channels() == 1)
	{

		// con trỏ data của histogram 1
		uchar* ptrHistMatrixData1 = hist1.data;
		for (int x = 0; x <= 255; x++, ptrHistMatrixData1 += hist1Channels) {

			//lấy giá của histogram lưu vào mảng
			arr1[0][x] = int(*ptrHistMatrixData1);
			//Tính tổng các phần tử
			sum1 += arr1[0][x];

		}
		// con trỏ data của histogram 1
		uchar* ptrHistMatrixData2 = hist2.data;
		for (int x = 0; x <= 255; x++, ptrHistMatrixData2 += hist2Channels) {
			//lấy giá của histogram lưu vào mảng
			arr2[0][x] = int(*ptrHistMatrixData2);
			//Tính tổng các phần tử
			sum2 += arr2[0][x];

		}

		for (int i = 0; i <= 255; i++)
		{
			//Chuẩn hóa các phần tử trong histogram
			arr1[0][i] = arr1[0][i] / sum1;
			arr2[0][i] = arr2[0][i] / sum2;
			//Tính độ tương đồng của 2 ảnh
			result += (arr1[0][i] - arr2[0][i]) * (arr1[0][i] - arr2[0][i]);
		}

		return sqrt(result);
	}

	else if (image1.channels() == 3 && image2.channels() == 3)
	{
		// con trỏ data của histogram 1
		uchar* ptrHistMatrixData1 = hist1.data;
		size_t hist1Step = hist1.step[0];
		uchar* blueHist1Data = hist1.data;
		uchar* greenHist1Data = hist1.data + hist1Step;
		uchar* redHist1Data = hist1.data + hist1Step + hist1Step;

		for (int x = 0; x <= 255; x++, blueHist1Data += hist1Channels) {

			//lấy giá của histogram lưu vào mảng
			arr1[0][x] = int(*blueHist1Data);

			arr1[1][x] = int(*greenHist1Data);

			arr1[2][x] = int(*redHist1Data);
			//Tính tổng các phần tử
			sum1 += arr1[0][x];


		}
		// con trỏ data của histogram 1
		uchar* ptrHistMatrixData2 = hist2.data;
		size_t hist2Step = hist2.step[0];
		uchar* blueHist2Data = hist2.data;
		uchar* greenHist2Data = hist2.data + hist2Step;
		uchar* redHist2Data = hist2.data + hist2Step + hist2Step;
		for (int x = 0; x <= 255; x++, blueHist2Data += hist2Channels) {

			//lấy giá của histogram lưu vào mảng
			arr2[0][x] = int(*blueHist2Data);

			arr2[1][x] = int(*greenHist2Data);

			arr2[2][x] = int(*redHist2Data);
			//Tính tổng các phần tử
			sum2 += arr2[0][x];


		}
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i <= 255; i++)
			{
				//Chuẩn hóa các phần tử trong histogram
				arr1[j][i] /= sum1;
				arr2[j][i] /= sum2;
				//Tính độ tương đồng của 2 ảnh
				result += (arr1[j][i] - arr2[j][i]) * (arr1[j][i] - arr2[j][i]);
			}
		}

		return sqrt(result);
	}
	else {
		std::cout << "\ncan not compare 2 image" << std::endl;
		return -1;
	}
}

ColorTransformer::ColorTransformer() = default;

ColorTransformer::~ColorTransformer() = default;
