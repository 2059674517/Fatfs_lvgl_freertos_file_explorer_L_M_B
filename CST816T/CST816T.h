#ifndef __CST816T_H__
#define __CST816T_H__
// #include "stdint.h"


// I2C��ز���
#define CST816T_I2CAddress_7bit 0x15
#define CST816T_I2CAddress_8bit_Read 	(CST816T_I2CAddress_7bit << 1) | 0x01
#define CST816T_I2CAddress_8bit_Write (CST816T_I2CAddress_7bit << 1)

// CST816T�ļĴ���
// �ο��ڡ�CST816Tͨ�ð汾SDK�Ĵ���˵��-v1��
#define CST816T_Register_GestureID			0x01	// ������
#define CST816T_Register_FingerNum			0x02	// ��ָ����
#define CST816T_Register_XposH					0x03	// X�����4λ
#define CST816T_Register_XposL					0x04	// X�����8λ
#define CST816T_Register_YposH					0x05	// Y�����4λ
#define CST816T_Register_YposL					0x06	// Y�����8λ
#define CST816T_Register_ChipID					0xA7	// ���̱��
#define CST816T_Register_FwVersion			0xA9	// ����汾��
#define CST816T_Register_FactoryID 			0xAA	// TP����ID
#define CST816T_Register_BPC0H					0xB0	// BPC0ֵ�ĸ�8λ
#define CST816T_Register_BPC0L					0xB1	// BPC0ֵ�ĵ�8λ
#define CST816T_Register_BPC1H					0xB2	// BPC1ֵ�ĸ�8λ
#define CST816T_Register_BPC1L 					0xB3	// BPC1ֵ�ĵ�8λ
#define CST816T_Register_SleepMode 			0xE5	// ֵΪ0x03ʱ��������״̬���޴������ѹ��ܣ�
#define CST816T_Register_ErrResetCtl 		0xEA	// ��λ����������
#define CST816T_Register_LongPressTick 	0xEB	// ����ʱ�����ޣ�Ĭ��Ϊ100����Լ1S
#define CST816T_Register_MotionMask 		0xEC	// �����˶�����ʹ��
#define CST816T_Register_IrqPluseWidth 	0xED	// �жϵ�����������
#define CST816T_Register_NorScanPer 		0xEE	// �������ټ������
#define CST816T_Register_MotionSlAngle 	0xEF	// ���Ƽ�⻬�������Ƕȿ���
#define CST816T_Register_LpScanRaw1H 		0xF0	// �͹���ɨ��1��ͨ���Ļ�׼ֵ�ĸ�8λ
#define CST816T_Register_LpScanRaw1L 		0xF1	// �͹���ɨ��1��ͨ���Ļ�׼ֵ�ĵ�8λ
#define CST816T_Register_LpScanRaw2H 		0xF2	// �͹���ɨ��2��ͨ���Ļ�׼ֵ�ĸ�8λ
#define CST816T_Register_LpScanRaw2L 		0xF3	// �͹���ɨ��2��ͨ���Ļ�׼ֵ�ĵ�8λ
#define CST816T_Register_LpAutoWakeTime 0xF4	// �͹���ʱ�Զ���У������
#define CST816T_Register_LpScanTH 			0xF5	// �͹���ɨ�軽�����ޡ�ԽСԽ����
#define CST816T_Register_LpScanWin 			0xF6	// �͹���ɨ�����̡�Խ��Խ����������Խ��
#define CST816T_Register_LpScanFreq 		0xF7	// �͹���ɨ��Ƶ�ʡ�ԽСԽ����
#define CST816T_Register_LpScanIdac 		0xF8	// �͹���ɨ�������ԽСԽ����
#define CST816T_Register_AutoSleepTime 	0xF9	// x�����޴���ʱ���Զ�����͹���ģʽ
#define CST816T_Register_IrqCtl 				0xFA	// ����������Ķ���
#define CST816T_Register_AutoReset 			0xFB	// x�����д���������Ч����ʱ���Զ���λ
#define CST816T_Register_LongPressTime 	0xFC	// ����x����Զ���λ
#define CST816T_Register_IOCtl 					0xFD	// ����ͨ������IRQ����ʵ�ִ��ص���λ����
#define CST816T_Register_DisAutoSleep 	0xFE	// Ĭ��Ϊ0��ʹ���Զ�����͹���ģʽ


// ���ܺ���
void CST816T_Init(void);								// ��ʼ��
uint8_t CST816T_GetGestureID(void);		// ��ȡ������
uint16_t CST816T_GetXpos(void);				// ��ȡ�����X����
uint16_t CST816T_GetYpos(void);				// ��ȡ�����Y����
uint8_t CST816T_GetChipID(void);				// ��ȡоƬID
uint8_t CST816T_GetRegisterData(uint8_t reg);	// ��ȡ�����Ĵ�������

extern uint8_t Pressed;

#endif
