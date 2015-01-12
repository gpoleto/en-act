//#include "it_unibz_enactmobile_EnActMain.h"
#include "it_unibz_enactmobile_EnActStart.h"
#include <fstream>
//#include <string>
#include <operations.h>
#include <android/log.h>
#include <stdlib.h>
#include <sstream>
//#include <jni.h>
//#include <eigen/Eigen/Dense>

//Meteor constest benchmark inclusions
//#include <stdio.h>
#include <omp.h>

//Mandelbrot benchmark
#include <cstdio>
#include <cstdlib>
//#include <vector>

typedef unsigned char Byte;

//Spectral norm benchmark
//#include <stdio.h>
#include <stdlib.h>
#include <cmath>
//#include <vector>
//#include <iostream>
#include <iomanip>


#include <jpeg/jpeglib.h>
#include <jpeg/jerror.h>

//#include "/Users/user/Tihomir/CPP_libs/CImg/CImg.h"
//#include "CImg.h"
//#include <OpenCV/sdk/native/jni/include/opencv2/imgproc/imgproc.hpp>
//#include <OpenCV/sdk/native/jni/include/opencv2/highgui/highgui.hpp>

//Working inclusions of OpenCV
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>

//#include <Magick++.h>

//#include <boost/gil/image.hpp>
//#include <boost/gil/typedefs.hpp>
//#include <boost/gil/extension/io/jpeg_io.hpp>
//#include <boost/gil/extension/numeric/kernel.hpp>
//#include <boost/gil/extension/numeric/convolve.hpp>


//Sometimes is needed to comment one of these namespace stmts, build, wait a while to refresh.
//Play a bit with these namesoace stmts to clear editor errors.
///// 'using namespace std' is declared in the .h////////////
//using namespace std;
//using namespace cimg_library;
//using namespace cv;
//using namespace Magick;



struct Pixel {
	int Red;
	int Green;
	int Blue;
};

JNIEXPORT jstring JNICALL Java_it_unibz_enactmobile_EnActStart_multiplyMatricesFromFile
  (JNIEnv *env, jobject obj, jstring path, jstring resultPath){

	__android_log_write(ANDROID_LOG_VERBOSE, "multiplyMatricesImage()", "Hello from multiplyMatrices()");
	const char *nativePath = env->GetStringUTFChars(path, 0);
	//char *nativeResultPath;
	const char *nativeResultPath_ch = env->GetStringUTFChars(resultPath, 0);

	//strcpy(nativeResultPath_ch, env->GetStringUTFChars(resultPath, 0));

	//__android_log_write(ANDROID_LOG_VERBOSE, "C++", nativePath);
	string matricesFile = charToStr(nativePath);
	env->ReleaseStringUTFChars(path, nativePath);
	//string matricesFile = "/storage/sdcard0/Documents/Matrices_small.txt";
	string nativeResultPath = charToStr(nativeResultPath_ch);
	env->ReleaseStringUTFChars(path, nativeResultPath_ch);
	__android_log_write(ANDROID_LOG_VERBOSE, "multiplyMatricesImage() -> resultPath", nativeResultPath.c_str());

	nativeResultPath.append("matrices_result_JNI.txt");
	string resultFile =	nativeResultPath;
	__android_log_write(ANDROID_LOG_VERBOSE, "C++", "PIZZA");
	__android_log_write(ANDROID_LOG_VERBOSE, "multiplyMatricesImage() -> resultFile", resultFile.c_str());
	//string z = "Tisho Misho, Gosho na Tosho. C+++++";
	//const char *z_char = (char*)z.c_str();

	string r = readFileAndMultiplyMatrices(matricesFile,resultFile);
	const char* res = (char*)r.c_str();

	return env->NewStringUTF(res);


}

string pixelSequences(int a[], int la, unsigned char data[], int ld) {
	string indices;
	stringstream ss;
	int j = 0;


	__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "sizeof(data): %d / sizeof(a): %d", ld, la);
	for (int i=49; i<ld; i++) {
		if (a[j] == data[i+2])
			if (a[j+1] == data[i+1])
				if(a[j+2] == data[i]){
					ss << i;

					indices.append(ss.str());
					indices.append("~");
					ss.str("");
					j+=3;
				}
	}

	return indices;
}

//static int DrawBitmap (AndroidBitmapInfo * pBitmapInfo, void * pPixels, const char * pszJpegFile)
//{
//
//	}

JNIEXPORT jstring JNICALL Java_it_unibz_enactmobile_EnActStart_filterImage
  (JNIEnv *env, jobject obj, jstring path, jstring resultPath){
	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Hello from filterImage()");

	const char *nativePath = env->GetStringUTFChars(path, 0);
	string imageFile = charToStr(nativePath);
	env->ReleaseStringUTFChars(path, nativePath);

	const char *nativeResultPath_ch = env -> GetStringUTFChars(resultPath, 0);
	string nativeResultPath = charToStr(nativeResultPath_ch);
	env -> ReleaseStringUTFChars(resultPath, nativeResultPath_ch);

	__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "|%s| || %d", imageFile.c_str(), 2057);

	bool bmp = false;
	if (bmp)
		filterBMPImage(imageFile, nativeResultPath);
	else
		filterJPGImage(imageFile, nativeResultPath);



	return env -> NewStringUTF("image");

	//GLuint *texture;

	//char *filename = "filename";
	//char *filename = nativePath;
	//char *filename = calloc(imageFile.length() + 1);
	//strcpy(filename, imageFile.c_str());

//	FILE *input = fopen(nativePath, "r");
//	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Done");
//	if (!input)
//	{
//	    //printf("Could not open input file '%s'\n", nativePath);
//		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Could not open input file");
//	    system("PAUSE");
//	    //return 1;
//	    return env -> NewStringUTF("Error!");
//	}
//
//	fseek(input, 0, SEEK_END);
//	size_t size = ftell(input);
//	rewind(input);
//
//	char *buffer = (char *) malloc(size);
//	if (!buffer)
//	{
//	    //printf("Out of memory, could not allocate %u bytes\n", size);
//		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Out of memory, could not allocate bytes");
//	    system("PAUSE");
//	    //return 1;
//	    return env -> NewStringUTF("Error!");
//	}

//	if (fread(buffer, 1, size, input) != size)
//	{
//	    //printf("Could not read from input file '%s'\n", nativePath);
//		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Could not read from input file");
//	    free(buffer);
//	    fclose(input);
//	    system("PAUSE");
//	    //return 1;
//	    return env -> NewStringUTF("Error!");
//	}
//	fclose(input);

	// we loaded the file from disk into memory now


	////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ifstream is(nativePath, ifstream::binary);
