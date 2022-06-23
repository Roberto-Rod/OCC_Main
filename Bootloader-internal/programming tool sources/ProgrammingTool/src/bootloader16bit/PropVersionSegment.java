// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropVersionSegment implements CommandSegment
{
    private final int version;
    
    PropVersionSegment(final int version) {
        this.version = version;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropVersion(others, this.version);
    }
    
    @Override
    public Integer getSequence() {
        return 4;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
