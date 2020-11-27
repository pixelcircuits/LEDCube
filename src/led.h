//-----------------------------------------------------------------------
// LED Interface Library
// summary:
//   LED data is output through DMA (but to go faster, is configured to eat up entire peripheral bus which means no additional DMA).
//   Data is decoded using a lookup table generated through the javascript function defined below.
// references:
//   https://www.pjrc.com/teensy/K20P64M72SF1RM.pdf
//-----------------------------------------------------------------------
#ifndef _led_h_
#define _led_h_

#include "system.h"

//-----------------------------------------------------------------------
// LED Interface Functions
//-----------------------------------------------------------------------
static void led_init();
static void led_outputLayer(uint8_t* dataBuffer, uint8_t layer);
static void led_dc(uint8_t brightness);

//-----------------------------------------------------------------------
// LED Defines
//-----------------------------------------------------------------------
#define DCB_B4_0 (((((DRIVER_DC_VAL_RED>>0) & 0x01) >> 0) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x01) >> 0) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x01) >> 0) * BIT_LED_BLUE))
#define DCB_B4_1 (((((DRIVER_DC_VAL_RED>>0) & 0x02) >> 1) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x02) >> 1) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x02) >> 1) * BIT_LED_BLUE))
#define DCB_B4_2 (((((DRIVER_DC_VAL_RED>>0) & 0x04) >> 2) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x04) >> 2) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x04) >> 2) * BIT_LED_BLUE))
#define DCB_B4_3 (((((DRIVER_DC_VAL_RED>>0) & 0x08) >> 3) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x08) >> 3) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x08) >> 3) * BIT_LED_BLUE))
#define DCB_B4_4 (((((DRIVER_DC_VAL_RED>>0) & 0x10) >> 4) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x10) >> 4) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x10) >> 4) * BIT_LED_BLUE))
#define DCB_B4_5 (((((DRIVER_DC_VAL_RED>>0) & 0x20) >> 5) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>0) & 0x20) >> 5) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>0) & 0x20) >> 5) * BIT_LED_BLUE))
#define DC_B4_LED  DCB_B4_5, DCB_B4_5+BIT_LED_CLK, DCB_B4_4, DCB_B4_4+BIT_LED_CLK, DCB_B4_3, DCB_B4_3+BIT_LED_CLK, DCB_B4_2, DCB_B4_2+BIT_LED_CLK, DCB_B4_1, DCB_B4_1+BIT_LED_CLK, DCB_B4_0, DCB_B4_0+BIT_LED_CLK
#define DCB_B3_0 (((((DRIVER_DC_VAL_RED>>1) & 0x01) >> 0) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x01) >> 0) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x01) >> 0) * BIT_LED_BLUE))
#define DCB_B3_1 (((((DRIVER_DC_VAL_RED>>1) & 0x02) >> 1) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x02) >> 1) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x02) >> 1) * BIT_LED_BLUE))
#define DCB_B3_2 (((((DRIVER_DC_VAL_RED>>1) & 0x04) >> 2) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x04) >> 2) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x04) >> 2) * BIT_LED_BLUE))
#define DCB_B3_3 (((((DRIVER_DC_VAL_RED>>1) & 0x08) >> 3) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x08) >> 3) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x08) >> 3) * BIT_LED_BLUE))
#define DCB_B3_4 (((((DRIVER_DC_VAL_RED>>1) & 0x10) >> 4) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x10) >> 4) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x10) >> 4) * BIT_LED_BLUE))
#define DCB_B3_5 (((((DRIVER_DC_VAL_RED>>1) & 0x20) >> 5) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>1) & 0x20) >> 5) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>1) & 0x20) >> 5) * BIT_LED_BLUE))
#define DC_B3_LED  DCB_B3_5, DCB_B3_5+BIT_LED_CLK, DCB_B3_4, DCB_B3_4+BIT_LED_CLK, DCB_B3_3, DCB_B3_3+BIT_LED_CLK, DCB_B3_2, DCB_B3_2+BIT_LED_CLK, DCB_B3_1, DCB_B3_1+BIT_LED_CLK, DCB_B3_0, DCB_B3_0+BIT_LED_CLK
#define DCB_B2_0 (((((DRIVER_DC_VAL_RED>>2) & 0x01) >> 0) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x01) >> 0) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x01) >> 0) * BIT_LED_BLUE))
#define DCB_B2_1 (((((DRIVER_DC_VAL_RED>>2) & 0x02) >> 1) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x02) >> 1) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x02) >> 1) * BIT_LED_BLUE))
#define DCB_B2_2 (((((DRIVER_DC_VAL_RED>>2) & 0x04) >> 2) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x04) >> 2) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x04) >> 2) * BIT_LED_BLUE))
#define DCB_B2_3 (((((DRIVER_DC_VAL_RED>>2) & 0x08) >> 3) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x08) >> 3) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x08) >> 3) * BIT_LED_BLUE))
#define DCB_B2_4 (((((DRIVER_DC_VAL_RED>>2) & 0x10) >> 4) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x10) >> 4) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x10) >> 4) * BIT_LED_BLUE))
#define DCB_B2_5 (((((DRIVER_DC_VAL_RED>>2) & 0x20) >> 5) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>2) & 0x20) >> 5) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>2) & 0x20) >> 5) * BIT_LED_BLUE))
#define DC_B2_LED  DCB_B2_5, DCB_B2_5+BIT_LED_CLK, DCB_B2_4, DCB_B2_4+BIT_LED_CLK, DCB_B2_3, DCB_B2_3+BIT_LED_CLK, DCB_B2_2, DCB_B2_2+BIT_LED_CLK, DCB_B2_1, DCB_B2_1+BIT_LED_CLK, DCB_B2_0, DCB_B2_0+BIT_LED_CLK
#define DCB_B1_0 (((((DRIVER_DC_VAL_RED>>3) & 0x01) >> 0) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x01) >> 0) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x01) >> 0) * BIT_LED_BLUE))
#define DCB_B1_1 (((((DRIVER_DC_VAL_RED>>3) & 0x02) >> 1) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x02) >> 1) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x02) >> 1) * BIT_LED_BLUE))
#define DCB_B1_2 (((((DRIVER_DC_VAL_RED>>3) & 0x04) >> 2) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x04) >> 2) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x04) >> 2) * BIT_LED_BLUE))
#define DCB_B1_3 (((((DRIVER_DC_VAL_RED>>3) & 0x08) >> 3) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x08) >> 3) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x08) >> 3) * BIT_LED_BLUE))
#define DCB_B1_4 (((((DRIVER_DC_VAL_RED>>3) & 0x10) >> 4) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x10) >> 4) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x10) >> 4) * BIT_LED_BLUE))
#define DCB_B1_5 (((((DRIVER_DC_VAL_RED>>3) & 0x20) >> 5) * BIT_LED_RED) | ((((DRIVER_DC_VAL_GREEN>>3) & 0x20) >> 5) * BIT_LED_GREEN) | ((((DRIVER_DC_VAL_BLUE>>3) & 0x20) >> 5) * BIT_LED_BLUE))
#define DC_B1_LED  DCB_B1_5, DCB_B1_5+BIT_LED_CLK, DCB_B1_4, DCB_B1_4+BIT_LED_CLK, DCB_B1_3, DCB_B1_3+BIT_LED_CLK, DCB_B1_2, DCB_B1_2+BIT_LED_CLK, DCB_B1_1, DCB_B1_1+BIT_LED_CLK, DCB_B1_0, DCB_B1_0+BIT_LED_CLK
#define LED_LAYERS_OFF     255
#define LED_LAYERS_IGNORE  254

