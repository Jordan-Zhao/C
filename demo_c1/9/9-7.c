#include <SDL.h>
#include <SDL_ttf.h>           	/*添加用于显示中文字体的库的头文件*/
int main()
{  /*除了屏幕指针外，把文字也看做是一个surface，指针text指向文字屏幕*/
   SDL_Surface *text,*screen;
   SDL_Rect drect;              	/*目标矩形*/
   TTF_Font *Nfont;             	/*文字样式对象*/
   if ( SDL_Init( SDL_INIT_VIDEO) < 0 ) {	/*初始化视频子系统*/
        fprintf(stderr, "无法初始化SDL: %s\n", SDL_GetError());
        exit(1);
    }
/*设置视频模式*/
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE); 
    if ( screen == NULL ) {
        fprintf(stderr, "无法设置640x480x16位色的视频模式：%s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);	/*退出*/
    SDL_Color red={ 255, 0, 0, 0 };	/* 设置字体颜色 */
    int fontsize=38;                  	/* 设置字体大小为38 */
    if(TTF_Init()!=0){               	/* 初始化字体*/
    fprintf(stderr, "Can't init ttf font!\n");
    exit(1);
  }
/* 打开字体库*/
  Nfont=TTF_OpenFont("/usr/share/fonts/simsun.ttc",fontsize);  
  TTF_SetFontStyle(Nfont,TTF_STYLE_NORMAL);         /* 设置字体样式 */
  text=TTF_RenderUTF8_Blended(Nfont,"Linux下TrueType字体显示示例", red); 
   TTF_CloseFont(Nfont); 	/*关闭字体库*/
  TTF_Quit();          		/* 退出 */
  drect.x=240;       			/* 在点（240，160）处开始写*/
  drect.y=160;
  drect.w=text->w;                  /*目标矩形的宽和高分别是所写字的宽和高*/
  drect.h=text->h;
  SDL_BlitSurface(text, NULL, screen, &drect); 	/*把目标对象快速转化*/
  SDL_UpdateRect(screen,0,0,0,0);                	/* 更新整个屏幕 */
  SDL_FreeSurface(text);                         	/*释放写有文字的surface*/
  SDL_Delay(5000);								/*让屏幕停留5秒钟的时间*/
  return 0;
}
