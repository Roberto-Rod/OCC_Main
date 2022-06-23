// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.nio.ByteOrder;
import java.util.function.Consumer;
import java.nio.ByteBuffer;

abstract class DefaultCommand implements Command
{
    @Override
    public void write(final ByteBuffer bb) {
        bb.put(this.accept((FnCommandVisitor<Byte>)new FnCommandAccessor()));
        bb.putShort(this.accept((FnCommandVisitor<Integer>)new FnDataLengthAccessor()).shortValue());
        bb.putInt(this.accept((FnCommandVisitor<Long>)new FnUnlockAccessor()).intValue());
        bb.putInt(this.accept((FnCommandVisitor<Long>)new FnAddressAccessor()).intValue());
        this.accept((FnCommandVisitor<Consumer<ByteBuffer>>)new FnDataAccessor()).accept(bb);
    }
    
    @Override
    public int size() {
        final ByteBuffer bb = ByteBuffer.allocate(1024);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        this.write(bb);
        bb.flip();
        return bb.limit();
    }
    
    @Override
    public Command setAddress(final long address) {
        return new PropAddress(this, address);
    }
    
    @Override
    public Command setUnlock(final long unlock) {
        return new PropUnlockCode(this, unlock);
    }
    
    @Override
    public Command setLength(final int length) {
        return new PropLength(this, length);
    }
    
    @Override
    public Command setCommand(final int cmd) {
        return new PropCommand(this, cmd);
    }
    
    @Override
    public Command addWord(final int data) {
        return this.accept((FnCommandVisitor<Command>)new FnAddWord(data));
    }
    
    @Override
    public Command setStatus(final int status) {
        return new PropStatus(this, status);
    }
    
    @Override
    public Command setVersion(final int version) {
        return new PropVersion(this, version);
    }
    
    @Override
    public Command setDeviceId(final int deviceId) {
        return new PropDeviceId(this, deviceId);
    }
    
    @Override
    public Command setEndAddress(final long endAddress) {
        return new PropEndAddress(this, endAddress);
    }
    
    @Override
    public Command setStartAddress(final long startAddress) {
        return new PropStartAddress(this, startAddress);
    }
    
    @Override
    public Command setErasePageSize(final int erasePageSize) {
        return new PropErasePageSize(this, erasePageSize);
    }
    
    @Override
    public Command setMaxPacketSize(final int maxPacketSize) {
        return new PropMaxPacketSize(this, maxPacketSize);
    }
    
    @Override
    public Command setMinWriteSize(final int minWriteSize) {
        return new PropMinWriteSize(this, minWriteSize);
    }
    
    @Override
    public Command setDummy(final Object notUsed, final int size) {
        return new PropDummy(this, size);
    }
    
    @Override
    public Command setProgramStartAddress(final long startAddress) {
        return new PropProgramStartAddress(this, startAddress);
    }
    
    @Override
    public Command setProgramEndAddress(final long endAddress) {
        return new PropProgramEndAddress(this, endAddress);
    }
    
    @Override
    public Command setProgramRegionId(final int region) {
        return new PropProgramRegionId(this, region);
    }
    
    @Override
    public abstract <T> T accept(final FnCommandVisitor<T> p0);
}
