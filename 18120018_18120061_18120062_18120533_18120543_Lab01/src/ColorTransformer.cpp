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
	return 0;
}

int ColorTransformer::DrawHistogram(const cv::Mat& histMatrix, cv::Mat& histImage)
{
	return 0;
}

float ColorTransformer::CompareImage(const cv::Mat& image1, cv::Mat& image2)
{
	return 0.0f;
}

ColorTransformer::ColorTransformer()
{
}

ColorTransformer::~ColorTransformer()
{
}
