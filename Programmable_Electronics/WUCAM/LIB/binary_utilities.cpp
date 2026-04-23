/* How can we extract binary values (16 and 32 bits long) from a byte array like a radio packet ?
Each number can be reconstructed by assembling the relevant bytes with the bitwise OR operator '|'.
Each byte is placed at the correct location in the result by means of the shift operator '<<'.
Shift may be applied to the individual bytes or to the result, note that it is safer to shift the result.
*/

// extract a 16 bits int from a byte array, starting at address bbuf
// (if an unsigned int is needed, just cast the result to an unsigned int)
  int from_16le( byte * bbuf ) {     // "le" is for "little-endian"
  int retval = bbuf[1];
  retval <<= 8; retval |= bbuf[0];
  return retval; 
  }
// extract a 32 bits long int from a byte array, starting at address bbuf
// (if an unsigned long is needed, just cast the result to an unsigned long)
  unsigned long from_32le( byte * bbuf ) {
  unsigned long retval = bbuf[3];
  retval <<= 8; retval |= bbuf[2];
  retval <<= 8; retval |= bbuf[1];
  retval <<= 8; retval |= bbuf[0];
  return retval; 
  }

/* How can we inject binary values (16 and 32 bits long) into a byte array like a radio packet ?
In C++, assigning a number to a byte copies only the 8 least significant bits.
This way, each byte is extracted at the least significant end (right end) of the input number, then the input number is shifted to the right in order to present the next byte.
*/

// inject a 16 bits int into a byte array, starting at address buf
// (if x is unsigned, just cast it to an int)
void to_16le( byte * buf, int x ) {
  buf[0] = x;
  buf[1] = x >> 8;
  }
// inject a 32 bits long int into a byte array, starting at address buf
// (if x is unsigned, just cast it to an long )
void to_32le( byte * buf, long x ) {
  buf[0] = x;
  buf[1] = x >> 8;
  buf[2] = x >> 16;
  buf[3] = x >> 24;
  }
