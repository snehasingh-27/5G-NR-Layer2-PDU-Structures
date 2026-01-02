// test_compile.c
#include <stdio.h>
#include "5g_nr_pdu_structures.h"

int main() {
    printf("=== 5G NR PDU Structure Sizes ===\n\n");
    
    printf("SDAP Layer:\n");
    printf("  SDAP Data PDU (with RQI/RDI): %zu byte(s)\n", 
           sizeof(sdap_data_pdu_with_rqi_rdi_t));
    printf("  SDAP Data PDU (without RQI/RDI): %zu byte(s)\n", 
           sizeof(sdap_data_pdu_without_rqi_rdi_t));

    printf("\nPDCP Layer:\n");
    printf("  PDCP Data PDU (12-bit SN):       %zu byte(s)\n", 
           sizeof(pdcp_data_pdu_12bit_sn_t));
    printf("  PDCP Data PDU (18-bit SN):       %zu byte(s)\n", 
           sizeof(pdcp_data_pdu_18bit_sn_t));
    printf("  PDCP Control PDU (Status):       %zu byte(s)\n", 
           sizeof(pdcp_control_pdu_status_report_t));
    printf("  PDCP Control PDU (ROHC):         %zu byte(s)\n", 
           sizeof(pdcp_control_pdu_rohc_feedback_t));

    printf("\nRLC Layer:\n");
    printf("  RLC UM 6-bit SN (complete):      %zu byte(s)\n", 
           sizeof(rlc_um_data_pdu_6bit_sn_complete_t));
    printf("  RLC UM 6-bit SN (segmented):     %zu byte(s)\n", 
           sizeof(rlc_um_data_pdu_6bit_sn_segmented_t));
    printf("  RLC UM 12-bit SN (complete):     %zu byte(s)\n", 
           sizeof(rlc_um_data_pdu_12bit_sn_complete_t));
    printf("  RLC UM 12-bit SN (segmented):    %zu byte(s)\n", 
           sizeof(rlc_um_data_pdu_12bit_sn_segmented_t));
    printf("  RLC AM 12-bit SN (complete):     %zu byte(s)\n", 
           sizeof(rlc_am_data_pdu_12bit_sn_complete_t));
    printf("  RLC AM 12-bit SN (segmented):    %zu byte(s)\n", 
           sizeof(rlc_am_data_pdu_12bit_sn_segmented_t));
    printf("  RLC AM 18-bit SN (complete):     %zu byte(s)\n", 
           sizeof(rlc_am_data_pdu_18bit_sn_complete_t));
    printf("  RLC AM 18-bit SN (segmented):    %zu byte(s)\n", 
           sizeof(rlc_am_data_pdu_18bit_sn_segmented_t));
    printf("  RLC AM STATUS PDU (12-bit):      %zu byte(s)\n", 
           sizeof(rlc_am_status_pdu_12bit_t));
    printf("  RLC AM STATUS PDU (18-bit):      %zu byte(s)\n", 
           sizeof(rlc_am_status_pdu_18bit_t));

    printf("\nMAC Layer:\n");
    printf("  MAC Subheader (short format):    %zu byte(s)\n", 
           sizeof(mac_subheader_short_t));
    printf("  MAC Subheader (long format):     %zu byte(s)\n", 
           sizeof(mac_subheader_long_t));
    printf("  MAC Subheader (fixed-size CE):   %zu byte(s)\n", 
           sizeof(mac_subheader_fixed_t));
    printf("  MAC Subheader (with extension):  %zu byte(s)\n", 
           sizeof(mac_subheader_with_extension_t));
    
    printf("\n=== Total Structures Defined: 24 ===\n");
    printf("\nAll 5G NR Layer-2 PDU structures compiled successfully!\n");

    return 0;
}
