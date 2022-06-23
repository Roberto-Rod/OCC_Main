// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Comparator;
import java.util.Collection;
import java.util.Collections;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class SegmentedImageImpl implements SegmentedImage
{
    private final Map<Integer, Integer> image;
    private final SegmentFactory factory;
    private Integer exclusiveEnd;
    private Integer inclusiveStart;
    private final List<Segment> segments;
    
    public SegmentedImageImpl(final Map<Integer, Integer> image, final SegmentFactory factory) {
        this.image = image;
        this.segments = new ArrayList<Segment>();
        this.factory = factory;
    }
    
    @Override
    public List<Segment> makeSegments() {
        if (this.image.isEmpty()) {
            return Collections.emptyList();
        }
        final Integer[] addresses = this.getKeyArray();
        final int length = addresses.length;
        final Integer[] backwardDiff = new Integer[length];
        backwardDiff[0] = 0;
        for (int index = 1; index < length; ++index) {
            backwardDiff[index] = addresses[index] - addresses[index - 1];
        }
        for (int index = 0; index < length; ++index) {
            if (index == 0) {
                this.segmentStart(addresses[index]);
            }
            else if (backwardDiff[index] != 2 && index + 1 != length) {
                this.segmentEnd(addresses[index - 1] + 2);
                this.makeSegment();
                this.segmentStart(addresses[index]);
            }
            else if (backwardDiff[index] != 2 && index + 1 == length) {
                this.segmentEnd(addresses[index - 1] + 2);
                this.makeSegment();
                this.segmentStart(addresses[index]);
                this.segmentEnd(addresses[index] + 2);
                this.makeSegment();
            }
            else if (backwardDiff[index] == 2 && index + 1 == length) {
                this.segmentEnd(addresses[index] + 2);
                this.makeSegment();
            }
            else if (backwardDiff[index] != 2 || index + 1 == length) {
                throw new IllegalStateException("An unexpected state was reached during verification.  This is a unified host bug!");
            }
        }
        return this.segments;
    }
    
    private void makeSegment() {
        this.segments.add(this.factory.makeSegment(this.inclusiveStart, this.exclusiveEnd));
    }
    
    private void segmentEnd(final Integer address) {
        this.exclusiveEnd = address;
    }
    
    private void segmentStart(final Integer address) {
        this.inclusiveStart = address;
    }
    
    private Integer[] getKeyArray() {
        final List<Integer> keys = new ArrayList<Integer>(this.image.keySet());
        keys.sort(Comparator.naturalOrder());
        final Integer[] array = new Integer[keys.size()];
        keys.toArray(array);
        return array;
    }
}
