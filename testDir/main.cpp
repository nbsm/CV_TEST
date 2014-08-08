#include <opencv2/opencv.hpp>
#include <opencv2/opencv_lib.hpp>

using namespace cv;

#define _REC

int main(int argc, char* argv[])
{
	// 基本画像データ
	Mat src = Mat::zeros(480, 640, CV_8UC1);
	Mat tmp;

	// 録画用リソース確保
#ifdef _REC
	VideoWriter vw = VideoWriter("./test.avi", CV_FOURCC('X','V','I','D'), 30, Size(640, 480), false);
#endif	/* _REC */

	char time[256];
	int hh=0, mm=0, ss=0, frame=0;
	string wname = "window";
	namedWindow(wname);
	moveWindow(wname, 61, 0);

	while (1) {
		src.copyTo(tmp);

		sprintf_s(time, 256, "%02d:%02d:%02d.%02d", hh, mm, ss, frame);

		putText(tmp, time, Point(100, 100), FONT_HERSHEY_SIMPLEX, 1.5, Scalar::all(200), 1, CV_AA);

		if (29 < ++frame) {
			frame = 0;
			if (59 < ++ss) {
				ss = 0;
				if (59 < ++mm) {
					mm = 0;
					++hh;
				}
			}
		}
		// 以下で録画秒数指定
		if (0 < mm)
			break;

#ifdef _REC
		vw << tmp;
#endif	/* _REC */

		imshow(wname, tmp);
		waitKey(30);
	}
	destroyAllWindows();
#ifdef _REC
	vw.release();
#endif	/* _REC */
	tmp.release();

	return 0;
}
