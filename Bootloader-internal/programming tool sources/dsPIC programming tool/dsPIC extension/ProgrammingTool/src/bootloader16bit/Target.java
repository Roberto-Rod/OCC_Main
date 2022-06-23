// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

import java.util.List;
import java.util.Map;
import java.io.IOException;

interface Target
{
    void flushInput() throws IOException;
    
    Map<Integer, Integer> read(final Command p0) throws IOException, TimeoutException, BadResponseException;
    
    void write(final List<Command> p0, final Runnable p1) throws IOException, TimeoutException, BadResponseException;
    
    Command getVersion() throws IOException, TimeoutException;
    
    Command erasePages(final int p0, final int p1) throws IOException, TimeoutException, BadResponseException;
    
    Command reset() throws IOException, TimeoutException, BadResponseException;
    
    Integer selfVerify() throws IOException, TimeoutException, BadResponseException;
    
    Command getDeviceData() throws IOException, TimeoutException, BadResponseException;
}
