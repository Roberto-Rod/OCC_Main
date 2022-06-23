// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropStartAddressSegment implements CommandSegment
{
    private final int cmd;
    
    PropStartAddressSegment(final int cmd) {
        this.cmd = cmd;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropStartAddress(others, this.cmd);
    }
    
    @Override
    public Integer getSequence() {
        return 10;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
