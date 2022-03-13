#include <opencv2/opencv.hpp>
#include <iostream>

int main(){
    cv::VideoCapture cap(0);
    cv::Mat frame;
    while (cap.read(frame)){
        cv::imwrite("current.jpg", frame);
        break;
    }
    return 0;
}
