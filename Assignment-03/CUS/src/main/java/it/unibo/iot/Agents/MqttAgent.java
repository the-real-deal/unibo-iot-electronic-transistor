package it.unibo.iot.Agents;

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

        Logger l = LoggerFactory.getLogger(MqttAgent.class);

        this.client = MqttClient.create(vertx);

        client.subscribe(this.topic, qualityOfService.value());

        return client.connect(this.port, this.hostName).onComplete(handle -> {
            client.publishHandler(s -> {
                try {
                    String[] msg = s.payload().toString().split(":");
                    double reading;
                    long timestamp;
                    reading = Double.parseDouble(msg[0]);
                    timestamp = Long.parseLong(msg[1]);
                    var waterLevel = new WaterLevel(reading, timestamp);

                    vertx.eventBus().publish(ChannelIdentifiers.MESSAGE_RECEIVED.value, waterLevel);
                    vertx.sharedData()
                            .getLocalMap(ChannelIdentifiers.WATER_LEVEL.value)
                            .put(MapKeys.WATER_LEVEL, waterLevel);
                } catch (NumberFormatException e) {
                    l.error("Error receiving data: ", e);
                }
            });
        });
    }
}
