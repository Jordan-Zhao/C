#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "SDL_draw.h"                   	/*包含SDL_draw库的头文件*/
int main()
{
int i;
double y;
    SDL_Surface *screen;                  	/*屏幕指针*/
    if ( SDL_Init( SDL_INIT_VIDEO) < 0 ) {            /*初始化视频子系统失败*/
        fprintf(stderr, "无法初始化: %s\n", SDL_GetError());
        exit(1);
}
/*设置视频模式*/
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if ( screen == NULL ) {
        fprintf(stderr, "无法设置640x480x16位色的视频模式：%s\n", SDL_GetError());
        exit(1);
    }
atexit(SDL_Quit);      /*退出*/
/*画直线，从点（240，180）到点（400，300），颜色为白色*/
Draw_Line(screen,240,180,400,300,SDL_MapRGB(screen->format,255,255,255));
/*画直线，从点（400，180）到点（240，300），颜色为红色*/
    Draw_Line(screen,400,180,240,300,SDL_MapRGB(screen->format,255,0,0));
for(i=0;i<=640;i+=2)
{
y=240-120*sin(3.14*i/180);
Draw_Pixel(screen,i,y,SDL_MapRGB(screen->format,0,255,0));
}
SDL_UpdateRect(screen, 0, 0, 0, 0);                  /*更新整个屏幕*/
    SDL_Delay(5000);                                     /*停留5秒钟*/
    return 0;
}
