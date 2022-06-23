// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropStatusSegment implements CommandSegment
{
    private final int cmd;
    
    PropStatusSegment(final int cmd) {
        this.cmd = cmd;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropStatus(others, this.cmd);
    }
    
    @Override
    public Integer getSequence() {
        return 5;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