//
//	int size = 0;
//	if(is) {
//		// get length of file:
//		    is.seekg (0, is.end);
//		    size = is.tellg();
//		    is.seekg (0, is.beg);
//	}
//
//	char * buffer = new char [size];
//	is.read (buffer,size);
//
//	if (is) {
//		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "all characters read successfully.");
//	} else {
//			__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "error: only several bytes could be read");
//		is.close();
//
//		// ...buffer contains the entire file...
//
//
//	}
//
//
//	ostringstream oss;
//	for (int i = 0; i<=7; i++) {
////		oss << buffer[i];
////		string msg = oss.str();
//		__android_log_write(ANDROID_LOG_VERBOSE, "Image RGB value byte", msg.c_str());
//		if (i==3) __android_log_write(ANDROID_LOG_VERBOSE, "-------------", "-------------");
//
//	}
//
////	for (size_t i = 0; (i + 3) < size; i += 4)
////	{
//////	    if (buffer[i + 0] == 0xFF && buffer[i + 1] == 0x00 && buffer[i + 2] == 0x00 && buffer[i + 3] == 0x00)
//////	    {
//////	        printf("Pixel %i is red\n", (i / 4));
//////	    }
////		int avg = (buffer[i] + buffer[i+1] + buffer[i+2] + buffer[i+3]) / 4;
////		buffer[i] = avg;
////		buffer[i+1] = avg;
////		buffer[i+2] = avg;
////		buffer[i+3] = avg;
////	}
//
//
////!! ! ! ! ! ! !   Does not write anything on disk!! ! ! ! ! ! ! ! ! ! ! ! ! !
//	//ofstream ofs(nativeResultPath_ch);
//	ofstream outFile;
//	nativeResultPath.append("image_result_JNI.bmp");
//	outFile.open(nativeResultPath.c_str(), ios::out | ios::app | ios::binary);
//	if(!outFile)
//		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage", "Cannot open output file.");
//	for (int i=0; i<size; i++) {
//		buffer[i] = buffer[i] - 20;
//		if (buffer[i] < 0)
//			buffer[i] = 0;
//		//outFile << buffer[i];
//	}
//
//	outFile.write(buffer,size);
//	outFile.flush();
//	outFile.close();
//	//free(buffer);
//
//	delete[] buffer;
	////////////////////////////////////////////////////////////////////////////////////////////////////////



//////// For Visual Studio  ////////////
//	Bitmap *myBitmap = new Bitmap("example.jpg");
//	Color pixelColor;
//	myBitmap->GetPixel(400, 400, &pixelColor);
//	//cout<<(int)pixelColor.GetRed()<<endl;
//	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", std::to_string((int)pixelColor.GetRed()));
//
//	return env -> NewStringUTF("image");

//////////// ImageMagick++  /////////////////
//	Image image;
//
//	try {
//		image.read(imageFile);
//		image.crop(Geometry(100, 100, 100, 100));
//		string resultFilename = nativeResultPath.append("image_result_JNI.png");
//		image.write(resultFilename);
//	} catch( Exception &error_ )
//    {
//      cout << "Caught exception: " << error_.what() << endl;
//      //return 1;
//    }
//
//
//	return env -> NewStringUTF("image");

//////////// OpenCV ///////////////
//	return env->NewStringUTF("pizza");

//	const char *nativePath = env->GetStringUTFChars(path, 0);
//	string imageFile = charToStr(nativePath);
//	env->ReleaseStringUTFChars(path, nativePath);
//
//	const char *nativeResultPath_ch = env -> GetStringUTFChars(resultPath, 0);
//	string nativeResultPath = charToStr(nativeResultPath_ch);
//	env -> ReleaseStringUTFChars(resultPath, nativeResultPath_ch);
//
//	/// Declare variables
//	Mat src, dst;
//	Mat kernel;
//	Point anchor;
//	double delta;
//	int ddepth;
//	int kernel_size;
//	int c;
//	/// Load an image
//	src = imread( imageFile.c_str() );
//	if( !src.data ) {
//		__android_log_write(ANDROID_LOG_ERROR, "filterImage()", "Source file could not be open");
//	}
//	/// Create window
//	/// Initialize arguments for the filter
//	anchor = Point( -1, -1 );
//	delta = 0;
//	ddepth = -1;
//
//	kernel_size = 3 + 20;//*( ind%5 );
//	kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
//	/// Apply filter
//	filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
//
////	string resultPath = "/storage/sdcard0/Documents/";
////	vector<string> pathPieces = split_string(imageFile, "/");
////	int pathPiecesLength = pathPieces.size();
////	vector<string> filenamePieces = split_string(pathPieces.at(pathPiecesLength-1), ".");
////	int filenamePiecesLength = filenamePieces.size();
////	string inputImageFormat = filenamePieces.at(filenamePiecesLength-1);
////	string resultFilename = "";
////	for (int i=0; i<filenamePieces.size()-1; i++){
////		resultFilename.append(filenamePieces.at(i));
////	}
////	resultFilename.append("_filtered");
//
//
////	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", resultFilename.c_str());
////	resultPath.append(resultFilename);
////	resultPath.append(".");
////	resultPath.append(inputImageFormat);
////	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", resultPath.c_str());
//
//	string resultFilename = nativeResultPath.append("image_result_JNI.png");
//	__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", resultFilename.c_str());
//	imwrite(resultFilename, dst);
//	//string zii = "_)_";
//
//	string finalReplyFromJNI = "You can find the result of the multiplication here:\n";
//	finalReplyFromJNI.append(resultFilename);
//
//	return env->NewStringUTF(finalReplyFromJNI.c_str());


	//--------------------------------------
	/*
	const char *nativePath = env->GetStringUTFChars(path, 0);
	//__android_log_write(ANDROID_LOG_VERBOSE, "C++", nativePath);
	string imageFile = charToStr(nativePath);
	env->ReleaseStringUTFChars(path, nativePath);

	CImg<unsigned char> inputImage(imageFile);
	string resultPath = "/storage/sdcard0/Documents/Blurred_Image";

	vector<string> pathPieces = split_string(imageFile, ".");
	int pathPiecesLength = pathPieces.size();
	string inputImageFormat = pathPieces.at(pathPiecesLength-1);
	resultPath.append(".");
	resultPath.append(inputImageFormat);
	CImg<unsigned char> outputImage(resultPath);
	//image.blur(2.5);
	outputImage = inputImage.get_blur(2.5);


	__android_log_write(ANDROID_LOG_VERBOSE, "blurImage()", resultPath.c_str());
	const char* res = resultPath.c_str();
	string zii = "_)_";
	return env->NewStringUTF(zii.c_str());
	*/
}

