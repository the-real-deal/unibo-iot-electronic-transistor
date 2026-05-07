package esiot.serial;

import java.awt.*;
import javax.swing.*;

public class DroneRemoteUnitGUI extends JFrame {
    private static JButton btnTakeOff;
    private static JButton btnLand;

    private static JLabel lblDroneState;
    private static JLabel lblHangarState;
    private static JLabel lblDistance;

    private enum DroneState {
        REST, TAKING_OFF, OPERATING, LANDING
    }

    private enum HangarState {
        NORMAL, PREALARM, ALARM
    }

    private enum CmdType {
        CMD, MSG
    }

    private enum CommandToReceive {
        SET_DISTANCE, SET_HANGARSTATE, SET_DRONESTATE
    }

    private enum CommandToSend {
        LANDING, TAKE_OFF
    }

    private static DroneState currentDroneState = DroneState.REST;
    private static HangarState currentHangarState = HangarState.NORMAL;
    private static int currentDistance = 0;

    public DroneRemoteUnitGUI() {
        super("Drone Remote Unit – DRU");

        setSize(480, 340);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(15, 15));
        JPanel commandsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
        commandsPanel.setBorder(BorderFactory.createTitledBorder("Comandi Drone"));
        btnTakeOff = styleButton("TAKE OFF", new Color(80, 150, 255));
        btnLand = styleButton("LAND", new Color(120, 200, 120));
        commandsPanel.add(btnTakeOff);
        commandsPanel.add(btnLand);

        btnTakeOff.addActionListener(
                e -> sendCommand(new ProtocolMessage("<CMD|" + CommandToSend.TAKE_OFF.toString() + ">")));
        btnLand.addActionListener(
                e -> sendCommand(new ProtocolMessage("<CMD|" + CommandToSend.LANDING.toString() + ">")));

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

        System.out.println("Info: Sending " + msg.getRaw());
        channel.sendMsg(msg.getRaw());
    }

    private static void msgHandler(ProtocolMessage msg) {
        System.out.println("Arduino Info: " + msg.getCommand());
    }

    private static void cmdHandler(ProtocolMessage msg) {
        CommandToReceive cmd = CommandToReceive.valueOf(msg.getCommand());
        switch (cmd) {
            case CommandToReceive.SET_DISTANCE:
                updateDistance(msg.getArg(0));
                break;
            case CommandToReceive.SET_DRONESTATE:
                updateDroneState(msg.getArg(0));
                break;
            case CommandToReceive.SET_HANGARSTATE:
                updateHangarState(msg.getArg(0));
                break;
            default:
                msgHandler(new ProtocolMessage(msg.getRaw()));
                break;
        }
    }

    public static void updateDistance(String arg) {
        SwingUtilities.invokeLater(() -> {
            int dist = Integer.parseInt(arg);
            currentDistance = dist;
            lblDistance.setText("Distanza: " + currentDistance + " cm");
        });
    }

    private static void updateDroneState(String arg) {
        SwingUtilities.invokeLater(() -> {
            currentDroneState = DroneState.valueOf(arg);
            lblDroneState.setText("Drone: " + currentDroneState);
        });
    }

    private static void updateHangarState(String arg) {
        SwingUtilities.invokeLater(() -> {
            currentHangarState = HangarState.valueOf(arg);
            lblDroneState.setText("Hangar: " + currentHangarState);
        });
    }

    private static void startSerialListener() {

        Thread serialThread = new Thread(() -> {
            while (true) {
                try {
                    ProtocolMessage msg = new ProtocolMessage(channel.receiveMsg());
                    CmdType type = CmdType.valueOf(msg.getType());
                    if (type.equals(CmdType.CMD)) {
                        cmdHandler(msg);
                    } else if (type.equals(CmdType.MSG)) {
                        msgHandler(msg);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        serialThread.setDaemon(true);
        serialThread.start();
    }

    public static void main(String[] args) throws Exception {
        channel = new SerialCommChannel("/dev/ttyACM0", 9600);
        System.out.println("Info: Waiting Arduino for rebooting...");
        Thread.sleep(4000);
        System.out.println("Info: Ready.");
        startSerialListener();
        SwingUtilities.invokeLater(DroneRemoteUnitGUI::new);
    }
}
