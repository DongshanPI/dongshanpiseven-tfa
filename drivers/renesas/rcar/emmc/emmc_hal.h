/*
 * Copyright (c) 2015-2017, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file  emmc_hal.h
 * @brief emmc boot driver is expecting this header file
 *
 */

#ifndef EMMC_HAL_H
#define EMMC_HAL_H
/* ************************ HEADER (INCLUDE) SECTION *********************** */
#include <stdint.h>
/* ***************** MACROS, CONSTANTS, COMPILATION FLAGS ****************** */

/** @brief memory card error/status types
 */
#define HAL_MEMCARD_OUT_OF_RANGE            0x80000000L
#define HAL_MEMCARD_ADDRESS_ERROR           0x40000000L
#define HAL_MEMCARD_BLOCK_LEN_ERROR         0x20000000L
#define HAL_MEMCARD_ERASE_SEQ_ERROR         0x10000000L
#define HAL_MEMCARD_ERASE_PARAM             0x08000000L
#define HAL_MEMCARD_WP_VIOLATION            0x04000000L
#define HAL_MEMCARD_CARD_IS_LOCKED          0x02000000L
#define HAL_MEMCARD_LOCK_UNLOCK_FAILED      0x01000000L
#define HAL_MEMCARD_COM_CRC_ERROR           0x00800000L
#define HAL_MEMCARD_ILEGAL_COMMAND          0x00400000L
#define HAL_MEMCARD_CARD_ECC_FAILED         0x00200000L
#define HAL_MEMCARD_CC_ERROR                0x00100000L
#define HAL_MEMCARD_ERROR                   0x00080000L
#define HAL_MEMCARD_UNDERRUN                0x00040000L
#define HAL_MEMCARD_OVERRUN                 0x00020000L
#define HAL_MEMCARD_CIDCSD_OVERWRITE        0x00010000L
#define HAL_MEMCARD_WP_ERASE_SKIP           0x00008000L
#define HAL_MEMCARD_CARD_ECC_DISABLED       0x00004000L
#define HAL_MEMCARD_ERASE_RESET             0x00002000L
#define HAL_MEMCARD_CARD_STATE              0x00001E00L
#define HAL_MEMCARD_CARD_READY_FOR_DATA     0x00000100L
#define HAL_MEMCARD_APP_CMD                 0x00000020L
#define HAL_MEMCARD_SWITCH_ERROR            0x00000080L
#define HAL_MEMCARD_AKE_SEQ_ERROR           0x00000008L
#define HAL_MEMCARD_NO_ERRORS               0x00000000L

/** @brief Memory card response types
 */
#define HAL_MEMCARD_COMMAND_INDEX_MASK      0x0003f

/* ********************** STRUCTURES, TYPE DEFINITIONS ********************* */

/** @brief Type of the return value.
 */
typedef enum {
	HAL_MEMCARD_FAIL = 0U,
	HAL_MEMCARD_OK = 1U,
	HAL_MEMCARD_DMA_ALLOC_FAIL = 2U,     /**< DMA channel allocation failed */
	HAL_MEMCARD_DMA_TRANSFER_FAIL = 3U,  /**< DMA transfer failed */
	HAL_MEMCARD_CARD_STATUS_ERROR = 4U,  /**< A non-masked error bit was set in the card status */
	HAL_MEMCARD_CMD_TIMEOUT = 5U,	     /**< Command timeout occurred */
	HAL_MEMCARD_DATA_TIMEOUT = 6U,	     /**< Data timeout occurred */
	HAL_MEMCARD_CMD_CRC_ERROR = 7U,	     /**< Command CRC error occurred */
	HAL_MEMCARD_DATA_CRC_ERROR = 8U	     /**< Data CRC error occurred */
} HAL_MEMCARD_RETURN;

/** @brief memory access operation
 */
typedef enum {
	HAL_MEMCARD_READ = 0U,	 /**< read */
	HAL_MEMCARD_WRITE = 1U	 /**< write */
} HAL_MEMCARD_OPERATION;

/** @brief Type of data width on memorycard bus
 */
