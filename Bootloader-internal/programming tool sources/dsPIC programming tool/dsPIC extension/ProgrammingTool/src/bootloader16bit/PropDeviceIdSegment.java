// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropDeviceIdSegment implements CommandSegment
{
    private final int cmd;
    
    PropDeviceIdSegment(final int cmd) {
        this.cmd = cmd;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropDeviceId(others, this.cmd);
    }
    
    @Override
    public Integer getSequence() {
        return 7;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
