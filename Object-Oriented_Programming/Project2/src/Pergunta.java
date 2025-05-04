import java.io.Serializable;
import java.util.*;

public abstract class Pergunta implements Serializable{
    private String pergunta;
    private ArrayList<String> opcoes1;
    private ArrayList<String> opcoes2;
    private String resposta;
    private String resposta2;
    private int pontuacao;

    Pergunta(){}

    Pergunta(String pergunta, ArrayList<String> opcoes, String solucao) {
        this.pergunta = pergunta;
        this.opcoes1 = opcoes;
        this.resposta = solucao;
        this.pontuacao = 5;
    }
    Pergunta(String pergunta, ArrayList<String> opcoes1, ArrayList<String> opcoes2,String solucao) {
        this.pergunta = pergunta;
        this.opcoes1 = opcoes1;
        this.opcoes2 = opcoes2;
        this.resposta= solucao;
        this.pontuacao = 5;
    }

    Pergunta(String pergunta, ArrayList<String> opcoes1, ArrayList<String> opcoes2, String solucaoJogadores, String solucaoCamisolas){
        this.pergunta = pergunta;
        this.opcoes1 = opcoes1;
        this.opcoes2 = opcoes2;
        this.resposta = solucaoJogadores;
        this.resposta2 = solucaoCamisolas;
        this.pontuacao = 5;
    }
    
    public String getResposta(){
        return resposta;
    }
    
    public String getPergunta(){
        return pergunta;
    }

    public ArrayList<String> getOpcoes1() {
        return opcoes1;
    }
    
    public ArrayList<String> getOpcoes2(){
        return opcoes2;
    }
    
    public int getPontuacao(){
        return pontuacao;
    }

    public boolean verificarResposta(String escolha) {
        return escolha.equals(getResposta());
    }

    public abstract int calculaPontuacao();

    public abstract Pergunta lePergunta(String[] partes);

    public abstract String toString();

    public abstract ArrayList<String> escolheOpcoes(int count);

}
