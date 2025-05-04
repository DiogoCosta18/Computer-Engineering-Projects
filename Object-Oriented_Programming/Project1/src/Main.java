import java.time.LocalDateTime;
import java.util.*;

import javax.print.DocFlavor.STRING;

public class Main {
    private List<Pergunta> perguntasRespondidas;
    private List<Pergunta> perguntasErradas;
    private LocalDateTime dataHora;
    
    private Jogador jogador;
    private int pontuacao;

    public void jogar() {
        
    }

    public void mostrarTop3() {
        
    }

    public static void main(String args[]){
        List<Pergunta> perguntas= new ArrayList<>();
        Arquivo arquivo = new Arquivo();
        perguntas = arquivo.lerPerguntas("C://Users//diogo//OneDrive//Documentos//Ficheiros//DEI//2_ANO//POO//Projeto//Projeto//src//Perguntas.txt");
        for (int i=0; i<perguntas.size(); i++){
            System.out.println(perguntas.get(i).toString());
        }
        
        
    }
}
