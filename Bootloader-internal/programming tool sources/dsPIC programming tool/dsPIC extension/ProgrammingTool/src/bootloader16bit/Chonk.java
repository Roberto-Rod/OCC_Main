// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;

interface Chonk
{
    List<Chunk> getChunks();
    
    Integer getAddress();
    
    List<Integer> getWords();
    
    void addChunk(final Chunk p0);
}
