#include "GeometricTransformer.h"

/*
 Lớp base dùng để nội suy màu của 1 pixel
*/
PixelInterpolate::PixelInterpolate() = default;
PixelInterpolate::~PixelInterpolate() = default;

/*
Cài đặt cho lớp BilinearInterpolate - Lớp nội suy màu theo phương pháp song tuyến tính
*/

/*
Hàm tính giá trị màu của ảnh kết quả từ nội suy màu trong ảnh gốc
Tham số
	- (tx,ty): tọa độ thực của ảnh gốc sau khi thực hiện phép biến đổi affine
	- pSrc: con trỏ ảnh gốc
	- srcWidthStep: widthstep của ảnh gốc
	- nChannels: số kênh màu của ảnh gốc
Trả về
	- Giá trị màu được nội suy
*/
uchar BilinearInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels) {
	// f'(x', y') = (1 - a)(1 - b)f(l,k) + a(1 - b)f(l+1,k) + b(1 - a)f(l, k + 1) + abf(l + 1, k + 1)

	// l = round(x)
	int l = (int)(round(tx));

	// k = round(y)
	int k = (int)(round(ty));

	// a = x - l
	float a = tx - l;

	// b = y - k
	float b = ty - k;

	// Tính f(l, k)
	int flk = (pSrc + (long long)srcWidthStep * l + (long long)nChannels * k)[0];

	// Tính f(l + 1, k)
	int fl1k = (pSrc + (long long)srcWidthStep * ((long long)l + 1) + (long long)nChannels * k)[0];

	// Tính f(l, k + 1)
	int flk1 = (pSrc + (long long)srcWidthStep * l + (long long)nChannels * ((long long)k + 1))[0];

	// Tính f(l + 1, k + 1)
	int fl1k1 = (pSrc + (long long)srcWidthStep * ((long long)l + 1) + (long long)nChannels * ((long long)k + 1))[0];

	return cv::saturate_cast<uchar>(round((1 - a) * (1 - b) * flk + a * (1 - b) * fl1k + (1 - a) * b * flk1 + a * b * fl1k1));
}

BilinearInterpolate::BilinearInterpolate() = default;
BilinearInterpolate::~BilinearInterpolate() = default;


/*
Cài đặt cho lớp NearestNeighborInterpolate - Lớp nội suy màu theo phương pháp láng giềng gần nhất
*/

/*
Hàm tính giá trị màu của ảnh kết quả từ nội suy màu trong ảnh gốc
Tham số
	- (tx,ty): tọa độ thực của ảnh gốc sau khi thực hiện phép biến đổi affine
	- pSrc: con trỏ ảnh gốc
	- srcWidthStep: widthstep của ảnh gốc
	- nChannels: số kênh màu của ảnh gốc
Trả về
	- Giá trị màu được nội suy
*/
uchar NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar * pSrc, int srcWidthStep, int nChannels) {
	int l = (int)round(tx);
	int k = (int)round(ty);
	return cv::saturate_cast<uchar>((pSrc + (long long)srcWidthStep * l + (long long)nChannels * k)[0]);
}

NearestNeighborInterpolate::NearestNeighborInterpolate() = default;
NearestNeighborInterpolate::~NearestNeighborInterpolate() = default;


cv::Mat AffineTransform::getMatrixTransform()
{
	return (this->_matrixTransform);
}

void AffineTransform::setMatrixTransform(cv::Mat matrixTransform)
{
	this->_matrixTransform = matrixTransform;
}

/*
Cài đặt lớp biểu diễn pháp biến đổi affine
*/
void AffineTransform::Translate(float dx, float dy) { // xây dựng matrix transform cho phép tịnh tiến theo vector (dx,dy)
	float TranslateMatrix[3][3] = { {1, 0, dx} ,{0, 1, dy}, {0, 0, 1} };
	cv::Mat translateMat = cv::Mat(3, 3, CV_32FC1, TranslateMatrix);
	this->_matrixTransform = translateMat * this->_matrixTransform;
}

