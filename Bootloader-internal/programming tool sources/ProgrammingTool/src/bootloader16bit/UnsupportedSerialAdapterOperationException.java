// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class UnsupportedSerialAdapterOperationException extends Exception
{
    UnsupportedSerialAdapterOperationException(final Throwable cause) {
        super(cause);
    }
    
    UnsupportedSerialAdapterOperationException(final String operationDescription) {
        this(new UnsupportedOperationException(operationDescription));
    }
}
