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
        frame = new JFrame("Smart Waste Disposal System");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);

        JPanel topPanel = new JPanel();
        topPanel.setLayout(new FlowLayout());
        btnEmpty = new JButton("Empty");
        btnRestore = new JButton("Restore");
        topPanel.add(btnEmpty);
        topPanel.add(btnRestore);

        frame.add(topPanel, BorderLayout.NORTH);
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new GridLayout(1, 2));

        JPanel leftPanel = new JPanel();
        leftPanel.setLayout(new BorderLayout());
        tempLabel = new JLabel("Temperature reached by hazardous waste:");
        tempValueLabel = new JLabel("0.00 °C");
        gifLabel = new JLabel(new ImageIcon(""));
        leftPanel.add(tempLabel, BorderLayout.NORTH);
        leftPanel.add(tempValueLabel, BorderLayout.CENTER);
        leftPanel.add(gifLabel, BorderLayout.SOUTH);

        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BorderLayout());
        wasteLevelLabel = new JLabel("Waste Level: 0%");
        wasteLevelProgress = new JProgressBar(0, 100);
        wasteLevelProgress.setValue(0);
        wasteLevelProgress.setStringPainted(true);
        wasteImageLabel = new JLabel(new ImageIcon(""));
        rightPanel.add(wasteLevelLabel, BorderLayout.NORTH);
        rightPanel.add(wasteLevelProgress, BorderLayout.CENTER);
        rightPanel.add(wasteImageLabel, BorderLayout.SOUTH);

        mainPanel.add(leftPanel);
        mainPanel.add(rightPanel);
        frame.add(mainPanel, BorderLayout.CENTER);

        frame.setVisible(true);
    }


    public static void main(String[] args) {
        SmartWasteDisposalGUI gui = new SmartWasteDisposalGUI();

    }
}
