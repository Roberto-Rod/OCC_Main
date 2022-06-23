// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class SegmentFactoryImpl implements SegmentFactory
{
    @Override
    public Segment makeSegment(final Integer inclusiveStart, final Integer exclusiveEnd) {
        return new SegmentImpl(inclusiveStart, exclusiveEnd);
    }
}
