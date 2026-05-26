plugins {
    // Apply the java plugin to add support for Java
    java

    // Apply the application plugin to add support for building a CLI application
    // You can run your app via task "run": ./gradlew run
    application

    /*
     * Adds tasks to export a runnable jar.
     * In order to create it, launch the "shadowJar" task.
     * The runnable jar will be found in build/libs/projectname-all.jar
     */
    id("com.gradleup.shadow") version "9.4.1"
}

repositories { // Where to search for dependencies
    mavenCentral()
}

dependencies {
    // Suppressions for SpotBugs
    compileOnly("com.github.spotbugs:spotbugs-annotations:4.9.8")

    // Maven dependencies are composed by a group name, a name and a version, separated by colons   
    /*
     * Simple Logging Facade for Java (SLF4J)
     * See: http://www.slf4j.org/
     */
    val slf4jVersion = "2.0.18"
    implementation("org.slf4j:slf4j-api:$slf4jVersion")
    // Logback backend for SLF4J
    runtimeOnly("ch.qos.logback:logback-classic:1.5.32")

    val vertxVersion = "5.0.12"

    // Source: https://mvnrepository.com/artifact/io.vertx/vertx-core
    implementation("io.vertx:vertx-core:$vertxVersion")
    // Source: https://mvnrepository.com/artifact/io.vertx/vertx-web
    implementation("io.vertx:vertx-web:$vertxVersion")
    // Source: https://mvnrepository.com/artifact/io.vertx/vertx-mqtt
    implementation("io.vertx:vertx-mqtt:$vertxVersion")
    // Source: https://mvnrepository.com/artifact/com.google.code.gson/gson
    implementation("com.google.code.gson:gson:2.13.2")

    // Serial library
    implementation("io.github.java-native:jssc:2.10.2")


    // JUnit API and testing engine
    testImplementation(platform("org.junit:junit-bom:6.1.0"))
    testImplementation("org.junit.jupiter:junit-jupiter-api")
    testRuntimeOnly("org.junit.platform:junit-platform-launcher")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine")
}

application {
    // Define the main class for the application.
    mainClass.set("it.unibo.iot.Server")
}

tasks.withType<Test>().configureEach {
    useJUnitPlatform() // Enables the engine of JUnit 5/6
    testLogging { // Additional Options
        // Display all events (test started, succeeded, failed...)
        events(*org.gradle.api.tasks.testing.logging.TestLogEvent.entries.toTypedArray())
        showStandardStreams = true // Show the standard output
    }
}

tasks.withType<Javadoc>().configureEach {
    isFailOnError = false
}