void filterBMPImage(string imageFile, string nativeResultPath){

	//--------| Read file |----------
		FILE* f = fopen(imageFile.c_str(), "rb");
		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", imageFile.c_str());
		if (f == NULL)
			__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Could not open input file");
	//	unsigned char info[54];
	//	fread(info, sizeof(unsigned char), 54, f); //read the 54-byte headers
	//	//fread(info, 1, 54, f); //read the 54-byte headers
	//	__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "Alive - sizeof(unsigned char): %d", sizeof(unsigned char));
	//
	//	//extract image height and width from the header
	//	int width = *(int*)&info[18];
	//	int height = *(int*)&info[22];
	//
	//	int size = 3 * width * height; //3 bytes per pixel - 1 for Blue, 1 for Green, 1 for Red
	//	unsigned char* data = new unsigned char[size];
	//	//fread(data, sizeof(unsigned char), size, f); //read the rest of the data at once
	//	fread(data, 54, size, f); //read the rest of the data at once
		fseek(f, 0, SEEK_END);
		int size = ftell(f);
		rewind(f);

		unsigned char data[size];
		__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "size: %d / sizeof(data): %d", size, sizeof(data));
		fread(data, sizeof(unsigned char), size, f);
		fclose(f);

		//Extract image height and width from the header.
		//The width of the image is stored in 2 bytes (unsigned 16bit).
		//That's why it is dereferenced from the 18th byte to form the final number.
		//Analogously for the height
		int width = *(int*)&data[18];
		if (width < 0)
			width *= (-1);
		int height = *(int*)&data[22];
		if (height < 0)
			height *= (-1);

		__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "width from &: %d / width naked: %d", width, data[18]);

		Pixel colorMatrix[height][width];

	//	//populate colorMatrix from data[]
	//	int r,c;
	//	int i = 54; //The first RGB value in data[]. In this case is the BLUE value since they are represented as (B,G,R) tuple
	//	for (r = height-1; r >= 0; r--) {
	//		for (c = width-1; c >= 0; c--) {
	//			colorMatrix[r][c].Blue = data[i];
	//			colorMatrix[r][c].Green = data[i+1];
	//			colorMatrix[r][c].Red = data[i+2];
	//			i+=3;
	//		}
	//		i++;
	//	}



		//--------| Modify |----------------

		//The debug.bmp pixel color information written manually. The values are taken from GIMP.
		//LEAVE IT for debugging the algorithm.
		int a[] = {190, 11, 26,   6,67,255,   119,119,119,   151,181,255,   93,0,162,
				   255,255,10,    203,0,255,  255,255,255,   253,180,182,   93,0,162,
				   54,255,7,      252,124,9,  0,0,0,         255,251,200,   93,0,162,
				   35,254,255,    21,129,4,   214,214,214,   246,204,255,   93,0,162,
				   93,0,162,      93,0,162,   93,0,162,      93,0,162,      93,0,162
				};
		string indices = pixelSequences(a, sizeof(a), data, sizeof(data));
		__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "indices: %s", indices.c_str());

		//Very dumb switch between the two effects.
		//In the short future should be changed.
		if (true) { //true = black_white | false = sepia
			int r,c;
			int i = 54; //The first RGB value in data[]. In this case is the BLUE value since they are represented as (B,G,R) tuple

			for (r = height-1; r >= 0; r--) { //y
				//for (c = width-1; c >= 0; c--) {
				for (c = 0; c <= width-1; c++) { //x

					if(r == 306 && c == 304)
						__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[Original] RGB values of the pixel (304x306): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

					//===| Black & White |===| Not grayscale!!! |======
	//				int bw = (data[i] + data[i+1] + data[i+2]) / 3;
	//				data[i] = bw; //Blue
	//				data[i+1] = bw; //Green
	//				data[i+2] = bw; //Red

	//				//The coefficients defined by ITU-R BT.601 (NTSC?)
	//				int grayscale = (floor(data[i+2] * 0.299 + 0.5)) + (floor(data[i+1] * 0.587 + 0.5)) + floor(data[i] * 0.114 + 0.5);

	//				//The coefficients for GIMP-like -> NOOOT
	//				int grayscale = (floor(data[i+2] * 0.3 + 0.5)) + (floor(data[i+1] * 0.59 + 0.5)) + floor(data[i] * 0.11 + 0.5);

					//The coefficients defined by ITU-R BT.709 (newer)
					int grayscale = (floor(data[i+2] * 0.2126 + 0.5)) + (floor(data[i+1] * 0.7152 + 0.5)) + floor(data[i] * 0.0722 + 0.5);

					data[i] = grayscale;
					data[i+1] = grayscale;
					data[i+2] = grayscale;

					if(r == 306 && c == 304)
						__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[Modified] RGB values of the pixel (304x306): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

	//				//===| Make bmp RED |====
	//				//Keep for debugging the algorithm
	//				data[i] = 0;
	//				data[i+1] = 0;
	//				data[i+2] = 255;
					i+=3;
				}
				i++;
			}
		} else { //sepia
			int r,c;
			int i = 54; //The first RGB value in data[]. In this case is the BLUE value since they are represented as (B,G,R) tuple
			__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "Height: %d / Width: %d", height, width);
			int j = 54;
			__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "First pixel in data[]: [R]: %d / [G]: %d / [B]: %d", data[j+2], data[j+1], data[j]);

			int x = 255;
			if (x == data[j+2])
				__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "int == unsigned char");
			else
				__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "int != unsigned char");

			for (r = height-1; r >= 0; r--) {
				//for (c = width-1; c >= 0; c--) {
				for (c = 0; c <= width-1; c++) {

	//				if (r == 356 && c == 1)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (0x356): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 159 && c == 262)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (262x159): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 234 && c == 397)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (397x234): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 234 && c == 398)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (398x234): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

					if (r == 0 && c == 0)
						__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[Original] RGB values of the pixel (3x3): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

					//Source = http://www.techrepublic.com/blog/how-do-i/how-do-i-convert-images-to-grayscale-and-sepia-tone-using-c/#.
					//According to the source, the coefficients are reccommended by Microsoft
					data[i] = (floor(data[i+2] * 0.272 + 0.5)) + (floor(data[i+1] * 0.534 + 0.5)) + (floor(data[i] * 0.131 + 0.5));
					if (data[i] > 255)
						data[i] = 255;
					data[i+1] = (floor(data[i+2] * 0.349 + 0.5)) + (floor(data[i+1] * 0.686 + 0.5)) + (floor(data[i] * 0.168 + 0.5));
					if (data[i+1] > 255)
						data[i+1] = 255;
					data[i+2] = (floor(data[i+2] * 0.393 + 0.5)) + (floor(data[i+1] * 0.769 + 0.5)) + (floor(data[i] * 0.189 + 0.5));
					if (data[i+2] > 255)
						data[i+2] = 255;

					//Pixel selection for debugging. Write the actual values from GIMP.
					//Keep in mind that if GIMP shows 15.3x16.1, this is pixel (16x17) ;-)
	//				if (r == 356 && c == 1)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (0x356): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 159 && c == 262)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (262x159): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 234 && c == 397)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (397x234): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);
	//				if (r == 234 && c == 398)
	//					__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RGB values of the pixel (398x234): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

					if (r == 0 && c == 0)
						__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[Modified] RGB values of the pixel (3x3): [R]: %d / [G]: %d / [B]: %d", data[i+2], data[i+1], data[i]);

					//update data[] index
					i+=3;
				}
				i++;
			}
		}

		int j = floor(255 * 0.393 + 0.5); //0.395
		__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "255 * 0.393: %d", j);

	//	// Make the picture RED. Start from the first red byte, which is buffer[2]
	//	// Originally, colors are represented as (B, G, R)
	//	__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "size: %d", size);
	//	__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "Pi: %f", 3.14);
	//	for (int i=56; i<size; i+=3) {
	//		data[i] = 255;
	//		data[i+1] = 0;
	//		data[i+2] = 0;
	//		if ((i-56) % (477*3-3) > 477*3-5 && i != 56)
	//			i += 1;
	//
	////		if (i == 509486){
	////			__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[B]: %d / [G]: %d / [R]: %d / [Ad]: %d / [Af]: %f", data[i], data[i+1], data[i+2], data[i+3], (float)data[i+3]);
	////			data[i] = 255;
	////			data[i+1] = 0;
	////			data[i+2] = 0;
	////		}
	////
	////
	//////		if (i<57) {
	//////			//__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "[56]: %d / [57]: %d / [58]: %d / [59]: %d", data[i], data[i+1], data[i+2], data[i+3]);
	//////			data[i] = 255;
	//////			data[i+1] = 0;
	//////			data[i+2] = 0;
	//////		} else {
	////			if (i == (56+(477*3))){
	////				data[i] = 255;
	////				data[i+1] = 0;
	////				data[i+2] = 0;
	////			} //else {
	////
	//////			data[i] += 20;
	//////			if (data[i] > 255)
	//////				data[i] = 255;
	////			if (i == 56 || i == 59 || i == 62 || i == 65 || i == 68 || i == 71 || i == 74 || i == 77){
	////				__android_log_print(ANDROID_LOG_VERBOSE, "filterImage()", "RED value: %d", data[i]);
	////				data[i] = 255;
	////				data[i+1] = 0;
	////				data[i+2] = 0;
	////			}
	//		//}
	//	}

		//---------| Write to file |-----------
		FILE* outFile;
		nativeResultPath.append("image_result_JNI.bmp");
		outFile = fopen(nativeResultPath.c_str(), "wb");
		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Alive2");

		//fwrite(data, sizeof(char), sizeof(data), outFile);
		fwrite(data, 1, sizeof(data), outFile);

		fclose(outFile);

		//delete[] data;
		__android_log_write(ANDROID_LOG_VERBOSE, "filterImage()", "Still Alive??");


}

