#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "stm32f7xx_hal_can.h"
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd.h"

CAN_HandleTypeDef HCAN1;
CanTxMsgTypeDef TxMessage; /* Tx message struct */
CanRxMsgTypeDef RxMessage; /* Rx message struct */
 
void InitializeCANBUS1();
void CAN1SendMessage(uint16_t SndID, uint8_t length, uint8_t *data);
void InitializeCANBUS1()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    CAN_FilterConfTypeDef CAN_FilterStruct;
 
    __HAL_RCC_CAN1_CLK_ENABLE();    /* Enable CANBUS-1 clock */
    __GPIOB_CLK_ENABLE();           /* Enable GPIOB clock */
                     
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;          /* Alternate Function Push-Pull mode */
    GPIO_InitStruct.Pull        = GPIO_PULLUP;              /* No resistor */
    GPIO_InitStruct.Speed       = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF9_CAN1;            /* Alternate pin function: AF9 / CAN1 */
    GPIO_InitStruct.Pin         = GPIO_PIN_8 | GPIO_PIN_9;  /* PB8 CN7 D15(CAN1_RX) & PB9 CN7 D14(CAN1_TX) */
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                 /* Initialize registers */

    /* 500kbps fCANCLK:54MHz */
    /* TQ = 54MHz / (Prescaler + 1) */
    /* CAN Bitrate = 1 / ((SJW + BS1 + BS2) * TQ) bps */
    HCAN1.Instance          = CAN1;
    HCAN1.pTxMsg            = &TxMessage; /* Pointer to CAN Tx message */
    HCAN1.pRxMsg            = &RxMessage; /* Pointer to CAN Rx message */
    HCAN1.Init.Prescaler    = 8;
 //   HCAN1.Init.Mode         = CAN_MODE_LOOPBACK; /* Normal communication mode */
    HCAN1.Init.Mode         = CAN_MODE_NORMAL; /* Normal communication mode */
    HCAN1.Init.SJW          = CAN_SJW_1TQ; /* 1 time-quanta re-sync jump width */
    HCAN1.Init.BS1          = CAN_BS1_9TQ; /* 9 tq before sampling point */
    HCAN1.Init.BS2          = CAN_BS2_2TQ; /* 2 tq after sampling point (before end) */
    HCAN1.Init.TTCM         = DISABLE; /* Time-triggered communication */
    HCAN1.Init.ABOM         = DISABLE; /* Automatic bus-off management */
    HCAN1.Init.AWUM         = DISABLE; /* Automatic wake-up mode */
    HCAN1.Init.NART         = DISABLE; /* Non-automatic retransmission mode */
    HCAN1.Init.RFLM         = DISABLE; /* Receive FIFO locked mode */
    HCAN1.Init.TXFP         = DISABLE; /* Transmit FIFO priority */
    HAL_CAN_Init(&HCAN1); /* Init CAN1 registers */
                                                                                                         
    CAN_FilterStruct.FilterIdHigh = 0x0000; /* Upper 16bit filter ID */
    CAN_FilterStruct.FilterIdLow = 0x0000; /* Filter lower 16bit ID */
    CAN_FilterStruct.FilterMaskIdHigh = 0x0000; /* Upper 16bit filter mask */
    CAN_FilterStruct.FilterMaskIdLow = 0x0000; /* Lower 16bit filter mask */
    CAN_FilterStruct.FilterFIFOAssignment = CAN_FILTER_FIFO0; /* Which FIFO will be assigned to filter */
    CAN_FilterStruct.FilterNumber = 0;
    CAN_FilterStruct.FilterMode = CAN_FILTERMODE_IDMASK; /* Identifier mask mode */
    CAN_FilterStruct.FilterScale = CAN_FILTERSCALE_32BIT; /* 32bit ID filter */
    CAN_FilterStruct.FilterActivation = ENABLE; /* Enable this filter */
    CAN_FilterStruct.BankNumber = 14; /* Start slave bank filter (?) */
    HAL_CAN_ConfigFilter(&HCAN1, &CAN_FilterStruct); /* Initialize filter */

    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 1); /* Set CAN1 Rx interrupt priority to 1-1 */
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn); /* Enable CAN1 Rx Interrupt */
    __HAL_CAN_ENABLE_IT(&HCAN1, CAN_IT_FMP0); /* Enable 'message pending in FIFO0' interrupt */
                                                                                                                                                                 
}
 
void CAN1SendMessage(uint16_t SndID, uint8_t length, uint8_t *data)
{
    HCAN1.pTxMsg->RTR = CAN_RTR_DATA; /* Remote transmission request:data */
    HCAN1.pTxMsg->IDE = CAN_ID_STD; /* Identifier type: standard */
    HCAN1.pTxMsg->StdId = SndID; /* Standard ID of this device */
    HCAN1.pTxMsg->DLC = length; /* Specify the data length */
    uint8_t d;
             
    for(d = 0; d < length; ++d)
    {
        HCAN1.pTxMsg->Data[d] = *(data + d); /* Write every byte to Data[] variable */
    }
    HAL_CAN_Transmit(&HCAN1, 500); /* Transmit the packet */
}
 
/* CAN1 Rx FIFO0 interrupt service routine */
void CAN1_RX0_IRQHandler()
{
    if(HAL_CAN_Receive(&HCAN1, 0, 5000) == HAL_OK) /* Packet received from CANBUS successfully */
    {
        BSP_LCD_DisplayStringAt(50, 100, (uint8_t*)"Recieve CAN Data!!!", CENTER_MODE);
    }
}
 
/* canbus.c */
