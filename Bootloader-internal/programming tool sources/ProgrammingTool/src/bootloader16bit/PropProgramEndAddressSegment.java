// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramEndAddressSegment implements CommandSegment
{
    private final int programEndAddress;
    
    PropProgramEndAddressSegment(final int programEndAddress) {
        this.programEndAddress = programEndAddress;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropProgramEndAddress(others, this.programEndAddress);
    }
    
    @Override
    public Integer getSequence() {
        return 16;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
