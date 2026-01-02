/******************************************************************************
 * 5G NR Layer-2 PDU Structure Definitions
 * 
 * Course: [Your Course Name/Code]
 * Assignment: Design of 5G NR PDU Structures (SDAP, PDCP, RLC, MAC)
 * Author: [Your Name]
 * Student ID: [Your ID]
 * Date: [Current Date]
 * 
 * Description:
 * This file contains C structure definitions for all PDU header formats
 * used in 5G NR Layer-2 protocols: SDAP, PDCP, RLC, and MAC.
 * All structures are derived directly from 3GPP specifications.
 * 
 * References:
 * - 3GPP TS 37.324: Service Data Adaptation Protocol (SDAP)
 * - 3GPP TS 38.323: Packet Data Convergence Protocol (PDCP)
 * - 3GPP TS 38.322: Radio Link Control (RLC)
 * - 3GPP TS 38.321: Medium Access Control (MAC)
 * 
 * Notes:
 * - Bit-field ordering assumes MSB-first packing as shown in specifications
 * - Actual compiler behavior may be platform-dependent
 * - Variable-length PDU portions (e.g., NACK blocks in RLC STATUS) are
 *   not fully represented and are marked as implementation-specific
 *****************************************************************************/

// 5g_nr_pdu_structures.h
#ifndef _5G_NR_PDU_STRUCTURES_H_
#define _5G_NR_PDU_STRUCTURES_H_

#include <stdint.h>

// Your structures will go here
/*============================================================================
 * SDAP LAYER PDU STRUCTURES
 * Reference: 3GPP TS 37.324
 *==========================================================================*/

/**
 * SDAP Data PDU - with RQI and RDI present
 * 
 * Layer: SDAP (Service Data Adaptation Protocol)
 * Reference: 3GPP TS 37.324 Section 6.2.2.1
 * Direction: UL and DL
 * 
 * Description:
 * This header is present when reflective QoS is configured.
 * It maps QoS flows to Data Radio Bearers (DRBs).
 * 
 * Fields:
 * - rdi (1 bit): Reflective QoS flow to DRB mapping indication
 *   - 0: No reflective mapping
 *   - 1: Reflective mapping applies
 * - rqi (1 bit): Reflective QoS indication  
 *   - 0: No reflective QoS
 *   - 1: Reflective QoS applies
 * - qfi (6 bits): QoS Flow Identifier (0-63)
 *   - Identifies the QoS flow for this PDU
 * 
 * Total size: 1 byte
 * 
 * Note: Bit-field ordering assumes MSB-first as per specification diagram.
 * Actual packing may be compiler-dependent.
 */
typedef struct sdap_data_pdu_with_rqi_rdi {
    uint8_t rdi : 1;  // Reflective QoS DRB mapping indication
    uint8_t rqi : 1;  // Reflective QoS indication
    uint8_t qfi : 6;  // QoS Flow Identifier (0-63)
} sdap_data_pdu_with_rqi_rdi_t;

/**
 * SDAP Data PDU - without RQI and RDI
 * 
 * Layer: SDAP
 * Reference: 3GPP TS 37.324 Section 6.2.2.1
 * Direction: UL and DL
 * 
 * Description:
 * This header is used when reflective QoS is not configured.
 * 
 * Fields:
 * - rsv (1 bit): Reserved bit, set to 0
 * - qfi (7 bits): QoS Flow Identifier (0-127)
 *   - Extended range when RDI/RQI not needed
 * 
 * Total size: 1 byte
 */
typedef struct sdap_data_pdu_without_rqi_rdi {
    uint8_t rsv : 1;  // Reserved (set to 0)
    uint8_t qfi : 7;  // QoS Flow Identifier (0-127)
} sdap_data_pdu_without_rqi_rdi_t;

/*============================================================================
 * PDCP LAYER PDU STRUCTURES
 * Reference: 3GPP TS 38.323
 *==========================================================================*/

/**
 * PDCP Data PDU with 12-bit Sequence Number
 * 
 * Layer: PDCP (Packet Data Convergence Protocol)
 * Reference: 3GPP TS 38.323 Section 6.2.2.1
 * Direction: UL and DL
 * 
 * Description:
 * Used for user plane data transmission with 12-bit sequence numbering.
 * Supports PDCP sequence number ranges up to 4096 (0-4095).
 * This format is commonly used for most data bearers.
 * 
 * Fields:
 * - dc (1 bit): Data/Control PDU indicator
 *   - 0: Control PDU
 *   - 1: Data PDU (always 1 for this structure)
 * - rsv (3 bits): Reserved bits, set to 0
 * - sn_high (4 bits): Upper 4 bits of 12-bit PDCP SN
 * - sn_low (8 bits): Lower 8 bits of 12-bit PDCP SN
 * 
 * Total header size: 2 bytes
 * Complete SN = (sn_high << 8) | sn_low (Range: 0-4095)
 * 
 * Note: PDCP SDU (user data) follows after this header.
 * May include integrity protection and ciphering.
 */
