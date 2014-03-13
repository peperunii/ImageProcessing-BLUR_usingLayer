This is an Image processing algorithm "ImageProcessing-BLUR_usingLayer" written on C++ using OpenCV libraries for opening and saving the images.
Compiled succesfully using Windows 7/8 / and Visual Studio 2012/2013

The algorithm works on all kind of images (and sizes) but some changes to the following parameters have to be made:

struct point_map BlurCentralPoint = { 1020, 760 }; // Some point, could be the central one { ui.cols/2, ui.rows/2 }
int SizeOfBlur = 5;      //percentage of width that is CLEAR (no Blur) around BlurCentralPoint
int SharpOrBlur = 1;     // Sharp = 1; Blur = 0;
int BlurAgression = 100; // ot 1 do 100; (Bigger than 0)
int BlurPixelRadius = 13;// Should be Even number - min 5