void filterJPGImage(string imageFile, string nativeResultPath){
//	int			yy;
//	int			nJpegLineBytes;			//
//
//	char*		lpbtBits;
//	JSAMPLE*	pSample;
//	FILE*		fp;
//	JSAMPROW	buffer[1];
//	JSAMPLE		tmp;
//
//	jpeg_decompress_struct		cInfo;
//	jpeg_error_mgr				jError;
//
//	fp = fopen(imageFile.c_str(),"rb");
//	if(fp == NULL)
//		return;//	0;
//
//	cInfo.err = jpeg_std_error(&jError);			//
//	//jError.error_exit = _JpegError;					//
//
//	jpeg_create_decompress(&cInfo);					//
//	jpeg_stdio_src(&cInfo,fp);						//
//	jpeg_read_header(&cInfo,TRUE);					//
//	jpeg_start_decompress(&cInfo);					//
//
//	nJpegLineBytes = cInfo.output_width * cInfo.output_components;		//
//
//	pSample = new JSAMPLE[nJpegLineBytes + 10];		//
//	buffer[0] = pSample;
//
//	yy = 0;
//
//	unsigned char a,r,g,b;
//	int width, height;
//	JSAMPARRAY pJpegBuffer;
//	unsigned char * pDummy = new unsigned char [width*height*4];
//
//	while(cInfo.output_scanline < cInfo.output_height)
//	{
//		for (int x=0;x<width;x++) {
//					a = 0; // alpha value is not supported on jpg
//					r = pJpegBuffer[0][cInfo.output_components*x];
//					if (cInfo.output_components>2)
//					{
//						g = pJpegBuffer[0][cInfo.output_components*x+1];
//						b = pJpegBuffer[0][cInfo.output_components*x+2];
//					} else {
//						g = r;
//						b = r;
//					}
//					*(pDummy++) = b;
//					*(pDummy++) = g;
//					*(pDummy++) = r;
//					*(pDummy++) = a;
//		}
//
//
////		if(yy >= pBitmapInfo->height)
////			break;
////
////		jpeg_read_scanlines(&cInfo,buffer,1);		//
////
////		int		xx;
////		int		x3;
////
////		uint16_t*  pLine = (uint16_t*)pPixels;
////		for(xx = 0, x3 = 0; xx < pBitmapInfo->width && x3 < nJpegLineBytes; xx++, x3 += 3)
////		{
////			//
////			pLine[xx] = make565(buffer[0][x3 + 0],buffer[0][x3 + 1],buffer[0][x3 + 2]);
////		}
//
//		// go to next line
////		pPixels = (char*)pPixels + pBitmapInfo->stride;
////		yy++;
//	}
//	delete	pSample;
//
//	jpeg_finish_decompress(&cInfo);		//
//	jpeg_destroy_decompress(&cInfo);
//	fclose(fp);

	return;//	1;
}

int loadJpg(const char* Name){
//	unsigned char a,r,g,b;
//	int width, height;
//	struct jpeg_decompress_struct cinfo;
//	struct jpeg_error_mgr jerr;
//
//	FILE * infile;    	/* source file */
//	JSAMPARRAY pJpegBuffer;   	/* Output row buffer */
//	int row_stride;   	/* physical row width in output buffer */
//	if ((infile = fopen(Name, "rb")) == NULL)
//	{
//		fprintf(stderr, "can't open %s\n", Name);
//		return 0;
//	}
//	cinfo.err = jpeg_std_error(&jerr);
//	jpeg_create_decompress(&cinfo);
//	jpeg_stdio_src(&cinfo, infile);
//	(void) jpeg_read_header(&cinfo, TRUE);
//	(void) jpeg_start_decompress(&cinfo);
//	width = cinfo.output_width;
//	height = cinfo.output_height;
//
//	unsigned char * pDummy = new unsigned char [width*height*4];
//	unsigned char * pTest=pDummy;
//	if (!pDummy){
//		printf("NO MEM FOR JPEG CONVERT!\n");
//		return 0;
//	}
//	row_stride = width * cinfo.output_components ;
//	pJpegBuffer = (*cinfo.mem->alloc_sarray)
//    		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
//
//	while (cinfo.output_scanline < cinfo.output_height) {
//		(void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
//		for (int x=0;x<width;x++) {
//			a = 0; // alpha value is not supported on jpg
//			r = pJpegBuffer[0][cinfo.output_components*x];
//			if (cinfo.output_components>2)
//			{
//				g = pJpegBuffer[0][cinfo.output_components*x+1];
//				b = pJpegBuffer[0][cinfo.output_components*x+2];
//			} else {
//				g = r;
//				b = r;
//			}
//			*(pDummy++) = b;
//			*(pDummy++) = g;
//			*(pDummy++) = r;
//			*(pDummy++) = a;
//		}
//	}
//	fclose(infile);
//	(void) jpeg_finish_decompress(&cinfo);
//	jpeg_destroy_decompress(&cinfo);
//
////	BMap = (int*)pTest;
////	Height = height;
////	Width = width;
//	Depht = 32;
	return 2057;
}

