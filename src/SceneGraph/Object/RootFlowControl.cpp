#include<hgl/object/RootFlowControl.h>
#include<hgl/graph/Render.h>

namespace hgl
{
    void RootFlowControl::OnClose()
    {
        FlowControl::OnClose();
        ExitApp();
    }

    void RootFlowControl::OnResize      (int w,int h)
    {
        graph::SetViewport(0,0,w,h);

        if (w > 0 && h > 0)
            graph::Ortho2DMatrix = ortho2d(w, h);

        FlowControl::OnResize(w,h);
    }
}//namespace hgl
