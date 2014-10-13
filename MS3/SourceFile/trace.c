
/***************************************************************************************
****************************************************************************************
* FILE		: trace.c
* Description	: 
*			  
* Copyright (c) 2007 by LIU YING. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		Liu Ying	2007/05/01	Initial Version
   
****************************************************************************************
****************************************************************************************/
#include <stdio.h>
#include <stdarg.h>


#include "common.h"
/*����ͼ��дһ��printf,��Ϊ��ռ��flash��Դ�ϸߣ���ʵ�ʷ��ֻ��������ĺ�*/
/*����Ϊ�ɱ������������뺯��ģ�棬����ҪU16���봫�룬�������*/
#if 0
void qprintf(const char *fmt, ...)
{
     va_list arg_ptr;  //����һ������ָ��������б��ָ��arg_ptr

     U16 i;

     va_start(arg_ptr, fmt);  //ʹarg_ptrָ���һ���ɱ����
     i = va_arg(arg_ptr, int);  //ȡ��arg_ptr��ǰ��ָ��Ĳ�����ֵ����ʹarg_ptrָ����һ������
	//j = va_arg(arg_ptr, int);
	//k = va_arg(arg_ptr, int);
	 va_end(arg_ptr);  //ָʾ��ȡ��������

	//uputchar(i >> 8);
	//uputchar(i & 0x00FF);
	//uputchar(j >> 8);
	//uputchar(j & 0x00FF);
	//uputchar(k >> 8);
	//uputchar(k & 0x00FF);


     return;
}

#endif


#if 0

//typedef char *va_list;

#define   _AUPBND        (sizeof (acpi_native_int) - 1)
#define   _ADNBND        (sizeof (acpi_native_int) - 1)
                     
#define _bnd(X, bnd) (((sizeof (X)) + (bnd)) & (~(bnd)))
//#define va_arg(ap, T) (*(T *)(((ap) += (_bnd (T, _AUPBND))) - (_bnd (T,_ADNBND))))
//#define va_end(ap)    (void) 0
//#define va_start(ap, A) (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

//start.c
static char xdata sprint_buf[100];
void qprintf(char *fmt, ...)
{
va_list args;
int n;
va_start(args, fmt);
n = vsprintf(sprint_buf, fmt, args);
va_end(args);
//write(stdout, sprint_buf, n);
//return n;
}


#define LEFT	0x01
#define PLUS	0x02
#define SPACE	0x04
#define SPECIAL	0x08
#define ZEROPAD	0x10
#define LARGE	0x20
#define SIGN	0x40	

int vsprintf(char *buf, const char *fmt, va_list args)
{
  int len;
  unsigned long num;
  int i, base;
  char *str;
  char *s;

  int flags;            // Flags to number()

  int field_width;    // Width of output field
  int precision;    // Min. # of digits for integers; max number of chars for from string
  int qualifier;    // 'h', 'l', or 'L' for integer fields

  for (str = buf; *fmt; fmt++)
  {
    if (*fmt != '%')
    {
      *str++ = *fmt;
      continue;
    }
          
    // Process flags
    flags = 0;
repeat:
    fmt++; // This also skips first '%'

#if 0
    switch (*fmt)
    {
      case '-': flags |= LEFT; goto repeat;
      case '+': flags |= PLUS; goto repeat;
      case ' ': flags |= SPACE; goto repeat;
      case '#': flags |= SPECIAL; goto repeat;
      case '0': flags |= ZEROPAD; goto repeat;
    }
#endif
      
    // Get field width
    field_width = -1;
#if 0
    if (is_digit(*fmt))
      field_width = skip_atoi(&fmt);
    else if (*fmt == '*')
    {
      fmt++;
      field_width = va_arg(args, int);
      if (field_width < 0)
      {
    field_width = -field_width;
    flags |= LEFT;
      }
    }
#endif

    // Get the precision
    precision = -1;
#if 0
    if (*fmt == '.')
    {
      ++fmt;    
      if (is_digit(*fmt))
        precision = skip_atoi(&fmt);
      else if (*fmt == '*')
      {
        ++fmt;
        precision = va_arg(args, int);
      }
      if (precision < 0) precision = 0;
    }
#endif

    // Get the conversion qualifier
    qualifier = -1;
#if 0
    if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
    {
      qualifier = *fmt;
      fmt++;
    }
#endif

    // Default base
    base = 10;

    switch (*fmt)
    {
      case 'c':
    if (!(flags & LEFT)) while (--field_width > 0) *str++ = ' ';
    *str++ = (unsigned char) va_arg(args, int);
    while (--field_width > 0) *str++ = ' ';
    continue;

#if 0
      case 's':
    s = va_arg(args, char *);
    if (!s)    s = "<NULL>";
    len = strnlen(s, precision);
    if (!(flags & LEFT)) while (len < field_width--) *str++ = ' ';
    for (i = 0; i < len; ++i) *str++ = *s++;
    while (len < field_width--) *str++ = ' ';
    continue;

      case 'p':
    if (field_width == -1)
    {
      field_width = 2 * sizeof(void *);
      flags |= ZEROPAD;
    }
    str = number(str, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);
    continue;

      case 'n':
    if (qualifier == 'l')
    {
      long *ip = va_arg(args, long *);
      *ip = (str - buf);
    }
    else
    {
      int *ip = va_arg(args, int *);
      *ip = (str - buf);
    }
    continue;

      case 'A':
    flags |= LARGE;

      case 'a':
    if (qualifier == 'l')
      str = eaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
    else
      str = iaddr(str, va_arg(args, unsigned char *), field_width, precision, flags);
    continue;

      // Integer number formats - set up the flags and "break"
      case 'o':
    base = 8;
    break;

      case 'X':
    flags |= LARGE;

      case 'x':
    base = 16;
    break;
#endif

      case 'd':
      case 'i':
    flags |= SIGN;

      case 'u':
    break;

#if 0
      case 'E':
      case 'G':
      case 'e':
      case 'f':
      case 'g':
        str = flt(str, va_arg(args, double), field_width, precision, *fmt, flags | SIGN);
    continue;
#endif

      default:
    if (*fmt != '%') *str++ = '%';
    if (*fmt)
      *str++ = *fmt;
    else
      --fmt;
    continue;
    }

    if (qualifier == 'l')
      num = va_arg(args, unsigned long);
    else if (qualifier == 'h')
    {
      if (flags & SIGN)
    num = va_arg(args, short);
      else
    num = va_arg(args, unsigned short);
    }
    else if (flags & SIGN)
      num = va_arg(args, int);
    else
      num = va_arg(args, unsigned int);

#if 0
    str = number(str, num, base, field_width, precision, flags);
#else
	uputchar(num >> 8);
	uputchar(num & 0x00FF);
#endif
  }

  *str = '\0';
  return str - buf;
}
#endif
