// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collection;
import java.util.ArrayList;
import java.util.List;

class ChonkBuilderImpl implements ChunkBuilder
{
    private Chonk chonk;
    private final List<Chonk> chonks;
    
    public ChonkBuilderImpl(final List<Chonk> chonks) {
        this.chonks = chonks;
        this.chonk = new ChonkImpl(new ArrayList<Chunk>());
    }
    
    @Override
    public void finish() {
        if (!this.chonk.getChunks().isEmpty()) {
            this.chonks.add(this.chonk);
        }
    }
    
    @Override
    public List<Chonk> getChonks() {
        return this.chonks;
    }
    
    @Override
    public void addChunk(final Chunk chunk) {
        this.chonk.addChunk(chunk);
    }
    
    @Override
    public void startNewChonk() {
        this.chonks.add(this.chonk);
        this.chonk = new ChonkImpl(new ArrayList<Chunk>());
    }
    
    @Override
    public ChunkBuilder combine(final ChunkBuilder other) {
        this.chonks.addAll(other.getChonks());
        return this;
    }
}
