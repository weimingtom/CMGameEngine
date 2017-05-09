﻿#ifndef HGL_WINDOW_INCLUDE
#define HGL_WINDOW_INCLUDE

#include<hgl/type/Vertex2.h>
#include<hgl/type/BaseString.h>
#include<hgl/object/RootFlowControl.h>
namespace hgl
{
    namespace platform
    {
        /**
        * 应用程序窗口基类
        */
        class Window
        {
        protected:

            OSString caption;
            bool full_screen;
            Vertex2i mouse_coord;

            int width,height;

            int GetWidth()const{return width;}
            int GetHeight()const{return height;}

            const bool GetFullScreen()const{return full_screen;}
            const Vertex2i &GetMouseCoord()const{return mouse_coord;}

        public:

            Property<bool>			FullScreen;															///<是否全屏状态
            Property<Vertex2i>      MouseCoord;                                                         ///<鼠标坐标
            Property<int>			Width;																///<窗口宽度
            Property<int>			Height;																///<窗口高度
            Property<bool>			SystemCursor;														///<是否使用系统光标

        public:	//方法

            Window();																					///<本类构造函数
            virtual ~Window()=default;                                                                  ///<本类析构函数

            virtual void ToMin()=0;																        ///<窗口最小化
            virtual void ToMax()=0;																        ///<窗口最大化

            virtual void Show()=0;																		///<显示窗口
            virtual void Hide()=0;																		///<隐藏窗口

            virtual const OSString &GetCaption()const{return caption;}
            virtual void SetCaption(const OSString &)=0;

        public:	//被实际操作系统接口层所调用的函数，在不了解的情况下请不要使用

            virtual void SetMouseCoord(const Vertex2i &coord){mouse_coord=coord;}						///<设置鼠标坐标
            virtual void SetSize(int w,int h)=0;														///<设置窗口大小

            virtual void MakeToCurrent()=0;																///<切换到当前
            virtual void SwapBuffer()=0;																///<交换缓冲区
            virtual void WaitEvent(const double &time_out=0)=0;                                         ///<等待下一个事件
            virtual void PollEvent()=0;                                                                 ///<轮询事件
            virtual bool IsOpen()=0;                                                                    ///<是否依然存在
            virtual void InitProcEvent(RootFlowControl *)=0;                                               ///<初始化事件处理接收器
        };//class Window
    }//namespace platform
}//namespace hgl
#endif//HGL_WINDOW_INCLUDE
