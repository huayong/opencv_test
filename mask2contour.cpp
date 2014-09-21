#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

char* filename = "horse.png";

Mat load_image = imread(filename, 0);  //the second parameter specifys that the image is 

Mat ori_image = load_image.clone();

const char *oriWindowName = "oriWindow";
const char *conWindowName = "conWindow";

void getPoint(){

	int sample = 5;

	ofstream ofile("horse.poly");

	vector<vector<Point>> contours;


	findContours(ori_image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); 
	//findContours(ori_image, contours, CV_CHAIN_APPROX_NONE, CV_CHAIN_APPROX_NONE);


	Mat result(ori_image.size(), CV_8U, Scalar(0));
	drawContours(result, contours, -1, Scalar(255), 1);
	imwrite("result.jpg", result);  //the contour image
	imshow(conWindowName, result);

	//save the coordinates of points of the contour to file
	int count = 0;
	for (int i = 0; i<contours.size(); i++)
	{
		ofile << i + 1 << endl;

		vector<Point> pp = contours[i];
		if (i == 0)
			ofile << contours.size() / sample << " out" << endl;
		else
			ofile << contours.size() / sample << " in" << endl;


		for (int j = 0; j < pp.size(); j++)
		{
			Point ppp = pp[j];
			//cout << count << "\t" << setprecision(21) << (double)ppp.x / ori_image.cols << "\t" << (double)ppp.y / ori_image.rows << "" << endl;
			if (count % sample == 0)
				//cout << count << "\t" << setprecision(21) << (double)ppp.x / ori_image.cols << "\t" << 1 - (double)ppp.y / ori_image.rows << "" << endl;
				//ofile << count / sample << "\t" << setprecision(21) << (double)ppp.x / ori_image.cols << "\t" << 1 - (double)ppp.y / ori_image.rows << "" << endl;
				//ofile << count / sample << "\t" << setprecision(21) << (double)ppp.x << "\t" << ori_image.rows - (double)ppp.y << "" << endl;
				ofile << setprecision(21) << (double)ppp.x << " " << ori_image.rows - (double)ppp.y << endl;
			count++;
		}
	}

	for (int i = 1; i <= count; i++){
		ofile << i << " ";
	}
	ofile << endl;

	//cout << count / sample << endl;
	ofile.close();
}

int main(int argc, char** argv)
{
	if (ori_image.empty())
	{
		return 0;
	}
	namedWindow(oriWindowName, WINDOW_AUTOSIZE);// Create a window for display.
	imshow(oriWindowName, ori_image);

	getPoint();

	namedWindow(conWindowName, WINDOW_AUTOSIZE);

	waitKey(0);

	return 0;
}
