#ifndef INCLUDE_CCSDS_PUS_STDIO_H_
#define INCLUDE_CCSDS_PUS_STDIO_H_

#include "basic_types.h"
#include "ccsds_pus_format.h"

/**
 * \brief Print packet header fields
 *
 * \param tc_packet_id telecommand packet_id
 */
void ccsds_pus_tmtc_print_packet_header_fields(uint16_t tc_packet_id);

/**
 * \brief Print packet sequence control fields
 *
 * \param tc_packet_seq_ctrl telecommand packet sequence control
 */
// TODO: Declare function ccsds_pus_tmtc_print_packet_seq_ctrl_fields
void ccsds_pus_tmtc_print_packet_seq_ctrl_fields(uint16_t tc_packet_seq_ctrl);

/**
 * \brief Print data field header
 *
 * \param tc_df_header telecommand data field header
 */
void ccsds_pus_tc_print_df_header_fields(struct ccsds_pus_tc_df_header tc_df_header);

/**
 * \brief Reads a telecommand from a file
 *
 * \param fd descriptor of the file from which the TC shall be read
 * \param tc_bytes vector that shall store the bytes of the read TC
 *
 * \return the number of bytes that are part of the telecommand
 */
// TODO: Declare function ccsds_pus_tc_read
uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]);


/**
 * \brief Stores a serialized telemetry packet into a file
 *
 * \param fd descriptor of the file into which the packet will be stored
 * \param tm_bytes vector that contains the generated serialized telemetry
 */
void ccsds_pus_tm_write(int fd, uint8_t tm_bytes[]);


#endif /* INCLUDE_CCSDS_PUS_STDIO_H_ */
