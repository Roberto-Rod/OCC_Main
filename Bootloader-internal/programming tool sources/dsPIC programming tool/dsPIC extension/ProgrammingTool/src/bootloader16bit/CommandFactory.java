// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

interface CommandFactory
{
    long getUnlockSequence();
    
    Command makeGetVersionCommand();
    
    int getVersionCommandId();
    
    Command makeBase();
    
    byte getReadFlashCommandId();
    
    byte getEraseFlashCommandId();
    
    byte getResetDeviceCommandId();
    
    byte getWriteFlashCommandId();
    
    byte getSelfVerifyCommandId();
    
    byte getMemoryAddressRangeCommandId();
}
