#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
//#include <Eigen/Dense>

using namespace std;

string readFileAndMultiplyMatrices(string inputFile, string resultFile);
//static int DrawBitmap (AndroidBitmapInfo * pBitmapInfo, void * pPixels, const char * pszJpegFile);
void filterBMPImage(string imageFile, string nativeResultPath);
void filterJPGImage(string imageFile, string nativeResultPath);
vector<string> split_string(string str, string delimiter);
void printStrVector(vector<string> str);
void printIntMatrix(vector<vector<int> > matrix);
string intToStr(int num);
string charToStr(const char* ch);
//Meteor contest
bool GoodPiece(unsigned int mask, unsigned int pos);
void Initialise();
void CompareSolution(unsigned char* board, unsigned char* min_solution,
			   unsigned char* max_solution);
void RecordSolution(unsigned int current_solution[]);
void searchLinear(unsigned int board, unsigned int pos, unsigned int used,
		 unsigned int placed, unsigned int current_solution[]);
void searchParallel(unsigned int board, unsigned int pos, unsigned int used,
		 unsigned int placed, unsigned int first_piece);
void runMeteor();
//Mandelbrot

//Spectral norm
double eval_A(int i, int j);
void eval_A_times_u(const vector<double> &u, vector<double> &Au);
void eval_At_times_u(const vector<double> &u, vector<double> &Au);
void eval_AtA_times_u(const vector<double> &u, vector<double> &AtAu);
