import java.util.*;

public class Futebol extends Desporto {
    private List<String> jogadores;
    private List<String> camisolas;
    private int pontuacao;

    Futebol(){
        super();
    }
    
    public Pergunta lePergunta(String[] partes){
        Pergunta pergunta = new Ciencias(partes[1], partes[2], partes[3], partes[4]);
        return pergunta;
    }
}