//-----------------------------------------------------------------------
// Lookup Tables
//-----------------------------------------------------------------------
const uint32_t decode_lu_r[256] = { 0x00000000, 0x80000000, 0x80000000, 0x00800000, 0x80800000, 0x80008000, 0x00808000, 0x00000080, 0x00800080, 0x00008080, 0x00808080, 0xa0000000, 0xa0800000, 0x20808000, 0xa0000080, 0x20008080, 0xa0808080, 0x00a00000, 0x00a08000, 0x00a00080, 0x80208080, 0xa0200000, 0x20a08000, 0x20a00080, 0x20a08080, 0x80802000, 0x8080a000, 0x0000a080, 0xa0002000, 0x2080a000, 0x2000a080, 0x80202000, 0x80a0a000, 0x0020a080, 0x20a02000, 0x20202080, 0x20a0a080, 0x00008020, 0x008000a0, 0xa0000020, 0x200000a0, 0x208080a0, 0x80208020, 0x002080a0, 0xa0a00020, 0x20a000a0, 0x00802020, 0x800020a0, 0xa0002020, 0xa00020a0, 0x00202020, 0x002020a0, 0xa0202020, 0xa02020a0, 0x84000000, 0x04800080, 0x24800000, 0xa4800080, 0x04208000, 0x84208080, 0x24a08000, 0xa4a08080, 0x04002080, 0x24802000, 0xa4802080, 0x8420a000, 0x84a0a080, 0xa4202080, 0x84800020, 0x840080a0, 0xa4808020, 0x84200020, 0x042080a0, 0xa4a08020, 0x84002020, 0x0400a0a0, 0xa480a020, 0x04a02020, 0x8420a0a0, 0xa42020a0, 0x00048000, 0x20040000, 0xa0840080, 0x80a48000, 0xa0a40000, 0xa0a48080, 0x80842080, 0xa084a000, 0x80a42000, 0x20242000, 0x2024a080, 0x800400a0, 0x20848020, 0x80a40020, 0x20240020, 0xa02480a0, 0x008420a0, 0xa084a020, 0x8024a020, 0x20a42020, 0x04040000, 0x84048080, 0xa4840080, 0x84240080, 0xa4a48000, 0x8404a000, 0x2404a000, 0x04a42000, 0xa4242000, 0xa4a4a080, 0x048480a0, 0xa40480a0, 0x042480a0, 0xa4a400a0, 0x048420a0, 0xa40420a0, 0x042420a0, 0x242420a0, 0x80808400, 0xa0808400, 0x80a08400, 0xa0a08400, 0x8080a400, 0xa080a400, 0x80a0a400, 0xa0a0a400, 0x80808420, 0x200004a0, 0x802004a0, 0xa02004a0, 0x008024a0, 0xa08024a0, 0x0020a4a0, 0xa020a4a0, 0x04808480, 0x04200400, 0xa4200400, 0x04802400, 0x2400a400, 0x04a0a400, 0x24202480, 0x048004a0, 0x240084a0, 0x04a084a0, 0x04002420, 0x24802420, 0x8420a420, 0xa4a0a420, 0x00840480, 0xa0048480, 0x80a48480, 0x00842400, 0xa004a400, 0x00242480, 0x2024a480, 0x808484a0, 0x00a40420, 0x20a48420, 0x008424a0, 0xa004a4a0, 0xa0242420, 0x84048400, 0xa4040480, 0x84248480, 0x84042400, 0x2484a400, 0x04a42480, 0xa4a4a480, 0xa4840420, 0x042404a0, 0xa42484a0, 0x24842420, 0x84a4a420, 0x2424a4a0, 0xa0000004, 0x00a08004, 0x20208084, 0xa0002004, 0x80a0a004, 0x2020a084, 0x20800024, 0x002000a4, 0x20a080a4, 0x2000a024, 0x00a020a4, 0x04000004, 0xa4808004, 0x84208084, 0x0400a004, 0x24802084, 0xa4202004, 0x040000a4, 0xa48080a4, 0x24a08024, 0x8400a0a4, 0x0420a024, 0xa4a020a4, 0xa0840004, 0x00a40084, 0x00842004, 0x20842084, 0xa0242004, 0x800400a4, 0x80240024, 0xa02400a4, 0xa0042024, 0x00a420a4, 0x04840004, 0x24840084, 0xa4a40004, 0x0404a084, 0x0424a004, 0xa424a084, 0x24848024, 0x84a480a4, 0x040420a4, 0x84242024, 0xa4a420a4, 0x20008404, 0x80208484, 0x8080a404, 0x80202404, 0x20a02484, 0x20008424, 0x00a084a4, 0x000024a4, 0x00a02424, 0x2020a4a4, 0xa4808404, 0xa4200404, 0x84802484, 0x04a0a404, 0x84000424, 0xa48004a4, 0x24a08424, 0xa4002424, 0x0420a4a4, 0x80848404, 0x80a40404, 0x20a48484, 0xa0042484, 0xa024a404, 0x20040424, 0x002484a4, 0x000424a4, 0x0024a424, 0x04040404, 0x24048484, 0x24240484, 0x2404a404, 0x24242404, 0x840484a4, 0x842404a4, 0x0484a424, 0x04a42424, 0xa4a4a4a4 };
const uint32_t decode_lu_g[256] = { 0x00000000, 0x40000000, 0x40000000, 0x00400000, 0x40400000, 0x40004000, 0x00404000, 0x00000040, 0x00400040, 0x00004040, 0x00404040, 0x50000000, 0x50400000, 0x10404000, 0x50000040, 0x10004040, 0x50404040, 0x00500000, 0x00504000, 0x00500040, 0x40104040, 0x50100000, 0x10504000, 0x10500040, 0x10504040, 0x40401000, 0x40405000, 0x00005040, 0x50001000, 0x10405000, 0x10005040, 0x40101000, 0x40505000, 0x00105040, 0x10501000, 0x10101040, 0x10505040, 0x00004010, 0x00400050, 0x50000010, 0x10000050, 0x10404050, 0x40104010, 0x00104050, 0x50500010, 0x10500050, 0x00401010, 0x40001050, 0x50001010, 0x50001050, 0x00101010, 0x00101050, 0x50101010, 0x50101050, 0x42000000, 0x02400040, 0x12400000, 0x52400040, 0x02104000, 0x42104040, 0x12504000, 0x52504040, 0x02001040, 0x12401000, 0x52401040, 0x42105000, 0x42505040, 0x52101040, 0x42400010, 0x42004050, 0x52404010, 0x42100010, 0x02104050, 0x52504010, 0x42001010, 0x02005050, 0x52405010, 0x02501010, 0x42105050, 0x52101050, 0x00024000, 0x10020000, 0x50420040, 0x40524000, 0x50520000, 0x50524040, 0x40421040, 0x50425000, 0x40521000, 0x10121000, 0x10125040, 0x40020050, 0x10424010, 0x40520010, 0x10120010, 0x50124050, 0x00421050, 0x50425010, 0x40125010, 0x10521010, 0x02020000, 0x42024040, 0x52420040, 0x42120040, 0x52524000, 0x42025000, 0x12025000, 0x02521000, 0x52121000, 0x52525040, 0x02424050, 0x52024050, 0x02124050, 0x52520050, 0x02421050, 0x52021050, 0x02121050, 0x12121050, 0x40404200, 0x50404200, 0x40504200, 0x50504200, 0x40405200, 0x50405200, 0x40505200, 0x50505200, 0x40404210, 0x10000250, 0x40100250, 0x50100250, 0x00401250, 0x50401250, 0x00105250, 0x50105250, 0x02404240, 0x02100200, 0x52100200, 0x02401200, 0x12005200, 0x02505200, 0x12101240, 0x02400250, 0x12004250, 0x02504250, 0x02001210, 0x12401210, 0x42105210, 0x52505210, 0x00420240, 0x50024240, 0x40524240, 0x00421200, 0x50025200, 0x00121240, 0x10125240, 0x40424250, 0x00520210, 0x10524210, 0x00421250, 0x50025250, 0x50121210, 0x42024200, 0x52020240, 0x42124240, 0x42021200, 0x12425200, 0x02521240, 0x52525240, 0x52420210, 0x02120250, 0x52124250, 0x12421210, 0x42525210, 0x12125250, 0x50000002, 0x00504002, 0x10104042, 0x50001002, 0x40505002, 0x10105042, 0x10400012, 0x00100052, 0x10504052, 0x10005012, 0x00501052, 0x02000002, 0x52404002, 0x42104042, 0x02005002, 0x12401042, 0x52101002, 0x02000052, 0x52404052, 0x12504012, 0x42005052, 0x02105012, 0x52501052, 0x50420002, 0x00520042, 0x00421002, 0x10421042, 0x50121002, 0x40020052, 0x40120012, 0x50120052, 0x50021012, 0x00521052, 0x02420002, 0x12420042, 0x52520002, 0x02025042, 0x02125002, 0x52125042, 0x12424012, 0x42524052, 0x02021052, 0x42121012, 0x52521052, 0x10004202, 0x40104242, 0x40405202, 0x40101202, 0x10501242, 0x10004212, 0x00504252, 0x00001252, 0x00501212, 0x10105252, 0x52404202, 0x52100202, 0x42401242, 0x02505202, 0x42000212, 0x52400252, 0x12504212, 0x52001212, 0x02105252, 0x40424202, 0x40520202, 0x10524242, 0x50021242, 0x50125202, 0x10020212, 0x00124252, 0x00021252, 0x00125212, 0x02020202, 0x12024242, 0x12120242, 0x12025202, 0x12121202, 0x42024252, 0x42120252, 0x02425212, 0x02521212, 0x52525252 };
const uint32_t decode_lu_b[256] = { 0x00000000, 0x20000000, 0x20000000, 0x00200000, 0x20200000, 0x20002000, 0x00202000, 0x00000020, 0x00200020, 0x00002020, 0x00202020, 0x28000000, 0x28200000, 0x08202000, 0x28000020, 0x08002020, 0x28202020, 0x00280000, 0x00282000, 0x00280020, 0x20082020, 0x28080000, 0x08282000, 0x08280020, 0x08282020, 0x20200800, 0x20202800, 0x00002820, 0x28000800, 0x08202800, 0x08002820, 0x20080800, 0x20282800, 0x00082820, 0x08280800, 0x08080820, 0x08282820, 0x00002008, 0x00200028, 0x28000008, 0x08000028, 0x08202028, 0x20082008, 0x00082028, 0x28280008, 0x08280028, 0x00200808, 0x20000828, 0x28000808, 0x28000828, 0x00080808, 0x00080828, 0x28080808, 0x28080828, 0x21000000, 0x01200020, 0x09200000, 0x29200020, 0x01082000, 0x21082020, 0x09282000, 0x29282020, 0x01000820, 0x09200800, 0x29200820, 0x21082800, 0x21282820, 0x29080820, 0x21200008, 0x21002028, 0x29202008, 0x21080008, 0x01082028, 0x29282008, 0x21000808, 0x01002828, 0x29202808, 0x01280808, 0x21082828, 0x29080828, 0x00012000, 0x08010000, 0x28210020, 0x20292000, 0x28290000, 0x28292020, 0x20210820, 0x28212800, 0x20290800, 0x08090800, 0x08092820, 0x20010028, 0x08212008, 0x20290008, 0x08090008, 0x28092028, 0x00210828, 0x28212808, 0x20092808, 0x08290808, 0x01010000, 0x21012020, 0x29210020, 0x21090020, 0x29292000, 0x21012800, 0x09012800, 0x01290800, 0x29090800, 0x29292820, 0x01212028, 0x29012028, 0x01092028, 0x29290028, 0x01210828, 0x29010828, 0x01090828, 0x09090828, 0x20202100, 0x28202100, 0x20282100, 0x28282100, 0x20202900, 0x28202900, 0x20282900, 0x28282900, 0x20202108, 0x08000128, 0x20080128, 0x28080128, 0x00200928, 0x28200928, 0x00082928, 0x28082928, 0x01202120, 0x01080100, 0x29080100, 0x01200900, 0x09002900, 0x01282900, 0x09080920, 0x01200128, 0x09002128, 0x01282128, 0x01000908, 0x09200908, 0x21082908, 0x29282908, 0x00210120, 0x28012120, 0x20292120, 0x00210900, 0x28012900, 0x00090920, 0x08092920, 0x20212128, 0x00290108, 0x08292108, 0x00210928, 0x28012928, 0x28090908, 0x21012100, 0x29010120, 0x21092120, 0x21010900, 0x09212900, 0x01290920, 0x29292920, 0x29210108, 0x01090128, 0x29092128, 0x09210908, 0x21292908, 0x09092928, 0x28000001, 0x00282001, 0x08082021, 0x28000801, 0x20282801, 0x08082821, 0x08200009, 0x00080029, 0x08282029, 0x08002809, 0x00280829, 0x01000001, 0x29202001, 0x21082021, 0x01002801, 0x09200821, 0x29080801, 0x01000029, 0x29202029, 0x09282009, 0x21002829, 0x01082809, 0x29280829, 0x28210001, 0x00290021, 0x00210801, 0x08210821, 0x28090801, 0x20010029, 0x20090009, 0x28090029, 0x28010809, 0x00290829, 0x01210001, 0x09210021, 0x29290001, 0x01012821, 0x01092801, 0x29092821, 0x09212009, 0x21292029, 0x01010829, 0x21090809, 0x29290829, 0x08002101, 0x20082121, 0x20202901, 0x20080901, 0x08280921, 0x08002109, 0x00282129, 0x00000929, 0x00280909, 0x08082929, 0x29202101, 0x29080101, 0x21200921, 0x01282901, 0x21000109, 0x29200129, 0x09282109, 0x29000909, 0x01082929, 0x20212101, 0x20290101, 0x08292121, 0x28010921, 0x28092901, 0x08010109, 0x00092129, 0x00010929, 0x00092909, 0x01010101, 0x09012121, 0x09090121, 0x09012901, 0x09090901, 0x21012129, 0x21090129, 0x01212909, 0x01290909, 0x29292929 };
const uint8_t dc_sequence_b4[NUM_LEDS_PER_DRIVER*NUM_DRIVER_DC_BITS*2] = { DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED, DC_B4_LED };
const uint8_t dc_sequence_b3[NUM_LEDS_PER_DRIVER*NUM_DRIVER_DC_BITS*2] = { DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED, DC_B3_LED };
const uint8_t dc_sequence_b2[NUM_LEDS_PER_DRIVER*NUM_DRIVER_DC_BITS*2] = { DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED, DC_B2_LED };
const uint8_t dc_sequence_b1[NUM_LEDS_PER_DRIVER*NUM_DRIVER_DC_BITS*2] = { DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED, DC_B1_LED };

