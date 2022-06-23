// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class VerificationException extends Exception
{
    private int address;
    private int actual;
    private int expected;
    
    public VerificationException(final int address, final int actual, final int expected) {
        this.address = address;
        this.actual = actual;
        this.expected = expected;
    }
    
    int getExpected() {
        return this.expected;
    }
    
    int getActual() {
        return this.actual;
    }
    
    int getAddress() {
        return this.address;
    }
}
