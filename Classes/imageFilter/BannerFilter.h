/* 
 * HaoRan ImageFilter Classes v0.1
 * Copyright (C) 2012 Zhenjun Dai
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation.
 */

#if !defined(BannerFilter_H)
#define BannerFilter_H

#include "RadialDistortionFilter.h"
#include <vector>

using namespace std;

namespace HaoRan_ImageFilter{

class BannerFilter : public RadialDistortionFilter{
public:
	/**
	 * 0垂直方向， 1水平方向
	 */
	bool IsHorizontal;
	
    int BannerNum;

	/**
	 * 
	 * @param bannerNum  数量 
	 * @param isHorizontal  true:水平方向   false:垂直方向
	 */
	BannerFilter(int bannerNum, bool isHorizontal): BannerNum(bannerNum),IsHorizontal(isHorizontal) {};

	virtual Image process(Image imageIn)
	{
	   int width = imageIn.getWidth();
       int height = imageIn.getHeight();
       int r = 0, g = 0, b = 0;
      
       Image clone = imageIn.clone();
       clone.clearImage(0xFFCCCCCC);//Color.LTGRAY
       vector<Point*> point;
       //Point* point = new Point[BannerNum];
	   if(IsHorizontal){//水平方向   
    	   float dh = height / BannerNum; 
    	   float dw = width;
    	   for(int i = 0; i < BannerNum; i++){
			   point.push_back(new Point(0, i * dh));
	       }	
    	   for (int x = 0; x < dh; x++) {
	            for (int y = 0; y < BannerNum; y++) {
	            	for(int k = 0 ; k < dw; k++) { 		
	            		int xx = (int)point[y]->X + k;
	            	    int yy = (int)point[y]->Y + (int)(x/1.1);    
		            	r = imageIn.getRComponent(xx, yy);
		            	g = imageIn.getGComponent(xx, yy);
		            	b = imageIn.getBComponent(xx, yy);
		            	clone.setPixelColor(xx,  yy, r, g, b);
	            	}
	            }
    	   }
    	   //对图像其余部分做填充
	       for(int xx = 0; xx < width; xx++){
	    	   for(int yy = (int)point[BannerNum-1]->Y + dh; yy <height ; yy++){
	            	r = imageIn.getRComponent(xx, yy);
	            	g = imageIn.getGComponent(xx, yy);
	            	b = imageIn.getBComponent(xx, yy);
	            	clone.setPixelColor(xx, yy, r, g, b);
      	       }
	       }	
       }
       else{//垂直方向
    	   int dw = width / BannerNum;	
    	   int dh = height;
           for(int i = 0; i < BannerNum; i++){
			   point.push_back(new Point(i * dw, 0));
	       }	       
	       for (int x = 0; x < dw; x++) {
	            for (int y = 0; y < BannerNum; y++) {
	            	for(int k = 0 ; k < dh; k++) {
                		int xx = (int)point[y]->X + (int)(x/1.1);
	            	    int yy = (int)point[y]->Y + k;
	                	r = imageIn.getRComponent(xx, yy);
		            	g = imageIn.getGComponent(xx, yy);
		            	b = imageIn.getBComponent(xx, yy);
		            	clone.setPixelColor(xx,  yy, r, g, b);
	            	}
	            }
	       }   
	       //对图像其余部分做填充
	       for(int yy = 0; yy < height; yy++){
	    	   for(int xx = (int)point[BannerNum-1]->X + dw; xx < width ; xx++){
	            	r = imageIn.getRComponent(xx, yy);
	            	g = imageIn.getGComponent(xx, yy);
	            	b = imageIn.getBComponent(xx, yy);
	            	clone.setPixelColor(xx, yy, r, g, b);
      	       }
	       }	
	   }
#ifndef WIN32 //only for apple ios
       clone.copyPixelsFromBuffer();
#endif
       return clone;  
	}
};

}// namespace HaoRan
#endif