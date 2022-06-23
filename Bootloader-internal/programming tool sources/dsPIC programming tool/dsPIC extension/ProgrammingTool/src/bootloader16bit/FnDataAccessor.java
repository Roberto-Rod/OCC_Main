// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.nio.ByteBuffer;
import java.util.function.Consumer;

class FnDataAccessor implements FnCommandVisitor<Consumer<ByteBuffer>>
{
    @Override
    public Consumer<ByteBuffer> forData(final Command others, final int data) {
        return bb -> {
            bb.putInt(data);
            others.accept((FnCommandVisitor<Consumer<ByteBuffer>>)this).accept(bb);
        };
    }
    
    @Override
    public Consumer<ByteBuffer> forBase() {
        return bb -> {};
    }
    
    private Consumer<ByteBuffer> makeDefaultConsumer(final Command others) {
        return bb -> others.accept((FnCommandVisitor<Consumer<ByteBuffer>>)this).accept(bb);
    }
    
    @Override
    public Consumer<ByteBuffer> forStartAddress(final Command others, final long startAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forDummy(final Command others, final int size) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forVersion(final Command others, final int version) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forMinWriteSize(final Command others, final int minWriteSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forMaxPacketSize(final Command others, final int maxPacketSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forErasePageSize(final Command others, final int erasePageSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forEndAddress(final Command others, final long endAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forDeviceId(final Command others, final int deviceId) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forCommand(final Command others, final int cmd) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forLength(final Command others, final int length) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forUnlock(final Command others, final long unlock) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forAddress(final Command others, final long address) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forStatus(final Command others, final int status) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forProgramEndAddress(final Command others, final long programEndAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forProgramStartAddress(final Command others, final long programStartAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<ByteBuffer> forProgramRegionId(final Command others, final int programRegion) {
        return this.makeDefaultConsumer(others);
    }
}
