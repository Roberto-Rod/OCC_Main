// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

interface ChunkBuilder
{
    void finish();
    
    List<Chonk> getChonks();
    
    void addChunk(final Chunk p0);
    
    void startNewChonk();
    
    ChunkBuilder combine(final ChunkBuilder p0);
}
