/*9-9.c程序：3D效果*/
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>	                                	/*OpenGL32 库头文件*/
#include <OpenGL/glu.h>	                                	/* GLu32 库头文件*/
#else
#include <GL/gl.h>	                                     	/*OpenGL32 库头文件*/
#include <GL/glu.h>	                                     	/* GLu32 库头文件*/
#endif
#include "SDL.h"
float rquad = 0.0f;                                   	/* 设置正方体旋转角度 */
void InitGL(int Width, int Height)	                 	/*初始化GL界面*/ 
{
  glViewport(0, 0, Width, Height);			//视觉角度
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		//背景色设置
  glClearDepth(1.0);				//清除深度缓存
  glDepthFunc(GL_LESS);				//为深度测试选择不同的比较函数
  glEnable(GL_DEPTH_TEST);			//激活深度测试
  glShadeModel(GL_SMOOTH);			//启用阴影平滑
  glMatrixMode(GL_PROJECTION);     	//选择投影矩阵
  glLoadIdentity();		             	//重置投影矩阵 
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,1.0f,100.0f);	// 计算观察窗口的比例和角度等的设置，重置投影矩阵
  glMatrixMode(GL_MODELVIEW);	//指明任何新的变换将会影响modelview matrix（模型观察矩阵）
}
void DrawGLScene()//绘制
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);//清除屏幕颜色和深度缓冲 
  glLoadIdentity();				//使用当前坐标矩阵方式
  glTranslatef(0.0f,0.0f,-10.0f);  //沿着（0.0，0.0，-10.0）移动
  glRotatef(rquad,-1.0f,-1.0f,-1.0f);//正方体在xyz方向上反方向旋转
  glBegin(GL_QUADS);				// 开始绘制正方体
  //绘制顶面
  glColor3f(0.0f,1.0f,0.0f);			// 颜色为蓝色
  glVertex3f( 1.0f, 1.0f,-1.0f);		// 右上顶点
  glVertex3f(-1.0f, 1.0f,-1.0f);		// 上面，左边的顶点
  glVertex3f(-1.0f, 1.0f, 1.0f);		// 左下顶点
  glVertex3f( 1.0f, 1.0f, 1.0f);		// 右下顶点
  // 绘制底面
  glColor3f(1.0f,0.5f,0.0f);			//橘红色
  glVertex3f( 1.0f,-1.0f, 1.0f);		// 右上顶点
  glVertex3f(-1.0f,-1.0f, 1.0f);		// 左上顶点
  glVertex3f(-1.0f,-1.0f,-1.0f);		// 左下顶点
  glVertex3f( 1.0f,-1.0f,-1.0f);		// 右下顶点
  // 绘制前面
  glColor3f(1.0f,0.0f,0.0f);			// 红色
  glVertex3f( 1.0f, 1.0f, 1.0f);		// 右上顶点
  glVertex3f(-1.0f, 1.0f, 1.0f);		// 左上顶点
  glVertex3f(-1.0f,-1.0f, 1.0f);		// 左下顶点
  glVertex3f( 1.0f,-1.0f, 1.0f);		// 右下顶点
  // 绘制背面.
  glColor3f(1.0f,1.0f,0.0f);			// 黄色
  glVertex3f( 1.0f,-1.0f,-1.0f);		// 右上顶点
  glVertex3f(-1.0f,-1.0f,-1.0f);		// 左上顶点
  glVertex3f(-1.0f, 1.0f,-1.0f);		// 左下顶点
  glVertex3f( 1.0f, 1.0f,-1.0f);		// 右下顶点
  // 绘制左面
  glColor3f(0.0f,0.0f,1.0f);			// 蓝色
  glVertex3f(-1.0f, 1.0f, 1.0f);		// 右上顶点
  glVertex3f(-1.0f, 1.0f,-1.0f);		// 左上顶点
  glVertex3f(-1.0f,-1.0f,-1.0f);		// 左下顶点
  glVertex3f(-1.0f,-1.0f, 1.0f);		// 右下顶点
  // 绘制右面
  glColor3f(1.0f,0.0f,1.0f);			// 紫色
  glVertex3f( 1.0f, 1.0f,-1.0f);	    	// 右上顶点
  glVertex3f( 1.0f, 1.0f, 1.0f);		// 左上顶点
  glVertex3f( 1.0f,-1.0f, 1.0f);		// 左下顶点
  glVertex3f( 1.0f,-1.0f,-1.0f);		// 右下顶点
  glEnd();					// 绘制完毕
  rquad-=1.0f;		        // 旋转的角度逆时针方向一个单位一个单位减少
  SDL_GL_SwapBuffers();
}
int main(int argc, char **argv) 
{  
  int done;
   if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {          /*初始化视频子系统*/
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
 /*设置视频模式*/
  if ( SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) == NULL ) {
    fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
    SDL_Quit();
    exit(2);
  }
  /* Loop, drawing and checking events */
  InitGL(640, 480);                          	//初始化GL界面，640*480大小
   done = 0;                                  	//事件标志
  while ( ! done ) {
    DrawGLScene();                           	//调用绘制函数
    { SDL_Event event;						//鼠标事件，当用户按下Esc键后退出
      while ( SDL_PollEvent(&event) ) {
        if ( event.type == SDL_KEYDOWN ) {
          if ( event.key.keysym.sym == SDLK_ESCAPE ) {
            done = 1;
          }
        }
      }
    }
  }
 atexit(SDL_Quit);				//退出
SDL_Delay(5000);                 	//停留5秒钟
return 0;
}