//-----------------------------------------------------------------------
// Helper Functions
//-----------------------------------------------------------------------
static inline void led_powerLayer(uint8_t layer) __attribute__((always_inline, unused));

//-----------------------------------------------------------------------
// LED Data
//-----------------------------------------------------------------------
static uint8_t led_buffer[2][NUM_DRIVER_GS_CYCLES*2];
static uint8_t* led_outputingBuffer;
static uint8_t* led_workingBuffer;
static volatile uint8_t led_outputtingLayer;

//-----------------------------------------------------------------------
// LED DMA Interrupt Routine
//-----------------------------------------------------------------------
void dma_ch0_isr() {
	DMA_CINT = 0; //clear interrupt request (interrupt for DMA channel0 cleared)
	
	//set blank high while we switch layers
	digitalByteWriteFast(LED_PORT, BIT_LED_BLANK);
	system_delay(1);
	
	//latch in the new data
	digitalWriteFast(PIN_LED_XLAT, HIGH);
	system_delay(1);
	digitalWriteFast(PIN_LED_XLAT, LOW);
	
	//power the new layer
	led_powerLayer(led_outputtingLayer);
}

//-----------------------------------------------------------------------
// Function Definitions
//-----------------------------------------------------------------------
static void led_init() {
	//data
	uint32_t i;
	for(i=0; i<NUM_DRIVER_GS_CYCLES*2; i+=2) {
		led_buffer[0][i] = led_buffer[1][i] = 0x00;
		if(i>=((NUM_DRIVER_GS_CYCLES*2)-(NUM_LEDS_PER_DRIVER*NUM_DRIVER_GS_BITS*2))) led_buffer[0][i+1] = led_buffer[1][i+1] = BIT_LED_CLK | BIT_LED_GSCLK;
		else led_buffer[0][i+1] = led_buffer[1][i+1] = BIT_LED_GSCLK;
	}
	led_outputingBuffer = led_buffer[0];
	led_workingBuffer = led_buffer[1];
	led_outputtingLayer = LED_LAYERS_OFF;
	
	//enable peripheral clocks for DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX;
	SIM_SCGC7 |= SIM_SCGC7_DMA;
	
	//set pin modes
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_GREEN, OUTPUT);
	pinMode(PIN_LED_BLUE, OUTPUT);
	pinMode(PIN_LED_CLK, OUTPUT);
	pinMode(PIN_LED_XLAT, OUTPUT);
	pinMode(PIN_LED_GSCLK, OUTPUT);
	pinMode(PIN_LED_BLANK, OUTPUT);
	pinMode(PIN_LED_VPRG, OUTPUT);
	pinMode(PIN_LED_DCPRG, OUTPUT);
	pinMode(PIN_LAYER_0, OUTPUT);
	pinMode(PIN_LAYER_1, OUTPUT);
	pinMode(PIN_LAYER_2, OUTPUT);
	pinMode(PIN_LAYER_3, OUTPUT);
	pinMode(PIN_LAYER_4, OUTPUT);
	pinMode(PIN_LAYER_5, OUTPUT);
	pinMode(PIN_LAYER_6, OUTPUT);
	pinMode(PIN_LAYER_7, OUTPUT);
	pinMode(PIN_LAYER_8, OUTPUT);
	pinMode(PIN_LAYER_9, OUTPUT);
	digitalWriteFast(PIN_LED_VPRG, LOW);
	digitalWriteFast(PIN_LED_DCPRG, HIGH);
	digitalWriteFast(PIN_LED_BLANK, HIGH);
	digitalWriteFast(PIN_LED_RED, LOW);
	digitalWriteFast(PIN_LED_GREEN, LOW);
	digitalWriteFast(PIN_LED_BLUE, LOW);
	digitalWriteFast(PIN_LED_CLK, LOW);
	digitalWriteFast(PIN_LED_XLAT, LOW);
	digitalWriteFast(PIN_LED_GSCLK, LOW);
	led_powerLayer(LED_LAYERS_OFF);
	
	//set DMA control register (defaults, no halt)
	DMA_CR = 0;
	
	//setup receive DMA (transfer control descriptor)
	DMA_TCD0_SADDR = led_outputingBuffer; //source address
	DMA_TCD0_SOFF = 1; //source offset (amount to incriment source address each iteration)
	DMA_TCD0_SLAST = -2*NUM_DRIVER_GS_CYCLES; //adjustment value added to the source address at the completion of the major iteration count
	DMA_TCD0_DADDR = &GPIOD_PDOR; //destination address
	DMA_TCD0_DOFF = 0; //destination offset (amount to incriment destination address each iteration)
	DMA_TCD0_DLASTSGA = 0; //value added to the destination address at the completion of the major iteration count
	DMA_TCD0_BITER_ELINKNO = 1; //starting major iteration count
	DMA_TCD0_CITER_ELINKNO = 1; //current major iteration count
	DMA_TCD0_ATTR = DMA_TCD_ATTR_SSIZE(0) | DMA_TCD_ATTR_DSIZE(0); //transfer attributes, source size 8bit and destination size 8bit
	DMA_TCD0_NBYTES_MLNO = 2*NUM_DRIVER_GS_CYCLES; //minor byte transfer count
	DMA_TCD0_CSR = DMA_TCD_CSR_INTMAJOR | DMA_TCD_CSR_DONE; //control and status, enable interrupt, start with done flag set (referenced later)
	
	//set DMA interrupt
	NVIC_ENABLE_IRQ(IRQ_DMA_CH0);
}

