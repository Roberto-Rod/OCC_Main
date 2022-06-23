// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropErasePageSizeSegment implements CommandSegment
{
    private final int pageSize;
    
    PropErasePageSizeSegment(final int pageSize) {
        this.pageSize = pageSize;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropErasePageSize(others, this.pageSize);
    }
    
    @Override
    public Integer getSequence() {
        return 8;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
