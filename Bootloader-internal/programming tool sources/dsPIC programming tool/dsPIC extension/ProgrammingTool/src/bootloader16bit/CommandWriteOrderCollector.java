// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Collections;
import java.util.Set;
import java.util.function.Function;
import java.util.Collection;
import java.util.function.BinaryOperator;
import java.util.function.BiConsumer;
import java.util.ArrayList;
import java.util.function.Supplier;
import java.util.List;
import java.util.stream.Collector;

class CommandWriteOrderCollector implements Collector<Command, List<Command>, List<Command>>
{
    @Override
    public Supplier<List<Command>> supplier() {
        return (Supplier<List<Command>>)ArrayList::new;
    }
    
    @Override
    public BiConsumer<List<Command>, Command> accumulator() {
        return List::add;
    }
    
    @Override
    public BinaryOperator<List<Command>> combiner() {
        return (BinaryOperator<List<Command>>)((commands0, commands1) -> {
            commands0.addAll(commands1);
            return commands0;
        });
    }
    
    @Override
    public Function<List<Command>, List<Command>> finisher() {
        final Command c;
        return (Function<List<Command>, List<Command>>)(commands -> {
            c = commands.remove(0);
            commands.add(c);
            return commands;
        });
    }
    
    @Override
    public Set<Characteristics> characteristics() {
        return Collections.emptySet();
    }
}
