package it.unibo.iot.CommChannel;

/**
 * Simple interface for an async msg communication channel
 * 
 * @author aricci
 *
 */
public interface CommChannel {

    /**
     * Send a message represented by a string (without new line).
     * 
     * Asynchronous model.
     * 
     * @param msg
     */
    void sendMsg(String msg);

    /**
     * Closes the serial communication channel.
     */
    void close();

}
