// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropMaxPacketSizeSegment implements CommandSegment
{
    private final int size;
    
    PropMaxPacketSizeSegment(final int size) {
        this.size = size;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropMaxPacketSize(others, this.size);
    }
    
    @Override
    public Integer getSequence() {
        return 6;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
