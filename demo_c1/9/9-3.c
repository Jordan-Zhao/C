#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_draw.h"                   		/*把SDL_draw库的头文件包含进来*/
int main()
{
    SDL_Surface *screen;  /*屏幕指针*/
    int r;                        
    if ( SDL_Init( SDL_INIT_VIDEO) < 0 ) { 	/*初始化视频子系统*/
        fprintf(stderr, "无法初始化SDL:%s\n", SDL_GetError());
        exit(1);
    }
    /*设置视频模式*/
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);  
    if ( screen == NULL ) {
        fprintf(stderr, "无法设置640x480x16位色的视频模式：%s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);   /* 退出 */
    /*画圆，点（320，240）为圆心，半径分别是65、50、35、20、5的5个同心圆，颜色为黄色*/
    for(r=5;r<=65;r+=15)
    {Draw_Circle(screen, 320,240, r, SDL_MapRGB(screen->format, 255,255,0));}
   
    SDL_UpdateRect(screen, 0, 0, 0, 0);   /* 	更新整个屏幕*/
    SDL_Delay(5000);                        	/*停留5秒钟*/
    return 0;
}
