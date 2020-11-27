#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const cv::Mat& sourceImage, cv::Mat& destinationImage, short b)
{
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
