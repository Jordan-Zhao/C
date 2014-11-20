#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char ** argv)
{
   SDL_Surface * screen;                       	//屏幕指针
SDL_Surface * image;                           	//图像指针
SDL_Event     event;                          	//事件对象
   int bAppRun = 1;			//一个内部标志参数
   int bTopBottom = 1; 		//屏幕上部
   int bLeftRight = 1;		//左右两边
   Uint32 Tstart, Tstop;	//时间开始和结束
   SDL_Rect dRect;//目标矩形
//初始化视频子系统和计时子系统
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
      fprintf(stderr, "不能初始化 %s\n", SDL_GetError());
      exit(1);
   }
   atexit(SDL_Quit);            //退出
screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE); //设置视频模式
   if (screen == NULL) {
      fprintf(stderr, "不能初始化640x480x8大小的视频模式： %s\n",
         SDL_GetError());
      exit(1);
   }
   image = SDL_LoadBMP("./b.bmp");  //加载位图
   if (image == NULL) {
      fprintf(stderr, "Couldn't load BMP, %s\n", SDL_GetError());
exit(1);
   }
   dRect.x = 0;//目标矩形的左上角坐标
   dRect.y = 0;
   dRect.w = image->w;//目标矩形的宽高是位图的宽高
   dRect.h = image->h;
   if (SDL_BlitSurface(image, NULL, screen, &dRect) < 0) {
      fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
SDL_FreeSurface(image);
      exit(1);
   }
   SDL_UpdateRect(screen, 0, 0, image->w, image->h);//更新目标矩形
   Tstart = SDL_GetTicks();//时间开始
   while (bAppRun==1) {//标志参数是1的时候，图像开始运动，其中包含了鼠标事件
     if (SDL_PollEvent(&event)) {
         switch (event.type) {
            case SDL_KEYDOWN://判断是否按下某键
             bAppRun = 0;
            break;
         }
      }        
Tstop = SDL_GetTicks();
      if ((Tstop - Tstart) > 15) { 
         Tstart = Tstop;
         SDL_FillRect(screen, &dRect, 0);
         if (bTopBottom==1) {	/*如果碰到屏幕上部或下部*/
            if ((dRect.y + dRect.h + 3) < screen->h) {
               dRect.y += 3;
            }
            else {
               bTopBottom = 0;
               dRect.y = screen->h - dRect.h;
            }
         } 
         else {
            if ((dRect.y - 3) > 0) {
               dRect.y -= 3;
            }
            else {
               bTopBottom = 1;
               dRect.y = 0;
            }
         }
         if (bLeftRight==1) {        //如果碰到右边或是左边，x坐标向左或向右
            if ((dRect.x + dRect.w + 3) < screen->w) {
               dRect.x += 3;
            }
            else {
               bLeftRight = 0;
               dRect.x = screen->w - dRect.w;
            }
         }
         else {
            if ((dRect.x - 3) > 0) {
               dRect.x -=3;
            }
            else {
               bLeftRight = 1;
               dRect.x = 0;
            }
         }	/*把目标对象快速转化*/
         if (SDL_BlitSurface(image, NULL, screen, &dRect) < 0) {
         fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError()); SDL_FreeSurface(image);
            exit(1);
         }
         SDL_Flip(screen);         //屏幕缓冲
      }
   }
   SDL_FreeSurface(image);	/*释放图像surface*/
   exit(1);
}
