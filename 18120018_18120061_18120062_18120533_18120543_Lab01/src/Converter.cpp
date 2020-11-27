#include "Converter.h"

/*
Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::RGB2GrayScale(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}

	// Check the source image is RGB type?
	if (sourceImage.type() != CV_8UC3)
	{
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with type of input image.\n";
		return 1; // Trả về 1
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Khởi tạo ảnh destination là ảnh grayscale với thông số height, width
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

			// Tính toán giá trị độ xám: // 0.2989 R + 0.5870 G + 0.1141 B
			uchar grayValue = (uchar)(0.1141 * blue + 0.5870 * green + 0.2989 * red);

			// Gán giá trị độ xám vừa tính được vào kênh vào của ảnh destination
			ptrDestinationRow[0] = grayValue;
		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_rgb_to_grayscale.jpg", destinationImage);


	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: converted image from RGB to GrayScale.\n";
	return 0;
}

/*
Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::GrayScale2RGB(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}

	// Check the source image is Gray Scale type?
	if (sourceImage.type() != CV_8UC1) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with type of input image.\n";
		return 0; // Trả về 1
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Khởi tạo ảnh destination là ảnh RGB với thông số height, width
	destinationImage = cv::Mat(sourceImage.rows, sourceImage.cols, CV_8UC3, cv::Scalar(0));

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
			// Lấy giá trị kênh màu gray của ảnh source
			uchar gray = ptrSourceRow[0];
			// Gán giá trị độ xám vừa lấy được vào kênh màu Blue của ảnh destination
			ptrDestinationRow[0] = gray;
			// Gán giá trị độ xám vừa lấy được vào kênh màu Green của ảnh destination
			ptrDestinationRow[1] = gray;
			// Gán giá trị độ xám vừa lấy được vào kênh màu Red của ảnh destination
			ptrDestinationRow[2] = gray;
		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_grayscale_to_rgb.jpg", destinationImage);

	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: converted image from GrayScale to RGB.\n";
	return 0;
}

/*
Hàm chuyển đổi không gian màu của ảnh từ RGB sang HSV
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::RGB2HSV(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1; // Trả về 1
	}

	// Check the source image is RGB type?
	if (sourceImage.type() != CV_8UC3)
	{
		// Chuyển đổi ảnh thất bại: in ra màn hình console tin nhắn
		std::cout << "[EXCEPTION] Error with type of input image.\n";
		return 1; // Trả về 1
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Khởi tạo ảnh destination là ảnh HSV với thông số height, width
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
			float blueValue = 1.0 * ptrSourceRow[0] / 255;
			float greenValue = 1.0 * ptrSourceRow[1] / 255;
			float redValue = 1.0 * ptrSourceRow[2] / 255;

			float hue, saturation, value;

			// Xác định giá trị màu lớn nhất trong ba màu
			float maxColorValue = fmaxf(fmaxf(redValue, greenValue), blueValue);

			// Xác định giá trị màu nhỏ nhất trong ba màu
			float minColorValue = fminf(fminf(redValue, greenValue), blueValue);

			// Xác định giá trị chênh lệch giữa màu lớn nhất và màu bé nhất trong ba màu = delta
			float delta = maxColorValue - minColorValue;

			// Tính value = độ sáng của màu sắc sẽ bằng giá trị max của 3 kênh màu
			value = maxColorValue;

			// Tính hue và saturation
			if (maxColorValue == 0.0f) {
				saturation = 0.0f;
				hue = 0.0f;
			}
			else
			{
				if (delta == 0.0f) {
					saturation = 0.0f;
					hue = 0.0f;
				}
				else {
					saturation = (delta) / maxColorValue;
					if (maxColorValue == redValue) {
						hue = 60 * (((greenValue - blueValue) / (delta)) + 0.0f);
					}
					else
						if (maxColorValue == greenValue) {
							hue = 60 * (((blueValue - redValue) / (delta)) + 2.0f);
						}
						else {
							hue = 60 * (((redValue - greenValue) / (delta)) + 4.0f);
						}
				}
			}

			// Nếu hue < 0
			if (hue < 0) hue += 360.0f;

			// Gán giá trị [hue, saturation, value] vào ma trận
			// Gán giá trị hue
			ptrDestinationRow[0] = cv::saturate_cast<uchar>(hue / 2);
			ptrDestinationRow[1] = cv::saturate_cast<uchar>(saturation * 255);
			ptrDestinationRow[2] = cv::saturate_cast<uchar>(value * 255);
		}
	}

	// Lưu ảnh xuống đĩa
	cv::imwrite("result_rgb_to_hsv.jpg", destinationImage);

	// Chuyển đổi ảnh thành công: in ra màn hình console tin nhắn
	std::cout << "Sucess: converted image from RGB to HSV.\n";
	return 0;
}

/*
Hàm chuyển đổi không gian màu của ảnh từ HSV sang RGB
	sourceImage: ảnh input
	destinationImage: ảnh output
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input,...)
*/
int Converter::HSV2RGB(const cv::Mat& sourceImage, cv::Mat& destinationImage)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1;
	}

	// Check the source image is HSV type?
	if (sourceImage.type() != CV_8UC3)
	{
		std::cout << "[EXCEPTION] Error with type of input image.\n";
		return 1;
	}

	// Chiều rộng của ảnh source
	int width = sourceImage.cols;

	// Chiều cao của ảnh source
	int heigth = sourceImage.rows;

	// Số channels của ảnh source
	int sourceChannels = sourceImage.channels();

	// Khởi tạo ảnh destination là ảnh HSV với thông số height, width
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

			// Hue = vùng màu, nhận giá trị từ [0 - 360] - tính theo độ
			float hue_value = ptrSourceRow[0] * 2.0f;

			// Saturation = độ bão hòa màu, nhận giá trị từ [0.0 - 1.0]
			float saturation_value = ptrSourceRow[1] / 255.0f;

			// Value = giá trị hay độ sáng của màu sắc, nhận giá trị từ [0.0 - 1.0]
			float value_value = ptrSourceRow[2] / 255.0f;

			float chroma = value_value * saturation_value;

			float hprime = cv::saturate_cast<float>(1.0 * hue_value / 60);

			float X = cv::saturate_cast<float>(chroma * (1 - fabs(fmod(hprime, 2) - 1)));

			float m = value_value - chroma;

			float redValue = 0.0f;
			float greenValue = 0.0f;
			float blueValue = 0.0f;

			// HSV Transform normal
			0 <= hprime && hprime < 1 ?
				redValue = chroma, greenValue = X, blueValue = 0 :
				1 <= hprime && hprime < 2 ?
				redValue = X, greenValue = chroma, blueValue = 0 :
				2 <= hprime && hprime < 3 ?
				redValue = 0, greenValue = chroma, blueValue = X :
				3 <= hprime && hprime < 4 ?
				redValue = 0, greenValue = X, blueValue = chroma :
				4 <= hprime && hprime < 5 ?
				redValue = X, greenValue = 0, blueValue = chroma :
				5 <= hprime && hprime < 6 ?
				redValue = chroma, greenValue = 0, blueValue = X :
				redValue = 0, greenValue = 0, blueValue = 0;

			redValue += m;
			blueValue += m;
			greenValue += m;

			// HSV Transform Alter
			float k_red = cv::saturate_cast<float>(fmod((5 + 1.0 * hue_value / 60), 6));
			float k_green = cv::saturate_cast<float>(fmod((3 + 1.0 * hue_value / 60), 6));
			float k_blue = cv::saturate_cast<float>(fmod((1 + 1.0 * hue_value / 60), 6));

			float f_red = cv::saturate_cast<float>(value_value - cv::saturate_cast<float>(value_value * saturation_value) * fmax(0, fmin(fmin(k_red, 4 - k_red), 1)));
			float f_green = cv::saturate_cast<float>(value_value - cv::saturate_cast<float>(value_value * saturation_value) * fmax(0, fmin(fmin(k_green, 4 - k_green), 1)));
			float f_blue = cv::saturate_cast<float>(value_value - cv::saturate_cast<float>(value_value * saturation_value) * fmax(0, fmin(fmin(k_blue, 4 - k_blue), 1)));

			// Gán giá trị 3 kênh màu của ảnh đích 
			ptrDestinationRow[0] = cv::saturate_cast<uchar>(f_blue * 255.0f);
			ptrDestinationRow[1] = cv::saturate_cast<uchar>(f_green * 255.0f);
			ptrDestinationRow[2] = cv::saturate_cast<uchar>(f_red * 255.0f);
		}
	}

	cv::imwrite("result_hsv_to_rgb.jpg", destinationImage);

	// Chuyển đổi ảnh thành công
	std::cout << "Sucess: converted image from HSV to RGB.\n";
	return 1;
}

