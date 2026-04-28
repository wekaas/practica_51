#include <stdio.h>
#include <unistd.h> // <--- NECESARIO para read() y write()

#include "basic_types.h"
#include "ccsds_pus_stdio.h"
#include "ccsds_pus_format.h"
#include "serialize.h"

void ccsds_pus_tmtc_print_packet_header_fields(uint16_t tc_packet_id) {
	printf("APID: 0x%X\n", ccsds_pus_tc_get_APID(tc_packet_id));
}

void ccsds_pus_tmtc_print_packet_seq_ctrl_fields(uint16_t tc_packet_seq_ctrl) {
	printf("Sequence Flags: 0x%X\n",
			ccsds_pus_tc_get_seq_flags(tc_packet_seq_ctrl));
	printf("Sequence Count: %d\n",
			ccsds_pus_tc_get_seq_count(tc_packet_seq_ctrl));
}

void ccsds_pus_tc_print_df_header_fields(struct ccsds_pus_tc_df_header tc_df_header) {

    printf("ACK: 0x%X\n", ccsds_pus_tc_get_ack(tc_df_header.flag_ver_ack));
    printf("Service Type: %d\n", tc_df_header.type);
    printf("Service Subtype: %d\n", tc_df_header.subtype);
    printf("Source ID: 0x%X\n", tc_df_header.sourceID);

}


uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]) {
	uint16_t nbytes = 0;
	uint16_t tc_packet_len = 0;

	// Leemos los primeros 6 bytes (Header)
	read(fd, &tc_bytes[0], 6);

	// Deserializamos el campo de longitud (está en la posición 4)
	tc_packet_len = deserialize_uint16(&tc_bytes[4]);

	// En PUS, la longitud real es el valor del campo + 1
	uint16_t remaning_bytes = tc_packet_len + 1;

	// Leemos el resto (Data Field + CRC)
	read(fd, &tc_bytes[6], remaning_bytes);

	nbytes = 6 + remaning_bytes;
	return nbytes;
}

void ccsds_pus_tm_write(int fd, uint8_t tm_bytes[]) {
	// CORRECCIÓN: Llamada correcta a la función sin poner "int" o "uint8_t"
	// Obtenemos la longitud del paquete que está en el offset 4
	uint16_t tm_packet_len = deserialize_uint16(&tm_bytes[4]);

	// Escribimos en el descriptor de fichero: 6 (header) + longitud + 1
	write(fd, &tm_bytes[0], 6 + tm_packet_len + 1);

	return;
}
