//---------------------------------------------------------------------------//
//
//! @file gb_print.c
//! @brief ����Ļ��ӡ�ַ� 
//
//! @author Toby Zhang
//! @date 2010.07.11
//! @version v1.0
//! @note
//
//! ���ļ�ʹ��ͼ�ο��еĲ��ֺ����������û��Զ������ɵ��ֿ⣬����Ļ��ӡ�ַ�\n
//!
//! ARM�ں�   : ARMv7M Cortex-M3\n
//! ʹ��оƬ  : LM3S1968\n
//! ָ�    : Thumb2\n
//! ��������  : KEIL\n
//! ��Ȩ���� (C)2005-2010 ������Ƽ����޹�˾\n
//! \n
//! �޸���־  :\n
//! 2010.07.11    ��������.Toby Zhang\n
//
//
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//
//! \addtogroup gb_print_api
//! @{
//
//---------------------------------------------------------------------------//

#include "gb_print.h"
#include "grlib.h"
#include "formike128x128x16.h"


//---------------------------------------------------------------------------//
//
//! @brief ����Ļ��ӡһ�������ַ� 
//! @author Toby Zhang
//! @note
//! ����������Ļ��ӡһ�������ַ���16*16������ѭGB-2312��׼ 
// 
//! @param s32_x ��Ļ�ϵ�x������ 
//! @param s32_y ��Ļ�ϵ�y������ 
//! @param u8_index[2] �����ַ�����
//! @param font_gb_st16[] �û��Զ����ֿ⼯ 
//
//! @return void 
//
//  @deprecated
//! @since 2010.07.11
//! @see �� 
//
//---------------------------------------------------------------------------//
void GBPrintAscii(signed long s32_x,
                  signed long s32_y,
			      signed char s8_index,
				  unsigned long ulForeground,
			      unsigned long ulBackground)
{
    unsigned long i,j, k;
    unsigned char u8_data_buff; 
	const unsigned char *pu8_ascii_data;
	unsigned long u32_tmp = (s8_index - 32)*16;
	pu8_ascii_data = &g_x_font_asciii[u32_tmp];
    
	// �ҵ��ַ�����ģ���ݣ��������ݣ�����Ļ��ӡ 
    for(j=0; j< 16; )
    {
        // ȡ��������벿����ģ����
        u8_data_buff = *(pu8_ascii_data + j);

        // ѭ������8������д�� 
        for(k=0; k<8; k++)
		{
		    // ��������λ��ӡ��ͬ����ɫ
			if((u8_data_buff & 0x80) == 0x00)
			{
				// Ϊ0��������ɫ
			    DpyPixelDraw(&g_sFormike128x128x16, 
				             s32_x + k,
							 s32_y + j,
							 ulBackground); 
			}
			else
			{
				// Ϊ1����ǰ��ɫ
			    DpyPixelDraw(&g_sFormike128x128x16,
                             s32_x + k,
							 s32_y + j,
							 ulForeground);
			}
			u8_data_buff = u8_data_buff<<1;
		}
		
		// ��ģ����ָ���һ������
        j++;                 
    }			

}


