package it.unibo.iot.Agents;

import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.core.http.HttpMethod;
import io.vertx.core.http.HttpServer;
import io.vertx.core.json.JsonObject;
import io.vertx.core.shareddata.LocalMap;
import io.vertx.core.shareddata.SharedData;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.States;
import it.unibo.iot.Model.WaterLevel;

public class HttpAgent extends VerticleBase {

    // private static final Logger logger =
    // LoggerFactory.getLogger(HttpAgent.class);

    @Override
    public Future<?> start() throws Exception {

        HttpServer server = vertx.createHttpServer();

        Router router = Router.router(vertx);

        router.route().handler(CorsHandler.create()
                .addOrigin("*")
                .allowedMethod(HttpMethod.GET)
                .allowedMethod(HttpMethod.POST)
                .allowedMethod(HttpMethod.OPTIONS))
                .handler(BodyHandler.create());

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
                                // .put("waterLevel", Math.random() * 100)
                                .put("sampleTimestamp", waterLevel.get(MapKeys.WATER_LEVEL).readingTime())
                                .put("currentState", currentState.get(MapKeys.CURRENT_STATE).stateValue)
                                .put("valveLevel", valveLevel.get(MapKeys.VALVE_LEVEL))));

        router
                .route(HttpMethod.POST, "/interaction/valve")
                .handler(ctx -> {
                    try {
                        JsonObject request = ctx.body().asJsonObject();
                        if (request == null || !request.containsKey(MapKeys.VALVE_LEVEL)) {
                            ctx.response().setStatusCode(400).end("Missing valve level");
                            return;
                        }
                        Integer valveRequest = request.getInteger(MapKeys.VALVE_LEVEL);
                        vertx.eventBus().publish(ChannelIdentifiers.CONTROL_VALVE.value, valveRequest.toString());
                        valveLevel.put(MapKeys.VALVE_LEVEL, valveRequest);
                        // [TODO] decide who has to update the map
                        ctx.response().setStatusCode(200).end("OK");
                    } catch (Exception e) {
                        ctx.response().setStatusCode(500).end("Internal server error");
                    }
                });
        router
                .route(HttpMethod.POST, "/interaction/state")
                .handler(ctx -> {
                    try {
                        JsonObject request = ctx.body().asJsonObject();
                        if (request == null || !request.containsKey(MapKeys.CURRENT_STATE)) {
                            ctx.response().setStatusCode(400).end("Missing state parameter");
                            return;
                        }
                        String state = request.getString(MapKeys.CURRENT_STATE);
                        States s = States.UNKNOWN;
                        if (state.equals(States.AUTOMATIC.stateValue))
                            s = States.AUTOMATIC;
                        else if (state.equals(States.MANUAL.stateValue))
                            s = States.MANUAL;
                        if (!s.equals(States.UNKNOWN)) {
                            vertx.eventBus().publish(ChannelIdentifiers.STATE_CHANGED.value, s.stateValue);
                            currentState.put(MapKeys.CURRENT_STATE, s);
                            // [TODO] decide who has to update the map
                        }
                        ctx.response().setStatusCode(200).end("OK");
                    } catch (Exception e) {
                        ctx.response().setStatusCode(500).end("Internal server error");
                    }
                });

        return server.requestHandler(router).listen(8080);
    }

}
