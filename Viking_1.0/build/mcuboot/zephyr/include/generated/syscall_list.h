/* auto-generated by gen_syscalls.py, don't edit */

#ifndef ZEPHYR_SYSCALL_LIST_H
#define ZEPHYR_SYSCALL_LIST_H

#define K_SYSCALL_ADC_CHANNEL_SETUP 0
#define K_SYSCALL_ADC_READ 1
#define K_SYSCALL_ADC_READ_ASYNC 2
#define K_SYSCALL_ATOMIC_ADD 3
#define K_SYSCALL_ATOMIC_AND 4
#define K_SYSCALL_ATOMIC_CAS 5
#define K_SYSCALL_ATOMIC_NAND 6
#define K_SYSCALL_ATOMIC_OR 7
#define K_SYSCALL_ATOMIC_PTR_CAS 8
#define K_SYSCALL_ATOMIC_PTR_SET 9
#define K_SYSCALL_ATOMIC_SET 10
#define K_SYSCALL_ATOMIC_SUB 11
#define K_SYSCALL_ATOMIC_XOR 12
#define K_SYSCALL_BBRAM_CHECK_INVALID 13
#define K_SYSCALL_BBRAM_CHECK_POWER 14
#define K_SYSCALL_BBRAM_CHECK_STANDBY_POWER 15
#define K_SYSCALL_BBRAM_GET_SIZE 16
#define K_SYSCALL_BBRAM_READ 17
#define K_SYSCALL_BBRAM_WRITE 18
#define K_SYSCALL_CAN_ADD_RX_FILTER_MSGQ 19
#define K_SYSCALL_CAN_CALC_TIMING 20
#define K_SYSCALL_CAN_CALC_TIMING_DATA 21
#define K_SYSCALL_CAN_GET_CAPABILITIES 22
#define K_SYSCALL_CAN_GET_CORE_CLOCK 23
#define K_SYSCALL_CAN_GET_MAX_BITRATE 24
#define K_SYSCALL_CAN_GET_MAX_FILTERS 25
#define K_SYSCALL_CAN_GET_STATE 26
#define K_SYSCALL_CAN_GET_TIMING_DATA_MAX 27
#define K_SYSCALL_CAN_GET_TIMING_DATA_MIN 28
#define K_SYSCALL_CAN_GET_TIMING_MAX 29
#define K_SYSCALL_CAN_GET_TIMING_MIN 30
#define K_SYSCALL_CAN_RECOVER 31
#define K_SYSCALL_CAN_REMOVE_RX_FILTER 32
#define K_SYSCALL_CAN_SEND 33
#define K_SYSCALL_CAN_SET_BITRATE 34
#define K_SYSCALL_CAN_SET_BITRATE_DATA 35
#define K_SYSCALL_CAN_SET_MODE 36
#define K_SYSCALL_CAN_SET_TIMING 37
#define K_SYSCALL_CAN_SET_TIMING_DATA 38
#define K_SYSCALL_CAN_START 39
#define K_SYSCALL_CAN_STOP 40
#define K_SYSCALL_CLOCK_GETTIME 41
#define K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM 42
#define K_SYSCALL_COUNTER_GET_FREQUENCY 43
#define K_SYSCALL_COUNTER_GET_GUARD_PERIOD 44
#define K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE 45
#define K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS 46
#define K_SYSCALL_COUNTER_GET_PENDING_INT 47
#define K_SYSCALL_COUNTER_GET_TOP_VALUE 48
#define K_SYSCALL_COUNTER_GET_VALUE 49
#define K_SYSCALL_COUNTER_GET_VALUE_64 50
#define K_SYSCALL_COUNTER_IS_COUNTING_UP 51
#define K_SYSCALL_COUNTER_SET_CHANNEL_ALARM 52
#define K_SYSCALL_COUNTER_SET_GUARD_PERIOD 53
#define K_SYSCALL_COUNTER_SET_TOP_VALUE 54
#define K_SYSCALL_COUNTER_START 55
#define K_SYSCALL_COUNTER_STOP 56
#define K_SYSCALL_COUNTER_TICKS_TO_US 57
#define K_SYSCALL_COUNTER_US_TO_TICKS 58
#define K_SYSCALL_DAC_CHANNEL_SETUP 59
#define K_SYSCALL_DAC_WRITE_VALUE 60
#define K_SYSCALL_DEVICE_GET_BINDING 61
#define K_SYSCALL_DEVICE_IS_READY 62
#define K_SYSCALL_DMA_CHAN_FILTER 63
#define K_SYSCALL_DMA_RELEASE_CHANNEL 64
#define K_SYSCALL_DMA_REQUEST_CHANNEL 65
#define K_SYSCALL_DMA_RESUME 66
#define K_SYSCALL_DMA_START 67
#define K_SYSCALL_DMA_STOP 68
#define K_SYSCALL_DMA_SUSPEND 69
#define K_SYSCALL_EEPROM_GET_SIZE 70
#define K_SYSCALL_EEPROM_READ 71
#define K_SYSCALL_EEPROM_WRITE 72
#define K_SYSCALL_ENTROPY_GET_ENTROPY 73
#define K_SYSCALL_ESPI_CONFIG 74
#define K_SYSCALL_ESPI_FLASH_ERASE 75
#define K_SYSCALL_ESPI_GET_CHANNEL_STATUS 76
#define K_SYSCALL_ESPI_READ_FLASH 77
#define K_SYSCALL_ESPI_READ_LPC_REQUEST 78
#define K_SYSCALL_ESPI_READ_REQUEST 79
#define K_SYSCALL_ESPI_RECEIVE_OOB 80
#define K_SYSCALL_ESPI_RECEIVE_VWIRE 81
#define K_SYSCALL_ESPI_SAF_ACTIVATE 82
#define K_SYSCALL_ESPI_SAF_CONFIG 83
#define K_SYSCALL_ESPI_SAF_FLASH_ERASE 84
#define K_SYSCALL_ESPI_SAF_FLASH_READ 85
#define K_SYSCALL_ESPI_SAF_FLASH_WRITE 86
#define K_SYSCALL_ESPI_SAF_GET_CHANNEL_STATUS 87
#define K_SYSCALL_ESPI_SAF_SET_PROTECTION_REGIONS 88
#define K_SYSCALL_ESPI_SEND_OOB 89
#define K_SYSCALL_ESPI_SEND_VWIRE 90
#define K_SYSCALL_ESPI_WRITE_FLASH 91
#define K_SYSCALL_ESPI_WRITE_LPC_REQUEST 92
#define K_SYSCALL_ESPI_WRITE_REQUEST 93
#define K_SYSCALL_FLASH_ERASE 94
#define K_SYSCALL_FLASH_GET_PAGE_COUNT 95
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX 96
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS 97
#define K_SYSCALL_FLASH_GET_PARAMETERS 98
#define K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE 99
#define K_SYSCALL_FLASH_READ 100
#define K_SYSCALL_FLASH_READ_JEDEC_ID 101
#define K_SYSCALL_FLASH_SFDP_READ 102
#define K_SYSCALL_FLASH_SIMULATOR_GET_MEMORY 103
#define K_SYSCALL_FLASH_WRITE 104
#define K_SYSCALL_GPIO_GET_PENDING_INT 105
#define K_SYSCALL_GPIO_PIN_CONFIGURE 106
#define K_SYSCALL_GPIO_PIN_GET_CONFIG 107
#define K_SYSCALL_GPIO_PIN_INTERRUPT_CONFIGURE 108
#define K_SYSCALL_GPIO_PORT_CLEAR_BITS_RAW 109
#define K_SYSCALL_GPIO_PORT_GET_DIRECTION 110
#define K_SYSCALL_GPIO_PORT_GET_RAW 111
#define K_SYSCALL_GPIO_PORT_SET_BITS_RAW 112
#define K_SYSCALL_GPIO_PORT_SET_MASKED_RAW 113
#define K_SYSCALL_GPIO_PORT_TOGGLE_BITS 114
#define K_SYSCALL_HWINFO_CLEAR_RESET_CAUSE 115
#define K_SYSCALL_HWINFO_GET_DEVICE_ID 116
#define K_SYSCALL_HWINFO_GET_RESET_CAUSE 117
#define K_SYSCALL_HWINFO_GET_SUPPORTED_RESET_CAUSE 118
#define K_SYSCALL_I2C_CONFIGURE 119
#define K_SYSCALL_I2C_GET_CONFIG 120
#define K_SYSCALL_I2C_RECOVER_BUS 121
#define K_SYSCALL_I2C_TARGET_DRIVER_REGISTER 122
#define K_SYSCALL_I2C_TARGET_DRIVER_UNREGISTER 123
#define K_SYSCALL_I2C_TRANSFER 124
#define K_SYSCALL_I2S_BUF_READ 125
#define K_SYSCALL_I2S_BUF_WRITE 126
#define K_SYSCALL_I2S_CONFIGURE 127
#define K_SYSCALL_I2S_TRIGGER 128
#define K_SYSCALL_I3C_DO_CCC 129
#define K_SYSCALL_I3C_TRANSFER 130
#define K_SYSCALL_IPM_COMPLETE 131
#define K_SYSCALL_IPM_MAX_DATA_SIZE_GET 132
#define K_SYSCALL_IPM_MAX_ID_VAL_GET 133
#define K_SYSCALL_IPM_SEND 134
#define K_SYSCALL_IPM_SET_ENABLED 135
#define K_SYSCALL_IVSHMEM_GET_ID 136
#define K_SYSCALL_IVSHMEM_GET_MEM 137
#define K_SYSCALL_IVSHMEM_GET_VECTORS 138
#define K_SYSCALL_IVSHMEM_INT_PEER 139
#define K_SYSCALL_IVSHMEM_REGISTER_HANDLER 140
#define K_SYSCALL_KSCAN_CONFIG 141
#define K_SYSCALL_KSCAN_DISABLE_CALLBACK 142
#define K_SYSCALL_KSCAN_ENABLE_CALLBACK 143
#define K_SYSCALL_K_BUSY_WAIT 144
#define K_SYSCALL_K_CONDVAR_BROADCAST 145
#define K_SYSCALL_K_CONDVAR_INIT 146
#define K_SYSCALL_K_CONDVAR_SIGNAL 147
#define K_SYSCALL_K_CONDVAR_WAIT 148
#define K_SYSCALL_K_EVENT_CLEAR 149
#define K_SYSCALL_K_EVENT_INIT 150
#define K_SYSCALL_K_EVENT_POST 151
#define K_SYSCALL_K_EVENT_SET 152
#define K_SYSCALL_K_EVENT_SET_MASKED 153
#define K_SYSCALL_K_EVENT_WAIT 154
#define K_SYSCALL_K_EVENT_WAIT_ALL 155
#define K_SYSCALL_K_FLOAT_DISABLE 156
#define K_SYSCALL_K_FLOAT_ENABLE 157
#define K_SYSCALL_K_FUTEX_WAIT 158
#define K_SYSCALL_K_FUTEX_WAKE 159
#define K_SYSCALL_K_IS_PREEMPT_THREAD 160
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_IN_GET 161
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_OUT_GET 162
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_EVICTION_GET 163
#define K_SYSCALL_K_MEM_PAGING_STATS_GET 164
#define K_SYSCALL_K_MEM_PAGING_THREAD_STATS_GET 165
#define K_SYSCALL_K_MSGQ_ALLOC_INIT 166
#define K_SYSCALL_K_MSGQ_GET 167
#define K_SYSCALL_K_MSGQ_GET_ATTRS 168
#define K_SYSCALL_K_MSGQ_NUM_FREE_GET 169
#define K_SYSCALL_K_MSGQ_NUM_USED_GET 170
#define K_SYSCALL_K_MSGQ_PEEK 171
#define K_SYSCALL_K_MSGQ_PURGE 172
#define K_SYSCALL_K_MSGQ_PUT 173
#define K_SYSCALL_K_MUTEX_INIT 174
#define K_SYSCALL_K_MUTEX_LOCK 175
#define K_SYSCALL_K_MUTEX_UNLOCK 176
#define K_SYSCALL_K_OBJECT_ACCESS_GRANT 177
#define K_SYSCALL_K_OBJECT_ALLOC 178
#define K_SYSCALL_K_OBJECT_RELEASE 179
#define K_SYSCALL_K_PIPE_ALLOC_INIT 180
#define K_SYSCALL_K_PIPE_BUFFER_FLUSH 181
#define K_SYSCALL_K_PIPE_FLUSH 182
#define K_SYSCALL_K_PIPE_GET 183
#define K_SYSCALL_K_PIPE_PUT 184
#define K_SYSCALL_K_PIPE_READ_AVAIL 185
#define K_SYSCALL_K_PIPE_WRITE_AVAIL 186
#define K_SYSCALL_K_POLL 187
#define K_SYSCALL_K_POLL_SIGNAL_CHECK 188
#define K_SYSCALL_K_POLL_SIGNAL_INIT 189
#define K_SYSCALL_K_POLL_SIGNAL_RAISE 190
#define K_SYSCALL_K_POLL_SIGNAL_RESET 191
#define K_SYSCALL_K_QUEUE_ALLOC_APPEND 192
#define K_SYSCALL_K_QUEUE_ALLOC_PREPEND 193
#define K_SYSCALL_K_QUEUE_CANCEL_WAIT 194
#define K_SYSCALL_K_QUEUE_GET 195
#define K_SYSCALL_K_QUEUE_INIT 196
#define K_SYSCALL_K_QUEUE_IS_EMPTY 197
#define K_SYSCALL_K_QUEUE_PEEK_HEAD 198
#define K_SYSCALL_K_QUEUE_PEEK_TAIL 199
#define K_SYSCALL_K_SEM_COUNT_GET 200
#define K_SYSCALL_K_SEM_GIVE 201
#define K_SYSCALL_K_SEM_INIT 202
#define K_SYSCALL_K_SEM_RESET 203
#define K_SYSCALL_K_SEM_TAKE 204
#define K_SYSCALL_K_SLEEP 205
#define K_SYSCALL_K_STACK_ALLOC_INIT 206
#define K_SYSCALL_K_STACK_POP 207
#define K_SYSCALL_K_STACK_PUSH 208
#define K_SYSCALL_K_STR_OUT 209
#define K_SYSCALL_K_THREAD_ABORT 210
#define K_SYSCALL_K_THREAD_CREATE 211
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_GET 212
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_SET 213
#define K_SYSCALL_K_THREAD_DEADLINE_SET 214
#define K_SYSCALL_K_THREAD_JOIN 215
#define K_SYSCALL_K_THREAD_NAME_COPY 216
#define K_SYSCALL_K_THREAD_NAME_SET 217
#define K_SYSCALL_K_THREAD_PRIORITY_GET 218
#define K_SYSCALL_K_THREAD_PRIORITY_SET 219
#define K_SYSCALL_K_THREAD_RESUME 220
#define K_SYSCALL_K_THREAD_STACK_SPACE_GET 221
#define K_SYSCALL_K_THREAD_START 222
#define K_SYSCALL_K_THREAD_SUSPEND 223
#define K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS 224
#define K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS 225
#define K_SYSCALL_K_TIMER_EXPIRES_TICKS 226
#define K_SYSCALL_K_TIMER_REMAINING_TICKS 227
#define K_SYSCALL_K_TIMER_START 228
#define K_SYSCALL_K_TIMER_STATUS_GET 229
#define K_SYSCALL_K_TIMER_STATUS_SYNC 230
#define K_SYSCALL_K_TIMER_STOP 231
#define K_SYSCALL_K_TIMER_USER_DATA_GET 232
#define K_SYSCALL_K_TIMER_USER_DATA_SET 233
#define K_SYSCALL_K_UPTIME_TICKS 234
#define K_SYSCALL_K_USLEEP 235
#define K_SYSCALL_K_WAKEUP 236
#define K_SYSCALL_K_YIELD 237
#define K_SYSCALL_LED_BLINK 238
#define K_SYSCALL_LED_GET_INFO 239
#define K_SYSCALL_LED_OFF 240
#define K_SYSCALL_LED_ON 241
#define K_SYSCALL_LED_SET_BRIGHTNESS 242
#define K_SYSCALL_LED_SET_CHANNEL 243
#define K_SYSCALL_LED_SET_COLOR 244
#define K_SYSCALL_LED_WRITE_CHANNELS 245
#define K_SYSCALL_LOG_BUFFERED_CNT 246
#define K_SYSCALL_LOG_FILTER_SET 247
#define K_SYSCALL_LOG_PANIC 248
#define K_SYSCALL_LOG_PROCESS 249
#define K_SYSCALL_MAXIM_DS3231_GET_SYNCPOINT 250
#define K_SYSCALL_MAXIM_DS3231_REQ_SYNCPOINT 251
#define K_SYSCALL_MBOX_MAX_CHANNELS_GET 252
#define K_SYSCALL_MBOX_MTU_GET 253
#define K_SYSCALL_MBOX_SEND 254
#define K_SYSCALL_MBOX_SET_ENABLED 255
#define K_SYSCALL_MDIO_BUS_DISABLE 256
#define K_SYSCALL_MDIO_BUS_ENABLE 257
#define K_SYSCALL_MDIO_READ 258
#define K_SYSCALL_MDIO_WRITE 259
#define K_SYSCALL_NET_ADDR_NTOP 260
#define K_SYSCALL_NET_ADDR_PTON 261
#define K_SYSCALL_NET_ETH_GET_PTP_CLOCK_BY_INDEX 262
#define K_SYSCALL_NET_IF_GET_BY_INDEX 263
#define K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX 264
#define K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX 265
#define K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX 266
#define K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX 267
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX 268
#define K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX 269
#define K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX 270
#define K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX 271
#define K_SYSCALL_NRF_QSPI_NOR_BASE_CLOCK_DIV_FORCE 272
#define K_SYSCALL_PECI_CONFIG 273
#define K_SYSCALL_PECI_DISABLE 274
#define K_SYSCALL_PECI_ENABLE 275
#define K_SYSCALL_PECI_TRANSFER 276
#define K_SYSCALL_PHY_CONFIGURE_LINK 277
#define K_SYSCALL_PHY_GET_LINK_STATE 278
#define K_SYSCALL_PHY_LINK_CALLBACK_SET 279
#define K_SYSCALL_PHY_READ 280
#define K_SYSCALL_PHY_WRITE 281
#define K_SYSCALL_PS2_CONFIG 282
#define K_SYSCALL_PS2_DISABLE_CALLBACK 283
#define K_SYSCALL_PS2_ENABLE_CALLBACK 284
#define K_SYSCALL_PS2_READ 285
#define K_SYSCALL_PS2_WRITE 286
#define K_SYSCALL_PTP_CLOCK_GET 287
#define K_SYSCALL_PWM_CAPTURE_CYCLES 288
#define K_SYSCALL_PWM_DISABLE_CAPTURE 289
#define K_SYSCALL_PWM_ENABLE_CAPTURE 290
#define K_SYSCALL_PWM_GET_CYCLES_PER_SEC 291
#define K_SYSCALL_PWM_SET_CYCLES 292
#define K_SYSCALL_RESET_LINE_ASSERT 293
#define K_SYSCALL_RESET_LINE_DEASSERT 294
#define K_SYSCALL_RESET_LINE_TOGGLE 295
#define K_SYSCALL_RESET_STATUS 296
#define K_SYSCALL_RTIO_CQE_COPY_OUT 297
#define K_SYSCALL_RTIO_SQE_COPY_IN 298
#define K_SYSCALL_RTIO_SUBMIT 299
#define K_SYSCALL_SDHC_CARD_BUSY 300
#define K_SYSCALL_SDHC_CARD_PRESENT 301
#define K_SYSCALL_SDHC_EXECUTE_TUNING 302
#define K_SYSCALL_SDHC_GET_HOST_PROPS 303
#define K_SYSCALL_SDHC_HW_RESET 304
#define K_SYSCALL_SDHC_REQUEST 305
#define K_SYSCALL_SDHC_SET_IO 306
#define K_SYSCALL_SENSOR_ATTR_GET 307
#define K_SYSCALL_SENSOR_ATTR_SET 308
#define K_SYSCALL_SENSOR_CHANNEL_GET 309
#define K_SYSCALL_SENSOR_SAMPLE_FETCH 310
#define K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN 311
#define K_SYSCALL_SPI_RELEASE 312
#define K_SYSCALL_SPI_TRANSCEIVE 313
#define K_SYSCALL_SYSCON_GET_BASE 314
#define K_SYSCALL_SYSCON_GET_SIZE 315
#define K_SYSCALL_SYSCON_READ_REG 316
#define K_SYSCALL_SYSCON_WRITE_REG 317
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_AND_INVD_RANGE 318
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_RANGE 319
#define K_SYSCALL_SYS_CACHE_DATA_INVD_RANGE 320
#define K_SYSCALL_SYS_CLOCK_HW_CYCLES_PER_SEC_RUNTIME_GET 321
#define K_SYSCALL_SYS_CSRAND_GET 322
#define K_SYSCALL_SYS_RAND32_GET 323
#define K_SYSCALL_SYS_RAND_GET 324
#define K_SYSCALL_UART_CONFIGURE 325
#define K_SYSCALL_UART_CONFIG_GET 326
#define K_SYSCALL_UART_DRV_CMD 327
#define K_SYSCALL_UART_ERR_CHECK 328
#define K_SYSCALL_UART_IRQ_ERR_DISABLE 329
#define K_SYSCALL_UART_IRQ_ERR_ENABLE 330
#define K_SYSCALL_UART_IRQ_IS_PENDING 331
#define K_SYSCALL_UART_IRQ_RX_DISABLE 332
#define K_SYSCALL_UART_IRQ_RX_ENABLE 333
#define K_SYSCALL_UART_IRQ_TX_DISABLE 334
#define K_SYSCALL_UART_IRQ_TX_ENABLE 335
#define K_SYSCALL_UART_IRQ_UPDATE 336
#define K_SYSCALL_UART_LINE_CTRL_GET 337
#define K_SYSCALL_UART_LINE_CTRL_SET 338
#define K_SYSCALL_UART_MUX_FIND 339
#define K_SYSCALL_UART_POLL_IN 340
#define K_SYSCALL_UART_POLL_IN_U16 341
#define K_SYSCALL_UART_POLL_OUT 342
#define K_SYSCALL_UART_POLL_OUT_U16 343
#define K_SYSCALL_UART_RX_DISABLE 344
#define K_SYSCALL_UART_RX_ENABLE 345
#define K_SYSCALL_UART_RX_ENABLE_U16 346
#define K_SYSCALL_UART_TX 347
#define K_SYSCALL_UART_TX_ABORT 348
#define K_SYSCALL_UART_TX_U16 349
#define K_SYSCALL_USER_FAULT 350
#define K_SYSCALL_W1_CHANGE_BUS_LOCK 351
#define K_SYSCALL_W1_CONFIGURE 352
#define K_SYSCALL_W1_GET_SLAVE_COUNT 353
#define K_SYSCALL_W1_READ_BIT 354
#define K_SYSCALL_W1_READ_BLOCK 355
#define K_SYSCALL_W1_READ_BYTE 356
#define K_SYSCALL_W1_RESET_BUS 357
#define K_SYSCALL_W1_SEARCH_BUS 358
#define K_SYSCALL_W1_WRITE_BIT 359
#define K_SYSCALL_W1_WRITE_BLOCK 360
#define K_SYSCALL_W1_WRITE_BYTE 361
#define K_SYSCALL_WDT_DISABLE 362
#define K_SYSCALL_WDT_FEED 363
#define K_SYSCALL_WDT_SETUP 364
#define K_SYSCALL_ZEPHYR_FPUTC 365
#define K_SYSCALL_ZEPHYR_FWRITE 366
#define K_SYSCALL_ZEPHYR_READ_STDIN 367
#define K_SYSCALL_ZEPHYR_WRITE_STDOUT 368
#define K_SYSCALL_ZSOCK_ACCEPT 369
#define K_SYSCALL_ZSOCK_BIND 370
#define K_SYSCALL_ZSOCK_CLOSE 371
#define K_SYSCALL_ZSOCK_CONNECT 372
#define K_SYSCALL_ZSOCK_FCNTL 373
#define K_SYSCALL_ZSOCK_GETHOSTNAME 374
#define K_SYSCALL_ZSOCK_GETPEERNAME 375
#define K_SYSCALL_ZSOCK_GETSOCKNAME 376
#define K_SYSCALL_ZSOCK_GETSOCKOPT 377
#define K_SYSCALL_ZSOCK_GET_CONTEXT_OBJECT 378
#define K_SYSCALL_ZSOCK_INET_PTON 379
#define K_SYSCALL_ZSOCK_LISTEN 380
#define K_SYSCALL_ZSOCK_POLL 381
#define K_SYSCALL_ZSOCK_RECVFROM 382
#define K_SYSCALL_ZSOCK_SELECT 383
#define K_SYSCALL_ZSOCK_SENDMSG 384
#define K_SYSCALL_ZSOCK_SENDTO 385
#define K_SYSCALL_ZSOCK_SETSOCKOPT 386
#define K_SYSCALL_ZSOCK_SHUTDOWN 387
#define K_SYSCALL_ZSOCK_SOCKET 388
#define K_SYSCALL_ZSOCK_SOCKETPAIR 389
#define K_SYSCALL_Z_CURRENT_GET 390
#define K_SYSCALL_Z_ERRNO 391
#define K_SYSCALL_Z_LOG_MSG_RUNTIME_VCREATE 392
#define K_SYSCALL_Z_LOG_MSG_STATIC_CREATE 393
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_LOCK 394
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_UNLOCK 395
#define K_SYSCALL_Z_ZSOCK_GETADDRINFO_INTERNAL 396
#define K_SYSCALL_BAD 397
#define K_SYSCALL_LIMIT 398


#ifndef _ASMLANGUAGE

#include <stdint.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SYSCALL_LIST_H */