#include <iostream>
using namespace std;

void Stretch(MATRIX3X3& , Pixels& , int );
void Rotate(MATRIX3X3& , Pixels& , int);
void Squeeze(MATRIX3X3& , Pixels& , int);
void Shearing(MATRIX3X3& , Pixels&);
void Flip(MATRIX3X3& , Pixels& , int);
void CopyMatrix(Pixels&, PixelsTransformed&, int, int)
void MultMatrix(MATRIX3X3& product,MATRIX3X3& matrix1, Pixels& matrix2)

int main()
{
    //size for matrix transformation matrix 
    const int m = 2;
    //matrix for transofrmations
    typedef double MATRIX3X3[m][m];
    //choice for operation
    int choice;
    //choose whether x axis stretch or y axis stretch
    int XorYStretch;

    cv::Mat img = cv::imread("file.jpg");
    int Pixels[10000][10000];
    int PixelsTransformed[10000][10000]; 
   
    //size of image matrix
    int ImageRow = img.rows;
    int ImageColumn = img.cols;
    for(int i=0;i<ImageColumn;i++)
      {
         for(int j=0;j<ImageRow;j++)
            {
               Pixels[i][j]=img.at<int>(i,j);
            }
      }

    
    
    // Call functions to be performed
    cout << "Please choose a number to perform the operation desired"<< endl;
    cout << "1 for Stretching. 2 for Rotating. 3 for Squeezing. 4 for Shearing. 5 for flipping" << endl;
    cin >> choice;
    
    switch (choice) 
    {
        case 1:
            cout << "Please enter whether it is a Stretch along x axis(Press 1) or y axis (Press 2)" << endl;
            cin >> XorYStretch;
            void Stretch(&m, &p, XorYStretch);
            break;
        case 2:
            cout << "Please enter degrees for rotation" << endl;
            cin >> degrees;
            void Rotate(&m, &p, degrees);
            break;
        case 3:
            cout << "Please enter Squeeze Factor" << endl;
            cin >> SqFactor;
            void Squeeze(&m,&p, SqFactor);
            break;
        case 4:
            cout << "Please enter whether it is a Shear along x axis(Press 1) or y axis (Press 2)" << endl;
            cin >> XorYShear;
            
            void Shearing(&m, &p, XorYShear);
            break;
        case 5:
            cout << "Please enter whether it is a Stretch along x axis(Press 1) or y axis (Press 2) or along y = x (press 3)" << endl;
            cin >> XorYorLflip;
            void Flip(&m, &p, XorYorLflip)
            break;    
        default:
            // choice is doesn't match any case
            cout << "Error! Number is not correct";
            break;
    }
    
    // OUTPUT FINAL PICTURE
    return 0;
}
void CopyMatrix(Pixels& src, PixelsTransformed& dst, int ImageRow, int ImageCol)
{
  for (int i=0; i<ImageRow; ++i)
   for (int j=0; j<ImageCol; ++j) 
     dst[i][j] = src[i][j];
}

//using multiplication from swift library
void MultMatrix(MATRIX3X3& product,MATRIX3X3& matrix1, Pixels& matrix2)
{
  for (int x=0; x<3; ++x)
    for (int y=0; y<3; ++y)
    {
      double sum = 0;
      for (int z=0; z<3; ++z)
        sum += matrix1[x][z] * matrix2[z][y];
      product[x][y] = sum;
    }
}

void Stretch(MATRIX3X3& m1, Pixels& p, int XorYStretch)
{
  MATRIX3X3 m1;
  Pixels p1;
  int xStretch = 100;
  int yStretch = 100;

  if (XorYStretch == 1)
  {
      m1[0][0]=xStretch; m1[0][1]=0;   
      m1[1][0]=0;      m1[1][1]=1;
  }
    else if (XorYStretch == 2)
    {
        m1[0][0]=1;     m1[0][1]=0;   
        m1[1][0]=0;    m1[1][1]=yStretch;
    }

  MultMatrix(p1, m1, p);
  CopyMatrix(p, p1);
}

void Rotate(MATRIX3X3& m, Pixels& p, int degrees)
{
  MATRIX3X3 m1;
  Pixels p1;

  if (degrees == 0) return;

  double radians = 6.283185308 / (360.0 / degrees);
  double c = cos(radians);
  double s = sin(radians);
  
  m1[0][0]=c; m1[0][1]=s; 
  m1[1][0]=-s; m1[1][1]=c;
  
  MultMatrix(p1, m1, p);
  CopyMatrix(p, p1);
}
//leaves area unchanged

void Squeeze(MATRIX3X3& m, Pixels& p, int SqFactor)
{
  MATRIX3X3 m1;
  Pixels p1;

  m1[0][0]=SqFactor;    m1[0][1]=0;
  m1[1][0]=0;           m1[1][1]=(1/SqFactor);   

  MultMatrix(p1, m1, p);
  CopyMatrix(p, p1);
}

void Shearing(MATRIX3X3& m, Pixels& p, int XorYShear)
{
  MATRIX3X3 m1;
  Pixels p1;
  int ShearFactor = 100;
  // parallel to x axis
  if (XorYStretch == 1)
  {
      m1[0][0]=1;      m1[0][1]=ShearFactor;   
      m1[1][0]=0;      m1[1][1]=1;
  }
   // parallel to y axis
    else if (XorYStretch == 2)
    {
        m1[0][0]=1;             m1[0][1]=0;   
        m1[1][0]=ShearFactor;    m1[1][1]=1;
    }

  MultMatrix(p1, m1, p);
  CopyMatrix(p, p1);
}
void Flip(MATRIX3X3& m, Pixels& p, int XorYorLflip)
{
  MATRIX3X3 m1;
  Pixels p1;
  // x axis
  if (XorYorLflip == 1)
  {
      m1[0][0]=1;      m1[0][1]= 0;   
      m1[1][0]=0;      m1[1][1]= -1;
  }
   // y axis
    else if (XorYorLflip == 2)
    {
        m1[0][0]= -1;     m1[0][1]=0;   
        m1[1][0]= 0 ;      m1[1][1]=1;
    }
     // along y  = x
      else if (XorYorLflip == 3)
      {
        m1[0][0]=0;      m1[0][1]= 1;   
        m1[1][0]= 1;     m1[1][1]= 0;
      }

  MultMatrix(p1, m1, p);
  CopyMatrix(p, p1);
}
