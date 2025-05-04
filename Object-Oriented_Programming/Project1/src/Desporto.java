import java.util.ArrayList;
import java.util.List;

public abstract class Desporto extends Pergunta {
    private int pontuacao;
    ArrayList<String> opcoes;
    private List<String> opcoesCamisolas;
    private List<String> opcoesJogadores;
    String solucao;

    Desporto(){
        super();
    }

    Desporto(String pergunta, ArrayList<String> opcoesJogadores, ArrayList<String> opcoesCamisolas, String solucao){
        super(pergunta, opcoesJogadores, opcoesCamisolas, solucao);
    }

    Desporto(String pergunta, ArrayList<String> opcoes, String solucao){
        super(pergunta, opcoes, solucao);
    }

    public abstract Pergunta lePergunta(String[] partes);
}
