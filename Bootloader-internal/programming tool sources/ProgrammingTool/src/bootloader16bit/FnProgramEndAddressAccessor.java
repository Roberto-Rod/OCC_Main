// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnProgramEndAddressAccessor extends FnDefaultCommandVisitor<Integer>
{
    @Override
    public Integer forProgramEndAddress(final Command others, final long address) {
        return (int)address;
    }
    
    @Override
    public Integer forBase() {
        return 0;
    }
}
