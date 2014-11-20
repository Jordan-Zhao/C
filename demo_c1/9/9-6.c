#include<SDL.h>                    /*使用SDL库，需要包含SDL库的头文件*/
#include<stdlib.h>
void ShowBMP(char *pn,SDL_Surface * screen,int x,int y)	/*显示位图*/
{
		SDL_Surface *image;                                     	/*指向图片的指针*/
		SDL_Rect dest;                                           	/*目标矩形*/	
		image=SDL_LoadBMP(pn);                                 	/*加载位图*/
		if(image==NULL)                                    		/*加载位图失败*/
		{
			fprintf(stderr,"无法加载 %s:%s\n",pn,SDL_GetError());
			return;
		}
		dest.x=x;                                           	/*目标对象的位置坐标*/
		dest.y=y;
		dest.w=image->w;                                  	/*目标对象的大小*/
		dest.h=image->h;
		SDL_BlitSurface(image,NULL,screen,&dest);   	/*把目标对象快速转化*/
		SDL_UpdateRects(screen,1,&dest);              	/*更新目标*/
}

int main(){
		SDL_Surface *screen;                     	/*屏幕指针*/
		int x,y;                                   	/*用来计算目标对象的坐位位置*/
		if(SDL_Init(SDL_INIT_VIDEO)<0){       	/*初始化视频子系统*/
			fprintf(stderr,"无法初始化SDL: %s\n",SDL_GetError());
		exit(1);
		}
		screen=SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);  /*设置视频模式*/
		if(screen==NULL){
			fprintf(stderr,"无法设置640X480X16位色的视频模式 %s\n",SDL_GetError());
		}
		atexit(SDL_Quit);          /*在任何需要退出的时候退出，一般放在初始化之后*/
        for(x=80;x<=480;x+=80)              /*用两个for循环把图片排列起来*/
           for(y=60;y<360;y+=60)
             {
                ShowBMP("b.bmp",screen,x,y);
             }
		SDL_Delay(5000);                               /*让屏幕停留5秒钟的时间*/
   return 0;
}
