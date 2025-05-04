import java.util.*;

class Futebol extends Desporto {
    private ArrayList<String> opcoesCamisolas;
    private ArrayList<String> opcoesJogadores;
    private int pontuacao;

    Futebol(){
        super();
    }

    Futebol(String pergunta, ArrayList<String> opcoesJogadores, ArrayList<String> opcoesCamisolas, String solucaoJogadores, String solucaoCamisolas){
        super(pergunta, opcoesJogadores, opcoesCamisolas, solucaoJogadores, solucaoCamisolas);
    }
    
    public Pergunta lePergunta(String[] partes){
        opcoesCamisolas = new ArrayList<String>();
        opcoesJogadores = new ArrayList<String>();
        String[] jogadores = partes[2].split(",");
        String[] camisolas = partes[4].split(",");
        for (int i=0;i<jogadores.length;i++){
            opcoesJogadores.add(jogadores[i]);
        }
        for (int i=0;i<camisolas.length;i++){
            opcoesCamisolas.add(camisolas[i]);
        }
        Futebol pergunta = new Futebol(partes[1], opcoesJogadores, opcoesCamisolas, partes[3], partes[5]);
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
        if (count < 3) return getOpcoes1();
        else return getOpcoes2();
    }

    public int calculaPontuacao(){
        return getPontuacao() + 3 + 1;
    }
}
