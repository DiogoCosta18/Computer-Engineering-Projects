import java.util.ArrayList;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.io.Serializable;

public class Jogo implements Serializable{
    private Jogador jogador;
    private LocalDateTime dataHora;
    private int pontuacao;
    private ArrayList<Pergunta> perguntasCertas;
    private ArrayList<Pergunta> perguntasErradas;

    public Jogo(Jogador jogador, LocalDateTime dataHora, int pontuacao, ArrayList<Pergunta> perguntasCertas, ArrayList<Pergunta> perguntasErradas) {
        this.jogador = jogador;
        this.dataHora = dataHora;
        this.pontuacao = pontuacao;
        this.perguntasCertas = perguntasCertas;
        this.perguntasErradas = perguntasErradas;
    }

    public LocalDateTime getDataHora() {
        return dataHora;
    }

    public String getDataHoraFormatada() {
        DateTimeFormatter formato = DateTimeFormatter.ofPattern("yyyyMMddHHmm");
        String dataHoraFormatada = dataHora.format(formato);
        return dataHoraFormatada;
    }

    public Jogador getJogador() {
        return jogador;
    }

    public String getJogadorFormatada() {
        return jogador.getNomeFormatado();
    }

    public ArrayList<Pergunta> getPerguntasCertas() {
        return perguntasCertas;
    }
    
    public ArrayList<Pergunta> getPerguntasErradas() {
        return perguntasErradas;
    }

    public int getPontuacao() {
        return pontuacao;
    }
}
