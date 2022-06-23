// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Comparator;
import java.util.List;

public class FnDeconstructor implements FnCommandVisitor<List<CommandSegment>>
{
    private final List<CommandSegment> segments;
    private Integer seq;
    
    public FnDeconstructor(final List<CommandSegment> segments) {
        this.seq = 100;
        this.segments = segments;
    }
    
    @Override
    public List<CommandSegment> forDummy(final Command others, final int size) {
        this.segments.add(new PropDummySegment(size));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forVersion(final Command others, final int version) {
        this.segments.add(new PropVersionSegment(version));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forMinWriteSize(final Command others, final int minWriteSize) {
        this.segments.add(new PropMinWriteSizeSegment(minWriteSize));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forMaxPacketSize(final Command others, final int maxPacketSize) {
        this.segments.add(new PropMaxPacketSizeSegment(maxPacketSize));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forErasePageSize(final Command others, final int erasePageSize) {
        this.segments.add(new PropErasePageSizeSegment(erasePageSize));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forStartAddress(final Command others, final long startAddress) {
        this.segments.add(new PropStartAddressSegment((int)startAddress));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forEndAddress(final Command others, final long endAddress) {
        this.segments.add(new PropEndAddressSegment((int)endAddress));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forDeviceId(final Command others, final int deviceId) {
        this.segments.add(new PropDeviceIdSegment(deviceId));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forBase() {
        this.segments.sort(Comparator.naturalOrder());
        return this.segments;
    }
    
    @Override
    public List<CommandSegment> forCommand(final Command others, final int cmd) {
        this.segments.add(new PropCommandSegment(cmd));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forLength(final Command others, final int length) {
        this.segments.add(new PropLengthSegment(length));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forUnlock(final Command others, final long unlock) {
        this.segments.add(new PropUnlockCodeSegment((int)unlock));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forAddress(final Command others, final long address) {
        this.segments.add(new PropAddressSegment((int)address));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forData(final Command others, final int data) {
        final List<CommandSegment> segments = this.segments;
        final Integer seq = this.seq;
        ++this.seq;
        segments.add(new PropProgramWordSegment(data, seq));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forStatus(final Command others, final int status) {
        this.segments.add(new PropStatusSegment(status));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forProgramStartAddress(final Command others, final long startAddress) {
        this.segments.add(new PropProgramStartAddressSegment((int)startAddress));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forProgramEndAddress(final Command others, final long endAddress) {
        this.segments.add(new PropProgramEndAddressSegment((int)endAddress));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
    
    @Override
    public List<CommandSegment> forProgramRegionId(final Command others, final int regionId) {
        this.segments.add(new PropProgramRegionIdSegment(regionId));
        return others.accept((FnCommandVisitor<List<CommandSegment>>)this);
    }
}
