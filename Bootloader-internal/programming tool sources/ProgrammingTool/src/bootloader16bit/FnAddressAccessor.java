// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnAddressAccessor extends FnDefaultCommandVisitor<Long>
{
    @Override
    public Long forBase() {
        return 0L;
    }
    
    @Override
    public Long forAddress(final Command others, final long address) {
        return address;
    }
}
