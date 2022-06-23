// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropCommandSegment implements CommandSegment
{
    private final int cmd;
    
    PropCommandSegment(final int cmd) {
        this.cmd = cmd;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropCommand(others, this.cmd);
    }
    
    @Override
    public Integer getSequence() {
        return 0;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
