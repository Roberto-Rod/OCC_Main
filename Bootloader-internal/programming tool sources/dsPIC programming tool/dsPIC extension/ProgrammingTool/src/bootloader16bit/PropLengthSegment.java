// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropLengthSegment implements CommandSegment
{
    private final int length;
    
    PropLengthSegment(final int length) {
        this.length = length;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropLength(others, this.length);
    }
    
    @Override
    public Integer getSequence() {
        return 1;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
