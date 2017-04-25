#ifndef HGL_OS_DESKTOP_INCLUDE
#define HGL_OS_DESKTOP_INCLUDE

#include<hgl/type/DataType.h>
namespace hgl
{
    /**
    * �뱾�ز���ϵͳ��ع��ܺ��������ֿռ�
    */
    namespace os		///����ϵͳ��ع������ֿռ�
    {
#if HGL_OS == HGL_OS_Windows
        void PopupWebBrowser(const u16char *);															///<������ҳ�����
        void PopupEmailClient(const u16char *, const u16char *sub = nullptr);							///<���������ʼ��ͻ���
        
        /**
        * ��ݷ�ʽ���ݽṹ
        */
        struct ShortCut
        {
            OSString lnk_filename;          ///<ע�ⲻҪ����չ��
            OSString filename;              ///<ִ�еĳ����ļ�ȫ��
            OSString work_directory;        ///<����Ŀ¼
            OSString param;                 ///<����
            OSString icon_filename;         ///<ͼ���ļ�
            OSString descript;              ///<��ע
        };//struct ShortCut

        bool CreateShortCut(const ShortCut &);												        ///<������ݷ�ʽ

//        void *GetFileIcon(const u16char *,int &,int &,int &);										///<ȡ���ļ���ϵͳͼ��(��Vista���Ͽ���)
#endif//HGL_OS == HGL_OS_Windows

#if (HGL_OS==HGL_OS_Windows)||(HGL_OS==HGL_OS_MacOS)
        void CopyTextToClipboard(const u16char *);													///<�����ַ�����������
        const u16char *GetTextFromClipboard();														///<�Ӽ�����ȡ���ַ���
#endif//(HGL_OS==HGL_OS_Windows)||(HGL_OS==HGL_OS_MacOS)
    }//namespace os

    using namespace os;
}//namespace hgl
#endif//HGL_OS_DESKTOP_INCLUDE