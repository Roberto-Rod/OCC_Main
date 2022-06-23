// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnAddWord implements FnCommandVisitor<Command>
{
    private final int data;
    
    FnAddWord(final int data) {
        this.data = data;
    }
    
    @Override
    public Command forBase() {
        return new PropProgramWord(new PropCommandBase(), this.data);
    }
    
    @Override
    public Command forStartAddress(final Command others, final long startAddress) {
        return new PropStartAddress(others, startAddress);
    }
    
    @Override
    public Command forDummy(final Command others, final int size) {
        return new PropDummy(others, size);
    }
    
    @Override
    public Command forVersion(final Command others, final int version) {
        return new PropVersion(others, version);
    }
    
    @Override
    public Command forMinWriteSize(final Command others, final int minWriteSize) {
        return new PropMinWriteSize(others, minWriteSize);
    }
    
    @Override
    public Command forMaxPacketSize(final Command others, final int maxPacketSize) {
        return new PropMaxPacketSize(others, maxPacketSize);
    }
    
    @Override
    public Command forErasePageSize(final Command others, final int erasePageSize) {
        return new PropErasePageSize(others, erasePageSize);
    }
    
    @Override
    public Command forEndAddress(final Command others, final long endAddress) {
        return new PropEndAddress(others, endAddress);
    }
    
    @Override
    public Command forDeviceId(final Command others, final int deviceId) {
        return new PropDeviceId(others, deviceId);
    }
    
    @Override
    public Command forCommand(final Command others, final int cmd) {
        return new PropCommand(others.accept((FnCommandVisitor<Command>)this), cmd);
    }
    
    @Override
    public Command forLength(final Command others, final int length) {
        return new PropLength(others.accept((FnCommandVisitor<Command>)this), length);
    }
    
    @Override
    public Command forUnlock(final Command others, final long unlock) {
        return new PropUnlockCode(others.accept((FnCommandVisitor<Command>)this), unlock);
    }
    
    @Override
    public Command forAddress(final Command others, final long address) {
        return new PropAddress(others.accept((FnCommandVisitor<Command>)this), address);
    }
    
    @Override
    public Command forData(final Command others, final int data) {
        return new PropProgramWord(others.accept((FnCommandVisitor<Command>)this), data);
    }
    
    @Override
    public Command forStatus(final Command others, final int status) {
        return new PropStatus(others.accept((FnCommandVisitor<Command>)this), status);
    }
    
    @Override
    public Command forProgramEndAddress(final Command others, final long endAddress) {
        return new PropProgramEndAddress(others, endAddress);
    }
    
    @Override
    public Command forProgramStartAddress(final Command others, final long startAddress) {
        return new PropProgramStartAddress(others, startAddress);
    }
    
    @Override
    public Command forProgramRegionId(final Command others, final int programRegion) {
        return new PropProgramRegionId(others, programRegion);
    }
}
