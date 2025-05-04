import java.util.*;
import java.util.ArrayList;

public class Ski extends Desporto {
    private int pontuacao;
    private ArrayList<String> opcoes;

    Ski(){
        super();
    }

    Ski(String pergunta, ArrayList<String> opcoes, String solucao){
        super(pergunta, opcoes, solucao);
    }
    
    public Pergunta lePergunta(String[] partes){
        opcoes = new ArrayList<String>();
        String[] opcoesVF = partes[2].split(",");
        for (int i=0;i<opcoesVF.length;i++){
            opcoes.add(opcoesVF[i]);
        }
        Ski pergunta = new Ski(partes[1], opcoes, partes[3]);
        return pergunta;
    }

    public String toString(){
        String aux = getPergunta()+ "\n";
        for(int i=0; i < getOpcoes1().size();i++){
            aux+= getOpcoes1().get(i) + "\n";
        }
        return aux;
    }

    public ArrayList<String> escolheOpcoes(int count){
        return getOpcoes1();
    }
    
    public int calculaPontuacao(){
        return (getPontuacao() + 3) * 2;
    }
}
