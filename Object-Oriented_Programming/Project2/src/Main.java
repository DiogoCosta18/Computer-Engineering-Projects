import java.time.LocalDateTime;
import java.util.*;


public class Main {
    private ArrayList<Pergunta> perguntasCertas;
    private ArrayList<Pergunta> perguntasErradas;
    private LocalDateTime dataHora;
    private ArrayList<Pergunta> listaPerguntas;
    private ArrayList<Pergunta> perguntasSelecionadas;
    private Jogador jogador;
    private int pontuacao;

    public void jogar(int numero_perguntas) {
        perguntasCertas = new ArrayList<>();
        perguntasErradas = new ArrayList<>();
        perguntasSelecionadas = new ArrayList<>();
        Random random = new Random();
        for(int i=0; i<numero_perguntas;i++){
            //
            int indice;
            do{
                indice = random.nextInt(listaPerguntas.size());
            }
            while (perguntasSelecionadas.contains(listaPerguntas.get(indice)));
            perguntasSelecionadas.add(listaPerguntas.get(indice));
        }
    }

    public ArrayList<Pergunta> getPerguntasSelecionadas(){
        return perguntasSelecionadas;
    }

    public ArrayList<Pergunta> getListaPerguntas(){
        return listaPerguntas;
    }
    public ArrayList<Pergunta> getPerguntasCertas(){
        return perguntasCertas;
    }
    public ArrayList<Pergunta> getPerguntasErradas(){
        return perguntasErradas;
    }

    public void setListaPerguntas(ArrayList<Pergunta> listaPerguntas){
        this.listaPerguntas = listaPerguntas;
    }

    public String responderPergunta(Pergunta pergunta, String opcao){        
        Boolean respostaCerta = pergunta.verificarResposta(opcao);
        String acertou="";
        if (respostaCerta) {
            acertou+="Resposta correta!";
            perguntasCertas.add(pergunta);
        } else {
            acertou+="Resposta incorreta!";
            perguntasErradas.add(pergunta);
        }
        return acertou;
    }

    public int calculaPontuacao(){
        pontuacao = 0;
        for (Pergunta pergunta : perguntasCertas){
            pontuacao += pergunta.calculaPontuacao();
        }
        return pontuacao;
    }

    public void mostrarTop3() {
        
    }

    public static void main(String args[]){
        GUI jogoGUI = new GUI();
    }
}
