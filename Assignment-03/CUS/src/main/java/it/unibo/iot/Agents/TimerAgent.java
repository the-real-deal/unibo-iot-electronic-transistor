package it.unibo.iot.Agents;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.core.eventbus.EventBus;
import io.vertx.core.shareddata.LocalMap;
import io.vertx.core.shareddata.SharedData;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.States;
import it.unibo.iot.Model.WaterLevel;

public class TimerAgent extends VerticleBase {

    private enum InnerState {
        VALVE_CLOSED,
        VALVE_OPEN_50,
        VALVE_OPEN_FULL;
    }

    private final long connectionTimeout;
    private final long waterLevelTimeout;
    private EventBus eventBus;

    private final double waterThreshold;
    private final double waterThresholdMax;

    private InnerState state;

    private long connectionTimerId = -1;
    private long waterLevelTimerId = -1;

    /**
     * Initializes the timer agent
     * 
     * @param timeout      The amount of time (ms) to confirm the TMS is not working
     * @param waterTimeout The amount of time (ms) that has to pass with the water
     *                     level > t1, to proceed to open the valve
     * @param t1           The first water threshold
     * @param t2           the second water threshold
     */
    public TimerAgent(final long timeout, final long waterTimeout, final double t1, final double t2) {
        this.connectionTimeout = timeout;
        this.waterLevelTimeout = waterTimeout;
        this.waterThreshold = t1;
        this.waterThresholdMax = t2;
        this.state = InnerState.VALVE_CLOSED;
    }

    @Override
    public Future<?> start() throws Exception {
        this.eventBus = vertx.eventBus();
        SharedData sharedData = vertx.sharedData();
        LocalMap<String, States> stateMap = sharedData.getLocalMap(ChannelIdentifiers.CURRENT_STATE.value);
        LocalMap<String, WaterLevel> waterLevel = sharedData.getLocalMap(ChannelIdentifiers.WATER_LEVEL.value);

        stateMap.put(MapKeys.CURRENT_STATE, States.AUTOMATIC);

        Runnable resetTimer = () -> {
            stateMap.put(MapKeys.PREVIOUS_STATE, stateMap.get(MapKeys.CURRENT_STATE));
            stateMap.put(MapKeys.CURRENT_STATE, States.UNCONNECTED);
            eventBus.publish(ChannelIdentifiers.STATE_CHANGED.value, States.UNCONNECTED.stateValue);
        };

        this.connectionTimerId = startWatchdog(this.connectionTimeout, resetTimer);

        eventBus.<String>consumer(ChannelIdentifiers.MESSAGE_RECEIVED.value, message -> {
            if (stateMap.get(MapKeys.CURRENT_STATE) == States.UNCONNECTED) {
                States s = stateMap.get(MapKeys.PREVIOUS_STATE);
                stateMap.put(MapKeys.CURRENT_STATE, s);
                eventBus.publish(ChannelIdentifiers.STATE_CHANGED.value, s.stateValue);
            }

            WaterLevel current = waterLevel.get(MapKeys.WATER_LEVEL);

            this.connectionTimerId = stopWatchdog(this.connectionTimerId);
            this.connectionTimerId = startWatchdog(connectionTimeout, resetTimer);

            // if the state is automatic check the water level and start timers
            if (stateMap.get(MapKeys.CURRENT_STATE) == States.AUTOMATIC) {
                double waterReading = current.waterReading();
                switch (this.state) {
                    case InnerState.VALVE_CLOSED -> {
                        if (waterReading > this.waterThresholdMax) {
                            this.waterLevelTimerId = stopWatchdog(waterLevelTimerId);
                            eventBus.publish(ChannelIdentifiers.VALVE_OPENING.value, "100");
                            this.state = InnerState.VALVE_OPEN_FULL;
                        } else if (waterReading > this.waterThreshold) {
                            waterLevelTimerId = startWatchdog(this.waterLevelTimeout, () -> {
                                eventBus.publish(ChannelIdentifiers.VALVE_OPENING.value, "50");
                                this.state = InnerState.VALVE_OPEN_50;
                            });
                        }
                    }
                    case InnerState.VALVE_OPEN_50 -> {
                        if (waterReading > this.waterThresholdMax) {
                            this.waterLevelTimerId = stopWatchdog(waterLevelTimerId);
                            eventBus.publish(ChannelIdentifiers.VALVE_OPENING.value, "100");
                            this.state = InnerState.VALVE_OPEN_FULL;
                        } else if (waterReading < this.waterThreshold) {
                            eventBus.publish(ChannelIdentifiers.VALVE_OPENING.value, "0");
                            this.state = InnerState.VALVE_CLOSED;
                        }
                    }
                    case InnerState.VALVE_OPEN_FULL -> {
                        if (waterReading < this.waterThresholdMax) {
                            eventBus.publish(ChannelIdentifiers.VALVE_OPENING.value, "50");
                            this.state = InnerState.VALVE_OPEN_50;
                        }
                    }
                }
            }
        });

        return super.start();
    }

    /**
     * Starts a timer.
     * 
     * @param _timeout How long the timer should last
     * @param function What to do after the timer is done
     * @return The id of the timer
     */
    private long startWatchdog(final long _timeout, Runnable function) {
        return vertx.setTimer(_timeout, id -> {
            function.run();
        });
    }

    /**
     * Stops a timer.
     * 
     * @param watchdogId The id of the timer to stop
     * @return a default timer id
     */
    private long stopWatchdog(final long watchdogId) {
        if (watchdogId != -1) {
            vertx.cancelTimer(watchdogId);
        }
        return -1;
    }
}