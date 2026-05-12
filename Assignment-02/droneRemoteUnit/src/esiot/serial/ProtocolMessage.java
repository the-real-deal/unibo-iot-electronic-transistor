package esiot.serial;

import java.util.*;

public class ProtocolMessage {

    public enum MSGType{
        DISTANCE,
        SECURITY_STATE,
        HANGAR_STATE,
        LOG
    }

    private static final List<String> HANGAR_STATES = List.of(
        "Drone Inside",
        "Take Off",
        "Landing",
        "Drone Outside"
    );
    private static final List<String> SECURITY_STATES = List.of(
        "Normal",
        "Alarm"
    );

    private final String data;
    @SuppressWarnings("FieldMayBeFinal")
    private MSGType type;

    public ProtocolMessage(String input) {
        this.data = input;
        try {
            if(Double.parseDouble(this.data) > 0){ // horrible but works
                this.type = MSGType.DISTANCE;
            } else {
                this.type = MSGType.LOG;
            }
        } catch(NumberFormatException nfe) {
            if (HANGAR_STATES.contains(this.data)){
                this.type = MSGType.HANGAR_STATE;
            } else if(SECURITY_STATES.contains(this.data)) {
                this.type = MSGType.SECURITY_STATE;
            } else {
                this.type = MSGType.LOG;
            }
        }
    }

    public MSGType getType() {
        return type;
    }

    public String getData() {
        return data;
    }

    @Override
    public String toString() {
        return this.getData() + ": " + this.getType();
    }
}
