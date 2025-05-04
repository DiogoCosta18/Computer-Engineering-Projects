import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;



public class Arquivo {
    Arquivo(){}
    public ArrayList<Pergunta> lerPerguntas(String arquivo) {
        // ler do ficheiro
        ArrayList<Pergunta> perguntas = new ArrayList<>();
        try{
            File f= new File(arquivo);
            FileReader fr = new FileReader(f);
            BufferedReader br= new BufferedReader(fr);

            String linha;
            while ((linha = br.readLine()) != null) {
                String[] partes = linha.split(";");
                

                String tipo = partes[0];
                switch (tipo) {
                    case "Artes":
                        perguntas.add(new Artes().lePergunta(partes));
                        break;
                    case "Futebol":
                        perguntas.add(new Futebol().lePergunta(partes));
                        break;
                    case "Ski":
                        perguntas.add(new Ski().lePergunta(partes));
                        break;
                    case "Natacao":
                        perguntas.add(new Natacao().lePergunta(partes));
                        break;
                    case "Ciencias":
                        perguntas.add(new Ciencias().lePergunta(partes));
                        break;
                    default:
                        System.out.println("Tipo de pergunta desconhecido: " + tipo);  
                }
                //System.out.println(pergunta.toString());
            }
        br.close();
        }catch(FileNotFoundException e){
            System.out.println("Ficheiro nao encontrado");
        }catch(IOException e){
            System.out.println("Erro ao ler o ficheiro");
        }
        return perguntas;
    }

    private ArrayList<Jogo> carregarJogo() {
        File diretorio = new File("C:/Users/diogo/OneDrive/Documentos/Ficheiros/DEI/2_ANO/POO/Projeto2/Projeto-2/Projeto");
        File[] ficheiros = diretorio.listFiles((diretorioAtual, nome) -> nome.endsWith(".dat"));
        ArrayList<Jogo> jogo = new ArrayList<Jogo>();
        if (ficheiros != null) {
            for (File ficheiro : ficheiros) {
                try {
                    FileInputStream fileIn = new FileInputStream(ficheiro);
                    ObjectInputStream jogoInput = new ObjectInputStream(fileIn);
                    jogo.add((Jogo)jogoInput.readObject());
                    jogoInput.close();
                    fileIn.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
        return jogo;
    }

    private ArrayList<Jogo> calculaTop3(){
        ArrayList<Jogo> jogos = carregarJogo();
        ArrayList<Integer> pontuacao = new ArrayList<Integer>();
        for (int i = 0; i <jogos.size(); i++){
            int pontos = 0;
            ArrayList<Pergunta> perguntas = jogos.get(i).getPerguntasCertas();
            for (Pergunta pergunta : perguntas) {
                pontos += pergunta.calculaPontuacao();
            }
            pontuacao.add(pontos);
        }
        ArrayList<Jogo> top3 = new ArrayList<Jogo>();
        int aux = jogos.size();
        for (int j = 0; j < Math.min(3, aux); j++) {
            int maior = 0;
            int indice = 0;
            for (int i = 0; i < pontuacao.size(); i++) {
                if (pontuacao.get(i) >= maior) {
                    maior = pontuacao.get(i);
                    indice = i;
                }
            }
            top3.add(jogos.get(indice));
            pontuacao.remove(indice);
            jogos.remove(indice);
        }
        return top3;
    }

    public ArrayList<Jogo> top3(){
        return calculaTop3();
    }

    public String top3toString() {
        String string = "";
        ArrayList<Jogo> top3 = calculaTop3();
        System.err.println(top3.size());
        for (int j = 0; j < Math.min(3, top3.size()); j++) {
            string += (j+1) + "º Lugar: " + top3.get(j).getJogador().getNome() + "  : " + top3.get(j).getPontuacao() + "\n\n";
        }
        return string;
    }

    private void salvarJogo(Jogo guardaJogo){
        try {
            FileOutputStream ficheiro = new FileOutputStream("pootrivia_jogo_" + guardaJogo.getDataHoraFormatada() + "_" + guardaJogo.getJogadorFormatada() + ".dat");
            ObjectOutputStream objeto = new ObjectOutputStream(ficheiro);
            objeto.writeObject(guardaJogo);
            objeto.close();
            ficheiro.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void escreverFicheiro(Jogo guardaJogo){
        salvarJogo(guardaJogo);
    }
}

