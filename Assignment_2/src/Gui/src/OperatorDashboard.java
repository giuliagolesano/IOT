package src;

import javax.swing.*;
import java.awt.*;

public class OperatorDashboard {

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
    public OperatorDashboard() {
        frame = new JFrame("Smart Waste Disposal System");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);
        frame.setResizable(false); // Impostare la finestra come non ridimensionabile

        // Impostare sfondo giallo pastello
        frame.getContentPane().setBackground(new Color(255, 248, 198));  // Colore giallo pastello

        // Pannello superiore con i pulsanti
        JPanel topPanel = new JPanel();
        topPanel.setLayout(new FlowLayout());
        topPanel.setBackground(new Color(204, 255, 204)); // Colore verde chiaro pastello
        btnEmpty = new JButton("Empty");
        btnRestore = new JButton("Restore");

        // Pulsanti con sfondo rosso pastello
        btnEmpty.setBackground(new Color(255, 204, 204));  // Colore rosso pastello
        btnRestore.setBackground(new Color(255, 204, 204));  // Colore rosso pastello

        // Aggiungere i pulsanti al pannello
        topPanel.add(btnEmpty);
        topPanel.add(btnRestore);

        // Aggiungere il pannello superiore alla finestra
        frame.add(topPanel, BorderLayout.NORTH);

        // Pannello principale
        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new GridLayout(1, 2));

        // Pannello sinistro per la temperatura
        JPanel leftPanel = new JPanel();
        leftPanel.setLayout(new BorderLayout());
        leftPanel.setBackground(new Color(255, 248, 198));  // Giallo pastello
        tempLabel = new JLabel("Temperature reached:");
        tempValueLabel = new JLabel("0.00 °C");

        // Caricare l'immagine PNG
        gifLabel = new JLabel(new ImageIcon("temp.png"));
        gifLabel.setOpaque(true);
        gifLabel.setBackground(new Color(255, 248, 198));  // Giallo pastello

        leftPanel.add(tempLabel, BorderLayout.NORTH);
        leftPanel.add(tempValueLabel, BorderLayout.CENTER);
        leftPanel.add(gifLabel, BorderLayout.SOUTH);

        // Pannello destro per il livello del rifiuto
        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BorderLayout());
        rightPanel.setBackground(new Color(255, 248, 198));  // Giallo pastello
        wasteLevelLabel = new JLabel("Waste Level: ");
        wasteLevelProgress = new JProgressBar(0, 100);
        wasteLevelProgress.setValue(0);
        wasteLevelProgress.setStringPainted(true);

        wasteImageLabel = new JLabel(new ImageIcon("liquid.png"));
        wasteImageLabel.setOpaque(true);
        wasteImageLabel.setBackground(new Color(255, 248, 198));  // Giallo pastello

        rightPanel.add(wasteLevelLabel, BorderLayout.NORTH);
        rightPanel.add(wasteLevelProgress, BorderLayout.CENTER);
        rightPanel.add(wasteImageLabel, BorderLayout.SOUTH);

        // Aggiungere i pannelli sinistro e destro al pannello principale
        mainPanel.add(leftPanel);
        mainPanel.add(rightPanel);

        // Aggiungere il pannello principale alla finestra
        frame.add(mainPanel, BorderLayout.CENTER);

        frame.setVisible(true);
    }

    // Metodo main per avviare l'interfaccia
    public static void main(String[] args) {
        new OperatorDashboard();
    }
}
