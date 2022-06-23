// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

public class FnToStringVerbose implements FnCommandVisitor<String>
{
    public static String accept(final Command command) {
        return "{" + command.accept((FnCommandVisitor<String>)new FnToStringVerbose()) + "}";
    }
    
    @Override
    public String forDummy(final Command others, final int size) {
        return "XX " + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forVersion(final Command others, final int version) {
        return String.format("version=%04X\n", version) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forMinWriteSize(final Command others, final int minWriteSize) {
        return String.format("minWriteSize=%04X\n", minWriteSize) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forMaxPacketSize(final Command others, final int maxPacketSize) {
        return String.format("maxPacketSize=%04X\n", maxPacketSize) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forErasePageSize(final Command others, final int erasePageSize) {
        return String.format("erasePageSize=%04X\n", erasePageSize) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forStartAddress(final Command others, final long startAddress) {
        return String.format("startAddress=%08X\n", startAddress) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forEndAddress(final Command others, final long endAddress) {
        return String.format("endAddress=%08X\n", endAddress) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forDeviceId(final Command others, final int deviceId) {
        return String.format("deviceId=%04X\n", deviceId) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forBase() {
        return "";
    }
    
    @Override
    public String forCommand(final Command others, final int cmd) {
        return String.format("command=0x%02X\n", cmd) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forLength(final Command others, final int length) {
        return String.format("length=0x%04X\n", length) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forUnlock(final Command others, final long unlock) {
        return String.format("unlock=0x%08X\n", unlock) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forAddress(final Command others, final long address) {
        return String.format("address=0x%08X\n", address) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forData(final Command others, final int data) {
        return String.format("data=0x%08X\n", data) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forProgramEndAddress(final Command others, final long endAddress) {
        return String.format("programEndAddress=0x%08X\n", endAddress) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forProgramStartAddress(final Command others, final long startAddress) {
        return String.format("programStartAddress=0x%08X\n", startAddress) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forProgramRegionId(final Command others, final int region) {
        return String.format("programRegion=0x%08X\n", region) + others.accept((FnCommandVisitor<String>)this);
    }
    
    @Override
    public String forStatus(final Command others, final int status) {
        String statusString = null;
        switch (status & 0xFF) {
            case 1: {
                statusString = "Success";
                break;
            }
            case 255: {
                statusString = "Command Unsupported";
                break;
            }
            case 254: {
                statusString = "Invalid Address";
                break;
            }
            case 253: {
                statusString = "Invalid Length";
                break;
            }
            default: {
                statusString = "Unknown Status";
                break;
            }
        }
        return String.format("status=0x%02X (%s)\n", (byte)status, statusString) + others.accept((FnCommandVisitor<String>)this);
    }
}
