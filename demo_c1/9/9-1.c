/*9-1.c程序：初始化视频子系统，设置其显示模式，背景色渐变*/
#include<SDL.h>                             	/*使用SDL库，加载该库的头文件*/
#include<stdlib.h>
int main(){
		SDL_Surface *screen;                    	/*屏幕指针*/
		Uint32 color;                             	/*定义一个颜色值*/
  	int x;
		if(SDL_Init(SDL_INIT_VIDEO)<0){         	/*初始化视频子系统失败*/
			fprintf(stderr,"无法初始化SDL：%s\n",SDL_GetError());
			exit(1);
		}
		screen=SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);  /*设置视频模式*/
		if(screen==NULL){
			fprintf(stderr,"无法设置640x480x16位色的视频模式：%s",SDL_GetError());
			exit(1);	
		}
		atexit(SDL_Quit);                            	/*退出*/
  	for(x=0;x<=255;x+=1)                        	/*用循环来实现背景色渐变*/
  	{
	 	color=SDL_MapRGB(screen->format,255,255,x);/*SDL_MapRGB函数用来设置颜色*/
   	SDL_FillRect(screen,NULL,color);            	/*填充整个屏幕*/
	 	SDL_UpdateRect(screen,0,0,0,0);             	/*更新整个屏幕*/
   	}
   	SDL_Delay(6000);                                	/*停留6秒钟的时间*/
   	return 0;
}
