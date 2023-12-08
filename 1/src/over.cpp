#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());

  for (int i = 0; i<height;i++)
  {
    for(int j = 0; j<width;j++)
    {
      double r_a = A[i*width*4+j*4];
      double g_a = A[i*width*4+j*4+1];
      double b_a = A[i*width*4+j*4+2];
      double alpha_a = A[i*width*4+j*4+3]/255.0;

      double r_b = B[i*width*4+j*4];
      double g_b = B[i*width*4+j*4+1];
      double b_b = B[i*width*4+j*4+2];
      double alpha_b = B[i*width*4+j*4+3]/255.0;
  
      double alpha_comp = alpha_a+alpha_b*(1-alpha_a);

      C[i*width*4+j*4] = (r_a*alpha_a + r_b*alpha_b*(1-alpha_a))/alpha_comp;
      C[i*width*4+j*4+1] = (g_a*alpha_a + g_b*alpha_b*(1-alpha_a))/alpha_comp;
      C[i*width*4+j*4+2] = (b_a*alpha_a + b_b*alpha_b*(1-alpha_a))/alpha_comp;
      C[i*width*4+j*4+3] = alpha_comp*255.0;

    }

  }      
}
