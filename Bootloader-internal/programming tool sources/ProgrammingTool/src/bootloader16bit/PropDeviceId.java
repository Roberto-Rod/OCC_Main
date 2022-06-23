// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class PropDeviceId extends DefaultCommand
{
    private final Command others;
    private final int deviceId;
    
    PropDeviceId(final Command others, final int deviceId) {
        this.others = others;
        this.deviceId = deviceId;
    }
    
    @Override
    public <T> T accept(final FnCommandVisitor<T> ask) {
        return ask.forDeviceId(this.others, this.deviceId);
    }
}
