#include <stdio.h>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: luma_calc.exe path_to_video_input path_to_image_output\nexample: luma_calc.exe mask.mov output.png");
		return 0;
	}

    VideoCapture video_capture;

    video_capture.open(argv[1]);
	int width = video_capture.get(cv::CAP_PROP_FRAME_WIDTH);
	int height = video_capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	int frame_count = video_capture.get(cv::CAP_PROP_FRAME_COUNT);

	printf("%i %i %i\n", width, height, frame_count);
	
	Mat video;
	Mat image = Mat::zeros(cv::Size(1920, 1080), CV_8UC1);

	double value_step = 1.0 /(double)frame_count;
	printf("%f\n", value_step);

	for (int i = 0; i < frame_count; i++) {
		printf(".");
		video_capture >> video;
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				if ((video.data[r * width * 3 + c * 3] > 0 || video.data[r * width * 3 + c * 3 + 1] > 0 || video.data[r * width * 3 + c * 3 + 2] > 0) && image.data[r * width + c] == 0) {
					image.data[r * width + c] = (unsigned char)floorf(((double)i * value_step) * 255.0);
				}
			}
		}
	}
	printf("\n");

	imwrite(argv[2], image);

	return 0;
}