typedef enum {
	HAL_MEMCARD_DATA_WIDTH_1_BIT = 0U,
	HAL_MEMCARD_DATA_WIDTH_4_BIT = 1U,
	HAL_MEMCARD_DATA_WIDTH_8_BIT = 2U
} HAL_MEMCARD_DATA_WIDTH; /**< data (bus) width types */

/** @brief Presence of the memory card
 */
typedef enum {
	HAL_MEMCARD_CARD_IS_IN = 0U,
	HAL_MEMCARD_CARD_IS_OUT = 1U
} HAL_MEMCARD_PRESENCE_STATUS;	/* presence status of the memory card */

/** @brief mode of data transfer
 */
typedef enum {
	HAL_MEMCARD_DMA = 0U,
	HAL_MEMCARD_NOT_DMA = 1U
} HAL_MEMCARD_DATA_TRANSFER_MODE;

/** @brief Memory card response types.
 */
typedef enum hal_memcard_response_type {
	HAL_MEMCARD_RESPONSE_NONE = 0x00000U,
	HAL_MEMCARD_RESPONSE_R1 = 0x00100U,
	HAL_MEMCARD_RESPONSE_R1b = 0x00200U,
	HAL_MEMCARD_RESPONSE_R2 = 0x00300U,
	HAL_MEMCARD_RESPONSE_R3 = 0x00400U,
	HAL_MEMCARD_RESPONSE_R4 = 0x00500U,
	HAL_MEMCARD_RESPONSE_R5 = 0x00600U,
	HAL_MEMCARD_RESPONSE_R6 = 0x00700U,
	HAL_MEMCARD_RESPONSE_R7 = 0x00800U,
	HAL_MEMCARD_RESPONSE_TYPE_MASK = 0x00f00U
} HAL_MEMCARD_RESPONSE_TYPE;

/** @brief Memory card command types.
 */
typedef enum hal_memcard_command_type {
	HAL_MEMCARD_COMMAND_TYPE_BC = 0x00000U,
	HAL_MEMCARD_COMMAND_TYPE_BCR = 0x01000U,
	HAL_MEMCARD_COMMAND_TYPE_AC = 0x02000U,
	HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE = 0x03000U,
	HAL_MEMCARD_COMMAND_TYPE_ADTC_READ = 0x04000U,
	HAL_MEMCARD_COMMAND_TYPE_MASK = 0x07000U
} HAL_MEMCARD_COMMAND_TYPE;

/** @brief Type of memory card
 */
typedef enum hal_memcard_command_card_type {
	HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON = 0x00000U,
	HAL_MEMCARD_COMMAND_CARD_TYPE_MMC = 0x08000U,
	HAL_MEMCARD_COMMAND_CARD_TYPE_SD = 0x10000U,
	HAL_MEMCARD_COMMAND_CARD_TYPE_MASK = 0x18000U
} HAL_MEMCARD_COMMAND_CARD_TYPE;

/** @brief Memory card application command.
 */
typedef enum hal_memcard_command_app_norm {
	HAL_MEMCARD_COMMAND_NORMAL = 0x00000U,
	HAL_MEMCARD_COMMAND_APP = 0x20000U,
	HAL_MEMCARD_COMMAND_APP_NORM_MASK = 0x20000U
} HAL_MEMCARD_COMMAND_APP_NORM;

/** @brief Memory card command codes.
 */
