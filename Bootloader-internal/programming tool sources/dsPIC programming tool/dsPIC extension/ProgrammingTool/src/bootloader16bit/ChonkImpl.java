// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;

class ChonkImpl implements Chonk
{
    private final List<Chunk> chunks;
    
    ChonkImpl(final List<Chunk> chunks) {
        this.chunks = chunks;
    }
    
    @Override
    public List<Chunk> getChunks() {
        return this.chunks;
    }
    
    @Override
    public Integer getAddress() {
        if (this.chunks.isEmpty()) {
            throw new IllegalStateException("Malformed intermediate image component found.");
        }
        return this.chunks.get(0).getAddress();
    }
    
    @Override
    public List<Integer> getWords() {
        final List<Integer> words = new ArrayList<Integer>();
        for (final Chunk c : this.chunks) {
            words.add(c.getLo());
            words.add(c.getHi());
        }
        return words;
    }
    
    @Override
    public void addChunk(final Chunk chunk) {
        this.chunks.add(chunk);
    }
}
