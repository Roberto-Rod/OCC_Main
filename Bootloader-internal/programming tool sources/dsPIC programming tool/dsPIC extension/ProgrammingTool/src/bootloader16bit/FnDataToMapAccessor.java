// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.Map;
import java.util.function.Consumer;

class FnDataToMapAccessor implements FnCommandVisitor<Consumer<Map<Integer, Integer>>>
{
    private final Integer address;
    
    FnDataToMapAccessor(final Integer address) {
        this.address = address;
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forData(final Command others, final int data) {
        return bb -> {
            bb.put(this.address, data);
            others.accept((FnCommandVisitor<Consumer<Map<Integer, Integer>>>)new FnDataToMapAccessor(this.address + 2)).accept(bb);
        };
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forBase() {
        return bb -> {};
    }
    
    private Consumer<Map<Integer, Integer>> makeDefaultConsumer(final Command others) {
        return bb -> others.accept((FnCommandVisitor<Consumer<Map>>)this).accept(bb);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forStartAddress(final Command others, final long startAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forDummy(final Command others, final int size) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forVersion(final Command others, final int version) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forMinWriteSize(final Command others, final int minWriteSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forMaxPacketSize(final Command others, final int maxPacketSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forErasePageSize(final Command others, final int erasePageSize) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forEndAddress(final Command others, final long endAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forDeviceId(final Command others, final int deviceId) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forCommand(final Command others, final int cmd) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forLength(final Command others, final int length) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forUnlock(final Command others, final long unlock) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forAddress(final Command others, final long address) {
        return bb -> others.accept((FnCommandVisitor<Consumer<Map>>)new FnDataToMapAccessor((int)address)).accept(bb);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forStatus(final Command others, final int status) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forProgramEndAddress(final Command others, final long endAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forProgramStartAddress(final Command others, final long startAddress) {
        return this.makeDefaultConsumer(others);
    }
    
    @Override
    public Consumer<Map<Integer, Integer>> forProgramRegionId(final Command others, final int region) {
        return this.makeDefaultConsumer(others);
    }
}
