package it.unibo.iot.Agents;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;

public class SerialAgent extends VerticleBase implements SerialPortEventListener {

    @Override
    public Future<?> start() throws Exception {
        return super.start();
    }

    @Override
    public void serialEvent(SerialPortEvent serialPortEvent) {
        throw new UnsupportedOperationException("Unimplemented method 'serialEvent'");
    }

}