static void led_outputLayer(uint8_t* dataBuffer, uint8_t layer) {
	int32_t i;
	
	//update output buffer with appropriate data for given layer
	int32_t bufferIndex = ((NUM_DRIVER_GS_CYCLES*2)-(NUM_LEDS_PER_LAYER*NUM_DRIVER_GS_BITS*2));
	for(i=((layer+1)*NUM_LEDS_PER_LAYER*3)-3; i>=((int32_t)layer*NUM_LEDS_PER_LAYER*3); i-=3) {
		uint32_t data32 = *((uint32_t*)(dataBuffer+i));
		uint32_t tempR = decode_lu_r[(data32>>16)&0xff];
		uint32_t tempG = decode_lu_g[(data32>>8)&0xff];
		uint32_t tempB = decode_lu_b[(data32>>0)&0xff];
		uint32_t decode32;
		
		decode32 = (((tempB) | (tempG) | (tempR)))&0x07070707;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		
		decode32 = (((tempB&0x08080808) | (tempG) | (tempR))>>3)&0x07070707;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		
		decode32 = (((tempB) | (tempG) | (tempR&0x80808080))>>5)&0x07070707;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
		decode32 = decode32 >> 8;
		led_workingBuffer[bufferIndex] = decode32;
		led_workingBuffer[bufferIndex+1] = decode32 | BIT_LED_CLK | BIT_LED_GSCLK;
		bufferIndex = bufferIndex + 2;
	}
	
	//wait for previous DMA output to finish
	while (!(DMA_TCD0_CSR & DMA_TCD_CSR_DONE));
	
	//flip the outputting buffer/layer
	led_outputtingLayer = layer;
	uint8_t* temp = led_outputingBuffer;
	led_outputingBuffer = led_workingBuffer;
	led_workingBuffer = temp;
	
	//make sure blank is held high for enough time to let the previous layer turn off
	system_delay(100);
	digitalWriteFast(PIN_LED_VPRG, LOW);
	digitalWriteFast(PIN_LED_BLANK, LOW);
	
	//set data for new DMA output and start
	DMA_TCD0_SADDR = led_outputingBuffer;
	DMA_TCD0_NBYTES_MLNO = 2*NUM_DRIVER_GS_CYCLES;
	DMA_TCD0_CSR |= DMA_TCD_CSR_START;
}

