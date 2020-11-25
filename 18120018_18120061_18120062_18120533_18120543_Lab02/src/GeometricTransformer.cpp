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
	return 0;
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
	return 0;
}

NearestNeighborInterpolate::NearestNeighborInterpolate() = default;
NearestNeighborInterpolate::~NearestNeighborInterpolate() = default;


/*
Cài đặt lớp biểu diễn pháp biến đổi affine
*/
void AffineTransform::Translate(float dx, float dy) { // xây dựng matrix transform cho phép tịnh tiến theo vector (dx,dy)

}

void AffineTransform::Rotate(float angle) { // xây dựng matrix transform cho phép xoay 1 góc angle

}

void AffineTransform::Scale(float sx, float sy) { // xây dựng matrix transform cho phép tỉ lệ theo hệ số 		

}

void AffineTransform::TransformPoint(float& x, float& y) { // transform 1 điểm (x,y) theo matrix transform đã có

}

AffineTransform::AffineTransform() {

}

AffineTransform::~AffineTransform() {

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
	return 1;
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
	const cv::Mat & srcImage, cv::Mat & dstImage, float angle, PixelInterpolate * interpolator) {
	return 1;
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
	return 1;
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
	return 1;
}

GeometricTransformer::GeometricTransformer() = default;
GeometricTransformer::~GeometricTransformer() = default;