JNIEXPORT jstring JNICALL Java_it_unibz_enactmobile_EnActStart_meteorContestBenchmark
  (JNIEnv *env, jobject obj){

	/* The Computer Language Benchmarks Game
	   http://benchmarksgame.alioth.debian.org/
	   contributed by Stefan Westen
	   loosely based on Ben St. John's and Kevin Barnes' implementation

	   Main improvements:
	      - Check for isolated cells instead of bad islands
	      - Pre-calculate lists based on availability of 3 neighbouring cells
	      - OpenMP tasks
	*/

	//int main(int argc, char* argv[])

	//N = (int) n;

	void runMeteor();

	string finalReplyFromJNI = "Meteor contest executed.";
		return env->NewStringUTF(finalReplyFromJNI.c_str());
}

JNIEXPORT jstring JNICALL Java_it_unibz_enactmobile_EnActStart_mandelbrotBenchmark
  (JNIEnv *env, jobject obj, jint n){

	// The Computer Language Benchmarks Game
	// http://benchmarksgame.alioth.debian.org/
	//
	// contributed by Elam Kolenovic
	//
	// Changes (2013-05-07)
	//   - changed omp schedule for more even distribution of work
	//   - changed loop variables to signed integer because msvc was complaining
	//     when omp was enabled
	//   - replaced std::copy and std::fill by one loop. slightly faster.
	//   - swapped order of tests in for-i-loop. slightly faster.
	//
	// Changes (2013-04-19)
	//   - using omp
	//   - use buffer and fwrite at end instead of putchar
	//   - pre-calculate cr0[]
	//   - rename variables and use underscore before the index part of the name
	//   - inverted bit tests, better performance under MSVC
	//   - optional argument for file output, usefull in windows shell
	//
	// Changes (2013-04-07):
	//   - removed unnecessary arrays, faster especially on 32 bits
	//   - using putchar instead of iostreams, slightly faster
	//   - using namespace std for readability
	//   - replaced size_t with unsigned
	//   - removed some includes


	//using namespace std;

	//int main(int argc, char* argv[])
	//{
	    //const int    N              = max(0, (argc > 1) ? atoi(argv[1]) : 0);
		const int    N              = (int) n; //max(0, (argc > 1) ? atoi(argv[1]) : 0);
	    const int    width          = N;
	    const int    height         = N;
	    const int    max_x          = (width + 7) / 8;
	    const int    max_iterations = 50;
	    const double limit          = 2.0;
	    const double limit_sq       = limit * limit;

	    vector<Byte> buffer(height * max_x);

	    vector<double> cr0(8 * max_x);
	#pragma omp parallel for
	    for (int x = 0; x < max_x; ++x)
	    {
	        for (int k = 0; k < 8; ++k)
	        {
	            const int xk = 8 * x + k;
	            cr0[xk] = (2.0 * xk) / width - 1.5;
	        }
	    }

	#pragma omp parallel for schedule(guided)
	    for (int y = 0; y < height; ++y)
	    {
	        Byte* line = &buffer[y * max_x];

	        const double ci0 = 2.0 * y / height - 1.0;

	        for (int x = 0; x < max_x; ++x)
	        {
	            const double* cr0_x = &cr0[8 * x];
	            double cr[8];
	            double ci[8];
	            for (int k = 0; k < 8; ++k)
	            {
	                cr[k] = cr0_x[k];
	                ci[k] = ci0;
	            }

	            Byte bits = 0xFF;
	            for (int i = 0; bits && i < max_iterations; ++i)
	            {
	                Byte bit_k = 0x80;
	                for (int k = 0; k < 8; ++k)
	                {
	                    if (bits & bit_k)
	                    {
	                        const double cr_k    = cr[k];
	                        const double ci_k    = ci[k];
	                        const double cr_k_sq = cr_k * cr_k;
	                        const double ci_k_sq = ci_k * ci_k;

	                        cr[k] = cr_k_sq - ci_k_sq + cr0_x[k];
	                        ci[k] = 2.0 * cr_k * ci_k + ci0;

	                        if (cr_k_sq + ci_k_sq > limit_sq)
	                        {
	                            bits ^= bit_k;
	                        }
	                    }
	                    bit_k >>= 1;
	                }
	            }
	            line[x] = bits;
	        }
	    }

	    //FILE* out = (argc == 3) ? fopen(argv[2], "wb") : stdout;
	    //fprintf(out, "P4\n%u %u\n", width, height);
	    //fwrite(&buffer[0], buffer.size(), 1, out);

//	    if (out != stdout)
//	    {
//	        fclose(out);
//	    }

	    //return 0;
	//}




	string finalReplyFromJNI = "Mandelbrot executed.";
	return env->NewStringUTF(finalReplyFromJNI.c_str());
}

JNIEXPORT jstring JNICALL Java_it_unibz_enactmobile_EnActStart_spectralNormBenchmark
  (JNIEnv *env, jobject obj, jint n){


	// The Computer Language Benchmarks Game
	// http://benchmarksgame.alioth.debian.org/
	//
	// Original C contributed by Sebastien Loisel
	// Conversion to C++ by Jon Harrop
	// Compile: g++ -O3 -o spectralnorm spectralnorm.cpp  (This compile command may not work in Android NDK and JNI!!)

	//int main(int argc, char *argv[])
	//{
	  //int N = ((argc == 2) ? atoi(argv[1]) : 2000);
	  int N = (int) n;
	  vector<double> u(N), v(N);

	  fill(u.begin(), u.end(), 1);

	  for(int i=0; i<10; i++) {
	    eval_AtA_times_u(u, v);
	    fill(u.begin(), u.end(), 0);
	    eval_AtA_times_u(v, u);
	  }

	  double vBv=0, vv=0;
	  for(int i=0; i<N; i++) { vBv += u[i]*v[i]; vv += v[i]*v[i]; }

	  cout << setprecision(10) << sqrt(vBv/vv) << endl;

	  //return 0;
	//}




	string finalReplyFromJNI = "Spectral-norm executed.";
	return env->NewStringUTF(finalReplyFromJNI.c_str());
}

double eval_A(int i, int j) { return 1.0 / ((i+j)*(i+j+1)/2 + i + 1); }

void eval_A_times_u(const vector<double> &u, vector<double> &Au)
{
  for(int i=0; i<u.size(); i++)
    for(int j=0; j<u.size(); j++) Au[i] += eval_A(i,j) * u[j];
}

void eval_At_times_u(const vector<double> &u, vector<double> &Au)
{
  for(int i=0; i<u.size(); i++)
    for(int j=0; j<u.size(); j++) Au[i] += eval_A(j,i) * u[j];
}

void eval_AtA_times_u(const vector<double> &u, vector<double> &AtAu)
{ vector<double> v(u.size()); eval_A_times_u(u, v); eval_At_times_u(v, AtAu); }



