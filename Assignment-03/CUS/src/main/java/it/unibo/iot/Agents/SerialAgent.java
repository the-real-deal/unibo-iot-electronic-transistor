package it.unibo.iot.Agents;

import java.util.Objects;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.shareddata.LocalMap;
import it.unibo.iot.CommChannel.CommChannel;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.States;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class SerialAgent extends VerticleBase implements SerialPortEventListener, CommChannel {

    private static final Logger logger = LoggerFactory.getLogger(SerialAgent.class);

    private final SerialPort serialPort;
    private StringBuffer currentMsg = new StringBuffer("");

    private LocalMap<String, States> state;
    private LocalMap<String, Integer> valveLevel;

    @SuppressWarnings("LeakingThisInConstructor")
    public SerialAgent(String port, int rate) throws Exception {
        serialPort = new SerialPort(port);
        serialPort.openPort();

        serialPort.setParams(rate,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);

        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                SerialPort.FLOWCONTROL_RTSCTS_OUT);

        // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
        serialPort.addEventListener(this);

    }

    @Override
    public Future<?> start() throws Exception {

        this.state = vertx.sharedData().getLocalMap(ChannelIdentifiers.CURRENT_STATE.value);
        this.valveLevel = vertx.sharedData().getLocalMap(ChannelIdentifiers.VALVE_OPENING.value);

        EventBus eb = vertx.eventBus();

        eb.<String>consumer(ChannelIdentifiers.STATE_CHANGED.value, msg -> {
            this.sendMsg(msg.body());
        });

        eb.<String>consumer(ChannelIdentifiers.CONTROL_VALVE.value, msg -> {
            int value = Integer.parseInt(msg.body());
            valveLevel.put(MapKeys.VALVE_LEVEL, value);
            this.sendMsg(Integer.toString(value));
        });

        return super.start();
    }

    @Override
    public void serialEvent(SerialPortEvent serialPortEvent) {
        if (Objects.isNull(vertx)) {
            return;
        }
        /* if there are bytes received in the input buffer */
        if (serialPortEvent.isRXCHAR()) {
            try {
                String msg = serialPort.readString(serialPortEvent.getEventValue());

                msg = msg.replaceAll("\r", "");

                currentMsg.append(msg);

                boolean goAhead = true;

                while (goAhead) {
                    msg = currentMsg.toString();
                    int index = msg.indexOf("\n");
                    if (index >= 0) {
                        String message = msg.substring(0, index);
                        // if the value is succesfully parsed the value is the valve opening
                        logger.info("Message from serial: [" + msg + "]");
                        try {
                            int valve = Integer.parseInt(message);
                            // Set the valve global variable value
                            valveLevel.put(MapKeys.VALVE_LEVEL, valve);
                        } catch (NumberFormatException e) {
                            // in case the parse is not successfull, its a state change message
                            if (message.contains(States.AUTOMATIC.stateValue)) {
                                state.put(MapKeys.CURRENT_STATE, States.AUTOMATIC);
                                vertx.eventBus().publish(ChannelIdentifiers.STATE_CHANGED.value,
                                        States.AUTOMATIC.stateValue);
                                logger.info("Updating state: " + States.AUTOMATIC.stateValue);
                            } else if (message.contains(States.MANUAL.stateValue)) {
                                state.put(MapKeys.CURRENT_STATE, States.MANUAL);
                                vertx.eventBus().publish(ChannelIdentifiers.STATE_CHANGED.value,
                                        States.MANUAL.stateValue);
                                logger.info("Updating state: " + States.MANUAL.stateValue);
                            }
                        }
                        currentMsg = new StringBuffer("");
                        // if (index + 1 < message.length()) {
                        // currentMsg.append(message.substring(index + 1));
                        // }
                    } else {
                        goAhead = false;
                    }
                }

            } catch (SerialPortException ex) {
                logger.error("Error reading serial port: ", ex);
            }
        }
    }

    @Override
    public void sendMsg(String msg) {
        char[] array = (msg + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }
        try {
            synchronized (serialPort) {
                serialPort.writeBytes(bytes);
            }
        } catch (SerialPortException ex) {
            logger.error("Error while sending message through serial port: ", ex);
        }
    }

    @Override
    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (SerialPortException ex) {
            logger.error("Error while stopping the serial agent: ", ex);
        }
    }

}
