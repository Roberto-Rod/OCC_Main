// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.HashMap;
import java.util.Map;

class HexParserImpl extends HexParser
{
    private int state;
    private int bc0;
    private int bc1;
    private int byteCount;
    private int ad0;
    private int ad1;
    private int ad2;
    private int ad3;
    private int address;
    private int re0;
    private int re1;
    private int recordType;
    private int da0;
    private int da1;
    private int da2;
    private int da3;
    private int da4;
    private int da5;
    private int da6;
    private int da7;
    private int ela0;
    private int ela1;
    private int ela2;
    private int ela3;
    private final Map<Integer, Integer> memory;
    private int ela;
    private int checksum;
    private int cs0;
    private int cs1;
    private int recordLine;
    private final int EOF = -1;
    private final int BYTE_COUNT = 100;
    private final int ADDRESS = 200;
    private final int RECORD_TYPE = 300;
    private final int DATA = 400;
    private final int CHECKSUM = 500;
    private final int ELA = 600;
    private final int SWALLOW_WHITE_SPACE = 700;
    
    public Map<Integer, Integer> getMemory() {
        return this.memory;
    }
    
    HexParserImpl() {
        this.memory = new HashMap<Integer, Integer>();
        this.address = 0;
        this.ela = 0;
        this.recordLine = 0;
    }
    
    public void reset() {
        this.memory.clear();
        this.address = 0;
        this.ela = 0;
        this.recordLine = 0;
    }
    
    public void start() {
        this.state = 100;
        ++this.recordLine;
    }
    
    public void other(final byte code) throws ChecksumException {
        final int nibble = this.codeToNibble(code);
        switch (this.state) {
            case 100: {
                this.bc1 = nibble;
                ++this.state;
                break;
            }
            case 101: {
                this.bc0 = nibble;
                this.byteCount = this.bc1 * 16 + this.bc0;
                this.checksum = this.byteCount;
                this.state = 200;
                break;
            }
            case 200: {
                this.ad3 = nibble;
                ++this.state;
                break;
            }
            case 201: {
                this.ad2 = nibble;
                ++this.state;
                break;
            }
            case 202: {
                this.ad1 = nibble;
                ++this.state;
                break;
            }
            case 203: {
                this.ad0 = nibble;
                this.checksum += this.ad1 * 16 + this.ad0;
                this.checksum += this.ad3 * 16 + this.ad2;
                this.address = this.ela * 65536 + this.ad3 * 4096 + this.ad2 * 256 + this.ad1 * 16 + this.ad0;
                this.address /= 2;
                this.state = 300;
                break;
            }
            case 300: {
                this.re1 = nibble;
                ++this.state;
                break;
            }
            case 301: {
                this.re0 = nibble;
                this.recordType = this.re1 * 16 + this.re0;
                this.checksum += this.recordType;
                if (this.recordType == 0) {
                    this.state = 400;
                    break;
                }
                if (this.recordType == 1) {
                    this.state = -1;
                    break;
                }
                if (this.recordType == 4) {
                    this.state = 600;
                    break;
                }
                throw new IllegalStateException("Unknown record type: " + this.recordType);
            }
            case 400: {
                this.da7 = nibble;
                ++this.state;
                break;
            }
            case 401: {
                this.da6 = nibble;
                ++this.state;
                break;
            }
            case 402: {
                this.da5 = nibble;
                ++this.state;
                break;
            }
            case 403: {
                this.da4 = nibble;
                ++this.state;
                break;
            }
            case 404: {
                this.da3 = nibble;
                ++this.state;
                break;
            }
            case 405: {
                this.da2 = nibble;
                ++this.state;
                break;
            }
            case 406: {
                this.da1 = nibble;
                ++this.state;
                break;
            }
            case 407: {
                this.da0 = nibble;
                final int b0 = this.da7 * 16 + this.da6;
                final int b2 = this.da5 * 16 + this.da4;
                final int b3 = this.da3 * 16 + this.da2;
                final int b4 = this.da1 * 16 + this.da0;
                this.checksum += b0;
                this.checksum += b2;
                this.checksum += b3;
                this.checksum += b4;
                final int d = b4 * 16777216 + b3 * 65536 + b2 * 256 + b0;
                this.memory.put(this.address, d);
                this.byteCount -= 4;
                this.address += 2;
                if (this.byteCount == 0) {
                    this.state = 500;
                    break;
                }
                this.state = 400;
                break;
            }
            case 500: {
                this.cs1 = nibble;
                ++this.state;
                break;
            }
            case 501: {
                this.cs0 = nibble;
                final byte recordChecksum = (byte)(this.cs1 * 16 + this.cs0);
                final byte twosCompChecksum = (byte)(-(this.checksum & 0xFF));
                if (recordChecksum != twosCompChecksum) {
                    throw new ChecksumException(this.recordLine);
                }
                this.state = 700;
                break;
            }
            case 600: {
                this.ela3 = nibble;
                ++this.state;
                break;
            }
            case 601: {
                this.ela2 = nibble;
                ++this.state;
                break;
            }
            case 602: {
                this.ela1 = nibble;
                ++this.state;
                break;
            }
            case 603: {
                this.ela0 = nibble;
                ++this.state;
                final int elab0 = this.ela3 * 16 + this.ela2;
                final int elab2 = this.ela1 * 16 + this.ela0;
                this.checksum += elab0;
                this.checksum += elab2;
                this.ela = elab0 * 256 + elab2;
                this.state = 500;
                break;
            }
            case 700: {
                ++this.state;
                break;
            }
            case 701: {
                ++this.state;
                break;
            }
        }
    }
    
    private int codeToNibble(final byte code) {
        switch (code) {
            case 48: {
                return 0;
            }
            case 49: {
                return 1;
            }
            case 50: {
                return 2;
            }
            case 51: {
                return 3;
            }
            case 52: {
                return 4;
            }
            case 53: {
                return 5;
            }
            case 54: {
                return 6;
            }
            case 55: {
                return 7;
            }
            case 56: {
                return 8;
            }
            case 57: {
                return 9;
            }
            case 65: {
                return 10;
            }
            case 66: {
                return 11;
            }
            case 67: {
                return 12;
            }
            case 68: {
                return 13;
            }
            case 69: {
                return 14;
            }
            case 70: {
                return 15;
            }
            case 97: {
                return 10;
            }
            case 98: {
                return 11;
            }
            case 99: {
                return 12;
            }
            case 100: {
                return 13;
            }
            case 101: {
                return 14;
            }
            case 102: {
                return 15;
            }
            default: {
                return -1;
            }
        }
    }
}
