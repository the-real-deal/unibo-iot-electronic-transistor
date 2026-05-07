package esiot.serial;

import java.util.*;

public class ProtocolMessage {

    private final String raw;
    private final String type;
    private final String command;
    private final List<String> args;

    public ProtocolMessage(String input) {
        if (input == null || input.length() < 3 || !input.startsWith("<") || !input.endsWith(">")) {
            throw new IllegalArgumentException("Formato non valido: " + input);
        }

        this.raw = input;
        String content = input.substring(1, input.length() - 1);
        String[] parts = content.split("\\|");

        if (parts.length < 2) {
            throw new IllegalArgumentException("Formato incompleto: " + input);
        }

        this.type = parts[0];
        this.command = parts[1];
        if (parts.length > 2) {
            this.args = Collections.unmodifiableList(
                    Arrays.asList(parts).subList(2, parts.length));
        } else {
            this.args = Collections.emptyList();
        }
    }

    public String getType() {
        return type;
    }

    public String getCommand() {
        return command;
    }

    public String getArg(int index) {
        return args.get(index);
    }

    public String getRaw() {
        return raw;
    }
}
