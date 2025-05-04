import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class Artes extends Pergunta{
    private ArrayList<String> opcoesFaceis;
    private ArrayList<String> opcoesDificeis;

    Artes(){
        super();
    }

    Artes(String pergunta, ArrayList<String> opcoesFaceis, ArrayList<String> opcoesDificeis, String solucao){
        super(pergunta, opcoesFaceis, opcoesDificeis, solucao);
    }

    public Pergunta lePergunta(String[] partes){
        opcoesFaceis = new ArrayList<String>();
        opcoesDificeis = new ArrayList<String>();
        Random random = new Random(); // ao ler do fiheiro e feita logo uma divisao das ocpcoes, ficam logo definidas aas opcoes faceis e as dificeis
        String[] partesOpcoes = partes[2].split(",");
        int escolheOpcao = random.nextInt(partesOpcoes.length-1);
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
        String aux = getPergunta()+ "\n";
        for(int i=0; i < getOpcoes1().size();i++){
            aux += getOpcoes1().get(i) + "\n";
        }
        return aux;
    }

    public ArrayList<String> escolheOpcoes(int count){
        if (count < 3) return getOpcoes1();
        else return getOpcoes2();
    }

    public int calculaPontuacao(){
        return getPontuacao() * 10;
    }
}

