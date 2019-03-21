#include "PreProcess.h"

//global variables

int gaussian_ksize;
int dilatation_ksize = 2;

PreProcess::PreProcess()
{
}

PreProcess::~PreProcess()
{
}

Mat PreProcess::seuillage()
{
	Mat greyscale;
	Mat result;

	cvtColor(inputImage, this->outputImage, COLOR_BGR2GRAY);
	Mat gradx;
	Mat grady;

	Sobel(outputImage, gradx, CV_32F, 1,0,-1);
	Sobel(outputImage, grady, CV_32F, 0,1,-1);
	Mat gradient_tmp;
	Mat gradient;


	subtract(gradx, grady, gradient_tmp);

	convertScaleAbs(gradient_tmp, gradient);

	int size= 8;
	if (size % 2 == 0)
		size++;

	GaussianBlur(gradient, finalImage, Size(size, size), 0);

	Mat result_tmp;
	threshold(finalImage, result_tmp, 230, 255, THRESH_BINARY);
	

	Mat kernel;
	getStructuringElement(MORPH_RECT, Size(21,21), kernel);
	morphologyEx(result_tmp, result, MORPH_CLOSE, kernel );

	


	return result;

}

bool PreProcess::open(string filePath)
{
	inputImage = imread(filePath, IMREAD_COLOR);
	//cvtColor(tmp, inputImage, CV_RGB2GRAY);
	if (inputImage.empty())
		return false;
	finalImage = inputImage.clone();

	inputFilePath = filePath;

	return true;
}

void PreProcess::gaussian(int size, void *data)
{

	Mat outputImage = ((PreProcess *)data)->outputImage.clone();
	Mat tmp2 = outputImage.clone();
	if (size % 2 == 0)
		size++;
	GaussianBlur(outputImage, ((PreProcess *)data)->finalImage, Size(size, size), 0);
	imshow("Input Image", ((PreProcess *)data)->finalImage);
}

void PreProcess::dilatation(int size, void *data)
{

	Mat inputImage = ((PreProcess *)data)->inputImage.clone();
	Mat outputImage = ((PreProcess *)data)->outputImage;
	if (size < 2)
		size = 2;

	Mat element = getStructuringElement(MORPH_RECT,
										Size(size, 1));

	erode(inputImage, outputImage, element);
	((PreProcess *)data)->outputImage = outputImage;

	imshow("Input Image", outputImage);
}

void PreProcess::process()
{
	namedWindow("Input Image", WINDOW_AUTOSIZE);

	dilatation(24, this);
	gaussian(24, this);

	//createTrackbar("Dilatation","Input Image", &gaussian_ksize,  50, dilatation, this);
	//createTrackbar("Gaussien", "Input Image", &gaussian_ksize, 100, gaussian, this);

	//setMouseCallback("Input Image",save, this);
	imshow("Input Image", inputImage);
}

void PreProcess::save(int event, int x, int y, int flags, void *userdata)
{
}

Mat PreProcess::getFinalImage()
{
	return this->finalImage.clone();
}

Mat PreProcess::getInputImage()
{
	return this->inputImage.clone();
}
