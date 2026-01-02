# 5G NR Layer-2 PDU Structure Definitions

[![C](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![3GPP](https://img.shields.io/badge/3GPP-Release%2015%2F16-orange.svg)](https://www.3gpp.org/)

A comprehensive implementation of 5G New Radio (NR) Layer-2 Protocol Data Unit (PDU) header structures in C, strictly based on 3GPP specifications.

## 📋 Overview

This project provides complete C structure definitions for all PDU header formats used in 5G NR Layer-2 protocols:
- **SDAP** (Service Data Adaptation Protocol)
- **PDCP** (Packet Data Convergence Protocol)
- **RLC** (Radio Link Control)
- **MAC** (Medium Access Control)

All structures are derived directly from 3GPP specifications with bit-accurate field definitions and comprehensive documentation.

## 🎯 Features

- ✅ **24+ PDU structures** covering all Layer-2 protocols
- ✅ **Bit-field accurate** representations matching 3GPP specs
- ✅ **Comprehensive documentation** with field descriptions
- ✅ **Multiple variants** for different configuration modes
- ✅ **3GPP compliant** with specification references
- ✅ **Zero dependencies** - pure C with standard library only

## 📦 Structure Coverage

### SDAP Layer (TS 37.324)
- SDAP Data PDU with RQI/RDI
- SDAP Data PDU without RQI/RDI

### PDCP Layer (TS 38.323)
- PDCP Data PDU (12-bit SN)
- PDCP Data PDU (18-bit SN)
- PDCP Control PDU (Status Report)
- PDCP Control PDU (ROHC Feedback)

### RLC Layer (TS 38.322)
- RLC Transparent Mode (TM) - documented
- RLC Unacknowledged Mode (UM) - 6-bit and 12-bit SN variants
- RLC Acknowledged Mode (AM) - 12-bit and 18-bit SN variants
- RLC AM STATUS PDU

### MAC Layer (TS 38.321)
- MAC Subheader (8-bit length field)
- MAC Subheader (16-bit length field)
- MAC Subheader (fixed-size MAC CE)
- MAC Subheader with extension bit

## 🚀 Quick Start

### Prerequisites
- GCC compiler or compatible C compiler
- C11 standard support

### Clone the Repository
```bash
git clone https://github.com/YOUR_USERNAME/5G-NR-Layer2-PDU-Structures.git
cd 5G-NR-Layer2-PDU-Structures
```

### Compile and Test
```bash
cd src
gcc test_compile.c -o test
./test
```

### Expected Output
```
=== 5G NR PDU Structure Sizes ===

SDAP Layer:
  SDAP Data PDU (with RQI/RDI):    1 byte(s)
  SDAP Data PDU (without RQI/RDI): 1 byte(s)

PDCP Layer:
  PDCP Data PDU (12-bit SN):       2 byte(s)
  PDCP Data PDU (18-bit SN):       3 byte(s)
  ...

=== Total Structures Defined: 24 ===
All 5G NR Layer-2 PDU structures compiled successfully!
```

## 📖 Usage Example
```c
#include "5g_nr_pdu_structures.h"

int main() {
    // Create a PDCP Data PDU with 12-bit SN
    pdcp_data_pdu_12bit_sn_t pdcp_pdu = {
        .dc = 1,           // Data PDU
        .rsv = 0,          // Reserved bits
        .sn_high = 0x0F,   // Upper 4 bits of SN
        .sn_low = 0xFF     // Lower 8 bits (SN = 4095)
    };
    
    // Extract complete sequence number
    uint16_t sn = (pdcp_pdu.sn_high << 8) | pdcp_pdu.sn_low;
    printf("PDCP SN: %u\n", sn);
    
    return 0;
}
```

## 📚 Documentation

- [Specification References](docs/SPECIFICATION_REFERENCES.md) - 3GPP TS references
- [Structure Overview](docs/STRUCTURE_OVERVIEW.md) - Detailed structure documentation
- [Usage Examples](examples/usage_examples.c) - Code examples

## 🔧 Technical Details

### Bit-Field Ordering
All structures assume **MSB-first** (most significant bit first) bit-field ordering as shown in 3GPP specification diagrams. Note that C bit-field layout is compiler and platform dependent.

### Multi-Byte Fields
Sequence numbers and offsets spanning multiple bytes are split into separate bit-fields for proper alignment:
```c
uint16_t sn = (pdu->sn_high << 8) | pdu->sn_low;
```

### Variable-Length PDUs
Some PDUs have variable-length components documented but not fully implemented:
- PDCP Status Report bitmap
- RLC AM STATUS PDU NACK blocks
- MAC Control Element payloads

## 📋 3GPP Specification References

| Protocol | Specification | Title |
|----------|--------------|-------|
| SDAP | TS 37.324 | Service Data Adaptation Protocol (SDAP) specification |
| PDCP | TS 38.323 | NR; Packet Data Convergence Protocol (PDCP) specification |
| RLC | TS 38.322 | NR; Radio Link Control (RLC) protocol specification |
| MAC | TS 38.321 | NR; Medium Access Control (MAC) protocol specification |

## 🛠️ Development

### Project Structure
```
.
├── src/                    # Source files
├── docs/                   # Documentation
├── examples/               # Usage examples
├── README.md              # This file
└── LICENSE                # MIT License
```

### Compilation Flags
Recommended compilation with strict warnings:
```bash
gcc -Wall -Wextra -Werror -std=c11 test_compile.c -o test
```

## 🤝 Contributing

This is an academic project completed as part of a wireless communications course. While the project is complete, suggestions and improvements are welcome:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**[Your Name]**
- GitHub: [@YOUR_USERNAME](https://github.com/YOUR_USERNAME)
- LinkedIn: [Your LinkedIn](https://linkedin.com/in/YOUR_PROFILE)
- Email: your.email@example.com

## 🎓 Academic Context

This project was developed as part of an advanced wireless communications course focusing on 5G NR protocol stack implementation. It demonstrates:
- Deep understanding of 3GPP specifications
- Protocol-level design and bit manipulation in C
- Systematic approach to complex systems engineering

## 🙏 Acknowledgments

- 3GPP for comprehensive technical specifications
- [Your University Name] for educational support
- The wireless communications research community

## 📊 Project Statistics

- **Lines of Code**: ~1500+ (including documentation)
- **Structures Defined**: 24
- **Protocols Covered**: 4 (SDAP, PDCP, RLC, MAC)
- **Documentation Coverage**: 100%

## 🔗 Related Resources

- [3GPP Specifications Portal](https://www.3gpp.org/specifications)
- [5G NR Overview](https://www.3gpp.org/technologies/5g)
- [Layer-2 Protocol Stack Documentation](https://www.sharetechnote.com/html/5G/5G_ProtocolStack.html)

## 📝 Citation

If you use this work in your research or project, please cite:
```bibtex
@software{5g_nr_layer2_pdu,
  author = {Your Name},
  title = {5G NR Layer-2 PDU Structure Definitions},
  year = {2025},
  url = {https://github.com/YOUR_USERNAME/5G-NR-Layer2-PDU-Structures}
}
```
