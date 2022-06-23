// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropProgramRegionId extends DefaultCommand
{
    private final Command others;
    private final int programRegionId;
    
    PropProgramRegionId(final Command others, final int programRegionId) {
        this.others = others;
        this.programRegionId = programRegionId;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forProgramRegionId(this.others, this.programRegionId);
    }
}
