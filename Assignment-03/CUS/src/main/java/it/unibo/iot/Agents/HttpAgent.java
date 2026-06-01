package it.unibo.iot.Agents;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServer;
import io.vertx.core.json.JsonObject;
import io.vertx.core.shareddata.LocalMap;
import io.vertx.core.shareddata.SharedData;
import io.vertx.ext.web.Router;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.States;
import it.unibo.iot.Model.WaterLevel;

public class HttpAgent extends VerticleBase {

    @Override
    public Future<?> start() throws Exception {

        HttpServer server = vertx.createHttpServer();

        Router router = Router.router(vertx);

        SharedData sd = vertx.sharedData();

        LocalMap<String, Integer> valveLevel = sd.getLocalMap(ChannelIdentifiers.VALVE_OPENING.value);
        LocalMap<String, States> currentState = sd.getLocalMap(ChannelIdentifiers.CURRENT_STATE.value);
        LocalMap<String, WaterLevel> waterLevel = sd.getLocalMap(ChannelIdentifiers.WATER_LEVEL.value);

        /**
         * Single GET endpoint used to update the ui, the following is the json response
         * {
         * "waterLevel":"1",
         * "sampleTimestamp":"19:00",
         * "currentState":"unconnected",
         * "valveLevel":"30%"
         * }
         */
        router
                .get("/updateUI")
                .respond(
                        ctx -> Future.succeededFuture(new JsonObject()
                                .put("waterLevel", waterLevel.get(MapKeys.WATER_LEVEL).waterReading())
                                .put("sampleTimestamp", waterLevel.get(MapKeys.WATER_LEVEL).readingTime())
                                .put("currentState", currentState.get(MapKeys.CURRENT_STATE).stateValue)
                                .put("valveLevel", valveLevel.get(MapKeys.VALVE_LEVEL))));

        router
                .route(HttpMethod.POST, "/interaction/valve")
                .handler(ctx -> {

                    JsonObject request = ctx.body().asJsonObject();
                    if (request.containsKey(MapKeys.VALVE_LEVEL)) {
                        Integer valveRequest = request.getInteger(MapKeys.VALVE_LEVEL);
                        vertx.eventBus().publish(ChannelIdentifiers.CONTROL_VALVE.value, valveRequest);
                    }
                });
        router
                .route(HttpMethod.POST, "/interaction/state")
                .handler(ctx -> {

                    JsonObject request = ctx.body().asJsonObject();
                    if (request.containsKey(MapKeys.CURRENT_STATE)) {
                        String state = request.getString(MapKeys.CURRENT_STATE);
                        States s = States.UNKNOWN;
                        if (state.equals(States.AUTOMATIC.stateValue))
                            s = States.AUTOMATIC;
                        else if (state.equals(States.MANUAL.stateValue))
                            s = States.MANUAL;
                        if (!s.equals(States.UNKNOWN)) {
                            vertx.eventBus().publish(ChannelIdentifiers.STATE_CHANGED.value, s);
                        }
                    }
                });

        return server.requestHandler(router).listen();
    }

}
