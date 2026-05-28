package it.unibo.iot.Agents;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.Future;
import io.vertx.core.VerticleBase;
import io.vertx.mqtt.MqttClient;

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
        this.client = MqttClient.create(vertx);

        return client.connect(this.port, this.hostName).onComplete(handle -> {
            client.publishHandler(s -> {
                // Send message to the eventBus (event/msgRecv)
                // write the latest water level value to shared memory (waterLevel, value)
            }).subscribe(this.topic, qualityOfService.value());
        });
    }
}
