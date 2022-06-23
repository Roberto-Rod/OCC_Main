// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class FnUnlockAccessor extends FnDefaultCommandVisitor<Long>
{
    @Override
    public Long forUnlock(final Command others, final long unlock) {
        return unlock;
    }
    
    @Override
    public Long forBase() {
        return 0L;
    }
}
