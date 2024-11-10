import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.ImageIcon;

public class SmartWasteDisposalGUI {

    private JFrame frame;
    private JLabel tempLabel;
    private JLabel wasteLevelLabel;
    private JLabel tempValueLabel;
    private JLabel wasteImageLabel;
    private JLabel gifLabel;
    private JProgressBar wasteLevelProgress;
    private JButton btnEmpty;
    private JButton btnRestore;

    // Constructor to initialize the UI components
    public SmartWasteDisposalGUI() {
        // Initialize JFrame
        frame = new JFrame("Smart Waste Disposal System");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);

        // Top Panel with buttons
        JPanel topPanel = new JPanel();
        topPanel.setLayout(new FlowLayout());
        btnEmpty = new JButton("Empty");
        btnRestore = new JButton("Restore");
        topPanel.add(btnEmpty);
        topPanel.add(btnRestore);
        frame.add(topPanel, BorderLayout.NORTH);

        // Main content panel (split into two columns)
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new GridLayout(1, 2));

        // Left Column for Temperature
        JPanel leftPanel = new JPanel();
        leftPanel.setLayout(new BorderLayout());
        tempLabel = new JLabel("Temperature reached by hazardous waste:");
        tempValueLabel = new JLabel("0.00 °C");  // Placeholder for temperature value
        gifLabel = new JLabel(new ImageIcon("path_to_temperature_gif.gif"));  // Replace with your GIF path
        leftPanel.add(tempLabel, BorderLayout.NORTH);
        leftPanel.add(tempValueLabel, BorderLayout.CENTER);
        leftPanel.add(gifLabel, BorderLayout.SOUTH);
        
        // Right Column for Waste Level
        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BorderLayout());
        wasteLevelLabel = new JLabel("Waste Level: 0%"); // Placeholder
        wasteLevelProgress = new JProgressBar(0, 100);
        wasteLevelProgress.setValue(0);
        wasteLevelProgress.setStringPainted(true);
        wasteImageLabel = new JLabel(new ImageIcon("path_to_waste_container_image.png"));  // Replace with your image path
        rightPanel.add(wasteLevelLabel, BorderLayout.NORTH);
        rightPanel.add(wasteLevelProgress, BorderLayout.CENTER);
        rightPanel.add(wasteImageLabel, BorderLayout.SOUTH);

        // Add panels to main content panel
        mainPanel.add(leftPanel);
        mainPanel.add(rightPanel);
        frame.add(mainPanel, BorderLayout.CENTER);

        // Display the frame
        frame.setVisible(true);
    }

    // Method to read temperature and waste level from the Arduino (serial communication)
    public void startSerialCommunication() {
        SerialPort comPort = SerialPort.getCommPorts()[0];  // Adjust to correct COM port
        comPort.openPort();
        
        // This is just an example; you'll need to listen to the serial port and update the GUI accordingly
        new Thread(() -> {
            try {
                while (true) {
                    if (comPort.bytesAvailable() > 0) {
                        byte[] readBuffer = new byte[comPort.bytesAvailable()];
                        comPort.readBytes(readBuffer, readBuffer.length);
                        String data = new String(readBuffer);
                        
                        // Parse the data and update the labels accordingly
                        if (data.contains("TEMP")) {
                            String temp = data.split(":")[1].trim();
                            tempValueLabel.setText(temp + " °C");
                        }
                        if (data.contains("LEVEL")) {
                            String level = data.split(":")[1].trim();
                            wasteLevelLabel.setText("Waste Level: " + level + "%");
                            wasteLevelProgress.setValue(Integer.parseInt(level));
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }

    public static void main(String[] args) {
        SmartWasteDisposalGUI gui = new SmartWasteDisposalGUI();
        gui.startSerialCommunication();
    }
}
