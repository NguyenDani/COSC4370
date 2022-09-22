#include <iostream>
#include "BMP.h"
#include <cmath>

int main() {
  BMP bmpNew(800,800,false);
  //bmpNew.fill_region(0, 0, 500, 500, 0, 0, 0, 0);
  double y = sqrt(pow(64,2)-pow((0/12),2))*6;
  for(double i=0;i<=y*2;i+=0.05){
    double x = sqrt(pow(64,2)-pow(((i-y)/6),2))*12;
    bmpNew.set_pixel(round(x), i, 255, 255, 255, 0);    
  }
  bmpNew.write("output.bmp");
}
