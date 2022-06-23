// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropDummySegment implements CommandSegment
{
    private final int size;
    
    public PropDummySegment(final int size) {
        this.size = size;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropDummy(others, this.size);
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
