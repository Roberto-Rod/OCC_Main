// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropMinWriteSizeSegment implements CommandSegment
{
    private final int size;
    
    PropMinWriteSizeSegment(final int size) {
        this.size = size;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropMinWriteSize(others, this.size);
    }
    
    @Override
    public Integer getSequence() {
        return 9;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
