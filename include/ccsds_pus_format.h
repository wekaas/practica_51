#ifndef INCLUDE_CCSDS_PUS_FORMAT_H_
#define INCLUDE_CCSDS_PUS_FORMAT_H_

#include "basic_types.h"


/**
 * \brief Structure type to the Packet Header field of a TM/TC packet.
 */
struct ccsds_pus_tmtc_packet_header {

    uint16_t packet_id;

    // TODO: Complete definition of struct ccsds_pus_tmtc_packet_header

    uint16_t packet_seq_ctrl;
    uint16_t packet_length;

};

/**
 * \brief Structure type to store the Data Field Header field of a TC packet.
 */
struct ccsds_pus_tc_df_header {

    uint8_t flag_ver_ack;

    // TODO: Complete definition of struct ccsds_pus_tm_df_header

    uint8_t type;
    uint8_t subtype;
    uint8_t sourceID;

};

/**
 * \brief Structure type to store the Data Field Header field of a TM packet.
 */
struct ccsds_pus_tm_df_header {

    uint8_t version;
    uint8_t type;
    uint8_t subtype;
    uint8_t destinationID;

};


/**
 * \brief Get APID from a telecommand's Packet ID.
 *
 * \param tc_packet_id the telecommand's Packet ID
 *
 * \return the telecommand's APID
 */
#define ccsds_pus_tc_get_APID(tc_packet_id) ((tc_packet_id) & 0x07FF)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Flags
 */
// TODO: Define macro ccsds_pus_tc_get_seq_flags
#define ccsds_pus_tc_get_seq_flags(tc_packet_seq_ctrl) ((tc_packet_seq_ctrl & 0xC000) >> 14)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Count
 */
// TODO: Define macro ccsds_pus_tc_get_seq_count
#define ccsds_pus_tc_get_seq_count(tc_packet_seq_ctrl) (tc_packet_seq_ctrl & 0x3FFF)

/**
 * \brief Builds the most significant byte of the Data Field Header of a telmetry.
 *
 * \param version the value of the Version subfield
 *
 * \return the MSB of the Data Field Header
 */
#define ccsds_pus_tm_build_df_header_version(version) (((version) & 0x7) << 4)

/**
 * \brief Get Ack from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Ack
 */
// TODO: Define macro ccsds_pus_tc_get_ack
#define ccsds_pus_tc_get_ack(flag_ver_ack) ((flag_ver_ack) & 0x0F)

/**
 * \brief Deserializes the fields of a telecommand stored in a vector
 *
 * \param tc_bytes vector that stores the bytes of the telecommand
 * \param p_tc_packet_id pointer to the variable that shall store the Packet ID
 * \param p_tc_packet_seq_ctrl pointer to the variable that shall store the
 *                          Packet Sequence Control field
 * \param p_tc_packet_len pointer to the variable that shall store the Packet
 *                     Length field
 * \param p_tc_df_header pointer to the variable that shall store the Data Field
 *                    Header
 * \param p_tc_packet_err_ctrl pointer to the variable that shall store the
 *                          Packet Error Control
 */
// TODO: declare function ccsds_pus_tc_get_fields
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                        struct ccsds_pus_tmtc_packet_header * p_tc_packet_header,
                        struct ccsds_pus_tc_df_header * p_tc_df_header,
                        uint16_t * p_tc_packet_err_ctrl);

/**
 * \brief Builds the Packet ID of a telmetry.
 *
 * \param apid the value of the APID subfield
 *
 * \return the Packet ID field
 */
#define ccsds_pus_tm_build_packet_id(apid) ((1 << 11) | ((apid) & 0x07FF))

/**
 * \brief Builds the Packet Sequence Control of a telmetry.
 *
 * \param flags the value of the Sequence Flags subfield
 * \param count the value of the Sequence Count subfield
 *
 * \return the Packet Sequence Control field
 */
// TODO: Define macro ccsds_pus_tm_build_packet_seq_ctrl
#define ccsds_pus_tm_build_packet_seq_ctrl(sequence_flags, sequence_count) ((sequence_flags << 14) | (sequence_count & 0x3FFF))

/**
 * \brief Builds the Data Field Header of a telmetry.
 *
 * \param type the value of the Type subfield
 * \param subtype the value of the Subtype subfield
 * \param dest the value of the Destination ID subfield
 *
 * \return the Data Field Header
 */
// TODO: Define macro ccsds_pus_tm_build_df_header
#define ccsds_pus_tm_build_df_header(service_type, service_subtype, destination_ID) ((1 << 28) | (service_type << 16) | (service_subtype << 8) | destination_ID)

/**
 * \brief Serializes and stores into a vector the main fields of a TM packet.
 *
 * \param tm_bytes vector that will store the generated serialized telemetry
 * \param tm_packet_id the Packet ID field of the generated telemetry
 * \param tm_packet_seq_ctrl the Packet Sequence Control field of the
 *                           generated telemetry
 * \param tm_packet_length the Packet Length of the generated telemetry
 * \param tm_df_header the Data Field Header of the generated telemetry
 */
void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                        const struct ccsds_pus_tmtc_packet_header * p_tm_packet_header,
                        const struct ccsds_pus_tm_df_header * p_tm_df_header);


#endif /* INCLUDE_CCSDS_PUS_FORMAT_H_ */
