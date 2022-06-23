// 
// Decompiled by Procyon v0.5.36
// 

package bootloader16bit;

class BadResponseException extends Exception
{
    private final Command request;
    private final Command response;
    
    public BadResponseException(final Command request, final Command response) {
        this.request = request;
        this.response = response;
    }
    
    Command getResponse() {
        return this.response;
    }
    
    Command getRequest() {
        return this.request;
    }
}
