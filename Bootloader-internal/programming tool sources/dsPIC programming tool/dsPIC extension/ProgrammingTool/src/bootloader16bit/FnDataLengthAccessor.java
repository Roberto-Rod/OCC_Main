// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnDataLengthAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forLength(final Command others, final int length) {
        return length;
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
}
