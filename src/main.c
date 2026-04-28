#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Includes the declaration of the basic type aliases
#include "basic_types.h"
// Includes the field extraction function declarations
#include "ccsds_pus_format.h"
#include "ccsds_pus_stdio.h"
#include "crc.h"
#include "epd_pus_tmtc.h"

int main() {

	int tc_fd;
	int tm_fd;
	uint8_t read_byte;

	tc_fd = open("multiple-tcs.bin", O_RDONLY);
	tm_fd = open("multiple-tms.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	uint8_t ntcs;

	read(tc_fd, &read_byte, 1);
	ntcs = read_byte;

	uint16_t tm_count = 0;
	for (uint8_t tc = 0; tc < ntcs; tc = tc + 1) {

	    struct ccsds_pus_tmtc_packet_header tc_packet_header;
	    struct ccsds_pus_tc_df_header tc_df_header;

	    uint16_t tc_packet_err_ctrl;

	    uint16_t crc_value;
	    uint8_t nbytes = 0;

	    uint8_t tc_bytes[256];
	    uint8_t tm_bytes[256];

	    // Read telecommand from file
	    nbytes = ccsds_pus_tc_read(tc_fd, tc_bytes);

	    // Deserialize primary fields
	    ccsds_pus_tc_get_fields(tc_bytes, &tc_packet_header,
	            &tc_df_header,
	            &tc_packet_err_ctrl);

	    // Print the contents of all the fields
	    ccsds_pus_tmtc_print_packet_header_fields(tc_packet_header.packet_id);
	    ccsds_pus_tmtc_print_packet_seq_ctrl_fields(
	            tc_packet_header.packet_seq_ctrl);
	    ccsds_pus_tc_print_df_header_fields(tc_df_header);

	    // Calculate CRC
	    // We need to calculate the CRC with nbytes - 2, since the vector
	    // ALSO STORES the Packet Error Control field
	    crc_value = cal_crc_16(tc_bytes, nbytes - 2);

	    if (crc_value == tc_packet_err_ctrl) {

	        printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",
	                tc_packet_err_ctrl, crc_value);

	        // Generate TM (1,1) - Accept
	        epd_pus_build_tm_1_1(tm_bytes, tm_count,
	                tc_packet_header.packet_id,
	                tc_packet_header.packet_seq_ctrl);

	    } else {
	        printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n",
	                tc_packet_err_ctrl, crc_value);

	        // Generate TM (1,2) - Reject
	        epd_pus_build_tm_1_2_crc_error(tm_bytes, tm_count,
	                tc_packet_header.packet_id,
	                tc_packet_header.packet_seq_ctrl,
	                tc_packet_err_ctrl, crc_value);
	    }

	    ccsds_pus_tm_write(tm_fd, tm_bytes);

	    tm_count = tm_count + 1;

	}


		close(tc_fd);
		close(tm_fd);

		return 0;

	}
