package it.unibo.iot.Model;

public enum ChannelIdentifiers {

    WATER_LEVEL("device/waterLevel"),
    VALVE_OPENING("device/valveOpening"),
    MESSAGE_RECEIVED("event/msgRecv"),
    CONTROL_VALVE("event/controlValve"),
    STATE_CHANGED("event/stateChanged"),
    CURRENT_STATE("shared/state");

    public final String value;

    private ChannelIdentifiers(String name) {
        this.value = name;
    }
}
