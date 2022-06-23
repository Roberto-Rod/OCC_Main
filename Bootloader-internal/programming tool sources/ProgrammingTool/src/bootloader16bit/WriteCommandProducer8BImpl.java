// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Iterator;
import java.util.ArrayList;
import java.util.Collection;
import java.util.function.Predicate;
import java.util.function.Function;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collector;
import java.util.function.Supplier;
import java.util.Map;

public class WriteCommandProducer8BImpl implements WriteCommandProducer
{
    private final Map<Integer, Integer> image;
    private final CommandFactory factory;
    private final Supplier<Collector<Chunk, ChunkBuilder, List<Chonk>>> chunksToChonksCollector;
    
    WriteCommandProducer8BImpl(final Map<Integer, Integer> image, final Supplier<Collector<Chunk, ChunkBuilder, List<Chonk>>> collectorSupplier) {
        this.image = image;
        this.factory = new CommandFactoryImpl();
        this.chunksToChonksCollector = collectorSupplier;
    }
    
    @Override
    public List<Command> makeCommands() {
        if (this.image.isEmpty()) {
            return Collections.emptyList();
        }
        return this.getChunks().stream().collect((Collector<? super Object, ChunkBuilder, List<Chonk>>)this.chunksToChonksCollector.get()).stream().map((Function<? super Object, ?>)this.chonkToCommand()).filter((Predicate<? super Object>)this.getDegeneracyFilter()).collect((Collector<? super Object, Object, List<Command>>)this.getCommandOrderCollector());
    }
    
    private CommandWriteOrderCollector getCommandOrderCollector() {
        return new CommandWriteOrderCollector();
    }
    
    private Predicate<Command> getDegeneracyFilter() {
        return command -> !command.accept((FnCommandVisitor<Boolean>)new FnIsDegenerate());
    }
    
    private List<Chunk> getChunks() {
        final Integer minAddress = this.getMin();
        final Integer maxAddress = Collections.max((Collection<? extends Integer>)this.image.keySet());
        final List<Chunk> chunks = new ArrayList<Chunk>();
        for (int address = minAddress; address <= maxAddress; address += 4) {
            final int defaultValue = 16777215;
            final Integer lo = this.image.getOrDefault(address, defaultValue);
            final Integer hi = this.image.getOrDefault(address + 2, defaultValue);
            final Chunk chunk = new ChunkImpl(address, lo, hi);
            chunks.add(chunk);
        }
        return chunks;
    }
    
    private Integer getMin() {
        final Integer min = Collections.min((Collection<? extends Integer>)this.image.keySet());
        if (min % 4 == 0) {
            return min;
        }
        return min - 2;
    }
    
    private Function<Chonk, Command> chonkToCommand() {
        Command command;
        final Iterator<Integer> iterator;
        Integer i;
        final Command command2;
        return (Function<Chonk, Command>)(chonk -> {
            command = this.factory.makeBase().setCommand(this.factory.getWriteFlashCommandId()).setUnlock(this.factory.getUnlockSequence()).setAddress(chonk.getAddress()).setLength(0);
            chonk.getWords().iterator();
            while (iterator.hasNext()) {
                i = iterator.next();
                command = command.addWord(i);
            }
            command2 = command.setLength(command.accept((FnCommandVisitor<Integer>)new FnWriteDataByteCounter<Object>()));
            return command2;
        });
    }
}
