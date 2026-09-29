//
// Created by aadia on 12/8/2026.
//

#ifndef BASIC_PICO_PROJECT_ILI9341_HW_H
#define BASIC_PICO_PROJECT_ILI9341_HW_H

//Commands List

#define NO_OP         0x00 ///< No-op register
#define SW_RESET     0x01 ///< Software reset register
#define READ_DISP_ID_INFO     0x04 ///< Read display identification information
#define READ_DISP_ST       0x09 ///< Read Display Status

#define SLP_EN       0x10 ///< Enter Sleep Mode
#define SLP_OUT      0x11 ///< Sleep Out
#define PTL_ON       0x12 ///< Partial Mode ON
#define NORM_ON       0x13 ///< Normal Display Mode ON

#define READ_DISP_POW_MODE      0x0A ///< Read Display Power Mode
#define READ_MADCTL    0x0B ///< Read Display MADCTL (Memory Access Data Control)
#define READ_PIX_FMT    0x0C ///< Read Display Pixel Format
#define READ_IMG_FMT    0x0D ///< Read Display Image Format
#define READ_SELF_DIAG  0x0F ///< Read Display Self-Diagnostic Result

#define INV_OFF      0x20 ///< Display Inversion OFF
#define INV_ON       0x21 ///< Display Inversion ON
#define GAMMA_SET    0x26 ///< Gamma Set
#define DISP_OFF     0x28 ///< Display OFF
#define DISP_ON      0x29 ///< Display ON

#define COL_ADD_SET       0x2A ///< Column Address Set
#define PA_ADD_SET       0x2B ///< Page Address Set
#define RAM_WR       0x2C ///< Memory Write
#define RAM_RD       0x2E ///< Memory Read

#define PTL_AR       0x30 ///< Partial Area
#define V_SCR_DEF     0x33 ///< Vertical Scrolling Definition
#define MADCTL      0x36 ///< Memory Access Control
#define V_SCR_ST_ADD    0x37 ///< Vertical Scrolling Start Address
#define PIX_FMT      0x3A ///< COLMOD: Pixel Format Set

#define FRM_CTR1     0xB1 ///< Frame Rate Control (In Norm Mode/Full Colors)
#define FRM_CTR2     0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define FRM_CTR3     0xB3 ///< Frame Rate control (In Part Mode/Full Colors)
#define INV_CTR      0xB4 ///< Display Inversion Control
#define DISP_FUN_CTR     0xB6 ///< Display Function Control

#define PW_CTR1      0xC0 ///< Power Control 1
#define PW_CTR2      0xC1 ///< Power Control 2
#define PW_CTR3      0xC2 ///< Power Control 3
#define PW_CTR4      0xC3 ///< Power Control 4
#define PW_CTR5      0xC4 ///< Power Control 5
#define VM_CTR1      0xC5 ///< VCOM Control 1
#define VM_CTR2      0xC7 ///< VCOM Control 2

#define READ_ID1       0xDA ///< Read ID 1
#define READ_ID2       0xDB ///< Read ID 2
#define READ_ID3       0xDC ///< Read ID 3
#define READ_ID4       0xDD ///< Read ID 4

#define GMCTRP1     0xE0 ///< Positive Gamma Correction
#define GMCTRN1     0xE1 ///< Negative Gamma Correction
//#define PW_CTR6     0xFC



#define MHz                 4000000L
#define PIX_WIDTH           240
#define PIX_HEIGHT          320
#define PIX_BIT_COUNT        (PIX_WIDTH * PIX_HEIGHT)
#define PIX_BYTE_COUNT       (PIX_BITCOUNT / 8)
#define PIX_W32COUNT        (PIX_BITCOUNT / 32)
#define PIX_BYTE_STRIDE     (PIX_WIDTH / 8)


#endif //BASIC_PICO_PROJECT_ILI9341_HW_H
