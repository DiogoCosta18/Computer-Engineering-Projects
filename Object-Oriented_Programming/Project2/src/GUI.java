import javax.swing.*;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyledDocument;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class GUI extends JFrame {
    private JLabel perguntas;
    private JLabel respostas;
    private JTextPane top3; 
    public Main jogo;
    private JPanel buttonPanel;
    private JButton proximaPerguntaButton;
    private JButton newGame;
    private ArrayList<Pergunta> listaPerguntasSelecionadas;
    private int count;

    public GUI() {
        jogo = new Main();
        Arquivo arquivo = new Arquivo();
        jogo.setListaPerguntas(arquivo.lerPerguntas("C:/Users/diogo/OneDrive/Documentos/Ficheiros/DEI/2_ANO/POO/Projeto2/Projeto-2/Projeto/src/Perguntas.txt"));
        for (int i=0; i<jogo.getListaPerguntas().size(); i++){
            System.out.println(jogo.getListaPerguntas().get(i).toString());
        }
        
        setTitle("POO Trivia");
        setSize(1600, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());

        JPanel perguntasPanel = new JPanel();
        perguntasPanel.setLayout(new BorderLayout());
        perguntas = new JLabel();
        perguntas.setFont(new Font("Times New Roman", Font.BOLD, 26));
        perguntas.setHorizontalAlignment(JLabel.CENTER);
        perguntas.setVerticalAlignment(JLabel.CENTER);

        respostas = new JLabel();
        respostas.setFont(new Font("Times New Roman", Font.BOLD, 26));
        respostas.setVerticalAlignment(JLabel.CENTER);
        respostas.setHorizontalAlignment(JLabel.CENTER);

        JPanel top3Panel = new JPanel();
        top3Panel.setLayout(new BorderLayout());
        top3 = new JTextPane();
        StyledDocument doc = top3.getStyledDocument();
        SimpleAttributeSet center = new SimpleAttributeSet();
        StyleConstants.setAlignment(center, StyleConstants.ALIGN_CENTER);
        doc.setParagraphAttributes(0, doc.getLength(), center, false);
        top3.setFont(new Font("Times New Roman", Font.BOLD, 26));
        top3.setEditable(false);

        buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());

        top3.setText(arquivo.top3toString());

        newGame = new JButton("Start a new Game");
        newGame.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                top3Panel.removeAll();
                inicioJogo();
            }
        });
        buttonPanel.add(newGame);

        proximaPerguntaButton = new JButton("Próxima Pergunta");
        proximaPerguntaButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                apresentarProximaPergunta();
            }
        });
        proximaPerguntaButton.setVisible(false);
        buttonPanel.add(proximaPerguntaButton);

        top3Panel.add(top3);
        perguntasPanel.add(perguntas,BorderLayout.CENTER);
        perguntasPanel.add(respostas,BorderLayout.SOUTH);
        mainPanel.add(top3Panel, BorderLayout.NORTH);
        mainPanel.add(perguntasPanel, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);
        setContentPane(mainPanel);
        setVisible(true);
    }

        private void adicionarBotoesPergunta(Pergunta pergunta) {
            ArrayList<String> opcoes = pergunta.escolheOpcoes(count);
            count++;
            JPanel opcoesPanel = new JPanel();
            opcoesPanel.setLayout(new GridLayout(1, 0));
            buttonPanel.removeAll();
            for (String opcao : opcoes) {
                JButton opcaoButton = new JButton(opcao);
                buttonPanel.add(proximaPerguntaButton);
                opcaoButton.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        respostas.setText(jogo.responderPergunta(pergunta,opcao));
                        perguntas.setText("");
                        opcoesPanel.removeAll();
                        proximaPerguntaButton.setVisible(true);
                        if(listaPerguntasSelecionadas.isEmpty()) {
                            apresentaPontuacao();
                            opcoesPanel.removeAll();
                            buttonPanel.add(newGame);
                            proximaPerguntaButton.setVisible(false);
                            count = 0;
                        }
                    }
                });
                opcoesPanel.add(opcaoButton);               
            }
            buttonPanel.add(opcoesPanel);
            buttonPanel.revalidate();
            buttonPanel.repaint();
        }

        private void inicioJogo(){
            jogo.jogar(5);
            apresentarProximaPergunta();
        }

        private void apresentarProximaPergunta(){
            listaPerguntasSelecionadas = jogo.getPerguntasSelecionadas();
            if(!listaPerguntasSelecionadas.isEmpty()) {               
                Pergunta perguntaAtual = listaPerguntasSelecionadas.remove(0);
                perguntas.setText(perguntaAtual.getPergunta());
                respostas.setText("");
                adicionarBotoesPergunta(perguntaAtual);
                proximaPerguntaButton.setVisible(false);
            }
        }

        private void apresentaPontuacao() {
            int pontuacao = jogo.calculaPontuacao();
            PontuacaoGUI pontuacaoJanela = new PontuacaoGUI(pontuacao, jogo.getPerguntasCertas(), jogo.getPerguntasErradas());
        }

}