#include "avcodec.h"
#include "aac_adtstoasc_bsf.c"
#include "chomp_bsf.c"
#include "dump_extradata_bsf.c"
#include "dca_core_bsf.c"
#include "h264_mp4toannexb_bsf.c"
#include "hevc_mp4toannexb_bsf.c"
#include "imx_dump_header_bsf.c"
#include "mjpeg2jpeg_bsf.c"
#include "mjpega_dump_header_bsf.c"
#include "mp3_header_decompress_bsf.c"
#include "mpeg4_unpack_bframes_bsf.c"
#include "movsub_bsf.c"
#include "noise_bsf.c"
#include "remove_extradata_bsf.c"
#include "vp9_superframe_bsf.c"


static const AVBitStreamFilter *bitstream_filters[] = {
    &ff_aac_adtstoasc_bsf,
    &ff_chomp_bsf,
    &ff_dump_extradata_bsf,
    &ff_dca_core_bsf,
    &ff_h264_mp4toannexb_bsf,
    &ff_hevc_mp4toannexb_bsf,
    &ff_imx_dump_header_bsf,
    &ff_mjpeg2jpeg_bsf,
    &ff_mjpega_dump_header_bsf,
    &ff_mp3_header_decompress_bsf,
    &ff_mpeg4_unpack_bframes_bsf,
    &ff_mov2textsub_bsf,
    &ff_noise_bsf,
    &ff_remove_extradata_bsf,
    &ff_text2movsub_bsf,
    &ff_vp9_superframe_bsf,
    NULL };
