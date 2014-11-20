/*9.10程序：游戏*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>                           	//需要产生随机数，加载时间头文件
#include <SDL.h>
#ifdef macintosh                            	//对导入数据时分隔符的控制
#define DIR_SEP	":"
#define DIR_CUR ":"
#else
#define DIR_SEP	"/"
#define DIR_CUR	""
#endif
#define DATAFILE(X)	DIR_CUR "data" DIR_SEP X
#define	FRAMES_PER_SEC	10                 	//每秒钟的帧数
#define cannon_SPEED	5                  	//大炮运动速度
#define MAX_SHOTS	1                       	//最多可以发射多少发炮弹
#define SHOT_SPEED	10                      	//炮弹的速度
#define MAX_airs	2                       	//最多出现多少架飞机
#define AIR_SPEED	5                       	//飞机的速度
#define AIR_ODDS	(1*FRAMES_PER_SEC)		//剩下的飞机数
#define EXPLODE_TIME	4					//爆炸时间

typedef struct {							//对象结构体
		int alive;								//是否存活标志
		int facing;								//运动方向
		int x, y;								//坐标
		SDL_Surface *image;						//图像指针
} object;	
SDL_Surface *screen;							//屏幕指针
SDL_Surface *background;						//背景指针
object cannon;									//大炮对象
int reloading;									//重新加载标志
object shots[MAX_SHOTS];						//炮弹对象
object airs[MAX_airs];							//飞机对象
object explosions[MAX_airs+1];					//爆炸对象
#define MAX_UPDATES	3*(1+MAX_SHOTS+MAX_airs)	//最大更新次数
int numupdates;									//更新次数的变量
SDL_Rect srcupdate[MAX_UPDATES];				//源目标更新
SDL_Rect dstupdate[MAX_UPDATES];				//目标更新
struct blit {									//定义快速重绘对象结构体
		SDL_Surface *src;
		SDL_Rect *srcrect;
		SDL_Rect *dstrect;
} blits[MAX_UPDATES];
SDL_Surface *LoadImage(char *datafile)		//加载图片函数
{
		SDL_Surface *image, *surface;
		image = SDL_LoadBMP(datafile);			//用SDL_LoadBMP()函数加载图片
		if ( image == NULL ) {
			fprintf(stderr, "Couldn't load image %s: %s\n",
						datafile,SDL_GetError());
			return(NULL);
		}
		surface = SDL_DisplayFormat(image);			//用图片的形式显示
		SDL_FreeSurface(image);						//释放图片
		return(surface);
}
int LoadData(void)								//加载数据
{
		int i;
		cannon.image = LoadImage(DATAFILE("cannon.bmp"));	//加载大炮图片
		if ( cannon.image == NULL ) {
			return(0);
		}
		shots[0].image = LoadImage(DATAFILE("shot.bmp"));	//加载炮弹图片
		if ( shots[0].image == NULL ) {
			return(0);
		}
		for ( i=1; i<MAX_SHOTS; ++i ) {
			shots[i].image = shots[0].image;
		}
		airs[0].image = LoadImage(DATAFILE("air.bmp"));	//加载飞机图片
		if ( airs[0].image == NULL ) {
			return(0);
		}
		for ( i=1; i<MAX_airs; ++i ) {
			airs[i].image = airs[0].image;
		}
		explosions[0].image = LoadImage(DATAFILE("explosion.bmp"));//加载爆炸图片
		for ( i=1; i<MAX_airs+1; ++i ) {
			explosions[i].image = explosions[0].image;
		}
		background = LoadImage(DATAFILE("background.bmp"));//加载背景图片
		//设置更新目标矩形的指针
		for ( i=0; i<MAX_UPDATES; ++i ) {
			blits[i].srcrect = &srcupdate[i];
			blits[i].dstrect = &dstupdate[i];
		}
		return(1);
}
void FreeData(void)			//释放数据
{
		int i;
		SDL_FreeSurface(cannon.image);				//释放大炮图片
		SDL_FreeSurface(shots[0].image);			//释放炮弹图片
		SDL_FreeSurface(airs[0].image);				//释放飞机图片
		SDL_FreeSurface(explosions[0].image);		//释放爆炸图片
		SDL_FreeSurface(background);				//最后释放背景图片
}
void CreateAir(void)							//产生一架新的飞机
{
		int i;
		for ( i=0; i<MAX_airs; ++i ) {	//当飞机数没有达到最大值，并且存活值为1时，产生一架新的飞机
			if ( ! airs[i].alive )
				break;
		}
		if ( i == MAX_airs ) {    	//已经到达最大值就返回，不产生
			return;
		}
		do {                          	//用随机函数产生三个数，分别用来标记运动方向
			airs[i].facing = (rand()%3)-1;
		} while ( airs[i].facing == 0 );
		airs[i].y = 0;//确定飞机初始时的y方向上的位置，0即表示屏幕的上部
		if ( airs[i].facing < 0 ) {//如果飞机方向小于0，即反方向，飞机往左边移动
			airs[i].x = screen->w-airs[i].image->w-1;
		} else {
			airs[i].x = 0;
		}
		airs[i].alive = 1;
}
void DrawObject(object *sprite)			//画对象
{
		struct blit *update;

		update = &blits[numupdates++];
		update->src = sprite->image;
		update->srcrect->x = 0;				//根据源目标的大小和位置坐标来画
		update->srcrect->y = 0;
		update->srcrect->w = sprite->image->w;
		update->srcrect->h = sprite->image->h;
		update->dstrect->x = sprite->x;
		update->dstrect->y = sprite->y;
		update->dstrect->w = sprite->image->w;
		update->dstrect->h = sprite->image->h;
}
void EraseObject(object *sprite)		//消除目标
{
		struct blit *update;
		int wrap;
		//背景水平重叠达到清除画面效果
		update = &blits[numupdates++];
		update->src = background;
		update->srcrect->x = sprite->x%background->w;
		update->srcrect->y = sprite->y;
		update->srcrect->w = sprite->image->w;
		update->srcrect->h = sprite->image->h;
		wrap = (update->srcrect->x+update->srcrect->w)-(background->w);
		if ( wrap > 0 ) {
			update->srcrect->w -= wrap;
		}
		update->dstrect->x = sprite->x;
		update->dstrect->y = sprite->y;
		update->dstrect->w = update->srcrect->w;
		update->dstrect->h = update->srcrect->h;
		//一个背景一个背景的把屏幕重绘
		if ( wrap > 0 ) {
			update = &blits[numupdates++];
			update->src = background;
			update->srcrect->x = 0;
			update->srcrect->y = sprite->y;
			update->srcrect->w = wrap;
			update->srcrect->h = sprite->image->h;
			update->dstrect->x =((sprite->x/background->w)+1)*background->w;
			update->dstrect->y = sprite->y;
			update->dstrect->w = update->srcrect->w;
			update->dstrect->h = update->srcrect->h;
		}
}
void UpdateScreen(void)			//更新屏幕
{
		int i;
		for ( i=0; i<numupdates; ++i ) {
			SDL_LowerBlit(blits[i].src, blits[i].srcrect,
							screen, blits[i].dstrect);
		}
		SDL_UpdateRects(screen, numupdates, dstupdate);
		numupdates = 0;
}
int Collide(object *sprite1, object *sprite2)	//两个物体碰撞的情况
{
		if ( (sprite1->y >= (sprite2->y+sprite2->image->h)) ||
		     (sprite1->x >= (sprite2->x+sprite2->image->w)) ||
		     (sprite2->y >= (sprite1->y+sprite1->image->h)) ||
		     (sprite2->x >= (sprite1->x+sprite1->image->w)) ) {
			return(0);
		}
		return(1);
		     
}
void WaitFrame(void)
{
		static Uint32 next_tick = 0;
		Uint32 this_tick;
		this_tick = SDL_GetTicks(); //得到当前时间值
		if ( this_tick < next_tick ) {
			SDL_Delay(next_tick-this_tick);//延时时间
		}
		next_tick = this_tick + (1000/FRAMES_PER_SEC);//下一帧
}
void RunGame(void)			//开始游戏
{
		int i, j;
		SDL_Event event;		//SDL事件
		Uint8 *keys;
		numupdates = 0;
		SDL_Rect dst;			//开始把背景画上去
		dst.x = 0;
		dst.y = 0;
		dst.w = background->w;
		dst.h = background->h;
		SDL_BlitSurface(background, NULL, screen, &dst);
		SDL_UpdateRect(screen, 0, 0, 0, 0);			//更新屏幕
		cannon.alive = 1;   //初始化大炮参数，存活，位置和运动方向
		cannon.x = (screen->w - cannon.image->w)/2;
		cannon.y = (screen->h - cannon.image->h) -1;
		cannon.facing = 0;
		DrawObject(&cannon);	//画大炮
		for ( i=0; i<MAX_SHOTS; ++i ) {		//初始化炮弹的存活参数
			shots[i].alive = 0;
		}
		for ( i=0; i<MAX_airs; ++i ) {		//初始化飞机的存活参数
			airs[i].alive = 0;
		}
		CreateAir();				//产生飞机
		DrawObject(&airs[0]);   	//画飞机
		UpdateScreen();
		while ( cannon.alive ) {	//当大炮没有被炸毁的时候，游戏正常进行
			WaitFrame();
			while ( SDL_PollEvent(&event) ) {     	//循环接受键盘事件，直到退出
				if ( event.type == SDL_QUIT )
					return;
			}
			keys = SDL_GetKeyState(NULL);          	//得到键盘键的状态
			for ( i=0; i<MAX_SHOTS; ++i ) {			//清除炮弹
				if ( shots[i].alive ) {
					EraseObject(&shots[i]);
				}
			}
			for ( i=0; i<MAX_airs; ++i ) {	//清除飞机
				if ( airs[i].alive ) {
					EraseObject(&airs[i]);
				}
			}
			EraseObject(&cannon);
			for ( i=0; i<MAX_airs+1; ++i ) {	//清除爆炸
				if ( explosions[i].alive ) {
					EraseObject(&explosions[i]);
				}
			}
			for ( i=0; i<MAX_airs+1; ++i ) {	//爆炸次数记录，并减少
				if ( explosions[i].alive ) {
					--explosions[i].alive;
				}
			}
			if ( (rand()%AIR_ODDS) == 0 ) {		//产生新的飞机
				CreateAir();
			}
			if ( ! reloading ) {				//产生新的炮弹
				if ( keys[SDLK_SPACE] == SDL_PRESSED ) {//按下空格键，发射
					for ( i=0; i<MAX_SHOTS; ++i ) {
						if ( ! shots[i].alive ) {
							break;
						}
					}
					if ( i != MAX_SHOTS ) {        //炮弹移动轨迹
						shots[i].x = cannon.x +
						 (cannon.image->w-shots[i].image->w)/2;
						shots[i].y = cannon.y -
								  shots[i].image->h;
						shots[i].alive = 1;
					}
				}
			}
			reloading = (keys[SDLK_SPACE] == SDL_PRESSED);
			cannon.facing = 0;         	//移动大炮
			if ( keys[SDLK_RIGHT] ) {  	//右方向键向右运动
				++cannon.facing;
			}
			if ( keys[SDLK_LEFT] ) {   	//左方向键向左运动
				--cannon.facing;
			}
			cannon.x += cannon.facing*cannon_SPEED;         //计算移动的位移
			if ( cannon.x < 0 ) {
				cannon.x = 0;
			} else
			if ( cannon.x >= (screen->w-cannon.image->w) ) {//两边碰头的处理
				cannon.x = (screen->w-cannon.image->w)-1;
			}
			for ( i=0; i<MAX_airs; ++i ) {//移动飞机
				if ( airs[i].alive ) {
					airs[i].x += airs[i].facing*AIR_SPEED;	//计算飞机位移
					if ( airs[i].x < 0 ) {					//飞机两边碰头的计算
						airs[i].x = 0;
						airs[i].y += airs[i].image->h;
						airs[i].facing = 1;
					} else
					if ( airs[i].x >=
						   (screen->w-airs[i].image->w) ) {
						airs[i].x =
						   (screen->w-airs[i].image->w)-1;
						airs[i].y += airs[i].image->h;
						airs[i].facing = -1;
					}
				}
			}
			for ( i=0; i<MAX_SHOTS; ++i ) {		//炮弹的移动
				if ( shots[i].alive ) {
					shots[i].y -= SHOT_SPEED;  	//计算炮弹位移
					if ( shots[i].y < 0 ) {
						shots[i].alive = 0;
					}
				}
			}
			for ( j=0; j<MAX_SHOTS; ++j ) {		//处理碰撞
				for ( i=0; i<MAX_airs; ++i ) {
					if ( shots[j].alive && airs[i].alive &&
						  Collide(&shots[j], &airs[i]) ) {
						airs[i].alive = 0;
						explosions[i].x = airs[i].x;  //如果碰撞了，出现爆炸
						explosions[i].y = airs[i].y;
						explosions[i].alive = EXPLODE_TIME;
						shots[j].alive = 0;
						break;
					}
				}
			}
			for ( i=0; i<MAX_airs; ++i ) {	//飞机和大炮碰撞的处理
				if ( airs[i].alive && Collide(&cannon, &airs[i]) ) {
					airs[i].alive = 0;
					explosions[i].x = airs[i].x;		//出现爆炸
					explosions[i].y = airs[i].y;
					explosions[i].alive = EXPLODE_TIME;
					cannon.alive = 0;
					explosions[MAX_airs].x = cannon.x;	//大炮爆炸
					explosions[MAX_airs].y = cannon.y;
					explosions[MAX_airs].alive = EXPLODE_TIME;
				}
			}
			for ( i=0; i<MAX_airs; ++i ) {		//画飞机
				if ( airs[i].alive ) {
					DrawObject(&airs[i]);
				}
			}
			for ( i=0; i<MAX_SHOTS; ++i ) {		//画炮弹
				if ( shots[i].alive ) {
					DrawObject(&shots[i]);
				}
			}
			if ( cannon.alive ) {	//画大炮
				DrawObject(&cannon);
			}
			for ( i=0; i<MAX_airs+1; ++i ) {	//画爆炸
				if ( explosions[i].alive ) {
					DrawObject(&explosions[i]);
				}
			}
			UpdateScreen();
			if ( keys[SDLK_ESCAPE] == SDL_PRESSED ) {//按下Esc退出
				cannon.alive = 0;
			}
		}
		return;
}
int main(int argc, char *argv[])
{
//初始化视频子系统
		if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
			fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
			exit(2);
		}
		atexit(SDL_Quit);
		//设置视频模式
		screen = SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
		if ( screen == NULL ) {
			fprintf(stderr, "Couldn't set 640x480 video mode: %s\n",
								SDL_GetError());
			exit(2);
		}
		srand(time(NULL));//随机时间产生器
		if ( LoadData() ) {			//加载数据
			RunGame();				//运行游戏
			FreeData();             	//释放数据
		}
		exit(0);                      	//退出
}
