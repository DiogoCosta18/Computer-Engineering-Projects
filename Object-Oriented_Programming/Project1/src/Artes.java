import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class Artes extends Pergunta{
    private ArrayList<String> opcoesFaceis = new ArrayList<String>();
    private ArrayList<String> opcoesDificeis = new ArrayList<String>();

    Artes(){
        super();
    }

    Artes(String pergunta, ArrayList<String> opcoesFaceis, ArrayList<String> opcoesDificeis, String solucao){
        super(pergunta, opcoesFaceis, opcoesDificeis, solucao);
    }

    public Pergunta lePergunta(String[] partes){
        Random random = new Random();
        int escolheOpcao = random.nextInt(3);
        String[] partesOpcoes = partes[2].split(",");
        for (int i = escolheOpcao; i < escolheOpcao + 2; i++){
            opcoesFaceis.add(partesOpcoes[i]);
        }
        opcoesFaceis.add(partes[3]);
        for (int i = 0; i < partesOpcoes.length; i++){
            opcoesDificeis.add(partesOpcoes[i]);
        }
        opcoesDificeis.add(partes[3]);
        
        Artes pergunta = new Artes(partes[1], opcoesFaceis, opcoesDificeis, partes[3]);
        return pergunta;
    }

    public String toString(){
        String aux = getPergunta();
        for(int i=0; i < getOpcoes1().size();i++){
            aux+= "\n" + getOpcoes1().get(i);
        }
        return aux;
    }

}

