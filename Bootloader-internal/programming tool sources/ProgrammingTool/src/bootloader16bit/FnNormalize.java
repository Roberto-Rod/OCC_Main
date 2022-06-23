// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.ArrayList;
import java.util.List;

public class FnNormalize implements FnCommandVisitor<Command>
{
    @Override
    public Command forDummy(final Command others, final int size) {
        return this.reduce(new PropDummy(others, size).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forVersion(final Command others, final int version) {
        return this.reduce(new PropVersion(others, version).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forMinWriteSize(final Command others, final int minWriteSize) {
        return this.reduce(new PropMinWriteSize(others, minWriteSize).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forMaxPacketSize(final Command others, final int maxPacketSize) {
        return this.reduce(new PropMaxPacketSize(others, maxPacketSize).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forErasePageSize(final Command others, final int erasePageSize) {
        return this.reduce(new PropErasePageSize(others, erasePageSize).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forStartAddress(final Command others, final long startAddress) {
        return this.reduce(new PropStartAddress(others, startAddress).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forEndAddress(final Command others, final long endAddress) {
        return this.reduce(new PropEndAddress(others, endAddress).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forDeviceId(final Command others, final int deviceId) {
        return this.reduce(new PropDeviceId(others, deviceId).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forBase() {
        return new PropCommandBase();
    }
    
    @Override
    public Command forCommand(final Command others, final int cmd) {
        return this.reduce(new PropCommand(others, cmd).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forLength(final Command others, final int length) {
        return this.reduce(new PropLength(others, length).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forUnlock(final Command others, final long unlock) {
        return this.reduce(new PropUnlockCode(others, unlock).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forAddress(final Command others, final long address) {
        return this.reduce(new PropAddress(others, address).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forData(final Command others, final int data) {
        return this.reduce(new PropProgramWord(others, data).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forStatus(final Command others, final int status) {
        return this.reduce(new PropStatus(others, status).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forProgramStartAddress(final Command others, final long startAddress) {
        return this.reduce(new PropProgramStartAddress(others, startAddress).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forProgramEndAddress(final Command others, final long endAddress) {
        return this.reduce(new PropProgramEndAddress(others, endAddress).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    @Override
    public Command forProgramRegionId(final Command others, final int region) {
        return this.reduce(new PropProgramRegionId(others, region).accept((FnCommandVisitor<List<CommandSegment>>)new FnDeconstructor(new ArrayList<CommandSegment>())));
    }
    
    private Command reduce(final List<CommandSegment> ll) {
        if (ll.isEmpty()) {
            return new PropCommandBase();
        }
        final CommandSegment first = ll.remove(0);
        return first.attach(this.reduce(ll));
    }
}
