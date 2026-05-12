package esiot.serial;

import java.awt.*;
import javax.swing.*;

public class DroneRemoteUnitGUI extends JFrame {
    private static JButton btnTakeOff;
    private static JButton btnLand;

    private static JLabel lblDroneState;
    private static JLabel lblHangarState;
    private static JLabel lblDistance;
    private static JTextArea consoleArea;

    private enum CommandToSend {
        LANDING("Landing"), TAKE_OFF("Take Off");

        private final String text;

        private CommandToSend(String _text){
            this.text = _text;
        }

        @Override
        public String toString() {
            return this.text;
        }
    }

    public DroneRemoteUnitGUI() {
        super("Drone Remote Unit - DRU");

        setSize(1780, 840);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(15, 15));
        JPanel commandsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
        commandsPanel.setBorder(BorderFactory.createTitledBorder("Comandi Drone"));
        btnTakeOff = styleButton("TAKE OFF", new Color(80, 150, 255));
        btnLand = styleButton("LAND", new Color(120, 200, 120));
        commandsPanel.add(btnTakeOff);
        commandsPanel.add(btnLand);

        btnTakeOff.addActionListener(
                e -> sendCommand(new ProtocolMessage(CommandToSend.TAKE_OFF.toString())));
        btnLand.addActionListener(
                e -> sendCommand(new ProtocolMessage(CommandToSend.LANDING.toString())));

        JPanel statePanel = new JPanel();
        statePanel.setLayout(new GridLayout(3, 1, 5, 5));
        statePanel.setBorder(BorderFactory.createTitledBorder("Stato Sistema"));

        lblDroneState = bigLabel("Drone: REST");
        lblHangarState = bigLabel("Hangar: NORMAL");

        lblDistance = new JLabel("Distanza: -- cm", SwingConstants.CENTER);
        lblDistance.setFont(new Font("SansSerif", Font.PLAIN, 16));

        statePanel.add(lblDroneState);
        statePanel.add(lblHangarState);
        statePanel.add(lblDistance);

        add(commandsPanel, BorderLayout.NORTH);
        add(statePanel, BorderLayout.CENTER);



        // in the constructor, after building statePanel:
        consoleArea = new JTextArea(6, 40);
        consoleArea.setEditable(false);
        consoleArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        consoleArea.setBackground(Color.decode("#1a1a1a"));
        consoleArea.setForeground(Color.decode("#d4d4d4"));
        
        JScrollPane consoleScroll = new JScrollPane(consoleArea);
        consoleScroll.setBorder(BorderFactory.createTitledBorder("Console"));
        
        add(consoleScroll, BorderLayout.SOUTH);

        setVisible(true);
    }

    private JButton styleButton(String text, Color color) {
        JButton b = new JButton(text);
        b.setPreferredSize(new Dimension(160, 40));
        b.setFocusPainted(false);
        b.setBackground(color);
        b.setForeground(Color.white);
        b.setFont(new Font("SansSerif", Font.BOLD, 14));
        b.setBorder(BorderFactory.createEmptyBorder(5, 10, 5, 10));
        return b;
    }

    private JLabel bigLabel(String text) {
        JLabel l = new JLabel(text, SwingConstants.CENTER);
        l.setFont(new Font("SansSerif", Font.BOLD, 17));
        return l;
    }

    // ================================================================
    // METODI PER INVIO COMANDI (seriale)
    // ================================================================

    static CommChannel channel;

    private void sendCommand(ProtocolMessage msg) {
        logConsole("[Info]: Sending " + msg.getData());
        channel.sendMsg(msg.getData());
    }

    private static void msgHandler(ProtocolMessage msg) {
        logConsole("[" + msg.getType().toString() + "]-<" + msg.getData() + ">");
    }

    private static void cmdHandler(ProtocolMessage msg) {
        // System.out.println(msg);
        switch (msg.getType()) {
            case ProtocolMessage.MSGType.DISTANCE -> updateDistance(msg.getData());
            case ProtocolMessage.MSGType.SECURITY_STATE -> updateHangarState(msg.getData());
            case ProtocolMessage.MSGType.HANGAR_STATE -> updateDroneState(msg.getData());
            case ProtocolMessage.MSGType.LOG -> msgHandler(msg);
            default -> throw new AssertionError();
        }
    }

    public static void updateDistance(String arg) {
        SwingUtilities.invokeLater(() -> {
            lblDistance.setText("Distanza: " + arg + " cm");
        });
    }

    private static void updateDroneState(String arg) {
        SwingUtilities.invokeLater(() -> {
            lblDroneState.setText("Drone: " + arg);
        });
    }

    private static void updateHangarState(String arg) {
        SwingUtilities.invokeLater(() -> {
            lblHangarState.setText("Hangar: " + arg);
        });
    }

    private static void startSerialListener() {

        Thread serialThread = new Thread(() -> {
            while (true) {
                try {
                    ProtocolMessage msg = new ProtocolMessage(channel.receiveMsg());
                    cmdHandler(msg);
                } catch (InterruptedException e) {
                }
            }
        });

        serialThread.setDaemon(true);
        serialThread.start();
    }

    private static void logConsole(String text) {
        SwingUtilities.invokeLater(() -> {
            String ts = java.time.LocalTime.now()
            .format(java.time.format.DateTimeFormatter.ofPattern("HH:mm:ss"));
            consoleArea.append("[" + ts + "] " + text + "\n");
            consoleArea.setCaretPosition(consoleArea.getDocument().getLength()); // auto-scroll
        });
    }

    public static void main(String[] args) throws Exception {
        channel = new SerialCommChannel("/dev/ttyACM0", 9600);
        System.out.println("Info: Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Info: Ready.");
        SwingUtilities.invokeLater(DroneRemoteUnitGUI::new);
        startSerialListener();
    }
}
