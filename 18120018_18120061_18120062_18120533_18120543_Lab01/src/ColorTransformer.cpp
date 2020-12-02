#include "ColorTransformer.h"

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
	return 0;
}

int ColorTransformer::CalcHistogram(const cv::Mat& sourceImage, cv::Mat& histMatrix)
{
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
	// TODO: Implement with your code
	return 0.0f;
}

ColorTransformer::ColorTransformer() = default;

ColorTransformer::~ColorTransformer() = default;
