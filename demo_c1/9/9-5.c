#include <SDL.h>
#include <stdlib.h>
#include <string.h>
#include "SDL_draw.h"
int main()
{
    SDL_Surface *screen;
    if ( SDL_Init( SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "无法初始化SDL: %s\n ", SDL_GetError());
        exit(1);
    }
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    if ( screen == NULL ) {
        fprintf(stderr, "无法设置640x480x16位色的视频模式：%s\n ", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);
    //画水平直线，起点（240，240），x方向上偏移到400，颜色为白色
    Draw_HLine(screen, 240,240, 400,SDL_MapRGB(screen->format, 255,255,255));
    //画垂直直线，起点（320，180），y方向上偏移到300，颜色为红色
    Draw_VLine(screen, 320,180, 300,SDL_MapRGB(screen->format, 255,0,0));
    //画椭圆，圆心（240，180），x轴径76，y轴径56，颜色为蓝色
    Draw_Ellipse(screen,240,180,76,56,SDL_MapRGB(screen->format, 0,0,255));
    //填充椭圆，规格和以上相同
    Draw_FillEllipse(screen,400,300,76,56,SDL_MapRGB(screen->format, 0,0,255));
    //画圆角矩形，左上角坐标为（322，122），宽为156，高为116，圆角的半径为10，颜色为绿色
    Draw_Round(screen,322,122,156,116,10,SDL_MapRGB(screen->format, 0,255,0));
    //填充以上规格的圆角矩形
    Draw_FillRound(screen,162,242,156,116,10,SDL_MapRGB(screen->format, 0,255,0));
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    SDL_Delay(5000);
    return 0;
}