typedef struct pdcp_data_pdu_12bit_sn {
    // Byte 0
    uint8_t dc : 1;        // D/C bit: 1 = Data PDU
    uint8_t rsv : 3;       // Reserved bits (set to 0)
    uint8_t sn_high : 4;   // PDCP SN upper 4 bits
    // Byte 1
    uint8_t sn_low : 8;    // PDCP SN lower 8 bits
} pdcp_data_pdu_12bit_sn_t;

/**
 * PDCP Data PDU with 18-bit Sequence Number
 * 
 * Layer: PDCP
 * Reference: 3GPP TS 38.323 Section 6.2.2.2
 * Direction: UL and DL
 * 
 * Description:
 * Used for user plane data with extended 18-bit sequence numbering.
 * Supports PDCP sequence number ranges up to 262144 (0-262143).
 * Typically used for high-throughput bearers to prevent SN wrap-around
 * issues in high data rate scenarios.
 * 
 * Fields:
 * - dc (1 bit): Data/Control indicator (1 for Data PDU)
 * - rsv (5 bits): Reserved bits, set to 0
 * - sn_high (2 bits): Upper 2 bits of 18-bit PDCP SN
 * - sn_mid (8 bits): Middle 8 bits of PDCP SN
 * - sn_low (8 bits): Lower 8 bits of PDCP SN
 * 
 * Total header size: 3 bytes
 * Complete SN = (sn_high << 16) | (sn_mid << 8) | sn_low (Range: 0-262143)
 * 
 * Note: PDCP SDU follows. Header may be followed by integrity MAC-I
 * depending on security configuration.
 */
typedef struct pdcp_data_pdu_18bit_sn {
    // Byte 0
    uint8_t dc : 1;        // D/C bit: 1 = Data PDU
    uint8_t rsv : 5;       // Reserved bits (set to 0)
    uint8_t sn_high : 2;   // PDCP SN upper 2 bits
    // Byte 1
    uint8_t sn_mid : 8;    // PDCP SN middle 8 bits
    // Byte 2
    uint8_t sn_low : 8;    // PDCP SN lower 8 bits
} pdcp_data_pdu_18bit_sn_t;

/**
 * PDCP Control PDU - Status Report
 * 
 * Layer: PDCP
 * Reference: 3GPP TS 38.323 Section 6.2.3.1
 * Direction: UL and DL
 * 
 * Description:
 * Used by the PDCP receiver to report reception status of PDCP SDUs.
 * Indicates which PDCP SDUs are missing so the transmitter can perform
 * retransmissions. Used during PDCP re-establishment or handover scenarios.
 * 
 * Fields:
 * - dc (1 bit): Data/Control indicator (0 for Control PDU)
 * - pdu_type (3 bits): Control PDU type
 *   - 000: PDCP status report
 * - rsv (4 bits): Reserved bits (set to 0)
 * - fmc_high (8 bits): First Missing Count upper 8 bits
 * - fmc_mid (8 bits): FMC middle 8 bits  
 * - fmc_low (8 bits): FMC lower 8 bits
 *   FMC indicates the PDCP SN of the first missing PDCP SDU
 * 
 * Total fixed header size: 4 bytes
 * Complete FMC = (fmc_high << 16) | (fmc_mid << 8) | fmc_low
 * 
 * Note: Variable-length bitmap follows the header to indicate which
 * subsequent PDCP SDUs are missing (bit=0) or received (bit=1).
 * Bitmap structure is not included here (implementation specific).
 * 
 * Usage: Receiver sends this during handover to indicate which PDUs
 * from the old cell were not received and need retransmission.
 */
typedef struct pdcp_control_pdu_status_report {
    // Byte 0
    uint8_t dc : 1;           // D/C bit: 0 = Control PDU
    uint8_t pdu_type : 3;     // PDU Type: 000 = Status Report
    uint8_t rsv : 4;          // Reserved bits
    // Byte 1
    uint8_t fmc_high : 8;     // First Missing Count upper 8 bits
    // Byte 2
    uint8_t fmc_mid : 8;      // FMC middle 8 bits
    // Byte 3
    uint8_t fmc_low : 8;      // FMC lower 8 bits
    // Variable-length bitmap follows (not represented here)
} pdcp_control_pdu_status_report_t;