void AffineTransform::Rotate(float angle) { // xây dựng matrix transform cho phép xoay 1 góc angle
	float sin_alpha = sin(angle * M_PI / 180);
	float cos_alpha = cos(angle * M_PI / 180);

	float RotateMatrix[3][3] = { {cos_alpha, (-sin_alpha), 0}, {sin_alpha, cos_alpha, 0}, {0, 0, 1} };
	cv::Mat rotateMat = cv::Mat(3, 3, CV_32FC1, RotateMatrix);
	this->_matrixTransform = rotateMat * this->_matrixTransform;
}

void AffineTransform::Scale(float sx, float sy) { // xây dựng matrix transform cho phép tỉ lệ theo hệ số 		
	float ScaleMatrix[3][3] = { {sx, 0, 0}, {0, sy, 0}, {0, 0, 1} };
	cv::Mat scaleMat = cv::Mat(3, 3, CV_32FC1, ScaleMatrix);
	this->_matrixTransform = scaleMat * this->_matrixTransform;
}

void AffineTransform::TransformPoint(float& x, float& y) { // transform 1 điểm (x,y) theo matrix transform đã có
	float oldPointMatrix[] = { x, y, 1 };
	cv::Mat newPoint = this->_matrixTransform * cv::Mat(3, 3, CV_32FC1, oldPointMatrix);
	x = newPoint.ptr<float>(0)[0];
	y = newPoint.ptr<float>(0)[1];
}

AffineTransform::AffineTransform() {
	float matrix[3][3] = { {1, 0, 0}
							,{0, 1, 0}
							, {0, 0, 1} };
	this->_matrixTransform = cv::Mat(3, 3, CV_32FC1, matrix).clone();
}

AffineTransform::~AffineTransform() {
	this->_matrixTransform.release();
}

/*
Cài đặt lớp thực hiện phép biến đổi hình học trên ảnh
*/

