/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs.h"
#include "lv_hal_tick.h"
#include "lv_demo_benchmark.h"
#include "stdlib.h"
#include "file_browser.h"
#include "image_viewer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
SemaphoreHandle_t xSDMutex = NULL;
FIL file;
uint32_t total,mfree;                  // file objects
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId lvglHandle;
osThreadId AccelerateLvglHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
u8 exf_getfree(u8 *drv,u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
	u32 fre_clust=0, fre_sect=0, tot_sect=0;
	res =(u32)f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
    if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	
	    fre_sect=fre_clust*fs1->csize;				   
#if _MAX_SS!=512				  				
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	
		*free=fre_sect>>1;	
 	}
	return res;
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void lvgl_Task(void const * argument);
void AccelerateLvgl_t(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationTickHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 3 */
__weak void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	xSDMutex = xSemaphoreCreateMutex();
	if (xSDMutex == NULL) {
			printf("fail to create xSDMutex\r\n");
			Error_Handler(); 
	}
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of lvgl */
  osThreadDef(lvgl, lvgl_Task, osPriorityNormal, 0, 1024);
  lvglHandle = osThreadCreate(osThread(lvgl), NULL);

  /* definition and creation of AccelerateLvgl */
  osThreadDef(AccelerateLvgl, AccelerateLvgl_t, osPriorityNormal, 0, 256);
  AccelerateLvglHandle = osThreadCreate(osThread(AccelerateLvgl), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	//xSemaphoreTake(xSDMutex, pdMS_TO_TICKS(100));
	extern uint32_t __heap_base;   
	extern uint32_t __heap_limit;
	
//	printf("%d\r\n",xPortGetFreeHeapSize());
//	uint8_t *x = pvPortMalloc(100);
//	printf("%d\r\n",xPortGetFreeHeapSize());
//	printf("Heap start address: 0x%08X\r\nHeap end address: 0x%08X\r\nfree heap memory: %u bytes\r\n",(uint32_t)&__heap_limit,(uint32_t)&__heap_base, (uint32_t)&__heap_limit - (uint32_t)&__heap_base);
//	uint8_t *y = malloc(0x1);
//	y[0] = '1';
//	if(y == NULL)printf("1\r\n");
//	printf("%s %x\r\n",y,y);
//	printf("free heap memory: %u bytes\r\n", (uint32_t)&__heap_limit - (uint32_t)&__heap_base);
	retSD = f_mount(&SDFatFS,SDPath,1);
	switch(retSD)
	{
		case FR_NO_FILESYSTEM :  
		{
			printf("mkfs error \r\n");
			break;
		}
		case FR_OK :
		{
			printf("mount successful \r\n");
			break;
		}	
		case FR_NOT_READY :
		{
			printf("FR_NOT_READY \r\n");
			break;
		}	
		default :
			printf("other error %d\r\n",retUSER);
	}
	retSD=exf_getfree((uint8_t *)SDPath,&total,&mfree);
	if(retSD==0)
		printf(" total : %d MB,free : %d MB  \r\n\r\n",total>>10,mfree>>10);
	else
		printf(" Getfree error!!! \r\n");
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	file_browser_init();
  file_browser_create();
	
	//lv_demo_widgets();
	//xSemaphoreGive(xSDMutex);
  /* Infinite loop */
  for(;;)
  {
		lv_task_handler();
		vTaskDelay(pdMS_TO_TICKS(30));
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_lvgl_Task */
/**
* @brief Function implementing the lvgl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lvgl_Task */
void lvgl_Task(void const * argument)
{
  /* USER CODE BEGIN lvgl_Task */
	//vTaskDelay(pdMS_TO_TICKS(500));
	//xSemaphoreTake(xSDMutex, portMAX_DELAY);
//	extern uint8_t Pressed;
//	unsigned portBASE_TYPE uxHighWaterMark;
	//lv_demo_benchmark();
	//lv_demo_stress();
  /* Infinite loop */
  for(;;)
  {	
//		uxHighWaterMark=uxTaskGetStackHighWaterMark( defaultTaskHandle );
//    printf("Free:%ld %d\r\n",uxHighWaterMark,Pressed);
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
  /* USER CODE END lvgl_Task */
}

/* USER CODE BEGIN Header_AccelerateLvgl_t */
/**
* @brief Function implementing the AccelerateLvgl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AccelerateLvgl_t */
void AccelerateLvgl_t(void const * argument)
{
  /* USER CODE BEGIN AccelerateLvgl_t */
	
  /* Infinite loop */
  for(;;)
  {
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
  /* USER CODE END AccelerateLvgl_t */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
