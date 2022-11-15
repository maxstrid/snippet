import javax.swing.JFrame;

public class Runner {
  public static void main(String[] args) {
    JFrame fr = new JFrame("Screen");
    Screen s = new Screen();
    fr.add(s);
    fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    fr.pack();
    fr.setVisible(true);
  }
}