/**
 * PDCP Control PDU - ROHC Feedback
 * 
 * Layer: PDCP
 * Reference: 3GPP TS 38.323 Section 6.2.3.2
 * Direction: UL and DL
 * 
 * Description:
 * Carries ROHC (Robust Header Compression) feedback information from
 * the decompressor to the compressor. Used when header compression is
 * configured on the bearer to optimize bandwidth for protocols like
 * IP/UDP/RTP with repetitive headers.
 * 
 * Fields:
 * - d
 * Fields:
 * - dc (1 bit): Data/Control indicator (0 for Control PDU)
 * - pdu_type (3 bits): Control PDU type
 *   - 001: ROHC feedback packet
 * - rsv (4 bits): Reserved bits (set to 0)
 * 
 * Total fixed header size: 1 byte
 * 
 * Note: ROHC feedback payload follows this header. The payload format
 * is defined in RFC 5795 (ROHC specification) and contains feedback
 * information for the header compression context.
 */
typedef struct pdcp_control_pdu_rohc_feedback {
    uint8_t dc : 1;           // D/C bit: 0 = Control PDU
    uint8_t pdu_type : 3;     // PDU Type: 001 = ROHC feedback
    uint8_t rsv : 4;          // Reserved bits
} pdcp_control_pdu_rohc_feedback_t;
// Add more structures below...

/*============================================================================
 * RLC LAYER PDU STRUCTURES
 * Reference: 3GPP TS 38.322
 *==========================================================================*/

/*----------------------------------------------------------------------------
 * RLC Transparent Mode (TM)
 *--------------------------------------------------------------------------*/

/**
 * RLC TM Data PDU
 * 
 * Layer: RLC Transparent Mode
 * Reference: 3GPP TS 38.322 Section 6.2.2
 * Direction: UL and DL
 * 
 * Description:
 * Transparent Mode has NO header. Data is passed through without any
 * RLC processing. No segmentation, no retransmission, no reordering.
 * RLC entity simply passes SDUs to lower layer without modification.
 * 
 * This mode is typically used for:
 * - Voice services (VoLTE, VoNR) where low latency is critical
 * - Real-time traffic where retransmissions cause unacceptable delays
 * - Broadcast/multicast services
 * 
 * Structure: Not applicable (no header exists)
 * The RLC TM PDU is simply the raw RLC SDU with no encapsulation.
 * 
 * Note: No C structure needed - TM PDU is just transparent data bytes.
 * This comment serves as documentation that TM mode exists but has
 * no header structure to define.
 */
// No structure for TM - it's transparent (header-less)

/*----------------------------------------------------------------------------
 * RLC Unacknowledged Mode (UM)
 *--------------------------------------------------------------------------*/

/**
 * RLC UM Data PDU with 6-bit SN (complete SDU, no segmentation)
 * 
 * Layer: RLC Unacknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.3.3
 * Direction: UL and DL
 * 
 * Description:
 * Used when the entire RLC SDU fits in one PDU (no segmentation needed).
 * Supports sequence numbering up to 64 (SN range: 0-63).
 * Provides in-sequence delivery and duplicate detection.
 * 
 * Fields:
 * - si (2 bits): Segmentation Info
 *   - 00: Complete SDU (full SDU in this PDU)
 * - sn (6 bits): Sequence Number (0-63)
 * 
 * Total header size: 1 byte
 * 
 * Usage: For low to medium data rate bearers where 6-bit SN window
 * is sufficient to avoid sequence number wrap-around issues.
 */
typedef struct rlc_um_data_pdu_6bit_sn_complete {
    uint8_t si : 2;    // Segmentation Info: 00 = complete SDU
    uint8_t sn : 6;    // Sequence Number (0-63)
} rlc_um_data_pdu_6bit_sn_complete_t;

/**
 * RLC UM Data PDU with 6-bit SN (segmented SDU)
 * 
 * Layer: RLC Unacknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.3.3
 * Direction: UL and DL
 * 
 * Description:
 * Used when RLC SDU is segmented across multiple PDUs due to size constraints.
 * Includes Segment Offset (SO) to indicate the position of this segment
 * within the original SDU.
 * 
 * Fields:
 * - si (2 bits): Segmentation Info
 *   - 01: First segment of SDU
 *   - 10: Last segment of SDU
 *   - 11: Middle segment (neither first nor last)
 * - sn (6 bits): Sequence Number (0-63)
 * - so_high (8 bits): Segment Offset upper byte
 * - so_low (8 bits): Segment Offset lower byte
 * 
 * Total header size: 3 bytes
 * Complete SO = (so_high << 8) | so_low
 * SO indicates byte offset of this segment in the original RLC SDU
 * 
 * Example: If SDU is 5000 bytes split into 3 segments:
 * - Segment 1: SI=01, SO=0
 * - Segment 2: SI=11, SO=2000
 * - Segment 3: SI=10, SO=4000
 */
