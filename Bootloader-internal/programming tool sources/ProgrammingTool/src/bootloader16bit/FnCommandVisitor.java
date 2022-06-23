// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

interface FnCommandVisitor<T>
{
    T forDummy(final Command p0, final int p1);
    
    T forVersion(final Command p0, final int p1);
    
    T forMinWriteSize(final Command p0, final int p1);
    
    T forMaxPacketSize(final Command p0, final int p1);
    
    T forErasePageSize(final Command p0, final int p1);
    
    T forStartAddress(final Command p0, final long p1);
    
    T forEndAddress(final Command p0, final long p1);
    
    T forDeviceId(final Command p0, final int p1);
    
    T forBase();
    
    T forCommand(final Command p0, final int p1);
    
    T forLength(final Command p0, final int p1);
    
    T forUnlock(final Command p0, final long p1);
    
    T forAddress(final Command p0, final long p1);
    
    T forData(final Command p0, final int p1);
    
    T forStatus(final Command p0, final int p1);
    
    T forProgramStartAddress(final Command p0, final long p1);
    
    T forProgramEndAddress(final Command p0, final long p1);
    
    T forProgramRegionId(final Command p0, final int p1);
}
