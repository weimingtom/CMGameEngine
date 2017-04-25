﻿#ifndef HGL_CODE_PAGE_INCLUDE
#define HGL_CODE_PAGE_INCLUDE

#include<hgl/platform/Platform.h>
#include<hgl/Str.h>
#include<hgl/type/BaseString.h>
namespace hgl
{
	/**
	* Windows代码页枚举
	* 全部Windows所支持代码页请参见 http://msdn.microsoft.com/en-us/library/dd317756
	*/
	enum CharCodePage										///代码页枚举
	{
		ccpNone=0,                                          ///<起始定义，无意义

		//中文
		ccpGBK                          =936,               ///<中国GBK标准中文
		ccpBig5                         =950,               ///<中国台湾Big5标准繁体中文
		ccpGB2312                       =20936,             ///<中国GB2312标准简体中文
		ccpGB18030                      =54936,             ///<中国GB18030-2000标准中文

		//日文
		ccpShiftJIS                     =932,               ///<日文ShiftJIS
		ccpJISX							=50222,				///<日文JIS X/ISO 2022

		//韩文
		ccpKorean						=949,				///<韩文

		//苹果编码
		ccpMacJanpan					=10001,				///<日文
		ccpMacTraditionalChinese		=10002,				///<繁体中文
		ccpMacSimplifiedChinese			=10008,				///<简体中文

		//unicode
		ccpUTF7							=65000,				///<utf-7
		ccpUTF8							=65001,				///<utf-8

		ccpUTF16LE						=1200,
		ccpUTF16BE						=1201,
		ccpUTF32LE						=12000,
		ccpUTF32BE						=12001,

		ccpEnd                          					///<结束定义，无意义
	};//enum CharCodePage

	struct CodePageAndCharSet
	{
		CharCodePage codepage;
		CharSetName charset;
	};

	constexpr struct CodePageAndCharSet CodePage2CharSet[]=
	{
		{ccpNone,			"us-ascii"	},

		{ccpGBK,			"gbk"		},
		{ccpBig5,			"big5"		},
		{ccpGB2312,			"gb2312"	},
		{ccpGB18030,		"gb18030"	},

		{ccpShiftJIS,		"shift-jis"		},
		{ccpJISX,			"iso-2022-jp"	},

		{ccpKorean,			"ks_c_5601-1987"},

		{ccpMacJanpan,				"x-mac-japanese"	},
		{ccpMacTraditionalChinese,	"x-mac-chinesetrad"	},
		{ccpMacSimplifiedChinese,	"x-mac-chinesesimp"	},

		{ccpUTF7,			"utf-7"		},
		{ccpUTF8,			"utf-8"		},

		{ccpUTF16LE,		"utf-16le"	},
		{ccpUTF16BE,		"utf-16be"	},
		{ccpUTF32LE,		"utf-32le"	},
		{ccpUTF32BE,		"utf-32be"	},
	};//const struct

	constexpr int CharSetCount=sizeof(CodePage2CharSet)/sizeof(CodePageAndCharSet);

	inline const char *FindCharSet(CharCodePage ccp)
	{
		for(int i=0;i<CharSetCount;i++)
			if(CodePage2CharSet[i].codepage==ccp)
				return CodePage2CharSet[i].charset;

		return 0;
	}

	constexpr struct CodePageAndCharSet CodeSet2CharPage[]=
	{
		{ccpNone,			"us-ascii"	},

		{ccpGBK,			"gbk"		},

		{ccpBig5,			"big5"		},
		{ccpBig5,			"bigfive"	},

		{ccpGB2312,			"gb2312"	},
		{ccpGB18030,		"gb18030"	},

		{ccpShiftJIS,		"shift_jis"		},
		{ccpJISX,			"iso-2022-jp"	},

		{ccpKorean,			"ks_c_5601-1987"},

		{ccpMacJanpan,				"x-mac-japanese"	},
		{ccpMacTraditionalChinese,	"x-mac-chinesetrad"	},
		{ccpMacSimplifiedChinese,	"x-mac-chinesesimp"	},

		{ccpUTF7,			"utf7"		},
		{ccpUTF8,			"utf8"		},
		{ccpUTF16LE,		"utf16le"	},
		{ccpUTF16BE,		"utf16be"	},
		{ccpUTF32LE,		"utf32le"	},
		{ccpUTF32BE,		"utf32be"	},

		{ccpUTF16LE,		"ucs2le"	},
		{ccpUTF16BE,		"ucs2be"	},
		{ccpUTF32LE,		"ucs4le"	},
		{ccpUTF32BE,		"ucs4be"	}
	};//const struct CharSet Characters

