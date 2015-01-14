/*
 * amf.c
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef AMF_C_
#define AMF_C_
/**
 * 未压缩
 */
#define AudioFormat_UNCOMPRESSED 0x0
/**
 * ADPCM
 */
#define AudioFormat_ADPCM 0x1
/**
 * MP3
 */
#define AudioFormat_MP3 0x2
/**
 * NELLYMOSER_16K
 */
#define AudioFormat_NELLYMOSER_16K 0x4
/**
 * NELLYMOSER_8K
 */
#define AudioFormat_NELLYMOSER_8K 0x5
/**
 * AAC
 */
#define AudioFormat_AAC 0x10

/**
 *  5.5KHz
 */
#define AMPLERATE_5_5K 0x0

/**
 * 11kHz
 */
#define AMPLERATE_11K 0x1

/**
 * 22kHz
 */
#define AMPLERATE_22K 0x2

/**
 * 44kHz
 */
#define AMPLERATE_44K 0x3

/**
 * snd8Bit
 */
#define SND8BIT 0x0

/**
 * snd16Bit
 */
#define SND16BIT 0x1

#define SNDMOMO 0x0

#define SNDSTEREO 0x1

/**
 * seronson h.263
 */
#define Codec_SERONSON_H263 0x2

/**
 * screen video
 */
#define Codec_SCREEN_VIDEO 0x3

/**
 * On2 VP6
 */
#define Codec_ON2_VP6 0x4

/**
 * On2 VP6 with alpha channel
 */
#define Codec_ON2_VP6_WITH_ALPHA_CHANNEL 0x5

/**
 * Screen video version 2
 */
#define Codec_SCREEN_VIDEO_VERSION_2 0x6

/**
 * AVC (h.264)
 */
#define Codec_AVC_H264 0x7

/**
 * ·1-- keyframe
 */
#define KEYF_RAME 0x1

/**
 * 2 -- inner frame
 */
#define INNER_FRAME 0x2

/**
 * 3 -- disposable inner frame （h.263 only）
 */
#define DISPOSABLE_INNER_FRAME 0x3

/**
 * 4 -- generated keyframe
 */
#define GENERATED_KEYFRAME 0x4

#endif /* AMF_C_ */
