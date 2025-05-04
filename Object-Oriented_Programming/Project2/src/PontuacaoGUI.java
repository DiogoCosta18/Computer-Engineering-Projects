import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;

public class PontuacaoGUI extends JFrame {
    private JLabel pontuacaoLabel;
    private JTextField textBox;
    

    public PontuacaoGUI(int pontuacao, ArrayList<Pergunta> PerguntasCertas,ArrayList<Pergunta> PerguntasErradas) {
        setTitle("Pontuação");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JPanel panel = new JPanel();
        
        JLabel label = new JLabel("Nome");

        textBox = new JTextField(10);
        textBox.setHorizontalAlignment(JTextField.CENTER);

        JButton submit = new JButton("Submeter");
        submit.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                LocalDateTime dataHora = LocalDateTime.now();
                Jogador jogador = new Jogador(textBox.getText());
                Jogo guardaJogo = new Jogo(jogador, dataHora, pontuacao, PerguntasCertas, PerguntasErradas);
                Arquivo arquivoSalvarJogo = new Arquivo();
                arquivoSalvarJogo.escreverFicheiro(guardaJogo);
                PontuacaoGUI.this.dispose();
            }
        });
        panel.add(label);
        panel.add(textBox); 
        panel.add(submit);
        
        pontuacaoLabel = new JLabel("Sua Pontuação: " + pontuacao);
        pontuacaoLabel.setHorizontalAlignment(JLabel.CENTER);
        pontuacaoLabel.setFont(new Font("Bauhaus 93", Font.BOLD, 60));

        add(pontuacaoLabel, BorderLayout.CENTER);
        add(panel, BorderLayout.SOUTH);
        setLocationRelativeTo(null);  
        setVisible(true);
    }
}


