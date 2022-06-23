// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropAddressSegment implements CommandSegment
{
    private final int address;
    
    PropAddressSegment(final int address) {
        this.address = address;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropAddress(others, this.address);
    }
    
    @Override
    public Integer getSequence() {
        return 3;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
