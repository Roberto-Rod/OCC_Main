// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.function.Predicate;
import java.util.stream.IntStream;
import java.util.List;

public class SegmentImpl implements Segment
{
    private final Integer inclusiveStart;
    private final Integer exclusiveEnd;
    private final int WORD_SIZE = 4;
    
    SegmentImpl(final Integer inclusiveStart, final Integer exclusiveEnd) {
        this.inclusiveStart = inclusiveStart;
        this.exclusiveEnd = exclusiveEnd;
    }
    
    @Override
    public List<Integer> getAddresses() {
        return IntStream.range(this.inclusiveStart, this.exclusiveEnd).boxed().filter(SegmentImpl::isEven).collect((Collector<? super Integer, ?, List<Integer>>)Collectors.toList());
    }
    
    private static boolean isEven(final Integer integer) {
        return integer % 2 == 0;
    }
    
    @Override
    public int getExclusiveEnd() {
        return this.exclusiveEnd;
    }
    
    @Override
    public int getInclusiveStart() {
        return this.inclusiveStart;
    }
    
    @Override
    public int getLength() {
        return (this.exclusiveEnd - this.inclusiveStart) / 2 * 4;
    }
}
