/********************************************
*											*
*    Image processing software - Blur       *
*    Author Petar Nikolov                   *
*											*
*********************************************/

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

struct point_map
{
        int X;
        int Y;
}point_map;

using namespace std;
using namespace cv;
/**
* @function main
*/
int main( int argc, const char** argv )
{	

        Mat ui;
        /* Open Some image file regardless of the size - Just Change the parameters below B L U R */
        ui = imread("C:\\Users\\petar.nikolov\\Downloads\\grayscale.jpg", CV_LOAD_IMAGE_GRAYSCALE);
        IplImage *ui2 = cvCreateImage(cvSize(ui.cols,ui.rows),8,1);
        cv::Mat ui3 = cv::Mat::zeros(ui.rows, ui.cols, CV_8U); 
        double *matrix = (double *)calloc(ui.cols * ui.rows, sizeof(double));
        int *input = (int *)ui.data;
        int i, j, z, t; 
        uchar luma;
        int Sybiraemo = 0;
        double Number = 0;
        double Number0 = 0;
        double Number2 = 0;
        double Distance;
        double DistanceRatio;
        //// B L U R
        struct point_map BlurCentralPoint = { 1020, 760 };//ui.cols/2, ui.rows/2 };
        int SizeOfBlur = 5;//percentage of width that is CLEAR (no Blur) around BlurCentralPoint
        int SharpOrBlur = 1; // Sharp = 1; Blur = 0;
        int BlurAgression = 100; // ot 1 do 100; (Bigger than 0)
        int BlurPixelRadius = 13;// Should be Even number - min 5
        double MaxRatio;
        ////////////////

        MaxRatio = (double)MAX(BlurCentralPoint.X - ((double)SizeOfBlur * ui.cols / 100), ui.cols - BlurCentralPoint.X + ((double)SizeOfBlur * ui.cols / 100)) / ((double)SizeOfBlur * ui.cols / 100);
        for( i = 0; i < ui.rows; i++ )
        {
           for ( j = 0; j < ui.cols; j++ )
           {
                Distance = sqrt(pow(abs((double)BlurCentralPoint.X - j), 2) + pow(abs((double)BlurCentralPoint.Y - i), 2));
                if (Distance < ((double)SizeOfBlur * ui.cols / 100))
                {
                     matrix[i * ui.cols + j] = 1;
                }
                else
                {
                     DistanceRatio = Distance / ((double)SizeOfBlur * ui.cols / 100);
                     matrix[i * ui.cols + j] = 1 - ((double)BlurAgression/100 *( DistanceRatio/ MaxRatio));
                     if(matrix[i * ui.cols + j] < 0) matrix[i * ui.cols + j] = 0;
                }
           }
        }

        for( i = BlurPixelRadius/2; i < ui.rows-BlurPixelRadius/2; i++ )
        {
            for ( j = BlurPixelRadius/2; j < ui.cols-BlurPixelRadius/2; j++ )
            {
                if(ui.data[i*ui.cols + j] > 255) 
                        Number =0;

                Sybiraemo = 0;
                if(SharpOrBlur == 0)
                     Number2 = ((double)(matrix[i * ui.cols + j])/(pow((double)BlurPixelRadius,2) -1 - (12 + (2*(BlurPixelRadius - 5)))));
                else
                     Number2 = ((double)(1 - matrix[i * ui.cols + j])/(pow((double)BlurPixelRadius,2) -1 - (12 + (2*(BlurPixelRadius - 5)))));
                for( z = 0; z < BlurPixelRadius/2; z++)
                {
                     for( t = 0; t < BlurPixelRadius/2; t++)
                     {
                          if(  z == 0 && t == 0 ) continue;
                          Sybiraemo += ui.data[(i-z)*ui.cols + j-t];
                          Sybiraemo += ui.data[(i-z)*ui.cols + j+t];
                          Sybiraemo += ui.data[(i+z)*ui.cols + j-t];
                          Sybiraemo += ui.data[(i+z)*ui.cols + j+t];
                     }
                }
                  
                Number2 *= Sybiraemo;
                Number =0;
                if(SharpOrBlur == 0)
                    Number = (1-matrix[i * ui.cols + j])*ui.data[i*ui.cols + j] + (int)Number2;
                else 
                    Number = (matrix[i * ui.cols + j])*ui.data[i*ui.cols + j] + (int)Number2;
                if(Number > 255) 
                    Number = 255;
                if(Number < 0) 
                    Number = 0;
                ui3.data[i*ui.cols + j] = Number;
           }
        }

        cvNamedWindow("Camera",1);
        ui2->imageData = (char *)ui3.data;
        cvShowImage("Camera",ui2);
        //cvSaveImage("al.jpg",ui2);
        imwrite("al2.jpg",ui3);
        int c = cvWaitKey(15000);
        return 0;
}