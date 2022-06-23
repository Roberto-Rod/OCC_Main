// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnPop implements FnCommandVisitor<Command>
{
    @Override
    public Command forDummy(final Command others, final int size) {
        return others;
    }
    
    @Override
    public Command forVersion(final Command others, final int version) {
        return others;
    }
    
    @Override
    public Command forMinWriteSize(final Command others, final int minWriteSize) {
        return others;
    }
    
    @Override
    public Command forMaxPacketSize(final Command others, final int maxPacketSize) {
        return others;
    }
    
    @Override
    public Command forErasePageSize(final Command others, final int erasePageSize) {
        return others;
    }
    
    @Override
    public Command forStartAddress(final Command others, final long startAddress) {
        return others;
    }
    
    @Override
    public Command forEndAddress(final Command others, final long endAddress) {
        return others;
    }
    
    @Override
    public Command forDeviceId(final Command others, final int deviceId) {
        return others;
    }
    
    @Override
    public Command forBase() {
        throw new IllegalStateException();
    }
    
    @Override
    public Command forCommand(final Command others, final int cmd) {
        return others;
    }
    
    @Override
    public Command forLength(final Command others, final int length) {
        return others;
    }
    
    @Override
    public Command forUnlock(final Command others, final long unlock) {
        return others;
    }
    
    @Override
    public Command forAddress(final Command others, final long address) {
        return others;
    }
    
    @Override
    public Command forData(final Command others, final int data) {
        return others;
    }
    
    @Override
    public Command forStatus(final Command others, final int status) {
        return others;
    }
    
    @Override
    public Command forProgramStartAddress(final Command others, final long programStartAddress) {
        return others;
    }
    
    @Override
    public Command forProgramEndAddress(final Command others, final long programEndAddress) {
        return others;
    }
    
    @Override
    public Command forProgramRegionId(final Command others, final int programRegion) {
        return others;
    }
}