////////Meteor contest constants

const int nPieceCount = 10;
const int pieces[10][5][2]  = {
   {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {3, 1}},
   {{0, 0}, {0, 1}, {-2, 2}, {-1, 2}, {-3, 3}},
   {{0, 0}, {1, 0}, {2, 0}, {-1, 1}, {-1, 2}},
   {{0, 0}, {1, 0}, {2, 0}, {1, 1}, {1, 2}},
   {{0, 0}, {0, 1}, {1, 1}, {-1, 2}, {1, 2}},
   {{0, 0}, {1, 0}, {-2, 1}, {-1, 1}, {0, 1}},
   {{0, 0}, {1, 0}, {0, 1}, {-1, 2}, {-1, 3}},
   {{0, 0}, {2, 0}, {-1, 1}, {0, 1}, {1, 1}},
   {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},
   {{0, 0}, {0, 1}, {0, 2}, {-1, 3}, {0, 3}}
   };

unsigned int g_AllMasks[8192];
unsigned int *g_MaskStart[50][8];

unsigned char g_min_solution[50], g_max_solution[50];
unsigned int g_solutions;

unsigned int EvenRowsLookup[50];
unsigned int LeftBorderLookup[50];

bool GoodPiece(unsigned int mask, unsigned int pos)
{
   bool bOK(true);
   const unsigned long long even_rows = 0xf07c1f07c1f07c1f;
   const unsigned long long odd_rows = ~even_rows;
   const unsigned long long left_border = 0x1084210842108421;
   const unsigned long long right_border = left_border >> 1;
   unsigned long long a,b,a_old,s1,s2,s3,s4,s5,s6,s7,s8;

   b = (((unsigned long long)mask) << pos) | 0xFFFC000000000000ULL;

   b = ~b;

   while (b)
   {
	  a = b&-b;

	  do
	  {
		 s1 = a << 5;
		 s2 = a >> 5;
		 s3 = (a << 1)&(~left_border);
		 s4 = (a >> 1)&(~right_border);
		 s5 = ((a & even_rows) >> 6) &(~right_border);
		 s6 = ((a & even_rows) << 4) &(~right_border);
		 s7 = ((a & odd_rows) >> 4) & (~left_border);
		 s8 = ((a & odd_rows) << 6) &(~left_border);
		 a_old = a;
		 a = (a|s1|s2|s3|s4|s5|s6|s7|s8)&b;
	  } while (a_old!=a);
	  if (__builtin_popcountll(a)%5!=0)
	  {
		 bOK = false;
		 break;
	  }
	  b = b ^ a;
   }
   return bOK;
}

void Initialise()
{
   for (int i=0;i<50;i++)
   {
	  EvenRowsLookup[i] = 0xF07C1F07C1F07C1FULL >> i;
	  LeftBorderLookup[i] = 0x1084210842108421ULL >> i;
   }

   int nTotalCount = 0; //(0);
   int x[5], y[5];
   for (int nYBase=2;nYBase<4;nYBase++)
   {
	  for (int nXBase=0;nXBase<5;nXBase++)
	  {
		 int nPos = nXBase+5*nYBase;
		 g_MaskStart[nPos][0] = &g_AllMasks[nTotalCount];
		 for (int nPiece=0;nPiece<nPieceCount;nPiece++)
		 {
			for (int j=0;j<5;j++)
			{
			   x[j] = pieces[nPiece][j][0];
			   y[j] = pieces[nPiece][j][1];
			}

			int nCurrentRotation=0;
			for (nCurrentRotation=0;nCurrentRotation<12;nCurrentRotation++)
			{
			   if (nPiece!=3||(nCurrentRotation/3)%2==0)
			   {
				  int nMinX = x[0];
				  int nMinY = y[0];
				  for (int i=1;i<5;i++)
				  {
					 if (y[i]<nMinY||(y[i]==nMinY&&x[i]<nMinX))
					 {
						nMinX=x[i];
						nMinY=y[i];
					 }
				  }

				  unsigned int mask = 0;
				  bool bFit(true);

				  for (int i=0;i<5;i++)
				  {
					 int nX = (x[i]-nMinX+(nXBase-nYBase/2))
							  +(y[i]-nMinY+nYBase)/2;
					 int nY = y[i]-nMinY+nYBase;
					 if (nX>=0&&nX<5)
					 {
						int nBit = nX-nXBase+5*(nY-nYBase);
						mask |= (1<<nBit);
					 }
					 else
					 {
						bFit = false;
					 }
				  }
				  if (bFit)
				  {
					 if (GoodPiece(mask,nPos))
					 {
						g_AllMasks[nTotalCount++] =
						   mask|(1<<(nPiece+22));
					 }
				  }
			   }
			   for (int i=0;i<5;i++)
			   {
				  int xnew = x[i]+y[i];
				  int ynew = -x[i];
				  x[i] = xnew;
				  y[i] = ynew;
				  if (nCurrentRotation==5)
				  {
					 int xnew = x[i]+y[i];
					 int ynew = -y[i];
					 x[i] = xnew;
					 y[i] = ynew;
				  }
			   }
			}
		 }
		 g_AllMasks[nTotalCount++] = 0;
	  }
   }

   // copy rows 2 and 3 to other rows


   for (int nYBase=0;nYBase<10;nYBase++)
   {
	  if (nYBase!=2&&nYBase!=3)
	  {
		 for (int nXBase=0;nXBase<5;nXBase++)
		 {
			int nPos = nXBase+5*nYBase;
			int nOrigPos = nXBase+5*(nYBase%2+2);
			g_MaskStart[nPos][0] = &g_AllMasks[nTotalCount];
			unsigned int *pMask = g_MaskStart[nOrigPos][0];
			unsigned int bottom = (0xFFFC000000000000ULL>>nPos)
								 &0x003FFFFF;
			unsigned int last_row = (0xFFFC000000000000ULL>>(nPos+5))
								 &0x003FFFFF;
			while (*pMask)
			{
			   unsigned int mask=*pMask;
			   pMask++;
			   if ((mask&bottom)==0)
			   {
				  if (nYBase==0||(mask&last_row))
				  {
					 if (!GoodPiece(mask&0x003FFFFF,nPos))
					 {
						continue;
					 }
				  }
				  g_AllMasks[nTotalCount++] = mask;
			   }
			}
			g_AllMasks[nTotalCount++] = 0;
		 }
	  }
   }

   for (int nFilter=1;nFilter<8;nFilter++)
   {
	  for (int nPos=0;nPos<50;nPos++)
	  {
		 g_MaskStart[nPos][nFilter] = &g_AllMasks[nTotalCount];
		 unsigned int filter_mask;
		 filter_mask = ((nFilter&1)<<1)|((nFilter&6)<<
					 (4-(EvenRowsLookup[nPos]&1)));
		 unsigned int *pMask = g_MaskStart[nPos][0];
		 while (*pMask)
		 {
			unsigned int mask=*pMask;
			if ((mask&filter_mask)==0)
			{
			   g_AllMasks[nTotalCount++] = mask;
			}
			pMask++;
		 }
		 g_AllMasks[nTotalCount++] = 0;
	  }
   }
}

