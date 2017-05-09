#include"CameraControl.h"
#include<hgl/graph/Render.h>

const Vector3f  eye(100,100,80),
                center(0,0,0),
                up_vector(0,0,1),
                forward_vector(0,1,0);

CameraControlFlowObject::CameraControlFlowObject()
{
	cam.fov=45.0f;
	cam.znear=4.0f;
	cam.zfar=1000.0f;
    
    cam.width=GetScreenWidth();
    cam.height=GetScreenHeight();

	cam.eye=eye;
	cam.center=center;
	cam.world_up_vector=up_vector;
    cam.local_up_vector=up_vector;
    cam.local_forward_vector=forward_vector;

	step=0.01f;

	memset(mouse_down,0,sizeof(mouse_down));
}

void CameraControlFlowObject::OnResize(int w,int h)
{
    cam.width=w;
    cam.height=h;
}

bool CameraControlFlowObject::OnMouseMove(int x,int y)
{
	mouse_coord.Set(x,y);

	if(mouse_down[mbRight])
	{
		const Vector2f move=(mouse_coord-push_coord[mbRight])/500.0;

		cam.center=push_center[mbRight];
		cam.eye=push_eye[mbRight];

		cam.Forward(move[1]);
		cam.Left(move[0]);
	}
	else
	if(mouse_down[mbLeft])
	{
		const Vector2f move=(mouse_coord-push_coord[mbLeft])/10;

		cam.center=push_center[mbLeft];
		cam.eye=push_eye[mbLeft];

		cam.CenterRightRotate(move[0]);
		cam.CenterUpRotate(move[1]);
	}

	return(true);
}

bool CameraControlFlowObject::OnMouseWheel(int,int wheel)
{
	cam.Distance(wheel>0?0.9f:1.1f);

	return(true);
}

bool CameraControlFlowObject::OnMouseDown(MouseButton index)
{
	mouse_down[index]=true;

	push_coord[index]=mouse_coord;

	push_center[index]=cam.center;
	push_eye[index]=cam.eye;

	return(true);
}

bool CameraControlFlowObject::OnMouseUp(MouseButton index)
{
    mouse_down[index]=false;
    return(true);
}

bool CameraControlFlowObject::OnKeyDown(KeyboardButton key)
{
	if(key==kbPageUp	)cam.Distance(0.9f);	else	//����
	if(key==kbPageDown	)cam.Distance(1.1f);	else	//��Զ

	if(key==kbUp		)cam.UpRotate();		else	//������Ϊ����������ת
	if(key==kbDown		)cam.DownRotate();		else	//������Ϊ����������ת
	if(key==kbLeft		)cam.LeftRotate();		else	//������Ϊ����������ת
	if(key==kbRight		)cam.RightRotate();		else	//������Ϊ����������ת

	if(key==kbNum8		)cam.CenterUpRotate();		else	//��Ŀ���Ϊ����������ת
	if(key==kbNum2		)cam.CenterDownRotate();	else	//��Ŀ���Ϊ����������ת
	if(key==kbNum4		)cam.CenterLeftRotate();	else	//��Ŀ���Ϊ����������ת
	if(key==kbNum6		)cam.CenterRightRotate();	else	//��Ŀ���Ϊ����������ת

	if(key==kbEnter		)								//��λ
	{
		cam.eye=eye;
		cam.center=center;
		cam.world_up_vector=up_vector;
        cam.local_up_vector=up_vector;
        cam.local_forward_vector=forward_vector;
	}
	else
	if(key==kbMinus		)step*=0.9f;else				//-�ţ�����
	if(key==kbEquals	)step*=1.1f;else				//=�ţ�����

	if(key==kbW         )cam.Forward(step);else
	if(key==kbS         )cam.Backward(step);else
	if(key==kbA         )cam.Left(step);else
	if(key==kbD         )cam.Right(step);else
		return(false);

	return(true);
}

void CameraControlFlowObject::Update()
{
	MakeCameraMatrix(&proj,&mv,&cam);					//���������������proj/look����
}