typedef struct rlc_um_data_pdu_6bit_sn_segmented {
    // Byte 0
    uint8_t si : 2;       // Segmentation Info: 01, 10, or 11
    uint8_t sn : 6;       // Sequence Number (0-63)
    // Byte 1
    uint8_t so_high : 8;  // Segment Offset upper 8 bits
    // Byte 2
    uint8_t so_low : 8;   // Segment Offset lower 8 bits
} rlc_um_data_pdu_6bit_sn_segmented_t;

/**
 * RLC UM Data PDU with 12-bit SN (complete SDU)
 * 
 * Layer: RLC Unacknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.3.5
 * Direction: UL and DL
 * 
 * Description:
 * Extended sequence numbering for higher throughput bearers.
 * Supports sequence numbers up to 4096 (SN range: 0-4095).
 * Larger SN window reduces probability of SN wrap-around in high data rate scenarios.
 * 
 * Fields:
 * - si (2 bits): Segmentation Info (00 = complete SDU)
 * - rsv (2 bits): Reserved bits, set to 0
 * - sn_high (4 bits): SN upper 4 bits
 * - sn_low (8 bits): SN lower 8 bits
 * 
 * Total header size: 2 bytes
 * Complete SN = (sn_high << 8) | sn_low (Range: 0-4095)
 * 
 * Usage: For medium to high data rate bearers (e.g., video streaming,
 * web browsing) where 6-bit SN would wrap around too quickly.
 */
typedef struct rlc_um_data_pdu_12bit_sn_complete {
    // Byte 0
    uint8_t si : 2;       // Segmentation Info: 00 = complete
    uint8_t rsv : 2;      // Reserved bits
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_low : 8;   // SN lower 8 bits
} rlc_um_data_pdu_12bit_sn_complete_t;

/**
 * RLC UM Data PDU with 12-bit SN (segmented SDU)
 * 
 * Layer: RLC Unacknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.3.5
 * Direction: UL and DL
 * 
 * Description:
 * Extended SN with segmentation support for large SDUs.
 * 
 * Fields:
 * - si (2 bits): Segmentation Info (01, 10, or 11)
 * - rsv (2 bits): Reserved
 * - sn_high (4 bits): SN upper bits
 * - sn_low (8 bits): SN lower bits
 * - so_high (8 bits): Segment Offset upper byte
 * - so_low (8 bits): Segment Offset lower byte
 * 
 * Total header size: 4 bytes
 * Complete SN = (sn_high << 8) | sn_low
 * Complete SO = (so_high << 8) | so_low
 */
typedef struct rlc_um_data_pdu_12bit_sn_segmented {
    // Byte 0
    uint8_t si : 2;       // Segmentation Info: 01, 10, or 11
    uint8_t rsv : 2;      // Reserved bits
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_low : 8;   // SN lower 8 bits
    // Byte 2
    uint8_t so_high : 8;  // Segment Offset upper byte
    // Byte 3
    uint8_t so_low : 8;   // Segment Offset lower byte
} rlc_um_data_pdu_12bit_sn_segmented_t;

/*----------------------------------------------------------------------------
 * RLC Acknowledged Mode (AM)
 *--------------------------------------------------------------------------*/

/**
 * RLC AM Data PDU with 12-bit SN (complete SDU)
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.4.3
 * Direction: UL and DL
 * 
 * Description:
 * Acknowledged mode with ARQ (Automatic Repeat Request) support.
 * Receiver sends STATUS PDUs to acknowledge received PDUs and
 * request retransmission of missing ones. Guarantees reliable delivery.
 * 
 * Fields:
 * - dc (1 bit): Data/Control indicator
 *   - 1: Data PDU (this structure)
 *   - 0: Control PDU (STATUS PDU)
 * - p (1 bit): Polling bit
 *   - 1: Transmitter requests STATUS report from receiver
 *   - 0: No status report requested
 * - si (2 bits): Segmentation Info (00 = complete SDU)
 * - sn_high (4 bits): SN upper 4 bits
 * - sn_low (8 bits): SN lower 8 bits
 * 
 * Total header size: 2 bytes
 * Complete SN = (sn_high << 8) | sn_low (Range: 0-4095)
 * 
 * Usage: For bearers requiring guaranteed delivery (e.g., TCP traffic,
 * file downloads, web browsing, signaling). Trade-off is higher latency
 * due to retransmissions.
 */
typedef struct rlc_am_data_pdu_12bit_sn_complete {
    // Byte 0
    uint8_t dc : 1;       // D/C: 1 = Data PDU
    uint8_t p : 1;        // Polling bit
    uint8_t si : 2;       // Segmentation Info: 00 = complete
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_low : 8;   // SN lower 8 bits
} rlc_am_data_pdu_12bit_sn_complete_t;