void CompareSolution(unsigned char* board, unsigned char* min_solution,
			   unsigned char* max_solution)
{
   int i,j;

   for (i=0;i<50;i++)
   {
	  if (board[i]<min_solution[i])
	  {
		 for (j=0;j<50;j++)
		 {
			min_solution[j] = board[j];
		 }
		 break;
	  }
	  else if (board[i]>min_solution[i])
	  {
		 break;
	  }
   }
   for (i=0;i<50;i++)
   {
	  if (board[i]>max_solution[i])
	  {
		 for (j=0;j<50;j++)
		 {
			max_solution[j] = board[j];
		 }
		 break;
	  }
	  else if (board[i]<max_solution[i])
	  {
		 break;
	  }
   }
}

//void PrintBoard(unsigned char *board)
//{
//   int i;
//
//   for (i=0;i<50;i++)
//   {
//      printf ("%d ", board[i]);
//      if (i%5==4)
//      {
//         printf("\n");
//         if ((i&1)==0)
//         {
//            printf (" ");
//         }
//      }
//   }
//   printf ("\n");
//
//}

void RecordSolution(unsigned int current_solution[])
{
   unsigned char board[50], flip_board[50];
   int i;
   unsigned long piece;
   unsigned int mask, pos, current_bit, b1;
   unsigned long count;
   b1 = 0;
   pos = 0;
   for (i=0;i<10;i++)
   {
	  mask = current_solution[i];
	  piece = __builtin_ctz(mask>>22);
	  mask &= 0x003FFFFF;
	  b1 |= mask;
	  while (mask)
	  {
		 current_bit = mask&-mask;
		 count = __builtin_ctz(current_bit);
		 board[count+pos] = piece;
		 flip_board[49-count-pos] = piece;
		 mask ^= current_bit;
	  }
	  count = __builtin_ctz(~b1);
	  pos+=count;
	  b1 >>= count;
   }
   if (g_solutions==0)
   {
	  for (i=0;i<50;i++)
	  {
		 g_min_solution[i] = g_max_solution[i] = board[i];
	  }
   }
   else
   {
	  CompareSolution(board, g_min_solution, g_max_solution);
	  CompareSolution(flip_board, g_min_solution, g_max_solution);
   }

   g_solutions+=2;
}

void searchLinear(unsigned int board, unsigned int pos, unsigned int used,
		 unsigned int placed, unsigned int current_solution[])
{
   unsigned long count;
   unsigned int even_rows, odd_rows, left_border, right_border, s1, s2, s3,
				  s4, s5, s6, s7, s8;
   if (placed==10)
   {
	  #pragma omp critical

	  RecordSolution(current_solution);
   }
   else
   {
	  even_rows = EvenRowsLookup[pos];

	  odd_rows = ~even_rows;

	  left_border = LeftBorderLookup[pos];
	  right_border = left_border>>1;

	  s1 = (board << 1) | left_border;
	  s2 = (board >> 1) | right_border;
	  s3 = (board << 4) | ((1<<4)-1) | right_border;
	  s4 = (board >> 4) | left_border;
	  s5 = (board << 5) | ((1<<5)-1);
	  s6 = (board >> 5);
	  s7 = (board << 6) | ((1<<6)-1) | left_border;
	  s8 = (board >> 6) | right_border;

	  if (~board&s1&s2&s5&s6&((even_rows&s4&s7)|(odd_rows&s3&s8)))
	  {
		 return;
	  }

	  count = __builtin_ctz(~board);
	  pos+=count;
	  board >>= count;

	  unsigned int f;
	  f = ((board>>1)&1)|((board>>(4-(EvenRowsLookup[pos]&1)))&6);
	  unsigned int board_and_used = board|used;

	  unsigned int *masks = g_MaskStart[pos][f];
	  unsigned int mask;

	  while (*masks)
	  {
		 while ((*masks)&board_and_used)
		 {
			masks++;
		 }
		 if (*masks)
		 {
			mask = *masks;
			current_solution[placed] = mask;
			searchLinear(board|((mask&0x003FFFFF)), pos, used|(mask&0xFFC00000),
				  placed+1, current_solution);
			masks++;
		 }
	  }
   }
}

void searchParallel(unsigned int board, unsigned int pos, unsigned int used,
		 unsigned int placed, unsigned int first_piece)
{
   unsigned long count;

   count = __builtin_ctz(~board);
   pos+=count;
   board >>= count;

   unsigned int board_and_used = board|used;

   unsigned int *masks = g_MaskStart[pos][0];
   unsigned int mask;

   if (placed==0)
   {
	  while (*masks)
	  {
		 while ((*masks)&board_and_used)
		 {
			masks++;
		 }
		 if (*masks)
		 {
			mask = *masks++;
			{
			   searchParallel(board|((mask&0x003FFFFF)), pos, used|(mask&0xFFC00000),
				  placed+1, mask);
			}
		 }
	  }
   }
   else
   {   // placed==1

	  while (*masks)
	  {
		 while ((*masks)&board_and_used)
		 {
			masks++;
		 }
		 if (*masks)
		 {
			mask = *masks++;
			#pragma omp task default(none) firstprivate(board, mask, pos, used, placed, first_piece)

			{
			   unsigned int current_solution[10];
			   current_solution[0] = first_piece;
			   current_solution[placed] = mask;
			   searchLinear(board|((mask&0x003FFFFF)), pos, used|(mask&0xFFC00000),
				  placed+1, current_solution);
			}
		 }
	  }
   }
}

void runMeteor()
{
   //if (argc > 2)
	 //return 1;

   Initialise();

   g_solutions = 0;

   #pragma omp parallel

   {
	  #pragma omp single

	  {
		 searchParallel(0,0,0,0,0);
	  }
   }

   __android_log_write(ANDROID_LOG_VERBOSE, "run Meteor()", intToStr(g_solutions).c_str());
   //printf ("%d solutions found\n\n",g_solutions);
   //PrintBoard(g_min_solution);
   //PrintBoard(g_max_solution);

   //return 0;
}

