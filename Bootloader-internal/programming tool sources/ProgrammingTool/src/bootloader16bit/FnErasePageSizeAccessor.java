// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnErasePageSizeAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forErasePageSize(final Command others, final int erasePageSize) {
        return erasePageSize;
    }
}
