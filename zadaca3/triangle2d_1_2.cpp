#include <iostream>
#include <cmath>
#include <algorithm>
#include "tgaimage.h"
using namespace std;

class Point{
    public:
    int x, y;
    Point(){}
    Point(int x, int y):x(x),y(y){}
};

void set_color(int x, int y, TGAImage &image, TGAColor color)
{
    image.set(y, x, color);    
}

int edgefunction(Point a, Point b, Point c){
    return ((b.x-a.x)*(c.y-a.y) - (b.y - a.y)*(c.x - a.x));
}



void draw_triangle_2d(Point a, Point b, Point c,TGAImage &image, TGAColor color ){
    Point p{0,0};

    int minab_x = min (a.x,b.x);
    int minX = min (minab_x, c.x);

    int minab_y = min (a.y,b.y);
    int minY = min (minab_y, c.y);

    int maxab_x = max (a.x,b.x);
    int maxX = max (minab_x, c.x);

    int maxab_y = max (a.y,b.y);
    int maxY = max (minab_y, c.y);

    
    int ABC = edgefunction(a, b, c); 

    for (p.y = minY; p.y < maxY; p.y++){
        for (p.x = minX; p.x < maxX; p.x++){

            int ABP = edgefunction(a, b, p);
            int BCP = edgefunction(b, c, p);
            int CAP = edgefunction(c, a, p);

            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                set_color(p.x,p.y, image, color);

                
            }

        }
    

    }

    
}
void draw_triangle_2d_gouraud(Point a, Point b, Point c,TGAImage &image, TGAColor colorA, TGAColor colorB, TGAColor colorC ){
    Point p{0,0};

    int minab_x = min (a.x,b.x);
    int minX = min (minab_x, c.x);

    int minab_y = min (a.y,b.y);
    int minY = min (minab_y, c.y);

    int maxab_x = max (a.x,b.x);
    int maxX = max (minab_x, c.x);

    int maxab_y = max (a.y,b.y);
    int maxY = max (minab_y, c.y);

    
    int ABC = edgefunction(a, b, c); 

    for (p.y = minY; p.y < maxY; p.y++){
        for (p.x = minX; p.x < maxX; p.x++){

            int ABP = edgefunction(a, b, p);
            int BCP = edgefunction(b, c, p);
            int CAP = edgefunction(c, a, p);
            

            float weightA = BCP/ABC;
            float weightB = CAP/ABC;
            float weightC = ABP/ABC;


            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                unsigned char r = colorA.r * weightA + colorB.r* weightB + colorC.r* weightC;
                unsigned char g = colorA.g * weightA + colorB.g* weightB + colorC.g* weightC;
                unsigned char b = colorA.b * weightA + colorB.b* weightB + colorC.b* weightC;
                TGAColor T{r,g,b, 255};
                set_color(p.x,p.y, image, T);

                
            }

        }
    

    }

    
}

// dimenzije slike
const int width  = 512;
const int height = 512;

// definirajmo boje
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0, 0, 255);
const TGAColor blue  = TGAColor(0, 0, 255, 255);
const TGAColor green  = TGAColor(0, 255, 0, 255);

int main(){
    TGAImage image(width, height, TGAImage::RGB);
    
    // nacrtaj nekoliko duzina    
    Point a1{400,400};
    Point b1{60,200};
    Point c1{200,105};
    
    Point a2{200,80};
    Point b2{100,60};
    Point c2{400,500};
    draw_triangle(a1,b1,c1, image, white);
    draw_triangle_gouraud(a2, b2, c2, image, red, blue, green);

    Point a3{110,110};
    Point b3{10,100};
    Point c3{30,20};

    draw_triangle(a3,b3,c3,image, red);



    // spremi sliku 
    image.flip_vertically();
    image.write_tga_file("triangle1.tga");
}