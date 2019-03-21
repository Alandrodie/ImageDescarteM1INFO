#include <iostream>
using namespace std;

#include "PreProcess.h"
#include "CodeBarreDetection.h"




int main(int argc, char** argv) {

    

    PreProcess tools;
		bool opened = tools.open(argv[1]);
		

		if (!opened)
		{
			cerr << "Error opening image" << endl;
			cout << "Usage: imageBlur <Image_Path>" << endl;
			return -1;
		}
        Mat res =  tools.seuillage();

    namedWindow("Input Image", WINDOW_AUTOSIZE);
	imshow("Input Image", res);
    imwrite("../../res/greyscale.jpg", res);

   
    









    waitKey(0);  
}