typedef enum {
/* class 0 and class 1 */
	CMD0_GO_IDLE_STATE = 0 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_BC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD0 */
	CMD1_SEND_OP_COND = 1 | HAL_MEMCARD_RESPONSE_R3 | HAL_MEMCARD_COMMAND_TYPE_BCR | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD1 */
	CMD2_ALL_SEND_CID_MMC = 2 | HAL_MEMCARD_RESPONSE_R2 | HAL_MEMCARD_COMMAND_TYPE_BCR | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD2 */
	CMD2_ALL_SEND_CID_SD =
	    2 | HAL_MEMCARD_RESPONSE_R2 | HAL_MEMCARD_COMMAND_TYPE_BCR |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,
	CMD3_SET_RELATIVE_ADDR = 3 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD3 */
	CMD3_SEND_RELATIVE_ADDR =
	    3 | HAL_MEMCARD_RESPONSE_R6 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,
	CMD4_SET_DSR = 4 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_BC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD4 */
	CMD5_SLEEP_AWAKE = 5 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD5 */
	CMD6_SWITCH = 6 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD6 */
	CMD6_SWITCH_FUNC =
	    6 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,
	ACMD6_SET_BUS_WIDTH =
	    6 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,
	CMD7_SELECT_CARD = 7 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD7 */
	CMD7_SELECT_CARD_PROG = 7 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD7(from Disconnected State to Programming State) */
	CMD7_DESELECT_CARD =
	    7 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,
	CMD8_SEND_EXT_CSD = 8 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD8 */
	CMD8_SEND_IF_COND =
	    8 | HAL_MEMCARD_RESPONSE_R7 | HAL_MEMCARD_COMMAND_TYPE_BCR |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,
	CMD9_SEND_CSD = 9 | HAL_MEMCARD_RESPONSE_R2 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD9 */
	CMD10_SEND_CID = 10 | HAL_MEMCARD_RESPONSE_R2 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD10 */
	CMD11_READ_DAT_UNTIL_STOP = 11 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD11 */
	CMD12_STOP_TRANSMISSION = 12 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD12 */
	CMD12_STOP_TRANSMISSION_WRITE = 12 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD12(R1b : write case) */
	CMD13_SEND_STATUS = 13 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD13 */
	ACMD13_SD_STATUS =
	    13 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,
	CMD14_BUSTEST_R = 14 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD14 */
	CMD15_GO_INACTIVE_STATE = 15 | HAL_MEMCARD_RESPONSE_NONE | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD15 */

/* class 2 */
	CMD16_SET_BLOCKLEN = 16 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD16 */
	CMD17_READ_SINGLE_BLOCK = 17 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD17 */
	CMD18_READ_MULTIPLE_BLOCK = 18 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD18 */
	CMD19_BUS_TEST_W = 19 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD19 */

/* class 3 */
	CMD20_WRITE_DAT_UNTIL_STOP = 20 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD20 */
	CMD21 = 21,		/* CMD21 */
	CMD22 = 22,		/* CMD22 */
	ACMD22_SEND_NUM_WR_BLOCKS =
	    22 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,

/* class 4 */
	CMD23_SET_BLOCK_COUNT = 23 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD23 */
	ACMD23_SET_WR_BLK_ERASE_COUNT =
	    23 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,
	CMD24_WRITE_BLOCK = 24 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD24 */
	CMD25_WRITE_MULTIPLE_BLOCK = 25 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD25 */
	CMD26_PROGRAM_CID = 26 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD26 */
	CMD27_PROGRAM_CSD = 27 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD27 */

/* class 6 */
	CMD28_SET_WRITE_PROT = 28 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD28 */
	CMD29_CLR_WRITE_PROT = 29 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD29 */
	CMD30_SEND_WRITE_PROT = 30 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD30 */
	CMD30_SEND_WRITE_PROT_TYPE = 31 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD31 */

/* class 5 */
	CMD32_ERASE_WR_BLK_START = 32 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD32 */
	CMD33_ERASE_WR_BLK_END = 33 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD33 */
	CMD34 = 34,		/* CMD34 */
	CMD35_ERASE_GROUP_START = 35 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD35 */
	CMD36_ERASE_GROUP_END = 36 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD36 */
	CMD37 = 37,		/* CMD37 */
	CMD38_ERASE = 38 | HAL_MEMCARD_RESPONSE_R1b | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD38 */

/* class 9 */
	CMD39_FASTIO = 39 | HAL_MEMCARD_RESPONSE_R4 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD39 */
	CMD40_GO_IRQSTATE = 40 | HAL_MEMCARD_RESPONSE_R5 | HAL_MEMCARD_COMMAND_TYPE_BCR | HAL_MEMCARD_COMMAND_CARD_TYPE_MMC | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD40 */
	CMD41 = 41,		/* CMD41 */
	ACMD41_SD_SEND_OP_COND =
	    41 | HAL_MEMCARD_RESPONSE_R3 | HAL_MEMCARD_COMMAND_TYPE_BCR |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,

/* class 7 */
	CMD42_LOCK_UNLOCK = 42 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD42 */
	ACMD42_SET_CLR_CARD_DETECT =
	    42 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,
	CMD43 = 43,		/* CMD43 */
	CMD44 = 44,		/* CMD44 */
	CMD45 = 45,		/* CMD45 */
	CMD46 = 46,		/* CMD46 */
	CMD47 = 47,		/* CMD47 */
	CMD48 = 48,		/* CMD48 */
	CMD49 = 49,		/* CMD49 */
	CMD50 = 50,		/* CMD50 */
	CMD51 = 51,		/* CMD51 */
	ACMD51_SEND_SCR =
	    51 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_READ |
	    HAL_MEMCARD_COMMAND_CARD_TYPE_SD | HAL_MEMCARD_COMMAND_APP,
	CMD52 = 52,		/* CMD52 */
	CMD53 = 53,		/* CMD53 */
	CMD54 = 54,		/* CMD54 */

/* class 8 */
	CMD55_APP_CMD = 55 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_AC | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD55 */
	CMD56_GEN_CMD = 56 | HAL_MEMCARD_RESPONSE_R1 | HAL_MEMCARD_COMMAND_TYPE_ADTC_WRITE | HAL_MEMCARD_COMMAND_CARD_TYPE_COMMON | HAL_MEMCARD_COMMAND_NORMAL,	/* CMD56 */
	CMD57 = 57,		/* CMD57 */
	CMD58 = 58,		/* CMD58 */
	CMD59 = 59,		/* CMD59 */
	CMD60 = 60,		/* CMD60 */
	CMD61 = 61,		/* CMD61 */
	CMD62 = 62,		/* CMD62 */
	CMD63 = 63		/* CMD63 */
} HAL_MEMCARD_COMMAND;

