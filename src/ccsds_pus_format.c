#include "basic_types.h"
#include "ccsds_pus_format.h"
#include "serialize.h"

void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
		struct ccsds_pus_tmtc_packet_header *p_tc_packet_header,
		struct ccsds_pus_tc_df_header *p_tc_df_header,
		uint16_t *p_tc_packet_err_ctrl) {

	// Deserialize Packet ID and store it into field packet_id
	p_tc_packet_header->packet_id = deserialize_uint16(&tc_bytes[0]);

	// TODO: Deserialize Packet Seq. Control and store it into field packet_seq_ctrl
	p_tc_packet_header->packet_seq_ctrl = deserialize_uint16(&tc_bytes[2]);

	// TODO: Deserialize Packet Length and store it into field packet_length
	p_tc_packet_header->packet_length = deserialize_uint16(&tc_bytes[4]);

	// Read the MSB of the Data Field Header and store it into flag_ver_ack
	p_tc_df_header->flag_ver_ack = tc_bytes[6];

	// TODO: Read the remaining fields of the Data Field Header into the struct

	p_tc_df_header->type = tc_bytes[7];

	p_tc_df_header->subtype = tc_bytes[8];

	p_tc_df_header->sourceID = tc_bytes[9];

	// Deserialize Packet Error Control and store it at p_tc_packet_err_ctrl
	*p_tc_packet_err_ctrl = deserialize_uint16(
			&tc_bytes[p_tc_packet_header->packet_length + 5]);

}

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
        const struct ccsds_pus_tm_df_header * p_tm_df_header) {

    serialize_uint16(p_tm_packet_header->packet_id, &tm_bytes[0]);

    // TODO: Serialize Packet Sequence Control from packet_seq_ctrl

    serialize_uint16(p_tm_packet_header->packet_seq_ctrl, &tm_bytes[2]);

    // TODO: Serialize Packet Length from packet_length

    serialize_uint16(p_tm_packet_header->packet_length , &tm_bytes[4]);

    // Store version field into the corresponding byte
    tm_bytes[6] = p_tm_df_header->version;

    // TODO: Store the remaining fields into their respective locations

    tm_bytes[7] = p_tm_df_header->type;
    tm_bytes[8] = p_tm_df_header->subtype;
    tm_bytes[9] = p_tm_df_header->destinationID;

}



