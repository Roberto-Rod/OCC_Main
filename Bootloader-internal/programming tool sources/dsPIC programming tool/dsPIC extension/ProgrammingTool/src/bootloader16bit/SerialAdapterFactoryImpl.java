// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import console16bit.Console16bit;

class SerialAdapterFactoryImpl implements SerialAdapterFactory
{
    private final Bootloader16AbstractFactory factory;
    private final Console16bit console;
    
    public SerialAdapterFactoryImpl(final Bootloader16AbstractFactory factory, final Console16bit console) {
        this.factory = factory;
        this.console = console;
    }
    
    @Override
    public SerialAdapter makeSerialAdapter() {
        return this.factory.makeSerialAdapter(this.console);
    }
    
    @Override
    public SerialAdapter makeMockAdapter() {
        return this.factory.makeMockAdapter(this.console);
    }
}
