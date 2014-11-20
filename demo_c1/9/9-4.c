#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_draw.h"                        	/*把SDL_draw库的头文件包含进来*/
int main()
{
    SDL_Surface *screen;						/*屏幕指针*/
    if ( SDL_Init( SDL_INIT_VIDEO) < 0 ) {	/*初始化视频子系统*/
        fprintf(stderr, "无法初始化SDL: %s\n", SDL_GetError());
        exit(1);
    }
    /*设置视频模式*/
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);  
        if ( screen == NULL ) {
        fprintf(stderr,"无法设置640x480x16位色的视频模式：%s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);	/*退出*/
    /*画矩形，左上角顶点（80，180），宽和高分别是160和120，颜色为白色*/
    Draw_Rect(screen,80,180,160,120,SDL_MapRGB(screen->format,255,255,255));
    /*画两个矩形，重叠，黄边红色填充效果*/
    Draw_Rect(screen,319,179,242,122,SDL_MapRGB(screen->format,255,255,0));
    Draw_FillRect(screen,320,180,240,120,SDL_MapRGB(screen->format,255,0,0));
    SDL_UpdateRect(screen, 0, 0, 0, 0);	/*更新整个屏幕*/
    SDL_Delay(5000);						/*停留5秒钟*/
    return 0; 
}
