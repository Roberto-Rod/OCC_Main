// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collections;
import java.util.Set;
import java.util.function.Function;
import java.util.function.BinaryOperator;
import java.util.function.BiConsumer;
import java.util.ArrayList;
import java.util.function.Supplier;
import java.util.List;
import java.util.stream.Collector;

class ChunksToChonksCollectorImpl implements Collector<Chunk, ChunkBuilder, List<Chonk>>
{
    private int chunksThisChonk;
    private int chunksInAChonk;
    
    public ChunksToChonksCollectorImpl(final int chunksInAChonk) {
        this.chunksInAChonk = chunksInAChonk;
        this.chunksThisChonk = 0;
    }
    
    @Override
    public Supplier<ChunkBuilder> supplier() {
        final ChonkBuilderImpl chonkBuilderImpl;
        return (Supplier<ChunkBuilder>)(() -> {
            new ChonkBuilderImpl(new ArrayList<Chonk>());
            return chonkBuilderImpl;
        });
    }
    
    @Override
    public BiConsumer<ChunkBuilder, Chunk> accumulator() {
        return (build, chunk) -> {
            if (this.chunksThisChonk == this.chunksInAChonk) {
                build.startNewChonk();
                build.addChunk(chunk);
                this.chunksThisChonk = 1;
            }
            else {
                ++this.chunksThisChonk;
                build.addChunk(chunk);
            }
        };
    }
    
    @Override
    public BinaryOperator<ChunkBuilder> combiner() {
        return ChunkBuilder::combine;
    }
    
    @Override
    public Function<ChunkBuilder, List<Chonk>> finisher() {
        return (Function<ChunkBuilder, List<Chonk>>)(builder -> {
            builder.finish();
            return builder.getChonks();
        });
    }
    
    @Override
    public Set<Characteristics> characteristics() {
        return Collections.emptySet();
    }
}
