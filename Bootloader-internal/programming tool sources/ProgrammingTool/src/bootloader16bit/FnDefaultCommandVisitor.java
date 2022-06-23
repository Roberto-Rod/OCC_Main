// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnDefaultCommandVisitor<T> implements FnCommandVisitor<T>
{
    @Override
    public T forStartAddress(final Command others, final long startAddress) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forDummy(final Command others, final int size) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forVersion(final Command others, final int version) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forMinWriteSize(final Command others, final int minWriteSize) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forMaxPacketSize(final Command others, final int maxPacketSize) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forErasePageSize(final Command others, final int erasePageSize) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forEndAddress(final Command others, final long endAddress) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forDeviceId(final Command others, final int deviceId) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forBase() {
        throw new IllegalStateException();
    }
    
    @Override
    public T forCommand(final Command others, final int cmd) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forLength(final Command others, final int length) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forUnlock(final Command others, final long unlock) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forAddress(final Command others, final long address) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forData(final Command others, final int data) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forProgramStartAddress(final Command others, final long address) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forProgramEndAddress(final Command others, final long address) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forProgramRegionId(final Command others, final int region) {
        return others.accept((FnCommandVisitor<T>)this);
    }
    
    @Override
    public T forStatus(final Command others, final int status) {
        return others.accept((FnCommandVisitor<T>)this);
    }
}
