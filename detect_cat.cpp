
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/all_layers.hpp>
#include <utility>
#include <cstdlib>

using namespace std;
using namespace cv;
using namespace dnn;

double probability(const Mat& output, int &label){
    Mat softmax;
    exp(output.reshape(1,1), softmax);
    softmax /= sum(softmax)[0];

    Point classIdPoint;

    double final_prob;

    minMaxLoc(softmax, nullptr, &final_prob, nullptr, &classIdPoint);

    final_prob *= 100;
    label = classIdPoint.x;
    return final_prob;
}

Mat model(const Mat& frame){
    auto model = readNet("/home/pi/Programs/Molly_rasp/data/DenseNet_121.prototxt",
                         "/home/pi/Programs/Molly_rasp/data/DenseNet_121.caffemodel",
                         "Caffe");
    Mat blob = blobFromImage(frame, 0.01, Size(224, 224), Scalar(104, 117, 123));
    model.setInput(blob);
    return model.forward();
}

vector<string> file_conv(string path){
    vector<string> class_names;
    ifstream ifs(string(std::move(path)).c_str());
    string line;
    while (getline(ifs, line)){
        class_names.push_back(line);
    }
    return class_names;
}

bool class_checker(const char *class_name, const vector<string>& names){
    for (const auto& name : names){
        if (name  == class_name){
            return true;
        }
    }
    return false;
}

void hejhopp(){
    vector<string> class_names = file_conv("/home/pi/Programs/Molly_rasp/data/classification_classes_ILSVRC2012.txt");
    vector<string> cat_names = file_conv("/home/pi/Programs/Molly_rasp/data/cat.txt");

    VideoCapture capture(0);
    Mat frame;
    int label_id;
    double prob;

    while (capture.read(frame)){
        Mat dnn_output = model(frame);
        prob = probability(dnn_output, label_id);

        if (class_checker(class_names[label_id].c_str(), cat_names)){ 
	    imwrite("Molly_found.jpg", frame);
	    break;
        }
	waitKey(40);
    }
}

int main() {
    system("clear");
    cout << "Letar efter molly..." << endl;
    hejhopp();
    return 0;
}
