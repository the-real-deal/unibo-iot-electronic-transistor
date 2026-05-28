package it.unibo.iot.Agents;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;

public class TimerAgent extends VerticleBase {

    private final long timeout;

    private long timerId = -1;

    public TimerAgent(final long timeout) {
        this.timeout = timeout;
    }

    @Override
    public Future<?> start() throws Exception {
        /*
         * Listen to event bus for water level messages
         */

        // SharedData sharedData = vertx.sharedData();
        // LocalMap<String, String> stateMap = sharedData.getLocalMap(SHARED_MAP);

        // stateMap.put(STATE_KEY, "connected");

        // startWatchdog(stateMap);

        // vertx.eventBus().consumer(ADDRESS, message -> {
        // stateMap.put(STATE_KEY, "connected");
        // resetWatchdog(stateMap);
        // });

        return super.start();
    }

    // private void startWatchdog(LocalMap<String, String> stateMap) {
    // timerId = vertx.setTimer(this.timeout, id -> {
    // // stateMap.put(STATE_KEY, "unconnected");
    // });
    // }

    // private void resetWatchdog(LocalMap<String, String> stateMap) {
    // if (timerId != -1) {
    // vertx.cancelTimer(timerId);
    // }
    // startWatchdog(stateMap);
    // }

    @Override
    public Future<?> stop() throws Exception {
        if (timerId != -1) {
            vertx.cancelTimer(timerId);
        }
        return super.stop();
    }
}