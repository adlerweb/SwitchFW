#ifndef LIB_EEP_C_
	#define LIB_EEP_C_

	uint8_t lib_eep_read_byte(uint8_t * aAddr) {
		return eeprom_read_byte(aAddr);;
	}

	uint16_t lib_eep_read_word(uint16_t * aAddr) {
		return eeprom_read_word(aAddr);;
	}

	void lib_eep_write_word(uint16_t * aAddr, uint16_t aData) {
		if (eeprom_read_word(aAddr) != aData) {
			eeprom_write_word(aAddr, aData);
		}
	}

	void lib_eep_write_byte(uint8_t * aAddr, uint8_t aData) {
		if (eeprom_read_byte(aAddr) != aData) {
			eeprom_write_byte(aAddr, aData);
		}
	}

	/*uint8_t __attribute__((always_inline)) lib_eep_fw_read_byte(uint8_t * aAddr) {
		return eeprom_read_byte(Isb_Firmware_Offset + aAddr);;
	}

	uint16_t __attribute__((always_inline)) lib_eep_fw_read_word(uint16_t * aAddr) {
		return eeprom_read_word(Isb_Firmware_Offset + aAddr);;
	}

	void __attribute__((always_inline)) lib_eep_fw_write_byte(uint8_t * aAddr, uint8_t aData) {
		if (eeprom_read_byte(Isb_Firmware_Offset + aAddr) != aData) {
			eeprom_write_byte(Isb_Firmware_Offset + aAddr, aData);
		}
	}*/
	
	 //Compares and changes data at given EEPROM-address if it differs
	 void __attribute__ ((noinline)) eep_write_byte(uint8_t * aAddr, uint8_t aData)
	 {
		 if (eeprom_read_byte(aAddr) != aData)
		 {
			 eeprom_write_byte(aAddr, aData);
		 }
	 }

#endif /* LIB_EEP_C_ */
