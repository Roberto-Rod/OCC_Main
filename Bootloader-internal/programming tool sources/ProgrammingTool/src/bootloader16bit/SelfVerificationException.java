// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class SelfVerificationException extends Exception
{
    public static String NOT_SUPPORTED;
    public static String VERIFY_FAILED;
    public static String UNKNOWN;
    
    public SelfVerificationException() {
        this(SelfVerificationException.UNKNOWN);
    }
    
    public SelfVerificationException(final String message) {
        super(message);
    }
    
    static {
        SelfVerificationException.NOT_SUPPORTED = "Self verification is not supported.";
        SelfVerificationException.VERIFY_FAILED = "Self verification failed due to boot loader rejecting the application image.";
        SelfVerificationException.UNKNOWN = "Self verification failed.";
    }
}
