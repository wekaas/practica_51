#include "epd_pus_tmtc.h"
#include "epd_pus_mission.h"
#include "ccsds_pus_format.h"
#include "serialize.h"

void epd_pus_build_tm_1_1(uint8_t tm_bytes[],
                          uint16_t tm_seq_counter,
                          uint16_t tc_packet_id,
                          uint16_t tc_packet_seq_ctrl) {


    struct ccsds_pus_tmtc_packet_header tm_packet_header;
    struct ccsds_pus_tm_df_header df_header;

    tm_packet_header.packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

    tm_packet_header.packet_seq_ctrl = ccsds_pus_tm_build_packet_seq_ctrl(0x3,
            tm_seq_counter);

    tm_packet_header.packet_length = 0x07;

    df_header.version = ccsds_pus_tm_build_df_header_version(0x1);
    df_header.type = 1;
    df_header.subtype = 1;
    df_header.destinationID = EPD_DESTINATION_ID;

    ccsds_pus_tm_set_fields(&tm_bytes[0], &tm_packet_header, &df_header);

    serialize_uint16(tc_packet_id, &tm_bytes[10]);
    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);

    return;

}

void epd_pus_build_tm_1_2_crc_error(uint8_t tm_bytes[],
									uint16_t tm_seq_counter,
									uint16_t tc_packet_id,
									uint16_t tc_packet_seq_ctrl,
									uint16_t tc_packet_err_ctrl,
									uint16_t calculated_crc){


    struct ccsds_pus_tmtc_packet_header tm_packet_header;
    struct ccsds_pus_tm_df_header df_header;

    tm_packet_header.packet_id = ccsds_pus_tm_build_packet_id(EPD_APID);

    tm_packet_header.packet_seq_ctrl = ccsds_pus_tm_build_packet_seq_ctrl(0x3,
            tm_seq_counter);

    tm_packet_header.packet_length = 0x0D;

    df_header.version = ccsds_pus_tm_build_df_header_version(0x1);
    df_header.type = 1;
    df_header.subtype = 2;
    df_header.destinationID = EPD_DESTINATION_ID;

    ccsds_pus_tm_set_fields(&tm_bytes[0], &tm_packet_header, &df_header);

    serialize_uint16(tc_packet_id, &tm_bytes[10]);
    serialize_uint16(tc_packet_seq_ctrl, &tm_bytes[12]);
    serialize_uint16(0x02, &tm_bytes[14]);
    serialize_uint16(tc_packet_err_ctrl, &tm_bytes[16]);
    serialize_uint16(calculated_crc, &tm_bytes[18]);

    return;

}


