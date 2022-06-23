// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

interface SerialAdapterFactory
{
    SerialAdapter makeSerialAdapter();
    
    SerialAdapter makeMockAdapter();
}
