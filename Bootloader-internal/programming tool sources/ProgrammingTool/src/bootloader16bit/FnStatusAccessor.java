// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnStatusAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forStatus(final Command others, final int status) {
        return status;
    }
    
    @Override
    public Integer forBase() {
        throw new IllegalStateException("No status code found!");
    }
}
