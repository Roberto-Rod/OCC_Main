// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

interface CommandStatusFactory
{
    byte getCommandSuccessId();
    
    byte getCommandUnsupportedId();
    
    byte getAddressErrorId();
    
    byte getBadLengthId();
    
    byte getVerifyFailId();
}
