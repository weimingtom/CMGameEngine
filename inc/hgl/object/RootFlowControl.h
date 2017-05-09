#ifndef HGL_ROOT_FLOW_CONTROL_INCLUDE
#define HGL_ROOT_FLOW_CONTROL_INCLUDE

#include<hgl/object/FlowControl.h>
namespace hgl
{
    /**
    * ͼ��Ӧ�ø����̿�����
    */
    class RootFlowControl:public FlowControl
    {
    public: //�¼�

        using FlowControl::FlowControl;
        ~RootFlowControl()=default;

        virtual void OnClose        (               );                                              ///<���ڹر��¼�
        virtual void OnResize       (int,int        );                                              ///<���ڳߴ�����¼�
    };//class RootFlowControl
}//namespace hgl
#endif//HGL_ROOT_FLOW_CONTROL_INCLUDE
