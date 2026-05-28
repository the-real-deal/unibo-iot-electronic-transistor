package it.unibo.iot.Model;

import io.vertx.core.shareddata.Shareable;

public record WaterLevel(double waterReading, long readingTime) implements Shareable {
}