//---------------------------------------------------------------------------//
//
//! @brief ����Ļ��ӡһ�������ַ� 
//! @author Toby Zhang
//! @note
//! ����������Ļ��ӡһ�������ַ���16*16������ѭGB-2312��׼ 
// 
//! @param s32_x ��Ļ�ϵ�x������ 
//! @param s32_y ��Ļ�ϵ�y������ 
//! @param u8_index[2] �����ַ�����
//! @param font_gb_st16[] �û��Զ����ֿ⼯ 
//
//! @return void 
//
//  @deprecated
//! @since 2010.07.11
//! @see �� 
//
//---------------------------------------------------------------------------//
void GBPrintCharacter(unsigned long u32_x,
             unsigned long u32_y,
			 unsigned short u16_index,
			 unsigned long ulForeground,
		     unsigned long ulBackground)
{
    unsigned long u32_i,u32_j, u32_k;
    unsigned char u8_data_buff; 
	unsigned short u16_index_tmp;
	
	// ���û��Զ�����ֿ���������Ҫ��ӡ���ַ�����ģ
    for(u32_i = 0; u32_i < 200; u32_i++)
    {
	    // u16_index_tmp = *((unsigned short*)(g_x_font_gb_st16[u32_i].pu8_index));
            u16_index_tmp = *(g_x_font_gb_st16[u32_i].pu8_index + 1);
            u16_index_tmp = u16_index_tmp << 8;
            u16_index_tmp +=   *(g_x_font_gb_st16[u32_i].pu8_index + 0);
	    if(u16_index_tmp == 0)
		  break;
	    if(u16_index == u16_index_tmp)
	    {
		    // �ҵ��ַ�����ģ���ݣ��������ݣ�����Ļ��ӡ 
            for(u32_j = 0; u32_j < 32; )
            {
                // ȡ��������벿����ģ����
                u8_data_buff = g_x_font_gb_st16[u32_i].u8_mask[u32_j];

                // ѭ������8������д�� 
                for(u32_k = 0; u32_k < 8; u32_k++)
				{
				    // ��������λ��ӡ��ͬ����ɫ
					if((u8_data_buff & 0x80) == 0x00)
					{
						// Ϊ0��������ɫ
					    DpyPixelDraw(&g_sFormike128x128x16, 
						             u32_x + u32_k,
									 u32_y + u32_j / 2,
									 ulBackground); 
					}
					else
					{
						// Ϊ1����ǰ��ɫ
					    DpyPixelDraw(&g_sFormike128x128x16,
                                     u32_x + u32_k,
									 u32_y + u32_j / 2,
									 ulForeground);
					}
					u8_data_buff = u8_data_buff<<1;
				}
				
                // ��ģ����ָ���һ������
                u32_j++;

                // ȡ�������Ұ벿����ģ����
                u8_data_buff = g_x_font_gb_st16[u32_i].u8_mask[u32_j];

                // ѭ������8������д�� 
                for(u32_k=8; u32_k<16; u32_k++)
				{
				    // ��������λ��ӡ��ͬ����ɫ
					if((u8_data_buff & 0x80) == 0x00)
					{
						// Ϊ0��������ɫ 
					    DpyPixelDraw(&g_sFormike128x128x16,
						              u32_x + u32_k,
									  u32_y + u32_j / 2,
									  ulBackground); 
					}
					else
					{
						// Ϊ1����ǰ��ɫ 
					    DpyPixelDraw(&g_sFormike128x128x16,
                                     u32_x + u32_k,
									 u32_y + u32_j / 2,
									 ulForeground);
					}
					u8_data_buff = u8_data_buff<<1;
				}

                // ��ģ����ָ���һ������
                u32_j++;                 
            }			

			// ����ַ��Ĵ�ӡ������ѭ��
			break;   
		}
	}
}

//---------------------------------------------------------------------------//
//
//! @brief ��ӡһ�������ַ��� 
//! @author Toby Zhang
//! @note
//! ����Ļ��ӡһ�������ַ����� 
// 
//! @param s32_x ��Ļ�ϵ�x������ 
//! @param s32_y ��Ļ�ϵ�y������ 
//! @param u8_index[] �����ַ������ַ��� 
//! @param font_gb_st16[] �û��Զ����ֿ⼯
//
//! @return void
//
//  @deprecated
//! @since 2010.07.11
//! @see �ο�GBStringPrint(). 
//
//---------------------------------------------------------------------------//
void GBStringPrint(unsigned long u32_x,
                   unsigned long u32_y,
			       unsigned char *pu8_index,
				   unsigned long ulForeground,
				   unsigned long ulBackground
				   )
{
    unsigned long u8_i;
    unsigned long u32_string_length = 0;
	unsigned short u16_index;
	 
    // �õ��ַ����ĳ���
	u32_string_length = strlen((const char*)pu8_index);
	
	// �ֱ��ӡ�ַ�����ÿ���ַ�֮���һ�����ص�
	for(u8_i=0; u8_i<u32_string_length; )
	{
        if(*pu8_index <= 0x7F)
		{
		    GBPrintAscii(u32_x,
		                 u32_y,
						 *pu8_index,
						 ulForeground,
					     ulBackground);
			
			// ���������ַ�ָ��ָ����һ���ַ�
	        pu8_index += 1;  
			u32_x += 8;
			u8_i++;
		}
		else
		{
		    //u16_index = *((unsigned short*)pu8_index);
		   u16_index = *(pu8_index + 1);
                   u16_index  = u16_index << 8;
                   u16_index += *(pu8_index + 0);

			// ����Ļ��ӡ�����ַ�
	        GBPrintCharacter(u32_x,
		            u32_y,
	                u16_index,
					ulForeground,
					ulBackground);
	        
	        // ���������ַ�ָ��ָ����һ���ַ�
	        pu8_index += 2;  
			u8_i = u8_i + 2;
			u32_x += 16;
		}		
	}    
} 



//---------------------------------------------------------------------------//
//
// Close the Doxygen group.
//! @}
//
//---------------------------------------------------------------------------//