static void led_dc(uint8_t brightness) {
	if(brightness > 4) brightness = 4;
	if(brightness < 1) brightness = 1;
	
	const uint8_t* dc_sequence = dc_sequence_b4;
	if(brightness == 3) dc_sequence = dc_sequence_b3;
	if(brightness == 2) dc_sequence = dc_sequence_b2;
	if(brightness == 1) dc_sequence = dc_sequence_b1;
	
	//wait for previous DMA output to finish
	while (!(DMA_TCD0_CSR & DMA_TCD_CSR_DONE));
	
	//set the correct dc programming mode
	digitalWriteFast(PIN_LED_VPRG, HIGH);
	digitalWriteFast(PIN_LED_BLANK, HIGH);
	
	//set data for new DMA output and start
	led_outputtingLayer = LED_LAYERS_IGNORE;
	DMA_TCD0_SADDR = dc_sequence;
	DMA_TCD0_NBYTES_MLNO = NUM_LEDS_PER_DRIVER*NUM_DRIVER_DC_BITS*2;
	DMA_TCD0_CSR |= DMA_TCD_CSR_START;
}

static void led_powerLayer(uint8_t layer) {
	if(layer != LED_LAYERS_IGNORE) {
		if(layer == 0) digitalWriteFast(PIN_LAYER_0, HIGH); else digitalWriteFast(PIN_LAYER_0, LOW);
		if(layer == 1) digitalWriteFast(PIN_LAYER_1, HIGH); else digitalWriteFast(PIN_LAYER_1, LOW);
		if(layer == 2) digitalWriteFast(PIN_LAYER_2, HIGH); else digitalWriteFast(PIN_LAYER_2, LOW);
		if(layer == 3) digitalWriteFast(PIN_LAYER_3, HIGH); else digitalWriteFast(PIN_LAYER_3, LOW);
		if(layer == 4) digitalWriteFast(PIN_LAYER_4, HIGH); else digitalWriteFast(PIN_LAYER_4, LOW);
		if(layer == 5) digitalWriteFast(PIN_LAYER_5, HIGH); else digitalWriteFast(PIN_LAYER_5, LOW);
		if(layer == 6) digitalWriteFast(PIN_LAYER_6, HIGH); else digitalWriteFast(PIN_LAYER_6, LOW);
		if(layer == 7) digitalWriteFast(PIN_LAYER_7, HIGH); else digitalWriteFast(PIN_LAYER_7, LOW);
		if(layer == 8) digitalWriteFast(PIN_LAYER_8, HIGH); else digitalWriteFast(PIN_LAYER_8, LOW);
		if(layer == 9) digitalWriteFast(PIN_LAYER_9, HIGH); else digitalWriteFast(PIN_LAYER_9, LOW);
	}
}


