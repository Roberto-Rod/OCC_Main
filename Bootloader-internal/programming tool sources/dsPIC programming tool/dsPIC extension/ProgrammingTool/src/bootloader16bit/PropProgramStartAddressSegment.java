// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramStartAddressSegment implements CommandSegment
{
    private final int programStartAddress;
    
    PropProgramStartAddressSegment(final int programStartAddress) {
        this.programStartAddress = programStartAddress;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropProgramStartAddress(others, this.programStartAddress);
    }
    
    @Override
    public Integer getSequence() {
        return 12;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
