#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <cstdlib>

int main (int argc, char *argv[]) {
	
	//OpenCV video capture object
	cv::VideoCapture camera;

	//OpenCV image object
	cv::Mat image;

	//Camera id		Associated to a device number in /dev/videoX
	int cam_id;

	//check user args
	switch (argc) {
		
		case 1:		//No argument provided, so try /dev/video0
			
			cam_id = 0;
			break;

		case 2:		//An argument is provided. Get it and set cam_id

			cam_id = atoi(argv[1]);
			break;

		default:
			
			std::cout<<"Invalid number of arguments. Call program as: wecam_capture [video_device_id]."<<std::endl;
			std::cout<<"EXIT program."<<std::endl;
			break;

	}

	//Advertising to the user
	std::cout<<"Opening video device "<<cam_id<<"..."<<std::endl;

	//Open the video stream and make sure it's opened
	if (!camera.open(cam_id)) {
		
		std::cout<<"Error opening the camera. May be an invalid device id. EXIT program."<<std::endl;
		return -1;

	}

	//Capture loop. Out when user press a key
	while (1) {
		
		//Read image and check it
		if (!camera.read(image)) {

			std::cout<<"No frame"<<std::endl;
			cv::waitKey();

		}

		int central_pixel_y = image.rows/2;
		int central_pixel_x = image.cols/2;

		//Get pixel 3 channel values
		cv::Vec3b intensity = image.at<cv::Vec3b>(central_pixel_y, central_pixel_x);
		int blue = intensity.val[0];
		int green = intensity.val[1];
		int red = intensity.val[2];

		//Print image dimensions
		std::cout<<"Image size is: "<<image.rows<<"x"<<image.cols<<std::endl;

		//Print central pixel coordinates
		std::cout<<"The central pixel is at: "<<central_pixel_y<<"x"<<central_pixel_x<<std::endl;

		//Print central pixel 3 original channel values
		std::cout<<"And its original 3 channel values are: "<<std::endl;
		std::cout<<"Blue: "<<blue<<" Green: "<<green<<" Red: "<<red<<std::endl;

		//Set black to the central pixel and its neighbors
		for (int y = central_pixel_y - 4; y <= central_pixel_y + 4; y ++) {
    
			for (int x = central_pixel_x - 4; x <= central_pixel_x + 4; x ++) {
        
				image.at<cv::Vec3b>(y, x) = 0;
				
    		}
		}

		//Show image in a window
		cv::imshow("Output Window", image);

		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues
		if (cv::waitKey(1) >= 0) break;

	}

}
