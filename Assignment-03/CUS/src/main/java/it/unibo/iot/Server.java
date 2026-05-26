package it.unibo.iot;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

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
        logger.info("Hello, World!");
    }
}
