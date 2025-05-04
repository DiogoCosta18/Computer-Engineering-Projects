import java.util.ArrayList;
import java.util.List;

public abstract class Desporto extends Pergunta {
    private int pontuacao;
    private ArrayList<String> opcoes;
    private List<String> opcoesCamisolas;
    private List<String> opcoesJogadores;
    String solucao;

    Desporto(){
        super();
    }

    Desporto(String pergunta, ArrayList<String> opcoesJogadores, ArrayList<String> opcoesCamisolas, String solucaoJogadores, String solucaoCamisolas){
        super(pergunta, opcoesJogadores, opcoesCamisolas, solucaoJogadores, solucaoCamisolas);
    }

    Desporto(String pergunta, ArrayList<String> opcoes, String solucao){
        super(pergunta, opcoes, solucao);
    }
}
