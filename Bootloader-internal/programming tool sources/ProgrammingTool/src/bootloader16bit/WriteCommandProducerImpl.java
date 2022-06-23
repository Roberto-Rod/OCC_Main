// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Comparator;
import java.util.Collection;
import java.util.ArrayList;
import java.util.List;
import java.util.SortedMap;
import java.util.TreeMap;
import java.util.Map;

public class WriteCommandProducerImpl implements WriteCommandProducer
{
    private final Map<Integer, Integer> image;
    private TreeMap<Integer, Integer> sortedImage;
    private SortedMap<Integer, Integer> firstTwoWordsImage;
    private final WriteCommandConsumer consumer;
    private final int maxPayloadSize;
    private int maxIndex;
    private int index;
    private List<Integer> addresses;
    private int addressIncrement;
    private int payloadSize;
    private int elementSize;
    
    public WriteCommandProducerImpl(final Map<Integer, Integer> image, final WriteCommandConsumer consumer, final int maxPayloadSize) {
        if (image.size() < 2) {
            throw new IllegalArgumentException("Must provide >= 2 words for writing.");
        }
        this.image = image;
        this.consumer = consumer;
        this.maxPayloadSize = maxPayloadSize;
        this.sortedImage = new TreeMap<Integer, Integer>(image);
        final Map.Entry<Integer, Integer> firstWordPair = this.sortedImage.pollFirstEntry();
        final Map.Entry<Integer, Integer> secondWordPair = this.sortedImage.pollFirstEntry();
        (this.firstTwoWordsImage = new TreeMap<Integer, Integer>()).put(firstWordPair.getKey(), firstWordPair.getValue());
        this.firstTwoWordsImage.put(secondWordPair.getKey(), secondWordPair.getValue());
    }
    
    @Override
    public List<Command> makeCommands() {
        this.elementSize = 4;
        this.addressIncrement = 2;
        this.programLastWords();
        this.programFirstWords();
        return this.consumer.getCommands();
    }
    
    private void programFirstWords() {
        this.addresses = new ArrayList<Integer>(this.firstTwoWordsImage.keySet());
        this.produceAddresses();
    }
    
    private void programLastWords() {
        this.addresses = new ArrayList<Integer>(this.sortedImage.keySet());
        this.produceAddresses();
    }
    
    private void produceAddresses() {
        this.addresses.sort(Comparator.naturalOrder());
        this.maxIndex = this.addresses.size();
        this.index = 0;
        while (this.index < this.maxIndex) {
            this.produce();
            ++this.index;
        }
    }
    
    private void produce() {
        if (this.isOnlyElement()) {
            this.startNewPacket();
            this.payloadSizeClear();
            this.payloadSizeIncrement();
            this.endPacket();
        }
        else if (this.isFirstOfSeveral()) {
            this.startNewPacket();
            this.payloadSizeClear();
            this.payloadSizeIncrement();
        }
        else if (this.isInTheMiddleSomewhere() && this.isDiscontinuous()) {
            this.endPacket();
            this.startNewPacket();
            this.payloadSizeClear();
            this.payloadSizeIncrement();
        }
        else if (this.isInTheMiddleSomewhere() && this.isContinuous() && this.hasRoomForMore()) {
            this.addToPacket();
            this.payloadSizeIncrement();
        }
        else if (this.isInTheMiddleSomewhere() && this.isContinuous() && this.noRoomForMore()) {
            this.endPacket();
            this.startNewPacket();
            this.payloadSizeClear();
            this.payloadSizeIncrement();
        }
        else if (this.isTheEnd() && (this.isDiscontinuous() || this.noRoomForMore())) {
            this.endPacket();
            this.startNewPacket();
            this.payloadSizeClear();
            this.payloadSizeIncrement();
            this.endPacket();
        }
        else {
            if (!this.isTheEnd() || !this.isContinuous() || !this.hasRoomForMore()) {
                throw new IllegalStateException("Entered Illegal state while building commands.");
            }
            this.addToPacket();
            this.endPacket();
        }
    }
    
    private void endPacket() {
        this.consumer.endPacket();
    }
    
    private void payloadSizeIncrement() {
        this.payloadSize += this.elementSize;
    }
    
    private void payloadSizeClear() {
        this.payloadSize = 0;
    }
    
    private void addToPacket() {
        this.consumer.addToPacket(this.image.get(this.addresses.get(this.index)));
    }
    
    private void startNewPacket() {
        this.consumer.startNewPacket(this.addresses.get(this.index), this.image.get(this.addresses.get(this.index)));
    }
    
    private boolean hasRoomForMore() {
        return this.payloadSize + this.elementSize <= this.maxPayloadSize;
    }
    
    private boolean noRoomForMore() {
        return !this.hasRoomForMore();
    }
    
    private boolean isTheEnd() {
        return this.index == this.maxIndex - 1;
    }
    
    private boolean isInTheMiddleSomewhere() {
        return this.index != this.maxIndex - 1;
    }
    
    private boolean isDiscontinuous() {
        return !this.isContinuous();
    }
    
    private boolean isContinuous() {
        return this.addresses.get(this.index - 1) + this.addressIncrement == this.addresses.get(this.index);
    }
    
    private boolean isFirstOfSeveral() {
        return this.index == 0 && this.maxIndex > 1;
    }
    
    private boolean isOnlyElement() {
        return this.index == 0 && this.maxIndex == 1;
    }
}
