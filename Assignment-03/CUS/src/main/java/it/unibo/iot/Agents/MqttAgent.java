package it.unibo.iot.Agents;

import java.time.LocalTime;
import java.time.format.DateTimeFormatter;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.mqtt.MqttClient;
import it.unibo.iot.Model.ChannelIdentifiers;
import it.unibo.iot.Model.MapKeys;
import it.unibo.iot.Model.WaterLevel;

public class MqttAgent extends VerticleBase {

    private static final Logger logger = LoggerFactory.getLogger(MqttAgent.class);

    private MqttClient client;
    private final String hostName;
    private final int port;
    private final String topic;
    private final MqttQoS qualityOfService;

    public MqttAgent(String host, int _port, String _topic, MqttQoS qos) {
        this.hostName = host;
        this.port = _port;
        this.topic = _topic;
        this.qualityOfService = qos;
    }

    @Override
    public Future<?> start() throws Exception {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("HH:mm:ss");

        this.client = MqttClient.create(vertx);

        return client.connect(this.port, this.hostName).onSuccess(handle -> {

            client.subscribe(this.topic, qualityOfService.value());

            client.publishHandler(s -> {
                // logger.info("Message arrived: " + s.payload().toString());
                try {

                    double reading = Double.parseDouble(s.payload().toString());
                    LocalTime now = LocalTime.now();

                    WaterLevel waterLevel = new WaterLevel(reading, now.format(formatter));

                    logger.info("Mqtt message received!");

                    vertx.eventBus().publish(ChannelIdentifiers.MESSAGE_RECEIVED.value, "message received");

                    if (reading > 0) {
                        vertx.sharedData()
                                .getLocalMap(ChannelIdentifiers.WATER_LEVEL.value)
                                .put(MapKeys.WATER_LEVEL, waterLevel);
                    }
                } catch (NumberFormatException e) {
                    logger.error("Error receiving data: ", e);
                }
            });
        });
    }
}
