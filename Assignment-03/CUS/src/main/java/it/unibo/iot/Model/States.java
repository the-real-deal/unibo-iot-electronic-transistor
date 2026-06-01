package it.unibo.iot.Model;

import io.vertx.core.shareddata.Shareable;

public enum States implements Shareable {

    MANUAL("manual"),
    AUTOMATIC("automatic"),
    UNCONNECTED("unconnected"),
    UNKNOWN("unknown");

    public final String stateValue;

    private States(String value) {
        this.stateValue = value;
    }
}
