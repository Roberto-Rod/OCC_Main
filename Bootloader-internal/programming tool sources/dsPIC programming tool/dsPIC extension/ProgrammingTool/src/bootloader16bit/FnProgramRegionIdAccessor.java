// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnProgramRegionIdAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forProgramRegionId(final Command others, final int regionId) {
        return regionId;
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
}