/** @brief Configuration structure from HAL layer.
 *
 * If some field is not available it should be filled with 0xFF.
 * The API version is 32-bit unsigned integer telling the version of the API. The integer is divided to four sections which each can be treated as a 8-bit unsigned number:
 * Bits 31-24 make the most significant part of the version number. This number starts from 1 i.e. the second version of the API will be 0x02xxxxxx. This number changes only, if the API itself changes so much that it is not compatible anymore with older releases.
 * Bits 23-16 API minor version number. For example API version 2.1 would be 0x0201xxxx.
 * Bits 15-8 are the number of the year when release is done. The 0 is year 2000, 1 is year 2001 and so on
 * Bits 7- are the week number when release is done. First full week of the year is 1
 *
 * @note Example: let's assume that release 2.1 is done on week 10 year 2008 the version will get the value 0x0201080A
 */
typedef struct {
    /**
    * Version of the chipset API implementation
    *
    * bits [31:24] API specification major version number.<br>
    * bits [23:16] API specification minor version number.<br>
    * bits [15:8] API implemention year. (2000 = 0, 2001 = 1, ...)<br>
    * bits [7:0] API implemention week.<br>
    * Example: API specification version 4.0, implementation w46 2008 => 0x0400082E
    */
	uint32_t api_version;

    /** maximum block count which can be transferred at once */
	uint32_t max_block_count;

    /** maximum clock frequence in Hz supported by HW */
	uint32_t max_clock_freq;

    /** maximum data bus width supported by HW */
	uint16_t max_data_width;

    /** Is high-speed mode supported by HW (yes=1, no=0) */
	uint8_t hs_mode_supported;

    /** Is memory card removable (yes=1, no=0) */
	uint8_t card_removable;

} HAL_MEMCARD_HW_CONF;

/** @brief Configuration structure to HAL layer.
 */
typedef struct {
    /** how many times to try after fail, for instance sending command */
	uint32_t retries_after_fail;
} HAL_MEMCARD_INIT_CONF;

/* ********************** DECLARATION OF EXTERNAL DATA ********************* */

/* ************************** FUNCTION PROTOTYPES ************************** */

/* ********************************* CODE ********************************** */

#endif /* EMMC_HAL_H */

/* ******************************** END ************************************ */
