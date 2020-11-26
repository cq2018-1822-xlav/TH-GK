#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const cv::Mat& sourceImage, cv::Mat& destinationImage, short b)
{
	// Thay đổi độ sáng (Brightness): g(x, y) = f(x, y) + b
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	if (b < 0) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Input brightness must be positive.\n";
		return 0;
	}
	if (b == 0) {
		// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
		std::cout << "[LOG]: Nothing has change.\n";
		return 1;
	}
	// Chiều rộng của ảnh source
	int width = sourceImage.cols;
	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;
	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();
	// Source Image là ảnh RGB
	if (sourceChannels == 3) {
		// Khởi tạo ảnh destination với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC3, cv::Scalar(0));
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
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];
				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];
				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];
				ptrDestinationRow[0] = cv::saturate_cast<uchar>(blue + b);
				ptrDestinationRow[1] = cv::saturate_cast<uchar>(green + b);
				ptrDestinationRow[2] = cv::saturate_cast<uchar>(red + b);
			}
		}
	}
	// Source Image là ảnh GrayScale
	else if (sourceChannels == 1) {
		// Khởi tạo ảnh destination với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC1, cv::Scalar(0));
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
		// For each line
		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDestinationRow = ptrDestinationData;
			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {

				uchar gray = ptrSourceRow[0] + b;
				ptrDestinationRow[0] = gray;
			}
		}
	}
	// Lưu ảnh lại
	cv::imwrite("result_after_change_bightness.jpg", destinationImage);
	// Trả về 1: Chuyển đổi ảnh thành công
	return 1;
}

int ColorTransformer::ChangeContrast(const cv::Mat& sourceImage, cv::Mat& destinationImage, float c)
{
	// Thay đổi độ tương phản (Contrast): g(x, y) = c.f(x, y)
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	if (c < 0) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Input contrast value must be positive.\n";
		return 0;
	}
	if (c == 0) {
		// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
		std::cout << "[LOG]: Nothing has change.\n";
		return 1;
	}
	// Chiều rộng của ảnh source
	int width = sourceImage.cols;
	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;
	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();
	// Source Image là ảnh RGB
	if (sourceChannels == 3) {
		// Khởi tạo ảnh destination với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC3, cv::Scalar(0));
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
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];
				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];
				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];
				ptrDestinationRow[0] = cv::saturate_cast<uchar>(blue * c);
				ptrDestinationRow[1] = cv::saturate_cast<uchar>(green * c);
				ptrDestinationRow[2] = cv::saturate_cast<uchar>(red * c);
			}
		}
	}
	// Source Image là ảnh GrayScale
	else if (sourceChannels == 1) {
		// Khởi tạo ảnh destination với thông số height, width
		destinationImage = cv::Mat(heigth, width, CV_8UC1, cv::Scalar(0));
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
		// For each line
		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep, ptrDestinationData += destinationWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrDestinationRow = ptrDestinationData;
			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels, ptrDestinationRow += destinationChannels) {
				ptrDestinationRow[0] = cv::saturate_cast<uchar>(ptrSourceRow[0] * c);
			}
		}
	}
	// Lưu ảnh lại
	cv::imwrite("result_after_change_contrast.jpg", destinationImage);
	// Trả về 1: Chuyển đổi ảnh thành công
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
		histMatrix = cv::Mat(1, 256, CV_16UC1, cv::Scalar(0));
		// Số channels của ảnh destination
		int histMatrixChannels = histMatrix.channels();
		// Widthstep của ảnh source
		size_t sourceWidthStep = sourceImage.step[0];
		// Widthstep của ảnh destination
		size_t histMatrixWidthStep = histMatrix.step[0];
		// Con trỏ quản lý vùng nhớ data ảnh source
		uchar* ptrSourceData = sourceImage.data;
		// Con trỏ quản lý vùng nhớ data ảnh destination
		uchar* ptrHistMatrixData = histMatrix.data;
		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrHistMatrixRow = ptrHistMatrixData;

			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels) {

				uchar gray = ptrSourceRow[0];
				*(ptrHistMatrixData + gray) += 1;
			}
		}
		// Lưu ảnh xuống đĩa
		cv::imwrite("result_histogram_matrix_gray_scale.jpg", histMatrix);
		// Throw message
		std::cout << "Success: Calculated the histogram of image.\n";
		// Trả về 1
		return 1;
	}

	// Nếu ảnh đầu vào là ảnh RGB
	else if (sourceImage.channels() == 3) {
		// Khởi tạo ảnh histogram matrix với thông số height = 3, width = 256
		histMatrix = cv::Mat(3, 256, CV_16UC1, cv::Scalar(0));
		// Số channels của ảnh destination
		int histMatrixChannels = histMatrix.channels();
		// Widthstep của ảnh source
		size_t sourceWidthStep = sourceImage.step[0];
		// Widthstep của ảnh destination
		size_t histMatrixWidthStep = histMatrix.step[0];
		// Con trỏ quản lý vùng nhớ data ảnh source
		uchar* ptrSourceData = sourceImage.data;
		// Con trỏ quản lý vùng nhớ data ảnh destination
		uchar* ptrHistMatrixData = histMatrix.data;
		uchar* blueHistMatrixData = ptrHistMatrixData;
		uchar* greenHistMatrixData = ptrHistMatrixData + histMatrixWidthStep;
		uchar* redHistMatrixData = ptrHistMatrixData + histMatrixWidthStep + histMatrixWidthStep;
		for (int y = 0; y < heigth; y++, ptrSourceData += sourceWidthStep) {
			uchar* ptrSourceRow = ptrSourceData;
			uchar* ptrHistMatrixRow = ptrHistMatrixData;
			for (int x = 0; x < width; x++, ptrSourceRow += sourceChannels) {
				// Lấy giá trị kênh màu Blue của ảnh source
				uchar blue = ptrSourceRow[0];
				// Lấy giá trị kênh màu Green của ảnh source
				uchar green = ptrSourceRow[1];
				// Lấy giá trị kênh màu Red của ảnh source
				uchar red = ptrSourceRow[2];
				// Blue
				*(blueHistMatrixData + blue) += 1;
				// Green
				*(greenHistMatrixData + green) += 1;
				// Red
				*(redHistMatrixData + red) += 1;
			}
		}
		cv::imwrite("result_histogram_matrix_rgb.jpg", histMatrix);
		std::cout << "Success: Calculated the histogram of image.\n";
		return 1;
	}
	std::cout << "Exception: Can not calculate the histogram of image.\n";
	return 0;
}

int ColorTransformer::HistogramEqualization(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// TODO: Implement with your code
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
		std::cout << "Gray";
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
