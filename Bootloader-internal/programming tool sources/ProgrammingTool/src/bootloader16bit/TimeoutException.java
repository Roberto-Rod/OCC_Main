// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class TimeoutException extends Exception
{
    private byte[] partialResponse;
    
    public TimeoutException(final byte[] partialResponse) {
        this.partialResponse = partialResponse;
    }
    
    public byte[] getPartialResponse() {
        return this.partialResponse;
    }
}
