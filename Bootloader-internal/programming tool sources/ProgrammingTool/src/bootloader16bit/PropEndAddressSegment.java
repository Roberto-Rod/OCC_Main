// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropEndAddressSegment implements CommandSegment
{
    private final int cmd;
    
    PropEndAddressSegment(final int cmd) {
        this.cmd = cmd;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropEndAddress(others, this.cmd);
    }
    
    @Override
    public Integer getSequence() {
        return 11;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
