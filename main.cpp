#include "graphics.h"
#define titikawal 1
#define titikakhir 4
#define resolusiX 400
#define resolusiY 400
#include <math.h>
#include <iostream.h>
#include <string.h>
#include <vector.h>
int X1, Y1, X2, Y2;
void dda(int warna);
void bressenham(int warna);
void translasi(int x, int y);
void rotasi(float deg);
void skala(float pengaliX, float pengaliY);
using namespace std;
int main(int argc, char* argv[])
{
     char algoritma;
     string aksi[10];
     int jmlAksi = 0;
     for(int i = 1; i < argc; i++) 
     {
          if(!strcmp(argv[i],"-a"))
              if(strcmp(argv[i+1],"dda") && strcmp(argv[i+1],"bressenham"))
              {
                  printf("input error, harus menggunakan algoritma 'dda' atau 'bressenham'.\n");
                  break;     
              }else if(!strcmp(argv[i+1], "dda"))
                    algoritma = 'd', i++;
              else
                    algoritma = 'b', i++;
          else if(!strcmp(argv[i], "-p"))
          {
               X1 = atoi(argv[i+1]);
               Y1 = atoi(argv[i+2]);
               X2 = atoi(argv[i+3]);
               Y2 = atoi(argv[i+4]);
               i += 4;
          }else if(!strcmp(argv[i],"-t"))
          {
                for(i = i +1; i < argc; i++) 
                        aksi[jmlAksi++] = argv[i];              
          }   
     }
     printf("algoritma : %s\n",(algoritma == 'd')?"DDA":"Bressenham");
     printf("x1 : %d, y1 : %d, x2 : %d, y2 : %d\n", X1, Y1, X2, Y2);
     printf("aksi : \n");  
   
     initwindow(resolusiX, resolusiY, ".::Tugas 2 Komputer Grafik Kelompok 1::.");

     if(algoritma == 'd')
         dda(titikawal);
     else
         bressenham(titikawal);
     
     for(int i = 0; i < jmlAksi; i++)
     {
         if(aksi[i][0] == 'T')
         {
              int yz = aksi[i].find(",");
              if(yz > 0)
                 translasi(atoi(aksi[i].substr(2,aksi[i].find(",")-2).c_str()),atoi(aksi[i].substr(aksi[i].find(",")+1,aksi[i].size()-aksi[i].find(",")-1).c_str()));
              else
                 translasi(atoi(aksi[i].substr(2,aksi[i].size()-3).c_str()),atoi(aksi[i].substr(2,aksi[i].size()-3).c_str()));
         }else if(aksi[i][0] == 'R')
         {
               rotasi(atoi(aksi[i].substr(2,aksi[i].size()-3).c_str()));
         }else if(aksi[i][0] == 'S')
         {
              int yz = aksi[i].find(",");
              if(yz > 0)
                 skala(atof(aksi[i].substr(2,aksi[i].find(",")-2).c_str()),atof(aksi[i].substr(aksi[i].find(",")+1,aksi[i].size()-aksi[i].find(",")-1).c_str()));
              else
                 skala(atof(aksi[i].substr(2,aksi[i].size()-3).c_str()),atof(aksi[i].substr(2,aksi[i].size()-3).c_str()));
         }
            
     }
      
     if(algoritma == 'd')
         dda(titikakhir);
     else
         bressenham(titikakhir);    
     system("PAUSE");
     return 0;
}

void dda(int warna)
{   
     float r = 0;
     if(abs(X2-X1) >= abs(Y2-Y1))
          r = (X2 > X1)?(X2 - X1):(X1 - X2);
     else
         r = (Y2 > Y1)?(Y2 - Y1):(Y1-Y2);
     
     float xr = (X2 - X1) / r;
     float yr = (Y2 - Y1) / r;
     
     float x = X1, y = Y1;
     
     while(((X2 > X1)?(x < X2):(x > X2)) || ((Y2 > Y1)?(y < Y2):(y > Y2)))
     {
         x = (float)x + xr;
         y = (float)y + yr;
         putpixel(round(x),resolusiY - round(y),warna);
     }
}

void bressenham(int warna)
{
     float Dx = X2 - X1, Dy = Y2 - Y1, d2, x = X1, y = Y1, d1, e;
     if(abs(X2-X1) >= abs(Y2-Y1))
     {
          d2 = (2 * Dy) - (2 * Dx);         
          d1 = 2 * Dy;
          e = d1 - Dx; 
          putpixel(x,resolusiY - y,titikawal);
          while((X2 > X1)?(x <= X2):(x >= X2))
          {
               if((Y2 >= Y1)?(e >= 0):(e <= 0)) 
               {
                    e = e + d2;
                    y = (Y2 > Y1)?(y + 1):(y - 1);
               }else
                    e = e + d1;   
               x = (X2 > X1)?(x + 1):(x - 1);
               putpixel(x,resolusiY - y,warna);
          }
     }else
     {
          d1 = 2 * Dx;
          d2 = (2 * Dx) - (2 * Dy);
          e = d1 - Dy;
          putpixel(x,resolusiY - y,titikawal);
          while((Y2 > Y1)?(y <= Y2):(y >= Y2))
          {
               if((X2 >= X1)?(e >= 0):(e <= 0)) 
               {
                    e = e + d2;
                    x = (X2 > X1)?(x + 1):(x - 1);
               }else
                    e = e + d1;   
               y = (Y2 > Y1)?(y + 1):(y - 1);
               putpixel(x,resolusiY - y,warna);
          }
     }  
}
void translasi(int x, int y)
{
     printf(" - Translasi x : %d, y : %d\n", x, y);
     X1 += x; Y1 += y; X2 += x; Y2 += y;
}

void rotasi(float deg)
{
     printf(" - Rotasi %.0fdeg\n",deg);
     int X1r, X2r, Y1r, Y2r;
     deg *= 3.14159265/180;
     X1r = X1 * cos(deg) - Y1 * sin(deg);
     Y1r = X1 * sin(deg) + Y1* cos(deg);
     
     X2r = X2 * cos(deg) - Y2 * sin(deg);
     Y2r = X2 * sin(deg) + Y2 * cos(deg);
     X1 = X1r; Y1 = Y1r; X2 = X2r; Y2 = Y2r;
}
  
void skala(float pengaliX, float pengaliY)
{
     printf(" - Skala x:%f, y:%f\n",pengaliX, pengaliY);
     X1 *= pengaliX; X2 *= pengaliX; Y1 *= pengaliY; Y2 *= pengaliY;
}     