/**
 * RLC AM Data PDU with 12-bit SN (segmented SDU)
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.4.3
 * Direction: UL and DL
 * 
 * Description:
 * AM data PDU with segmentation support. Includes Segment Offset.
 * 
 * Fields:
 * - dc (1 bit): Data/Control (1 = Data)
 * - p (1 bit): Polling bit
 * - si (2 bits): Segmentation Info (01, 10, or 11)
 * - sn_high (4 bits): SN upper bits
 * - sn_low (8 bits): SN lower bits
 * - so_high (8 bits): Segment Offset upper byte
 * - so_low (8 bits): Segment Offset lower byte
 * 
 * Total header size: 4 bytes
 */
typedef struct rlc_am_data_pdu_12bit_sn_segmented {
    // Byte 0
    uint8_t dc : 1;       // D/C: 1 = Data PDU
    uint8_t p : 1;        // Polling bit
    uint8_t si : 2;       // Segmentation Info: 01, 10, or 11
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_low : 8;   // SN lower 8 bits
    // Byte 2
    uint8_t so_high : 8;  // Segment Offset upper byte
    // Byte 3
    uint8_t so_low : 8;   // Segment Offset lower byte
} rlc_am_data_pdu_12bit_sn_segmented_t;

/**
 * RLC AM Data PDU with 18-bit SN (complete SDU)
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.4.5
 * Direction: UL and DL
 * 
 * Description:
 * Extended 18-bit SN for very high throughput bearers with ARQ.
 * Supports sequence numbers up to 262144 (0-262143).
 * Prevents SN wrap-around even at very high data rates (e.g., 1+ Gbps).
 * 
 * Fields:
 * - dc (1 bit): Data/Control (1 = Data)
 * - p (1 bit): Polling bit
 * - si (2 bits): Segmentation Info (00 = complete)
 * - sn_high (4 bits): SN upper 4 bits
 * - sn_mid (8 bits): SN middle 8 bits
 * - sn_low (6 bits): SN lower 6 bits
 * - rsv (2 bits): Reserved
 * 
 * Total header size: 3 bytes
 * Complete SN = (sn_high << 14) | (sn_mid << 6) | sn_low
 */
typedef struct rlc_am_data_pdu_18bit_sn_complete {
    // Byte 0
    uint8_t dc : 1;       // D/C: 1 = Data PDU
    uint8_t p : 1;        // Polling bit
    uint8_t si : 2;       // Segmentation Info: 00 = complete
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_mid : 8;   // SN middle 8 bits
    // Byte 2
    uint8_t sn_low : 6;   // SN lower 6 bits
    uint8_t rsv : 2;      // Reserved bits
} rlc_am_data_pdu_18bit_sn_complete_t;

/**
 * RLC AM Data PDU with 18-bit SN (segmented SDU)
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.4.5
 * Direction: UL and DL
 * 
 * Description:
 * 18-bit SN with segmentation support for very high throughput scenarios.
 * 
 * Fields:
 * - dc, p, si, sn fields (same as complete variant)
 * - so_high, so_low: Segment Offset (16 bits total)
 * 
 * Total header size: 5 bytes
 */
typedef struct rlc_am_data_pdu_18bit_sn_segmented {
    // Byte 0
    uint8_t dc : 1;       // D/C: 1 = Data PDU
    uint8_t p : 1;        // Polling bit
    uint8_t si : 2;       // Segmentation Info: 01, 10, or 11
    uint8_t sn_high : 4;  // SN upper 4 bits
    // Byte 1
    uint8_t sn_mid : 8;   // SN middle 8 bits
    // Byte 2
    uint8_t sn_low : 6;   // SN lower 6 bits
    uint8_t rsv : 2;      // Reserved bits
    // Byte 3
    uint8_t so_high : 8;  // Segment Offset upper byte
    // Byte 4
    uint8_t so_low : 8;   // Segment Offset lower byte
} rlc_am_data_pdu_18bit_sn_segmented_t;

