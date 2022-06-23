// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramRegionIdSegment implements CommandSegment
{
    private final int programRegionId;
    
    PropProgramRegionIdSegment(final int programRegionId) {
        this.programRegionId = programRegionId;
    }
    
    @Override
    public Command attach(final Command others) {
        return new PropProgramRegionId(others, this.programRegionId);
    }
    
    @Override
    public Integer getSequence() {
        return 7;
    }
    
    @Override
    public int compareTo(final CommandSegment o) {
        return this.getSequence().compareTo(o.getSequence());
    }
}
