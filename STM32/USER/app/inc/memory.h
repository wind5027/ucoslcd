/*
**********************************************************************************
*文件说明：内存分配管理头文件                                                     
*文件名称：memory.h                                                               
*创建日期：2009.07.22                                                             
*创 建 人：王玮                                                                   
*---------------------------------------------------------------------------------
*修改日期：                                                                       
*修改说明：                                                                       
**********************************************************************************
*/
#ifndef MEMORY_H
#define MEMORY_H


#include "user_type.h"
#include "user_cfg.h"
#include "includes.h"


/************************************************
**说明: SRAM起始地址
************************************************/
#define SRAM_BASE_ADDR      ((Uint32)0x63d00000)

#define BUF_ADDR1           (PDat1 *)(SRAM_BASE_ADDR)
#define BUF_ADDR2           (PDat2 *)(SRAM_BASE_ADDR + 1024)


//extern PDat1 * PD1;
//extern PDat2 * PD2;


/************************************************
**说明: 内存分区数目及长度
************************************************/
#define PARTITION_NUM                       (6) 
#define PARTITION_LENGTH                    (4096)


/************************************************
**说明: FSMC占用互斥信号量
************************************************/
extern OS_EVENT * FSMCMutex;

**说明: 内存管理相关变量
************************************************/
extern OS_MEM * MEMPointer;
extern Uint8 MEMPartition[PARTITION_NUM][PARTITION_LENGTH];




/*
**********************************************************************************
*函数名称：void MEM_cpy(Uint8 * dest,Uint8 * src,Uint8 count)                    
*函数功能：由src所指内存区域复制count个字节到dest所指内存区域                    
*入口参数：dest 目标地址                                                         
*          src 源地址                                                            
*          Uint8 count 复制长度                                                  
*返回参数：无                                                                    
**********************************************************************************
*/
extern void MEM_Cpy(Uint8 * dest,Uint8 * src,Uint8 count) ;

/*
**********************************************************************************
*函数名称：Bit MEM_cmp(Uint8 * buf1,Uint8 * buf2,Uint8 count)                     
*函数功能：比较内存区域buf1和buf2的前count个字节是否相同                          
*入口参数：buf1 buf2 count                                                        
*返回参数：相等为0 不等为1                                                        
**********************************************************************************
*/
extern Bool MEM_Cmp(Uint8 * buf1,Uint8 * buf2,Uint8 count); 

/*
**********************************************************************************
*函数名称：MEM_set(Uint8 *buffer,Uint8 c,Uint8 count)                             
*函数功能：把buffer所指内存区域的前count个字节设置成字符c。                       
*入口参数：buffer c count                                                         
*返回参数：无                                                                     
**********************************************************************************
*/
extern void MEM_Set(Uint8 *buffer,Uint8 c,Uint16 count);


#endif



