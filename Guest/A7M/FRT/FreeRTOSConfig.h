#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
extern uint32_t SystemCoreClock;

#define configUSE_PREEMPTION			1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE			0
#define configMAX_PRIORITIES			( 7 )
#define configCPU_CLOCK_HZ				( SystemCoreClock )
#define configTICK_RATE_HZ				100
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 256 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 40 * 1024 ) ) /* Has not effect in this demo as the heap is manually pointed to AHB RAM. */
#define configMAX_TASK_NAME_LEN			( 9 )
#define configIDLE_SHOULD_YIELD			0
#define configQUEUE_REGISTRY_SIZE		10
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configUSE_MUTEXES				1
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )
#define configUSE_COUNTING_SEMAPHORES 	1
#define configUSE_ALTERNATIVE_API 		0
#define configUSE_RECURSIVE_MUTEXES		1

/* Hook function related definitions. */
#define configUSE_TICK_HOOK				0
#define configUSE_IDLE_HOOK				0
#define configUSE_MALLOC_FAILED_HOOK	0
#define configCHECK_FOR_STACK_OVERFLOW	0

/* Software timer related definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH		5
#define configTIMER_TASK_STACK_DEPTH	configMINIMAL_STACK_SIZE

/* Run time stats gathering definitions. */
#define configGENERATE_RUN_TIME_STATS	0
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE()

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		0
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_uxTaskGetStackHighWaterMark	1
#define INCLUDE_xTimerGetTimerTaskHandle	0
#define INCLUDE_xTaskGetIdleTaskHandle		0
#define INCLUDE_xQueueGetMutexHolder		1

#define configUSE_STATS_FORMATTING_FUNCTIONS	0

/* Assert statement defined for debug builds. */
#ifdef DEBUG
	#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }
#endif

/* The maximum priority an interrupt that uses an interrupt safe FreeRTOS API
function can have.  Note that lower priority have numerically higher values.  */
#define configMAX_LIBRARY_INTERRUPT_PRIORITY	( 5 )

/* The minimum possible interrupt priority. */
#define configMIN_LIBRARY_INTERRUPT_PRIORITY	( 7 )

/* The lowest priority. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configMIN_LIBRARY_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Priority 5, or 248 as only the top five bits are implemented. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	(configMAX_LIBRARY_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler                     SVC_Handler
#define xPortPendSVHandler                  PendSV_Handler
#define xPortSysTickHandler                 SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
