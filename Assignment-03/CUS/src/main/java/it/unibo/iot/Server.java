package it.unibo.iot;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Vertx;
import it.unibo.iot.Agents.HttpAgent;
import it.unibo.iot.Agents.MqttAgent;
import it.unibo.iot.Agents.SerialAgent;
import it.unibo.iot.Agents.TimerAgent;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.States;
import it.unibo.iot.Model.WaterLevel;

/**
 * Monolitic application that fetches movie rates.
 */
public final class Server {

    private static final Logger logger = LoggerFactory.getLogger(Server.class);

    private Server() {
    }

    /**
     * Launches the application. Expects {@code OMDB_API_KEY} to be a valid
     * environment variable.
     *
     * @param args a string with the movie/series name.
     */
    public static void main(final String[] args) {
        Vertx vertx = Vertx.vertx();

        // Create the shared variables and put default values
        vertx.sharedData().getLocalMap(ChannelIdentifiers.VALVE_OPENING.value).put(MapKeys.VALVE_LEVEL, 0);
        vertx.sharedData().getLocalMap(ChannelIdentifiers.WATER_LEVEL.value).put(MapKeys.WATER_LEVEL,
                new WaterLevel(0, ""));
        // Set the global state
        vertx.sharedData().getLocalMap(ChannelIdentifiers.CURRENT_STATE.value).put(MapKeys.CURRENT_STATE,
                States.AUTOMATIC);

        vertx.deployVerticle(new HttpAgent()).onComplete(handle -> {
            if (!handle.failed()) {
                logger.info("Web Server started");
            } else {
                logger.error("Error starting web server: ", handle.cause());
            }
        });

        vertx.deployVerticle(
                // broker.mqtt-dashboard.com
                new MqttAgent("192.168.63.170", 1883, "waterLevel/readings",
                        MqttQoS.AT_MOST_ONCE))
                .onComplete(handle -> {
                    if (!handle.failed()) {
                        logger.info("Mqtt listener started!");
                    } else {
                        logger.error("Error starting mqtt listener: ", handle.cause());
                    }
                });

        vertx.deployVerticle(
                new TimerAgent(10000, 4000, 0.5, 1.2)).onComplete(handle -> {
                    if (!handle.failed()) {
                        logger.info("Timer agent started!");
                    } else {
                        logger.error("Error starting timer agent: ", handle.cause());
                    }
                });

        try {
            vertx.deployVerticle(new SerialAgent("/dev/ttyACM0", 9600)).onComplete(handle -> {
                if (!handle.failed()) {
                    logger.info("Serial agent started!");
                } else {
                    logger.error("Error starting serial agent: ", handle.cause());
                }
            });
        } catch (Exception e) {
            logger.error("Error starting serial agent: ", e);
        }
    }
}
