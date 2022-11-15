import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Graphics;

public class Screen extends JPanel {
    public Dimension getPreferredSize() {
        return new Dimension(800, 600);
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
    }
}
