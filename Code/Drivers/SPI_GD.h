/*********************************************************************************
  *FileName:	SPI_GD.h
  *Author:  	qianwan
  *Details: 	GD32 SPI���� API
  
				ʹ��DMAʱ����ʹ�ô�DMA�����ĳ�ʼ����������
			**	SPI_USE_TX_DMA == 1ʱ��������DMA
				DMA������Ҫ�ڷ���DMA��DMAx_IRQHandler�����е���IRQ_Tx
				//////////////////////////////////////////////////////////////////
			**	SPI_USE_RX_DMA == 1ʱ��������DMA
				DMA������Ҫ�ڽ���DMA��DMAx_IRQHandler�����е���IRQ_Rx
  
			**	GD32�汾������STM32�Ĳ������ڣ�GD32�汾SPI_Init�������أ���ʹ�õ�
				DMAֱ�Ӵ����ָ�뼴��
				
  *Version:  	1.2.1
  *Date:  		2023/03/05
  *Other:		ȡ����Delay����������
 
  *Version:  	1.2
  *Date:  		2023/01/29
  *Other:		ʹ�ú궨�忪��DMA�շ�
**********************************************************************************/
#ifndef SPI_GD_H
#define SPI_GD_H
#include <main.h>
#ifdef __cplusplus
/*******����DMA�շ�********/
#define SPI_USE_TX_DMA 1
#define SPI_USE_RX_DMA 0
/**************************/
#define SPI_TIME_OVER_TIME 0xFFFF
/*! 
 *  @brief      ����SPI����
 *  @brief		Ϊ�����ṩSPI��ʼ�������ݽ���������CS���ơ�MISO���ƵȻ�������
 */
class cSPI
{
	protected:
	uint32_t SPI;
	uint32_t CS_Port;
	uint32_t CS_Pin;

	public:
	inline void CS_0(void)
	{GPIO_BC(this->CS_Port)=this->CS_Pin;}
	inline void CS_1(void)
	{GPIO_BOP(this->CS_Port)=this->CS_Pin;}

	uint8_t SPI_ExchangeOneByte(uint8_t Data);
	
	public:
	/*SPI_Init��������ݲ�ͬ�Ĵ������أ����������ѡ��DMAģʽ*/
	/*��ʹ��DMA��������ʽ*/
	void SPI_Init(uint32_t SPI, uint32_t CS_Port, uint32_t CS_Pin)
	{
		this->SPI = SPI;
		this->CS_Port = CS_Port;
		this->CS_Pin = CS_Pin;
		this->CS_1();
		spi_enable(this->SPI);
	}
	
	#if (SPI_USE_TX_DMA==1)&&(SPI_USE_RX_DMA==0)
	protected:
	uint32_t DMAt;
	dma_channel_enum DMA_CHt;
	public:
	void SPI_Init(uint32_t SPI, uint32_t CS_Port, uint32_t CS_Pin,
				  uint32_t DMA,dma_channel_enum DMA_CH)
	{
		this->SPI = SPI;
		this->CS_Port = CS_Port;
		this->CS_Pin = CS_Pin;
		this->DMAt = DMA;
		this->DMA_CHt = DMA_CH;
		spi_enable(this->SPI);
		this->CS_1();
		
	}
	uint8_t Transmit_DMA(uint8_t *data,uint16_t num);
	uint8_t IRQ_Tx(void);
	
	/*��ʹ��DMA����*/
	#elif (SPI_USE_TX_DMA==0)&&(SPI_USE_RX_DMA==1)
	protected:
	uint32_t DMAr;
	dma_channel_enum DMA_CHr;
	public:
	void SPI_Init(uint32_t SPI, uint32_t CS_Port, uint32_t CS_Pin,
				  uint32_t DMA,dma_channel_enum DMA_CH)
	{
		this->SPI = SPI;
		this->CS_Port = CS_Port;
		this->CS_Pin = CS_Pin;
		this->DMAr = DMA;
		this->DMA_CHr = DMA_CH;
		spi_enable(this->SPI);
		this->CS_1();
	}
	uint8_t Receive_DMA(uint8_t *data,uint16_t num);
	uint8_t IRQ_Rx(void);
	
	/*ʹ��DMA�շ�*/
	#elif (SPI_USE_TX_DMA==1)&&(SPI_USE_RX_DMA==1)
	protected:
	uint32_t DMAt;
	dma_channel_enum DMA_CHt;
	uint32_t DMAr;
	dma_channel_enum DMA_CHr;
	public:
	void SPI_Init(uint32_t SPI, uint32_t CS_Port, uint32_t CS_Pin, 
				  uint32_t DMAr, dma_channel_enum DMA_CHr, 
				  uint32_t DMAt,dma_channel_enum DMA_CHt)
	{
		this->SPI = SPI;
		this->CS_Port = CS_Port;
		this->CS_Pin = CS_Pin;
		this->DMAt = DMAt;
		this->DMA_CHt = DMA_CHt;
		this->DMAr = DMAr;
		this->DMA_CHr = DMA_CHr;
		spi_enable(this->SPI);
		this->CS_1();
	}
	
	uint16_t Transmit_DMA(uint8_t *data,uint16_t num);
	uint16_t Receive_DMA(uint8_t *data,uint16_t num);
	uint8_t IRQ_Rx(void);
	uint8_t IRQ_Tx(void);
	#endif
};


#endif
#endif