/*
Hàm chuyển đổi không gian màu của ảnh
	sourceImage: ảnh input
	destinationImage: ảnh output cùng kích thước, cùng loại với ảnh input
type: loại chuyển đổi
	0,1: chuyển từ RGB sang GrayScale và ngược lại
	2,3: chuyển từ RGB sang HSV và ngược lại
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input hay type không chính xác,...)
*/
int Converter::Convert(cv::Mat& sourceImage, cv::Mat& destinationImage, int type)
{
	// Kiểm trả ảnh đầu vào
	if (!sourceImage.data) {
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 1;
	}

	// Switch để chọn lựa type chuyển đổi
	switch (type)
	{
	case 0: return this->RGB2GrayScale(sourceImage, destinationImage);

	case 1: return this->GrayScale2RGB(sourceImage, destinationImage);

	case 2: return this->RGB2HSV(sourceImage, destinationImage);

	case 3: return this->HSV2RGB(sourceImage, destinationImage);

	default:
		// Exception: Type không hỗ trợ
		std::cerr << "[EXCEPTION] Type is not supported.\n";
		return 1;
	}

	// Chuyển đổi ảnh thành công
	return 0;
}


/*
Hàm chuyển đổi không gian màu của ảnh
	sourceImage: ảnh input
	destinationImage: ảnh output cùng kích thước, cùng loại với ảnh input
type: loại chuyển đổi
	0,1: chuyển từ RGB sang GrayScale và ngược lại
	2,3: chuyển từ RGB sang HSV và ngược lại
Hàm trả về
	0: nếu chuyển thành công
	1: nếu chuyển thất bại (không đọc được ảnh input hay type không chính xác,...)
*/
int Converter::Convert(IplImage* sourceImage, IplImage* destinationImage, int type)
{
	cv::Mat matSourceImage = cv::cvarrToMat(sourceImage);
	cv::Mat matDestinationImage = cv::cvarrToMat(destinationImage);

	/*
	Mat cvarrToMat(const CvArr* arr, bool copyData=false, bool allowND=true, int coiMode=0 )
	Parameters:
	•arr — input CvMat, IplImage , or CvMatND.
	•copyData — when false (default value), no data is copied and only the new header is created, in this case, the original array should not be deallocated while the new matrix header is used; if the parameter is true, all the data is copied and you may deallocate the original array right after the conversion.
	•allowND — when true (default value), CvMatND is converted to 2-dimensional Mat, if it is possible (see the discussion below); if it is not possible, or when the parameter is false, the function will report an error.
	•coiMode — parameter specifying how the IplImage COI (when set) is handled.
	◦If coiMode=0 and COI is set, the function reports an error.
	◦If coiMode=1 , the function never reports an error. Instead, it returns the header to the whole original image and you will have to check and process COI manually. See extractImageCOI() .
	Normally, the function is used to convert an old-style 2D array ( CvMat or IplImage ) to Mat.
	However, the function can also take CvMatND as an input and create Mat() for it, if it is possible.
	And, for CvMatND A , it is possible if and only if A.dim[i].size*A.dim.step[i] == A.dim.step[i-1] for all or for all but one i, 0 < i < A.dims .
	That is, the matrix data should be continuous or it should be representable as a sequence of continuous matrices. By using this function in this way, you can process CvMatND using an arbitrary element-wise function.
	The last parameter, coiMode , specifies how to deal with an image with COI set. By default, it is 0 and the function reports an error when an image with COI comes in. And coiMode=1 means that no error is signalled.
	You have to check COI presence and handle it manually. The modern structures, such as Mat and MatND do not support COI natively.
	To process an individual channel of a new-style array, you need either to organize a loop over the array (for example, using matrix iterators) where the channel of interest will be processed, or extract the COI using mixChannels() (for new-style arrays) or extractImageCOI() (for old-style arrays), process this individual channel, and insert it back to the output array if needed (using mixChannels() or insertImageCOI() , respectively).
	*/

	// Kiểm trả ảnh đầu vào
	if (!matSourceImage.data) {
		std::cout << "Exception: Error with input image.\n";
		return 1;
	}

	// Switch để chọn lựa type chuyển đổi
	switch (type)
	{
	case 0: return this->RGB2GrayScale(matSourceImage, matDestinationImage);

	case 1: return this->GrayScale2RGB(matSourceImage, matDestinationImage);

	case 2: return this->RGB2HSV(matSourceImage, matDestinationImage);

	case 3: return this->HSV2RGB(matSourceImage, matDestinationImage);

	default:
		// Exception: Type không hỗ trợ
		std::cerr << "[EXCEPTION] Type is not supported.\n";
		return 1;
	}

	// Chuyển đổi ảnh thành công
	return 0;
}

// Constructor
Converter::Converter() = default;

// Destructor
Converter::~Converter() = default;