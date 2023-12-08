#include "demosaic.h"

int find_4sides_avg(const std::vector<unsigned char> & bayer,const int & width, const int & height,int i,int j)
{
  int avg_num = 0;
  int sum = 0;

  if(j>0&&j<width-1)
  {
    sum += bayer[i*width+j+1];
    sum += bayer[i*width+j-1];

    avg_num+=2;
  }
  else if(j==0)
  {
    sum += bayer[i*width+j+1];
    avg_num+=1;
  }
  else if (j == width-1)
  {
    sum += bayer[i*width+j-1];
    avg_num+=1;
  }

  if(i>0&&i<height-1)
  {
    sum += bayer[(i-1)*width+j];
    sum += bayer[(i+1)*width+j];

    avg_num+=2;
  }
  else if(i==0)
  {
    sum += bayer[(i+1)*width+j];
    avg_num+=1;
  }
  else if (i == height-1)
  {
    sum += bayer[(i-1)*width+j];
    avg_num+=1;
  }

  return sum/avg_num;
}

int find_leftright_avg(const std::vector<unsigned char> & bayer,const int & width, const int & height,int i,int j)
{
  int avg_num = 0;
  int sum = 0;

  if(j>0&&j<width-1)
  {
    sum += bayer[i*width+j+1];
    sum += bayer[i*width+j-1];

    avg_num+=2;
  }
  else if(j==0)
  {
    sum += bayer[i*width+j+1];
    avg_num+=1;
  }
  else if (j == width-1)
  {
    sum += bayer[i*width+j-1];
    avg_num+=1;
  }

  return sum/avg_num;
}

int find_topbottom_avg(const std::vector<unsigned char> & bayer,const int & width, const int & height,int i,int j)
{
  int avg_num = 0;
  int sum = 0;

  if(i>0&&i<height-1)
  {
    sum += bayer[(i-1)*width+j];
    sum += bayer[(i+1)*width+j];

    avg_num+=2;
  }
  else if(i==0)
  {
    sum += bayer[(i+1)*width+j];
    avg_num+=1;
  }
  else if (i == height-1)
  {
    sum += bayer[(i-1)*width+j];
    avg_num+=1;
  }
  return sum/avg_num;
}

int find_4corners_avg(const std::vector<unsigned char> & bayer,const int & width, const int & height,int i,int j)
{
  int sum = 0;
  int avg_num = 0;

  if(j>0 &&j<width-1)
  {
    if(i>0&&i<height-1)
    {
      sum = bayer[(i-1)*width+j-1]+ bayer[(i-1)*width+j+1]+ bayer[(i+1)*width+j-1]+ bayer[(i+1)*width+j+1];
      avg_num+=4;
    }
    else if(i==0)
    {
      sum =  bayer[(i+1)*width+j-1]+ bayer[(i+1)*width+j+1];
      avg_num+=2;
    }
    else if (i == height-1)
    {
      sum = bayer[(i-1)*width+j-1]+ bayer[(i-1)*width+j+1];
      avg_num+=2;
    }


  }
  else if(j ==0)
  {
    if(i>0&&i<height-1)
    {
      sum = bayer[(i-1)*width+j+1]+ bayer[(i+1)*width+j+1];
      avg_num+=2;
    }
    else if(i==0)
    {
      sum = bayer[(i+1)*width+j+1];
      avg_num+=1;
    }
    else if (i == height-1)
    {
      sum = bayer[(i-1)*width+j+1];
      avg_num+=1;
    }
  }
  else if (j==width-1)
  {
    if(i>0&&i<height-1)
    {
      sum = bayer[(i-1)*width+j-1]+ bayer[(i+1)*width+j-1];
      avg_num+=2;
    }
    else if(i==0)
    {
      sum = bayer[(i+1)*width+j-1];
      avg_num+=1;
    }
    else if (i == height-1)
    {
      sum = bayer[(i-1)*width+j-1];
      avg_num+=1;
    }
  }

  return sum/avg_num;
}


void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 1; i<height-1;i++)
  {
    for(int j = 1; j<width-1;j++)
    {
      if(i%2==0)
      {
        if(j%2==0)
        {
          //blue pixel center
          rgb[i*width*3+j*3+2] = bayer[i*width+j];

          //green
          rgb[i*width*3+j*3+1] = find_4sides_avg( bayer, width, height,i,j);

          //red
          rgb[i*width*3+j*3] = find_4corners_avg(bayer, width, height,i,j);

        }
        else
        {
          //green pixel center
          rgb[i*width*3+j*3+1] = bayer[i*width+j];

          //red
          rgb[i*width*3+j*3]= find_topbottom_avg(bayer, width, height,i,j);

          //blue
          rgb[i*width*3+j*3+2] = find_leftright_avg(bayer, width, height,i,j);

        }

      }
      else
      {
        if(j%2==0)
        {
          //green pixel center
          rgb[i*width*3+j*3+1] = bayer[i*width+j];

          //red
          rgb[i*width*3+j*3]= find_leftright_avg(bayer, width, height,i,j);

          //blue         
          rgb[i*width*3+j*3+2] = find_topbottom_avg(bayer, width, height,i,j);
        }
        else
        {
          //red pixel center
          rgb[i*width*3+j*3] = bayer[i*width+j];

          //green
          rgb[i*width*3+j*3+1] = find_4sides_avg(bayer, width, height,i,j);

          //blue
          rgb[i*width*3+j*3+2] = find_4corners_avg(bayer, width, height,i,j);
          
        }
      }
    }
  }  
}