string readFileAndMultiplyMatrices(string inputFile, string resultFile){

	string text = "";
	string line;
	ifstream matricesFile (inputFile.c_str());
	__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Going to read the input file...");
	if (matricesFile.is_open())
	{
		while ( getline (matricesFile,line) )
		{
			//cout << line << '\n';
			//__android_log_write(ANDROID_LOG_VERBOSE, "C++", line.c_str());
			text.append(line);
			text.append("\n");

		}

		//__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", text.c_str());
		matricesFile.close();
	}
	else __android_log_write(ANDROID_LOG_ERROR, "readFileAndMultiplyMatrices()", "Unable to open the input file");


	__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Input from input file read!!!");
	vector<string> matrices = split_string(text,"~");
	//printStrVector(matrices);
	//__android_log_write(ANDROID_LOG_VERBOSE, "matrixA", matrices.at(1).c_str());
	vector<string> rows_matrixA = split_string(matrices.at(1),";");
	vector<string> rows_matrixB = split_string(matrices.at(2),";");

	//Populate matrixA----------
	vector<string> elements_row_A = split_string(rows_matrixA.at(0),",");
	int rowsA = rows_matrixA.size();
	int colsA = elements_row_A.size();
	int matrixA[rowsA][colsA];

	for(int r=0; r<rowsA; r++){
		vector<string> elements_row_A = split_string(rows_matrixA.at(r),",");
		for(int c=0; c<colsA; c++){
			matrixA[r][c] = atoi(elements_row_A.at(c).c_str());
		}
	}
	//---------------------------

	//print matrixA
//	//printIntMatrix(matrixA, rows_matrixA.size(), elements_row_A.size());
//	for(int r=0; r<rows_matrixA.size(); r++){
//		for(int c=0; c<elements_row_A.size(); c++){
//			const char* current = intToStr(matrixA[r][c]).c_str();
//			__android_log_write(ANDROID_LOG_VERBOSE, "int matrix printer", current);
//		}
//	}

//	__android_log_write(ANDROID_LOG_VERBOSE, "C++", "vvvvvvvvvvvvvvvvvvvvvvv");


	__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Matrix A populated!!!");
	//Populate matrixB----------
	vector<string> elements_row_B = split_string(rows_matrixB.at(0),",");
	int rowsB = rows_matrixB.size();
	int colsB = elements_row_B.size();
	int matrixB[rowsB][colsB];

	for(int r=0; r<rowsB; r++){
		vector<string> elements_row_B = split_string(rows_matrixB.at(r),",");
		for(int c=0; c<colsB; c++){
			matrixB[r][c] = atoi(elements_row_B.at(c).c_str());
		}
	}
	//---------------------------

	//print matrixB---------------
//	for(int r=0; r<rows_matrixB.size(); r++){
//		for(int c=0; c<elements_row_B.size(); c++){
//			const char* current = intToStr(matrixB[r][c]).c_str();
//			__android_log_write(ANDROID_LOG_VERBOSE, "int matrix printer", current);
//		}
//	}


	__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Matrix B populated!!!");
	//Multiply matrices
	int ca,rr,cr; //indices of the matrices
	int rowsAB = rowsA;
	int colsAB = colsB;
	int matrixAxB[rowsAB][colsAB];

	for (rr=0; rr<rowsAB; rr++){
		for (cr=0; cr<colsAB; cr++){

			int res = 0;
			for(ca = 0; ca<colsA; ca++){
				res += (matrixA[rr][ca] * matrixB[ca][cr]);
			}

			matrixAxB[rr][cr] = res;
			//const char* current = intToStr(res).c_str();
			//__android_log_write(ANDROID_LOG_VERBOSE, "resulting matrix", current);

		}
	}

	__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Matrices multiplied!!!");



	/*
	//Populate matrix A----------------
	vector<vector<int> > matrixA;
	vector<string>::iterator it;
	//it=rows_matrixA.begin();
	__android_log_write(ANDROID_LOG_VERBOSE, "C++", "Segno di vita");
	for(int r = 0; r < rows_matrixA.size(); r++){
		vector<string> column_matrixA = split_string(rows_matrixA.at(r),",");
		for(int c = 0; c < column_matrixA.size(); c++){
			//int current = atoi(column_matrixA.at(c).c_str());
			matrixA.at(r).push_back(atoi(column_matrixA.at(c).c_str()));
		}
	}
	//-------------------------------
	printIntMatrix(matrixA);
	*/

	//Write the result to the Result.txt file------------------------
	const char* result_File = resultFile.c_str();
	ofstream file (result_File);
	if (file.is_open())
	{
		//cr = 0;
		//rr = 0;
		string rline = "";
		for(rr=0; rr<rowsAB; rr++){
			for(cr=0; cr<colsAB-1; cr++){
				//file << intToStr(matrixAxB[rr][cr]);
				rline.append(intToStr(matrixAxB[rr][cr]));
				rline.append(",");
			}
			rline.append(intToStr(matrixAxB[rr][cr]));
			if(rr != (rowsAB-1))
				rline.append(";\n");
			//file << rline;
		}
		file << rline;
//		myfile << "This is a line.\n";
//		myfile << "This is another line.\n";
//		myfile.close();
		file.close();

		__android_log_write(ANDROID_LOG_VERBOSE, "readFileAndMultiplyMatrices()", "Result written to file!!!");
	}
	else __android_log_write(ANDROID_LOG_ERROR, "readFileAndMultiplyMatrices()", "Unable to open the output file");


	string finalReplyFromJNI = "You can find the result of the multiplication here:\n";
	finalReplyFromJNI.append(resultFile);

	return finalReplyFromJNI;
}

vector<string> split_string(string str, string delimiter){
	vector<string> pieces;

	//std::string s = "scott>=tiger>=mushroom";
	//std::string delimiter = ">=";

	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
	    token = str.substr(0, pos);
	    //std::cout << token << std::endl;
	    pieces.push_back(token);
	    str.erase(0, pos + delimiter.length());
	}
	pieces.push_back(str);
	//std::cout << s << std::endl;
	//printStrVector(pieces);
	//__android_log_write(ANDROID_LOG_VERBOSE, "split_string()", "String splitted around delimiter!!!");
	return pieces;
}

void printStrVector(vector<string> str){
	__android_log_write(ANDROID_LOG_VERBOSE, "string vector printer", "==================");
	vector<string>::iterator it;
	for(it=str.begin(); it<str.end(); it++) {
		__android_log_write(ANDROID_LOG_VERBOSE, "string vector printer", "Element:");
		__android_log_write(ANDROID_LOG_VERBOSE, "string vector printer", (*it).c_str());

	}
	__android_log_write(ANDROID_LOG_VERBOSE, "string vector printer", "==================");
}

void printIntMatrix(vector<vector<int> > matrix){
	/*for(int r=0; r<row; r++){
		for(int c=0; c<col; c++){
			const char* current = intToStr(arr[r][c]).c_str();
			__android_log_write(ANDROID_LOG_VERBOSE, "int matrix printer", current);
		}
	}*/

	/*string row = "";
	for(int r = 0; r < matrix.size(); r++){
		for(int c = 0; c < matrix.at(r).size(); c++){
			//ostringstream ss;
			//ss << matrix.at(r).at(c);
			row.append(intToStr(matrix.at(r).at(c)));
			row.append(" | ");
			//const char *current = ss.str().c_str();
			//const char* current =

		}
		__android_log_write(ANDROID_LOG_VERBOSE, "int matrix printer", row.c_str());
	}*/
}

string intToStr(int num){
	ostringstream ss;
	ss << num;
	return ss.str();
}

string charToStr(const char* ch) {
	stringstream ss;
	string s;
	//char c = 'a';
	ss << ch;
	ss >> s;
	return s;
}

























