import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class Ciencias extends Pergunta {
    private ArrayList<String> opcoesFaceis = new ArrayList<String>();
    private ArrayList<String> opcoesDificeis = new ArrayList<String>();
    String solucao;
    
    Ciencias(){
        super();
    }

    Ciencias(String pergunta, ArrayList<String> opcoesFaceis, ArrayList<String> opcoesDificeis, String solucao){
        super(pergunta, opcoesFaceis, opcoesDificeis, solucao);
    }

    /*private Pergunta generateRandomPerguntaCiencias(){
        Random random = new Random();
        int escolheOpcao = nextInt(2);
        if (escolheOpcao == 0) {
            ArrayList<String> opcao = opcoesFaceis;
        } else if (escolheOpcao==1){
            ArrayList<String> opcao = opcoesDificeis;
        }
        Pergunta pergunta = new Ciencias(pergunta,opcao);
        return pergunta;
    }*/

    public Pergunta lePergunta(String[] partes){
        String[] partesOpcoes = partes[2].split(",");
        for (int i=0;i<partesOpcoes.length;i++){
            opcoesFaceis.add(partesOpcoes[i]);
        }
        partesOpcoes = partes[3].split(",");
        for (int i=0;i<partesOpcoes.length;i++){
            opcoesDificeis.add(partesOpcoes[i]);
        }
        //System.out.println(opcoesFaceis);
        //System.out.println(opcoesDificeis);
        Ciencias pergunta = new Ciencias(partes[1], opcoesFaceis, opcoesDificeis, partes[4]);
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
