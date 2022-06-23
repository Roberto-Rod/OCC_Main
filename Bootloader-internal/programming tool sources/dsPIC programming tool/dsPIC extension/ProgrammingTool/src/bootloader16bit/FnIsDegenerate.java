// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnIsDegenerate extends FnDefaultCommandVisitor<Boolean>
{
    @Override
    public Boolean forBase() {
        return true;
    }
    
    @Override
    public Boolean forData(final Command others, final int data) {
        if (data == 16777215) {
            return others.accept((FnCommandVisitor<Boolean>)this);
        }
        return false;
    }
}