/**
 * RLC AM STATUS PDU - 12-bit ACK_SN (Control PDU for ACK/NACK reporting)
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.5
 * Direction: UL and DL
 * 
 * Description:
 * Receiver uses STATUS PDU to inform transmitter which PDUs were
 * received successfully (ACK) and which need retransmission (NACK).
 * This implements the ARQ protocol for reliable delivery.
 * 
 * Fixed Header Fields:
 * - dc (1 bit): Data/Control (0 = Control PDU)
 * - cpt (3 bits): Control PDU Type
 *   - 000: STATUS PDU
 * - ack_sn_high (4 bits): ACK_SN upper 4 bits
 * - ack_sn_low (8 bits): ACK_SN lower 8 bits
 *   ACK_SN acknowledges all RLC Data PDUs with SN < ACK_SN
 * - e1 (1 bit): Extension bit
 *   - 1: NACK_SN field follows (reporting missing PDUs)
 *   - 0: No more NACK_SN fields (all received up to ACK_SN)
 * - rsv (7 bits): Reserved or part of first NACK_SN
 * 
 * Total fixed header size: 3 bytes
 * Complete ACK_SN = (ack_sn_high << 8) | ack_sn_low
 * 
 * Variable Part (not fully represented in this structure):
 * - Multiple NACK_SN blocks follow if E1=1
 * - Each NACK block can indicate:
 *   - Single missing SN
 *   - Range of missing SNs (with E2 extension)
 *   - Segment-level NACKs (with E3 extension for SO_start/SO_end)
 * 
 * Example: ACK_SN=100, NACK_SN=95,97 means:
 * - PDUs 0-94: successfully received
 * - PDU 95: missing (needs retransmission)
 * - PDU 96: successfully received
 * - PDU 97: missing (needs retransmission)
 * - PDUs 98-99: successfully received
 * 
 * Note: This structure represents only the fixed header portion.
 * NACK blocks follow with variable count and are implementation-specific.
 */
typedef struct rlc_am_status_pdu_12bit {
    // Byte 0
    uint8_t dc : 1;          // D/C: 0 = Control PDU
    uint8_t cpt : 3;         // Control PDU Type: 000 = STATUS
    uint8_t ack_sn_high : 4; // ACK_SN upper 4 bits
    // Byte 1
    uint8_t ack_sn_low : 8;  // ACK_SN lower 8 bits
    // Byte 2
    uint8_t e1 : 1;          // Extension: 1 = NACK_SN follows
    uint8_t rsv : 7;         // Reserved or first NACK_SN bits
    // Variable NACK blocks follow (not represented here)...
} rlc_am_status_pdu_12bit_t;

/**
 * RLC AM STATUS PDU - 18-bit ACK_SN
 * 
 * Layer: RLC Acknowledged Mode
 * Reference: 3GPP TS 38.322 Section 6.2.5
 * Direction: UL and DL
 * 
 * Description:
 * STATUS PDU variant for 18-bit SN configuration.
 * Used in very high throughput scenarios with extended SN space.
 * 
 * Fields:
 * - dc (1 bit): D/C (0 = Control PDU)
 * - cpt (3 bits): Control PDU Type (000 = STATUS)
 * - ack_sn_high (4 bits): ACK_SN upper 4 bits
 * - ack_sn_mid (8 bits): ACK_SN middle 8 bits
 * - ack_sn_low (6 bits): ACK_SN lower 6 bits
 * - e1 (1 bit): Extension bit (1 = NACK follows)
 * - rsv (1 bit): Reserved
 * 
 * Total fixed header size: 4 bytes
 * Complete ACK_SN = (ack_sn_high << 14) | (ack_sn_mid << 6) | ack_sn_low
 * 
 * Variable NACK blocks follow (format same as 12-bit but with 18-bit SNs)
 */
typedef struct rlc_am_status_pdu_18bit {
    // Byte 0
    uint8_t dc : 1;          // D/C: 0 = Control PDU
    uint8_t cpt : 3;         // Control PDU Type: 000 = STATUS
    uint8_t ack_sn_high : 4; // ACK_SN upper 4 bits
    // Byte 1
    uint8_t ack_sn_mid : 8;  // ACK_SN middle 8 bits
    // Byte 2
    uint8_t ack_sn_low : 6;  // ACK_SN lower 6 bits
    uint8_t e1 : 1;          // Extension: 1 = NACK_SN follows
    uint8_t rsv : 1;         // Reserved
    // Byte 3 onwards: Variable NACK blocks (not represented here)...
} rlc_am_status_pdu_18bit_t;

/*============================================================================
 * MAC LAYER PDU STRUCTURES
 * Reference: 3GPP TS 38.321
 *==========================================================================*/

/**
 * MAC PDU Structure Overview
 * 
 * A MAC PDU consists of:
 * 1. One or more MAC subheaders
 * 2. Corresponding MAC SDUs or MAC Control Elements (CEs)
 * 3. Optional padding
 * 
 * Structure:
 * +------------+------------+-------+------------+
 * | Subheader1 | Subheader2 | ..... | SubheaderN |
 * +------------+------------+-------+------------+
 * | MAC SDU 1  | MAC SDU 2  | ..... | MAC SDU N  |
 * +------------+------------+-------+------------+
 * 
 * Each subheader describes the content that follows (SDU or CE).
 */