/***************************************************************
 * Bit Packing in Lookup Tables                                *
 ***************************************************************
   10100100                           10100100                           10100100                           10100100
R  b11 [0] b07 [0] [0] b03 [0] [0]    b10 [0] b06 [0] [0] b02 [0] [0]    b09 [0] b05 [0] [0] b01 [0] [0]    b08 [0] b04 [0] [0] b00 [0] [0]

   01010010                           01010010                           01010010                           01010010
G  [0] b11 [0] b07 [0] [0] b03 [0]    [0] b10 [0] b06 [0] [0] b02 [0]    [0] b09 [0] b05 [0] [0] b01 [0]    [0] b08 [0] b04 [0] [0] b00 [0]

   00101001                           00101001                           00101001                           00101001
B  [0] [0] b11 [0] b07 [0] [0] b03    [0] [0] b10 [0] b06 [0] [0] b02    [0] [0] b09 [0] b05 [0] [0] b01    [0] [0] b08 [0] b04 [0] [0] b00

//decoding
temp_r = decode_lu_r[r];
temp_g = decode_lu_g[g];
temp_b = decode_lu_b[b];
bits0_3 = (((temp_b) | (temp_g) | (temp_r)))&0x07070707;
bits4_7 = (((temp_b&0x08080808) | (temp_g) | (temp_r))>>3)&0x07070707;
bits8_11 = (((temp_b) | (temp_g) | (temp_r&0x80808080))>>5)&0x07070707;
 */
 
