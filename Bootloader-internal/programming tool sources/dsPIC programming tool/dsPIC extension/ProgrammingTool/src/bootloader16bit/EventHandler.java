// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.concurrent.ExecutionException;
import java.io.IOException;

public interface EventHandler
{
    void illegalState(final IllegalStateException p0);
    
    void checksumFailed(final int p0);
    
    void serialConfigException(final IOException p0);
    
    void resetRequested();
    
    void resetSuccessful();
    
    void setProgress(final double p0);
    
    void programmingFinished();
    
    void programmingStarted();
    
    void eraseRequested();
    
    void eraseFinished();
    
    void finishedEverything();
    
    void readBackVerificationRequested();
    
    void readBackVerificationPassed();
    
    void readBackVerificationFailed(final int p0, final int p1, final int p2);
    
    void selfVerificationRequested();
    
    void selfVerificationPassed();
    
    void selfVerificationFailed();
    
    void selfVerificationNotSupported();
    
    void adapterInUseException(final SerialAdapterInUseException p0, final SerialAdapter p1);
    
    void unsupportedAdapterOperation();
    
    void interruptException(final InterruptedException p0);
    
    void executionException(final ExecutionException p0);
    
    void ioException(final IOException p0);
    
    void timeoutException(final TimeoutException p0);
    
    void badResponse(final Command p0, final Command p1);
}
