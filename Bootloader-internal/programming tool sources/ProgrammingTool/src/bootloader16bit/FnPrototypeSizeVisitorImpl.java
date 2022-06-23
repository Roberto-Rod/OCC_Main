// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnPrototypeSizeVisitorImpl implements FnCommandVisitor<Integer>
{
    @Override
    public Integer forDummy(final Command others, final int size) {
        return size + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forVersion(final Command others, final int version) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forMinWriteSize(final Command others, final int minWriteSize) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forMaxPacketSize(final Command others, final int maxPacketSize) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forErasePageSize(final Command others, final int erasePageSize) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forStartAddress(final Command others, final long startAddress) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forEndAddress(final Command others, final long endAddress) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forDeviceId(final Command others, final int deviceId) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
    
    @Override
    public Integer forCommand(final Command others, final int cmd) {
        return 1 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forLength(final Command others, final int length) {
        return 2 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forUnlock(final Command others, final long unlock) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forAddress(final Command others, final long address) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forData(final Command others, final int data) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forStatus(final Command others, final int status) {
        return 1 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forProgramStartAddress(final Command others, final long startAddress) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forProgramEndAddress(final Command others, final long endAddress) {
        return 4 + others.accept((FnCommandVisitor<Integer>)this);
    }
    
    @Override
    public Integer forProgramRegionId(final Command others, final int region) {
        return 1 + others.accept((FnCommandVisitor<Integer>)this);
    }
}