/*
Hàm biến đổi ảnh theo 1 phép biến đổi affine đã có
Tham số
 - beforeImage: ảnh gốc trước khi transform
 - afterImage: ảnh sau khi thực hiện phép biến đổi affine
 - transformer: phép biến đổi affine
 - interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::Transform(
	const cv::Mat & beforeImage,
	cv::Mat & afterImage,
	AffineTransform * transformer,
	PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!beforeImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthBeforeImage = beforeImage.cols;
	// Chiều cao của ảnh source
	int heigthBeforeImage = beforeImage.rows;
	// Số channels của ảnh source
	int sourceChannels = beforeImage.channels();
	// Width step của ảnh source
	size_t sourceWidthStep = beforeImage.step[0];
	// Lấy ma trận affine
	cv::Mat matrixTransform = transformer->getMatrixTransform();
	float B[] =
	{
		0, 0, 1.0,
	};
	cv::Mat P = cv::Mat(3, 1, CV_32FC1, B);
	// Con trỏ ảnh gốc
	uchar* pSrc = beforeImage.data;
	// Chiều cao của ảnh destination
	int heightAfterImage = afterImage.rows;
	// Chiều rộng của ảnh destination
	int widthAfterImage = afterImage.cols;
	for (int i = 0; i < heightAfterImage; i++)
	{
		uchar* pData = afterImage.ptr<uchar>(i);
		for (int j = 0; j < widthAfterImage; j++)
		{
			// Đặt Px = x, Py = y với x, y là tọa độ đối với tâm (0,0) là gốc trên cùng bên trái
			P.ptr<float>(0)[0] = i * 1.0;
			P.ptr<float>(1)[0] = j * 1.0;
			// Tìm tọa độ thực trên ảnh gốc
			cv::Mat srcP = matrixTransform * P;
			// tx, ty là index thực của điểm ảnh trên ma trận ảnh gốc
			float tx = srcP.ptr<float>(0)[0];
			float ty = srcP.ptr<float>(1)[0];
			// Chỉ xét tx, ty nằm trong ảnh gốc
			if (tx >= 0 && ty >= 0 && tx < heigthBeforeImage && ty < widthBeforeImage)
			{
				for (int c = 0; c < sourceChannels; c++) {
					// Áp dụng Interpolate cho từng channel
					pData[j * sourceChannels + c] = interpolator->Interpolate(tx, ty, pSrc + c, sourceWidthStep, sourceChannels);
				}	
			}
		}
	}
	// Giải phóng ma trận P
	P.release();
	// Giải phóng ma trận biến đổi
	matrixTransform.release();
	return 1;
}


/*
Hàm xoay bảo toàn nội dung ảnh theo góc xoay cho trước
Tham số
- srcImage: ảnh input
- dstImage: ảnh sau khi thực hiện phép xoay
- angle: góc xoay (đơn vị: độ)
- interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::RotateKeepImage(
	const cv::Mat & srcImage, cv::Mat & dstImage, float angle, PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!srcImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthSourceImage = srcImage.cols;
	// Chiều cao của ảnh source
	int heigthSourceImage = srcImage.rows;
	// Số channels của ảnh source
	int sourceChannels = srcImage.channels();
	// Width step của ảnh source
	size_t sourceWidthStep = srcImage.step[0];
	// Tính chiều dài của ảnh đích
	int dstWidth = (int)(widthSourceImage * cos(angle * M_PI / 180) + heigthSourceImage * sin(angle * M_PI / 180));
	// Tính chiều rộng của ảnh đích
	int dstHeight = (int)(widthSourceImage * sin(angle * M_PI / 180) + heigthSourceImage * cos(angle * M_PI / 180));
	// Khởi tạo affine transform
	AffineTransform affineTransform;
	// Tịnh tiến điểm về gốc tọa độ
	affineTransform.Translate(dstHeight / 2 - heigthSourceImage / 2, dstWidth / 2 - widthSourceImage / 2);
	affineTransform.Translate(-dstHeight / 2, -dstWidth / 2);
	// Quay ảnh một góc angle
	affineTransform.Rotate(angle);
	// Tịnh tiến ảnh về chính giữa
	affineTransform.Translate(dstHeight / 2, dstWidth / 2);
	// Khởi tạo ma trận nghịch đảo
	cv::Mat inverseMatrix = affineTransform.getMatrixTransform().inv();
	// Set ma trận nghịch đảo vào affine transform
	affineTransform.setMatrixTransform(inverseMatrix);
	if (sourceChannels == 1) {
		dstImage = cv::Mat::zeros(dstHeight, dstWidth, CV_8UC1);
	}
	else if (sourceChannels == 3) {
		dstImage = cv::Mat::zeros(dstHeight, dstWidth, CV_8UC3);
	}
	else {
		std::cout << "[EXCEPTION]: Too many channels or unsupported this number of channels.\n";
		return 0;
	}
	// Gọi hàm Transform
	GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
	// giải phóng ma trận nghịch đảo
	inverseMatrix.release();
	// Giải phóng Affine Transform
	affineTransform.~AffineTransform();
	return 1;	// Trả về 1
}


/*
Hàm xoay không bảo toàn nội dung ảnh theo góc xoay cho trước
Tham số
- srcImage: ảnh input
- dstImage: ảnh sau khi thực hiện phép xoay
- angle: góc xoay (đơn vị: độ)
- interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::RotateUnkeepImage(
	const cv::Mat & srcImage,
	cv::Mat & dstImage,
	float angle,
	PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!srcImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthSourceImage = srcImage.cols;
	// Chiều cao của ảnh source
	int heigthSourceImage = srcImage.rows;
	// Số channels của ảnh source
	int sourceChannels = srcImage.channels();
	// Width step của ảnh source
	size_t sourceWidthStep = srcImage.step[0];
	// Khởi tạo affine transform
	AffineTransform affineTransform;
	// Tịnh tiến ảnh về gốc tọa độ
	affineTransform.Translate(-heigthSourceImage / 2, -widthSourceImage / 2);
	// Quay một gốc angle
	affineTransform.Rotate(angle);
	// Tịnh tiến ảnh trở về chính giữa
	affineTransform.Translate(heigthSourceImage / 2, widthSourceImage / 2);
	// Khởi tạo ma trận nghịch đảo
	cv::Mat inverseMatrix = affineTransform.getMatrixTransform().inv();
	// Set ma trận nghịch đảo vào affine transform
	affineTransform.setMatrixTransform(inverseMatrix);
	if (sourceChannels == 1) {
		dstImage = cv::Mat::zeros(heigthSourceImage, widthSourceImage, CV_8UC1);
	}
	else if (sourceChannels == 3) {
		dstImage = cv::Mat::zeros(heigthSourceImage, widthSourceImage, CV_8UC3);
	}
	else {
		std::cout << "[EXCEPTION]: Too many channels or unsupported this number of channels.\n";
		return 0;
	}
	// Gọi hàm Transform
	GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
	// giải phóng ma trận nghịch đảo
	inverseMatrix.release();
	// Giải phóng Affine Transform
	affineTransform.~AffineTransform();
	return 1;	// Trả về 1
}

/*
Hàm phóng to, thu nhỏ ảnh theo tỉ lệ cho trước
Tham số
- srcImage: ảnh input
- dstImage: ảnh sau khi thực hiện phép xoay
- sx, sy: tỉ lệ phóng to, thu nhỏ ảnh
- interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::Scale(
	const cv::Mat & srcImage,
	cv::Mat & dstImage,
	float sx, float sy,
	PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!srcImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthBeforeImage = srcImage.cols;
	// Chiều cao của ảnh source
	int heigthBeforeImage = srcImage.rows;
	// Số channels của ảnh source
	int sourceChannels = srcImage.channels();
	// Width step của ảnh source
	size_t sourceWidthStep = srcImage.step[0];
	// Khởi tạo Affine Transform
	AffineTransform affineTransform;
	// Tịnh tiến ảnh về gốc tọa độ
	affineTransform.Translate(-heigthBeforeImage / 2, -widthBeforeImage / 2);
	// Scale theo tỉ lệ
	affineTransform.Scale(sx, sy);
	// Tịnh tiến ảnh trở về chính giữa
	affineTransform.Translate(heigthBeforeImage / 2, widthBeforeImage / 2);
	// Khởi tạo ma trận nghịch đảo
	cv::Mat inverseMatrix = affineTransform.getMatrixTransform().inv();
	// Set ma trận nghịch đảo vào affine transform
	affineTransform.setMatrixTransform(inverseMatrix);
	// Khởi tạo ảnh kết quả
	if (sourceChannels == 1) {
		dstImage = cv::Mat::zeros(heigthBeforeImage, widthBeforeImage, CV_8UC1);
	}
	else if (sourceChannels == 3) {
		dstImage = cv::Mat::zeros(heigthBeforeImage, widthBeforeImage, CV_8UC3);
	}
	else {
		std::cout << "[EXCEPTION]: Too many channels or unsupported this number of channels.\n";
		return 0;
	}
	// Gọi hàm Transform
	GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
	// giải phóng ma trận nghịch đảo
	inverseMatrix.release();
	// Giải phóng Affine Transform
	affineTransform.~AffineTransform();
	return 1; // Nếu biến đổi thành công
}


/*
Hàm thay đổi kích thước ảnh
Tham số
- srcImage: ảnh input
- dstImage: ảnh sau khi thay đổi kích thước
- newWidth, newHeight: kích thước mới
- interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::Resize(
	const cv::Mat & srcImage,
	cv::Mat & dstImage,
	int newWidth, int newHeight,
	PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!srcImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthBeforeImage = srcImage.cols;
	// Chiều cao của ảnh source
	int heigthBeforeImage = srcImage.rows;
	// Số channels của ảnh source
	int sourceChannels = srcImage.channels();
	// Width step của ảnh source
	size_t sourceWidthStep = srcImage.step[0];
	// Khởi tạo ảnh kết quả
	if (sourceChannels == 1) { // Nếu là ảnh grayscale - 1 kênh
		dstImage = cv::Mat::zeros(newHeight, newWidth, CV_8UC1);
	}
	else if (sourceChannels == 3) {	// Nếu là ảnh màu - 3 kênh
		dstImage = cv::Mat::zeros(newHeight, newWidth, CV_8UC3);
	}
	else {	// Khác
		std::cout << "[EXCEPTION]: Too many channels or unsupported this number of channels.\n";
		return 0;
	}
	// Tính toán hệ số a
	float a = 1.0 * heigthBeforeImage / newHeight;
	// Tính toán hệ số b
	float b = 1.0 * widthBeforeImage / newWidth;
	// Khởi tạo affine transform
	AffineTransform affineTransform;
	// Khởi tạo ma trận resize
	float matrix[3][3] = { {a, 0, 0}
							,{0, b, 0}
							, {0, 0, 1} };
	// Đưa ma trận resize vào affine transform
	affineTransform.setMatrixTransform(cv::Mat(3, 3, CV_32FC1, matrix).clone());
	// Gọi hàm Transform
	GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
	// Giải phóng affine
	affineTransform.~AffineTransform();
	return 1;
}


/*
Hàm lấy đối xứng ảnh
Tham số
- srcImage: ảnh input
- dstImage: ảnh sau khi lấy đối xứng
- direction = 1 nếu lấy đối xứng theo trục ngang và direction = 0 nếu lấy đối xứng theo trục đứng
- interpolator: biến chỉ định phương pháp nội suy màu
Trả về:
 - 0: Nếu ảnh input ko tồn tại hay ko thực hiện được phép biến đổi
 - 1: Nếu biến đổi thành công
*/
int GeometricTransformer::Flip(
	const cv::Mat & srcImage,
	cv::Mat & dstImage,
	bool direction,
	PixelInterpolate * interpolator) {
	// Kiểm trả ảnh đầu vào
	if (!srcImage.data) {
		// Phát hiện lỗi: ảnh input ko tồn tại
		std::cout << "[EXCEPTION] Error with input image.\n";
		return 0; // Trả về 0
	}
	// Chiều rộng của ảnh source
	int widthBeforeImage = srcImage.cols;
	// Chiều cao của ảnh source
	int heigthBeforeImage = srcImage.rows;
	// Số channels của ảnh source
	int sourceChannels = srcImage.channels();
	size_t sourceWidthStep = srcImage.step[0];
	// Nếu là lấy đối xứng theo trục ngang Ox
	if (direction == 1) {
		// Khởi tạo Affine Transform
		AffineTransform affineTransform;
		// Khởi tạo ma trận cho affine: Ma trận cho phép flip theo trục Ox
		float matrix[3][3] = { {-1, 0, heigthBeforeImage - 1}
								,{0, 1, 0}
								, {0, 0, 1} };
		// Đưa ma trận vừa khởi tạo vào affine
		affineTransform.setMatrixTransform(cv::Mat(3, 3, CV_32FC1, matrix).clone());
		// Gọi hàm Transform
		GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
		affineTransform.~AffineTransform();
		return 1;  // Trả về 1
	}
	// Nếu là lấy đối xứng theo trục đứng Oy
	else if (direction == 0) {
		// Khởi tạo Affine Transform
		AffineTransform affineTransform;
		// Khởi tạo ma trận cho affine: Ma trận cho phép flip theo trục Oy
		float matrix[3][3] = { {1, 0, 0}
								,{0, -1, widthBeforeImage - 1}
								, {0, 0, 1} };
		// Đưa ma trận vừa khởi tạo vào affine
		affineTransform.setMatrixTransform(cv::Mat(3, 3, CV_32FC1, matrix).clone());
		// Gọi hàm Transform
		GeometricTransformer::Transform(srcImage, dstImage, &affineTransform, interpolator);
		// Giải phóng affine
		affineTransform.~AffineTransform();
		return 1;  // Trả về 1
	}
	else {
		return 0;
	}
}

GeometricTransformer::GeometricTransformer() = default;
GeometricTransformer::~GeometricTransformer() = default;