	constexpr int CharPageCount=sizeof(CodeSet2CharPage)/sizeof(CodePageAndCharSet);

	inline CharCodePage FindCodePage(const char *char_set)
	{
		for(int i=0;i<CharPageCount;i++)
			if(!charset_cmp(CodePage2CharSet[i].charset,char_set))
				return CodePage2CharSet[i].codepage;

		return ccpNone;
	}

	struct CharSet
	{
		CharCodePage codepage;
        CharSetName charset;

	public:

		CharSet()
		{
			codepage=ccpNone;
			strcpy(charset,CharSetNameLength,"us-ascii");
		}

		CharSet(CharCodePage ccp,const char *cs)
		{
			codepage=ccp;
			strcpy(charset,CharSetNameLength,cs);
		}

		CharSet(CharCodePage);
		CharSet(const char *);

		CharSet(const CodePageAndCharSet &cs)
		{
			codepage=cs.codepage;
			strcpy(charset,CharSetNameLength,cs.charset);
		}

        CompOperatorMemcmp(const CharSet &)
	};//struct CharacterSet

	inline CharSet::CharSet(CharCodePage ccp)
	{
		codepage=ccp;
		strcpy(charset,CharSetNameLength,FindCharSet(ccp));
	}

	inline CharSet::CharSet(const char *cs)
	{
		strcpy(charset,CharSetNameLength,cs);
		codepage=FindCodePage(cs);
	}

	extern CharSet DefaultCharSet();

    extern CharSet UTF8CharSet;
    extern CharSet UTF16LECharSet;
    extern CharSet UTF16BECharSet;

	/**
	 * 使用指定字符集转换字符串到 u16char *字符串
	 * @param charset	字符集
	 * @param dst		u16char *字符串缓冲区，自动分配，需手动delete[]
	 * @param src		原始字符串
	 * @param src_size	字符串长度,-1表示全部
	 * @return 转换成功后的字符串字符数
	 */
	int to_utf16(const CharSet &charset,u16char **dst,const char *src,const int src_size=-1);

    int to_utf8(const CharSet &charset,char **dst,const char *src,const int src_size=-1);

	/**
	 * 转换u16char *字符串到指定字符集的字符串
	 * @param charset	字符集
	 * @param dst		char *字符串缓冲区，自动分配，需手动delete[]
	 * @param src		u16char *字符串
	 * @param src_size	字符串长度,-1表示全部
	 * @return 转换成功后的字符串字符数
	 */
	int utf16_to(const CharSet &charset,char **dst,const u16char *src,const int src_size=-1);

    int utf8_to(const CharSet &charset,char **dst,const char *src,const int src_size=-1);

	int				u16_to_u8(char *,int,const u16char *,const int=-1);							///<转换u16char *到utf8格式的char *
	int				u8_to_u16(u16char *,int,const char *,const int=-1);							///<转换utf8格式的char *到u16char *

	char *			u16_to_u8(const u16char *,const int,int &);									///<转换u16char *到utf8格式的char *
	u16char *		u8_to_u16(const char *,const int,int &);									///<转换utf8格式的char *到u16char *

	inline char *	u16_to_u8(const u16char *str)
	{
		int len;
		return u16_to_u8(str,hgl::strlen<u16char>(str)+1,len);
	}

	inline u16char *u8_to_u16(const char *str)
	{
		int len;
		return u8_to_u16(str,hgl::strlen<char>(str)+1,len);
	}

	inline UTF16String to_u16(const char *u8_str,int length)
	{
		int wlen;
		u16char *ws=u8_to_u16(u8_str,length,wlen);

		return UTF16String(ws,wlen,true);
	}

	inline UTF16String to_u16(const UTF8String &u8str)
	{
		return to_u16(u8str.c_str(),u8str.Length());
	}

	inline UTF16String to_u16(const char *str)
	{
		int wlen;

		u16char *ws=u8_to_u16(str,strlen(str),wlen);

		return UTF16String(ws,wlen,true);
	}

	inline UTF8String to_u8(const u16char *wide_str,int length)
	{
		int ulen;

		char *us=u16_to_u8(wide_str,length,ulen);

		return UTF8String(us,ulen,true);
	}

	inline UTF8String to_u8(const UTF16String &ws)
	{
		return to_u8(ws.c_str(),ws.Length());
	}

	//utf32<->utf16互转请使用hgl_equcpy,代码在datatype.h
}//namespace hgl
#endif//HGL_CODE_PAGE_INCLUDE
