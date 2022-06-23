// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class ChecksumException extends Exception
{
    private int recordLine;
    
    ChecksumException(final int recordLine) {
        this.recordLine = recordLine;
    }
    
    int getRecordLine() {
        return this.recordLine;
    }
}
