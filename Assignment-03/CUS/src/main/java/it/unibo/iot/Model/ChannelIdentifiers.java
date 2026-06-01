package it.unibo.iot.Model;

public enum ChannelIdentifiers {

    /**
     * Shared variable for the water level
     */
    WATER_LEVEL("device/waterLevel"),
    /**
     * Shared variable for the valve opening percentage
     */
    VALVE_OPENING("device/valveOpening"),
    /**
     * Event for the message delivery confirmation
     */
    MESSAGE_RECEIVED("event/msgRecv"),
    /**
     * Event fired when the valve has to move
     */
    CONTROL_VALVE("event/controlValve"),
    /**
     * Event fired when the application state changes
     */
    STATE_CHANGED("event/stateChanged"),
    /**
     * Global variable for the current state
     */
    CURRENT_STATE("shared/state");

    public final String value;

    private ChannelIdentifiers(String name) {
        this.value = name;
    }
}