/***************************************************************
 * Generating Lookup Tables through Javascript                 *
 ***************************************************************
// Gamma Curve
var g = 1.8;
var n = 256;
var m = 4096;

var gamma = [];
for(var i=1; i<n+1; i++) {
	gamma.push(Math.round((Math.pow(i*(m/n), g)/Math.pow(m, g))*(m-1)));
}

//packed lookup
var decode_lu_r = [];
var decode_lu_g = [];
var decode_lu_b = [];
for(var i=0; i<n; i++) {
	var lu = (((gamma[i]&0x800)==0x800) ? 0x00000001 : 0) | (((gamma[i]&0x400)==0x400) ? 0x00000100 : 0) | (((gamma[i]&0x200)==0x200) ? 0x00010000 : 0) | (((gamma[i]&0x100)==0x100) ? 0x01000000 : 0)
			| (((gamma[i]&0x080)==0x080) ? 0x00000008 : 0) | (((gamma[i]&0x040)==0x040) ? 0x00000800 : 0) | (((gamma[i]&0x020)==0x020) ? 0x00080000 : 0) | (((gamma[i]&0x010)==0x010) ? 0x08000000 : 0)
			| (((gamma[i]&0x008)==0x008) ? 0x00000020 : 0) | (((gamma[i]&0x004)==0x004) ? 0x00002000 : 0) | (((gamma[i]&0x002)==0x002) ? 0x00200000 : 0) | (((gamma[i]&0x001)==0x001) ? 0x20000000 : 0);
			
	decode_lu_b.push(lu); decode_lu_g.push(lu<<1); decode_lu_r.push(lu<<2);
}
var s = "";
s += "const uint32_t decode_lu_r[" + n + "] = { "; for(var i=0; i<n; i++) s += "0x" + Number(decode_lu_r[i]>>>0).toString(16).padStart(8,'0') + ", "; s += "}\n";
s += "const uint32_t decode_lu_g[" + n + "] = { "; for(var i=0; i<n; i++) s += "0x" + Number(decode_lu_g[i]>>>0).toString(16).padStart(8,'0') + ", "; s += "}\n";
s += "const uint32_t decode_lu_b[" + n + "] = { "; for(var i=0; i<n; i++) s += "0x" + Number(decode_lu_b[i]>>>0).toString(16).padStart(8,'0') + ", "; s += "}\n";
*/

#endif /*_led_h_*/