/**
 * MAC Subheader with 8-bit Length Field (Short Format)
 * 
 * Layer: MAC (Medium Access Control)
 * Reference: 3GPP TS 38.321 Section 6.1.2
 * Direction: UL and DL
 * 
 * Description:
 * Used when the MAC SDU or MAC CE size is less than 256 bytes.
 * This is the most common subheader format for typical packet sizes.
 * 
 * Fields:
 * - r (1 bit): Reserved bit, set to 0
 * - f (1 bit): Format indicator
 *   - 0: 8-bit length field (this structure)
 *   - 1: 16-bit length field (use long format)
 * - lcid (6 bits): Logical Channel ID
 *   - 0-32: Identifies the logical channel for MAC SDU
 *   - 33-63: Reserved values for MAC Control Elements
 *     Examples:
 *     - 52: C-RNTI MAC CE
 *     - 54: Short Truncated BSR
 *     - 59: Single Entry PHR
 *     - 62: Long Truncated BSR
 *     - 63: Padding
 * - l (8 bits): Length field
 *   - Indicates size of MAC SDU or MAC CE in bytes (0-255)
 * 
 * Total subheader size: 2 bytes
 * 
 * Usage: For small to medium sized packets (web browsing, VoIP,
 * control signaling, most user data).
 */
typedef struct mac_subheader_short {
    // Byte 0
    uint8_t r : 1;       // Reserved bit
    uint8_t f : 1;       // Format: 0 = 8-bit length
    uint8_t lcid : 6;    // Logical Channel ID
    // Byte 1
    uint8_t l : 8;       // Length field (0-255 bytes)
} mac_subheader_short_t;

/**
 * MAC Subheader with 16-bit Length Field (Long Format)
 * 
 * Layer: MAC
 * Reference: 3GPP TS 38.321 Section 6.1.2
 * Direction: UL and DL
 * 
 * Description:
 * Used when the MAC SDU or MAC CE size is 256 bytes or larger.
 * Required for large packets (e.g., video frames, file transfers).
 * 
 * Fields:
 * - r (1 bit): Reserved bit, set to 0
 * - f (1 bit): Format indicator
 *   - 1: 16-bit length field (this structure)
 * - lcid (6 bits): Logical Channel ID (same meaning as short format)
 * - l_high (8 bits): Length field upper 8 bits
 * - l_low (8 bits): Length field lower 8 bits
 * 
 * Total subheader size: 3 bytes
 * Complete Length = (l_high << 8) | l_low (Range: 0-65535 bytes)
 * 
 * Usage: For large packets in high-throughput scenarios (video streaming,
 * large file downloads, aggregated packets).
 */
typedef struct mac_subheader_long {
    // Byte 0
    uint8_t r : 1;       // Reserved bit
    uint8_t f : 1;       // Format: 1 = 16-bit length
    uint8_t lcid : 6;    // Logical Channel ID
    // Byte 1
    uint8_t l_high : 8;  // Length field upper 8 bits
    // Byte 2
    uint8_t l_low : 8;   // Length field lower 8 bits
} mac_subheader_long_t;

/**
 * MAC Subheader for Fixed-Size MAC CE (No Length Field)
 * 
 * Layer: MAC
 * Reference: 3GPP TS 38.321 Section 6.1.2
 * Direction: UL and DL
 * 
 * Description:
 * Some MAC Control Elements have fixed, pre-defined sizes.
 * For these CEs, no length field is needed in the subheader.
 * 
 * Fields:
 * - r (1 bit): Reserved bit, set to 0
 * - lcid (6 bits): Logical Channel ID identifying the MAC CE type
 *   Examples of fixed-size MAC CEs:
 *   - LCID 52: C-RNTI (2 bytes)
 *   - LCID 54: Short Truncated BSR (1 byte)
 *   - LCID 59: Single Entry PHR (1 byte)
 *   - LCID 63: Padding (variable, but fills remaining space)
 * 
 * Total subheader size: 1 byte
 * 
 * Note: The F bit and Length field are omitted because the size
 * is implicitly known from the LCID value. This saves overhead
 * for common control messages.
 * 
 * Usage: For control signaling (power headroom reports, buffer status
 * reports, timing advance commands, etc.).
 */
typedef struct mac_subheader_fixed {
    uint8_t r : 1;       // Reserved bit
    uint8_t lcid : 6;    // Logical Channel ID (indicates CE type)
    uint8_t e : 1;       // Extension bit (see note below)
    // Note: Some specifications show E bit at different positions.
    // Verify exact bit ordering from TS 38.321 Figure 6.1.2-1.
} mac_subheader_fixed_t;

