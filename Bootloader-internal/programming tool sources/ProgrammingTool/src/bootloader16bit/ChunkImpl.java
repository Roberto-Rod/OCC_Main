// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class ChunkImpl implements Chunk
{
    private final Integer address;
    private final Integer lo;
    private final Integer hi;
    
    ChunkImpl(final Integer address, final Integer lo, final Integer hi) {
        this.address = address;
        this.lo = lo;
        this.hi = hi;
    }
    
    @Override
    public Integer getAddress() {
        return this.address;
    }
    
    @Override
    public Integer getLo() {
        return this.lo;
    }
    
    @Override
    public Integer getHi() {
        return this.hi;
    }
}
