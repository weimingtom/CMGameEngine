﻿#ifndef HGL_OS_LINUX_INCLUDE
#define HGL_OS_LINUX_INCLUDE

#include<limits.h>
//--------------------------------------------------------------------------------------------------
using u32char           =char32_t;
using u16char			=char16_t;
using os_char			=char;
#define to_oschar		to_u8
#define OS_TEXT(str)	u8##str
#define U8_TEXT(str)	u8##str
#define U16_TEXT(str)	u##str

#define HGL_OS_NAME				OS_TEXT("Linux")
#define HGL_LIB_OS				"Linux"											//库操作系统前缀
//--------------------------------------------------------------------------------------------------
#define HGL_PLUGIN_FRONTNAME	"libCMP."										//插件文件名前缀
#define HGL_PLUGIN_EXTNAME		".so"											//插件文件扩展名
#define HGL_PLUGIN_FUNC 		extern "C"										//插件函数定义

#define HGL_DIRECTORY_SEPARATOR '/'												//目录分隔符

#define HGL_LINE_END			"\n"											//换行符
#define HGL_LINE_END_SIZE		1												//换行符长度

#define HGL_MEM_ALIGN			16												//内存对齐字节数

#define HGL_MAX_PATH			_POSIX_PATH_MAX

#define HGL_FMT_I64				"%lld"
#define HGL_FMT_U64				"%llu"
#define HGL_FMT_DOUBLE			"%lf"
#define HGL_FMT_LONG_DOUBLE		"%le"
//--------------------------------------------------------------------------------------------------
#include<malloc.h>
#include<pthread.h>

#define hgl_malloc(size)		memalign(HGL_MEM_ALIGN,size)
#define hgl_realloc(ptr,size)	realloc(ptr,size)
#define hgl_free				free

#define OS_EXTERNAL_H           <dlfcn.h>
typedef void *                  ExternalModulePointer;
#define pi_get                  dlsym
#define pi_close                dlclose

typedef pthread_mutex_t         hgl_thread_mutex;

#define iconv_str				char *

#define struct_stat64			struct stat64
#define tell64(fp)				lseek64(fp,0,SEEK_CUR)
#define read64					read
#define write64					write

#define struct_dirent64 		struct dirent64

#define sprintf_s				snprintf
//--------------------------------------------------------------------------------------------------
#endif//HGL_OS_LINUX_INCLUDE