/**
 * MAC Subheader - General Structure with E bit
 * 
 * Layer: MAC
 * Reference: 3GPP TS 38.321 Section 6.1.2
 * Direction: UL and DL
 * 
 * Description:
 * This represents the most general MAC subheader format including
 * the Extension (E) bit, which is present in actual implementations
 * but often implicitly handled.
 * 
 * The E bit indicates whether more subheaders follow:
 * - E = 1: Another subheader follows
 * - E = 0: This is the last subheader (data follows)
 * 
 * Fields:
 * - r (1 bit): Reserved
 * - f (1 bit): Format (0=8-bit L, 1=16-bit L)
 * - lcid (6 bits): Logical Channel ID
 * - l (8 or 16 bits): Length (if F=0, 8 bits; if F=1, 16 bits)
 * 
 * Note: The E bit position varies by implementation. Some place it
 * before the R bit, others after LCID. Consult TS 38.321 Section 6.1.2
 * Figure 6.1.2-1 for exact bit layout.
 * 
 * Total size: 2 bytes (short) or 3 bytes (long)
 */
typedef struct mac_subheader_with_extension {
    // Byte 0
    uint8_t r : 1;       // Reserved bit
    uint8_t f : 1;       // Format indicator
    uint8_t lcid : 6;    // Logical Channel ID
    // Byte 1
    uint8_t l : 8;       // Length field (if F=0)
    // Note: If F=1, length extends to 16 bits (byte 1-2)
    // E bit handling varies - check spec for exact position
} mac_subheader_with_extension_t;

/**
 * Important Notes on MAC Subheader Bit Ordering:
 * 
 * CRITICAL: The exact bit ordering of R, F, LCID, E, and L fields
 * can vary based on interpretation of TS 38.321 figures.
 * 
 * Common variations:
 * 1. R-F-LCID-L (no E bit shown separately)
 * 2. R-F-LCID with E bit in separate octet
 * 3. E-R-F-LCID-L (E bit first)
 * 
 * For this assignment, the structures above follow the most common
 * interpretation. However, students should:
 * 
 * 1. Carefully examine TS 38.321 Section 6.1.2 Figure 6.1.2-1
 * 2. Note any ambiguities in comments
 * 3. Justify their bit-field ordering choice in documentation
 * 
 * The E (Extension) bit is logically present to chain subheaders,
 * but its exact position in the bit structure should be verified
 * against the specification diagram.
 * 
 * Bit-field ordering assumption: MSB-first (left-to-right in spec diagrams)
 * Actual compiler behavior may require byte-swapping or reordering.
 */

/**
 * MAC PDU Multiplexing Example:
 * 
 * Example MAC PDU with 2 SDUs:
 * 
 * +----------------+----------------+----------+----------+
 * | Subhdr LCID=4  | Subhdr LCID=5  | SDU from | SDU from |
 * | F=0, L=100     | F=0, L=50      | LCID 4   | LCID 5   |
 * +----------------+----------------+----------+----------+
 * |<-- 2 bytes -->||<-- 2 bytes -->||<-100 B->||<-50 B-->|
 * 
 * Total MAC PDU size = 2 + 2 + 100 + 50 = 154 bytes
 * 
 * This multiplexing allows MAC to efficiently pack data from multiple
 * logical channels (different QoS flows, signaling, control) into a
 * single transmission block.
 */

/*============================================================================
 * IMPLEMENTATION NOTES AND ASSUMPTIONS
 *==========================================================================*/

/**
 * BIT-FIELD ORDERING:
 * -------------------
 * All structures assume MSB-first (most significant bit first) bit-field 
 * ordering as shown in 3GPP specification diagrams. However, C bit-field 
 * layout is compiler and platform dependent.
 * 
 * In practice, these structures may require:
 * - Byte swapping for network byte order
 * - Compiler-specific pragmas (#pragma pack)
 * - Platform-specific endianness handling
 * 
 * For this assignment, structures follow the logical bit ordering from
 * specifications, suitable for educational and reference purposes.
 * 
 * MULTI-BYTE FIELDS:
 * ------------------
 * Sequence numbers and offsets spanning multiple bytes are split into
 * separate bit-fields (e.g., sn_high, sn_low) to maintain byte alignment.
 * 
 * Reconstruction example for 12-bit SN:
 *   uint16_t sn = (pdu->sn_high << 8) | pdu->sn_low;
 * 
 * VARIABLE-LENGTH STRUCTURES:
 * ---------------------------
 * Some PDUs have variable-length components not fully represented here:
 * - PDCP Status Report: Variable bitmap follows fixed header
 * - RLC AM STATUS PDU: Variable NACK blocks follow fixed header
 * - MAC Control Elements: Variable payload after subheader
 * 
 * These are documented in comments as "variable portion follows."
 * 
 * COMPILER PADDING:
 * -----------------
 * Some structures may be padded by the compiler to align to word boundaries.
 * The sizeof() values shown in testing reflect actual memory layout which
 * may include padding bytes. This is expected behavior.
 * 
 * Example: RLC AM STATUS PDU (18-bit) may show 3 bytes instead of 
 * expected 4 bytes due to compiler optimization of bit-field packing.
 */

#endif
